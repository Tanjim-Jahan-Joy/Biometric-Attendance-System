# Biometric Attendance System (BAS)

## Overview
The Biometric Attendance System (BAS) is an embedded IoT-based solution designed to automate attendance tracking using fingerprint recognition. The system improves reliability by eliminating proxy attendance and ensuring accurate data collection.

It integrates hardware and software components to capture fingerprint data, verify users, and store attendance records in a centralized database. The system is designed with scalability, low cost, and real-world deployment in mind.

---

## Key Features
- Fingerprint-based user authentication  
- Real-time data transmission over Wi-Fi  
- Centralized database integration (MySQL)  
- SMS notification support (GSM or SMS gateway)  
- OLED display for system feedback  
- Keypad-based user input interface  
- Structured attendance logging  
- Scalable multi-device support  

---

## System Architecture
Follow the instruction for setuping the Biometric Attendance System project

---

## Hardware Components
- ESP32 microcontroller  
- Fingerprint sensor (R305 / R307)  
- OLED display (I2C)  
- 4x4 matrix keypad  
- GSM module (SIM900A) or SMS gateway  
- Power supply unit  

---

## Software and Technologies
- Embedded C (Arduino framework)  
- ESP32 Wi-Fi libraries  
- PHP backend  
- MySQL database  
- JSON-based communication  
- HTML, CSS, JavaScript (web interface)  

---

## Database Structure

### Students Table

| Field     | Description                      |
|-----------|----------------------------------|
| deviceID  | Device identifier                |
| serialNum | Fingerprint storage position     |
| ID        | Unique user ID                   |
| class     | Class number                     |
| section   | Section name                     |
| roll      | Roll number                      |
| enrolled  | Enrollment status (true/false)   |

### Class Tables (class1, class2, ...)
Stores detailed information such as name and contact details.

---

## System Workflow

### Enrollment
1. User enters ID using keypad  
2. Fingerprint is captured and stored  
3. Data is sent to the server  
4. Database is updated  
5. Optional SMS confirmation is sent  

### Attendance
1. User scans fingerprint  
2. Identity is verified  
3. Attendance is recorded  
4. Data is sent to the server  

### Deletion
Requires matching:
- ID  
- Device ID  
- Serial Number  

---

## Communication Format

### Request (ESP32 → Server)
```json
{
  "id": "12345",
  "action": "enroll"
}

{
  "status": "success",
  "message": "Enrollment successful",
  "name": "John Doe",
  "class": 1,
  "section": "A",
  "roll": 10,
  "phoneNum": "0123456789"
}

## Installation and Setup

### Hardware Setup
- Connect fingerprint sensor via UART  
- Connect OLED via I2C  
- Connect keypad to GPIO pins  
- Ensure proper power supply  

### Firmware Setup
- Open project in Arduino IDE  
- Select ESP32 board  
- Configure Wi-Fi and server settings  
- Upload firmware  

### Server Setup
- Install XAMPP or LAMP  
- Configure PHP backend  
- Import MySQL database  
- Update API endpoints  

---

## Future Improvements
- Face recognition integration  
- Embedded Linux deployment  
- Mobile application support  
- Advanced analytics  
- Power optimization  

---

## Use Cases
- Schools and universities  
- Offices and organizations  
- Industrial monitoring systems  
- Access control applications  

---

## Contribution
Contributions are welcome. Fork the repository and submit a pull request.

---

If you want next level:
- I can convert this into **GitHub professional README (badges, shields, diagrams, screenshots)**  
- Or align it with your **actual folder structure (firmware/, server/, docs/ etc.)** which makes it look like a real commercial project.
