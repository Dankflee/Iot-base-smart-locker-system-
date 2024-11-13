# Locker Access Control System with RFID, Keypad, and Ultrasonic Sensor

This project is an Arduino-based locker access control system using RFID, a keypad, and an ultrasonic sensor. The system grants access to the locker based on a valid RFID card/tag or correct passkey entered via a keypad. It also uses an ultrasonic sensor to measure distance, with an added buzzer feature for security.

## Components

- **Arduino Uno**
- **MFRC522 RFID Module**
- **4x4 Keypad**
- **Ultrasonic Distance Sensor (HC-SR04)**
- **BO Motor**
- **Buzzer**
- **Jumper Wires**
- **Breadboard (Optional)**

## Pin Connections

- **Buzzer**: Pin 7
- **Ultrasonic Sensor**:
  - TRIG Pin: Pin 4
  - ECHO Pin: Pin 5
- **RFID**:
  - SS Pin: Pin 10
  - RST Pin: Pin 9
- **Motor**: Pin 6
- **Keypad**:
  - Rows: A0, A1, A2, A3
  - Columns: A4, A5, 2, 3

## Libraries Required

- **SPI**: For communication with the RFID module.
- **MFRC522**: For reading RFID cards/tags.
- **Keypad**: For interfacing with the 4x4 keypad.

## Features

- **RFID-based Access**: Access is granted if the scanned RFID card's UID matches the predefined valid UID.
- **Keypad-based Access**: Access is granted by entering a passkey on the keypad. The correct passkey is "1234".
- **Ultrasonic Sensor**: If the distance measured by the ultrasonic sensor exceeds 8 cm, a buzzer will sound for security.
- **Motor Control**: If access is granted, the motor is activated for 5 seconds to open the locker door.
- **Buzzer**: The buzzer will sound for 1 second if access is denied or if the distance exceeds 8 cm.

## Setup and Installation

1. **Install Arduino IDE**: Download and install the Arduino IDE from the official website.
2. **Install Libraries**: Open the Arduino IDE and go to `Sketch > Include Library > Manage Libraries`. Search for and install:
   - MFRC522
   - Keypad
3. **Connect the Components**: 
   - Connect the RFID module, keypad, ultrasonic sensor, motor, and buzzer to the Arduino Uno as per the pin configuration mentioned above.
4. **Upload the Code**: Open the code provided in the `.ino` file and upload it to your Arduino board.
5. **Test the System**: Place an RFID card near the reader or enter the passkey on the keypad to test the system. The motor should activate and the buzzer should sound based on the input.

## Code Explanation

- **RFID Module**: The system checks for a new RFID card and reads the UID. If the UID matches the predefined valid UID, the motor is activated to open the locker door.
- **Keypad**: If a key is pressed on the keypad, the system compares the entered passkey with the predefined correct passkey. If it matches, the motor is activated.
- **Ultrasonic Sensor**: The sensor measures the distance and triggers the buzzer if the distance exceeds 8 cm, adding an extra layer of security.

## Security Note

Make sure to replace the `targetUID` with your own valid RFID UID, and modify the `correctPasskey` for a more secure passcode.

## Troubleshooting

- **RFID Not Working**: Ensure that the RFID module is connected correctly and that the UID of the card/tag is correctly set in the code.
- **Keypad Not Responding**: Check the wiring of the keypad and ensure the row and column pins are correctly connected.
- **Motor Not Working**: Verify the motor wiring and ensure it is compatible with the Arduino’s output pins.

## License

This project is open source. Feel free to modify and use the code for your own projects.

