#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>

// Pin definitions
#define BUZZER_PIN 7          // Buzzer connected to pin 7
#define TRIG_PIN 4            // Ultrasonic sensor TRIG pin connected to pin 4
#define ECHO_PIN 5            // Ultrasonic sensor ECHO pin connected to pin 5
#define SS_PIN 10             // RFID SS (SDA) pin
#define RST_PIN 9             // RFID RST pin
#define MOTOR_PIN 6           // Motor connected to pin 6

// RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {A4, A5, 2, 3};   // Connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables
String enteredPasskey = "";
const String correctPasskey = "1234";
const String targetUID = "A9 73 33 02";   // Replace with your valid RFID UID (no spaces)
bool lockerOpened = false;

void setup() {
  Serial.begin(9600);
  
  // Initialize RFID
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Place your RFID card/tag near the reader...");
  // Initialize pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  
  digitalWrite(MOTOR_PIN, LOW);  // Ensure motor is off initially
}

void loop() {
  // Check ultrasonic sensor
  long distance = measureDistance();
  
  // If distance is more than 8 cm, sound the buzzer
  if (distance > 8) {
    soundBuzzer();
  }

  // Check keypad
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      if (enteredPasskey == correctPasskey) {
        grantAccess();
      } else {
        denyAccess();
      }
      enteredPasskey = "";
    } else {
      enteredPasskey += key;
    }
  }
  
  // Check RFID
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;  // No new card found, exit loop
  }

  // Display UID
  Serial.print("UID: ");
  String uidString = ""; // Variable to hold the UID as a string
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    // Convert UID byte to uppercase hex format manually
    String uidByteHex = String(mfrc522.uid.uidByte[i], HEX); // Convert to hex
    uidByteHex.toUpperCase(); // Convert to uppercase
    
    // Pad the UID byte to ensure it has two digits
    if (uidByteHex.length() < 2) {
      uidByteHex = "0" + uidByteHex; // Pad single digit with a leading zero
    }
    
    // Append the UID byte to the UID string
    uidString += uidByteHex; 
    if (i < mfrc522.uid.size - 1) {
      uidString += " "; // Add space between bytes
    }
    
    Serial.print(uidByteHex); // Print each byte
    Serial.print(" ");
  }
  Serial.println(); // Print new line for next reading

  // Compare the UID string with the target UID
  if (uidString.equalsIgnoreCase(targetUID)) {
    Serial.println("Match found: true");
    grantAccess();
  } else {
    Serial.println("Match found: false");
    denyAccess();
  }

  // Halt the card and stop communication
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}







// Measure distance using ultrasonic sensor
long measureDistance() {
  // Send a 10µs pulse to the TRIG pin to start measurement
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the length of the ECHO pulse
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in centimeters
  long distance = duration * 0.034 / 2; // Speed of sound: 343 m/s
  
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");
  
  return distance;
}

// Grant access and open the door
void grantAccess() {
  lockerOpened = true;
  Serial.println("Access granted");
  
  // Run motor to open the locker (for 5 seconds)
  digitalWrite(MOTOR_PIN, HIGH);  // Start motor
  delay(5000);  // Run motor for 5 seconds
  digitalWrite(MOTOR_PIN, LOW);   // Stop motor
}

// Deny access and sound buzzer
void denyAccess() {
  soundBuzzer();
  Serial.println("Access denied");
}

// Sound buzzer for a second
void soundBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}