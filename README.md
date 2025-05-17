# 🚗 Qt Parking Management System

**A secure desktop application** built with C++17 and Qt framework featuring dynamic lot management, JSON data storage, and encrypted user credentials.

![C++](https://img.shields.io/badge/C++-17-blue) ![Qt](https://img.shields.io/badge/Qt-4.8.1-green) ![JSON](https://img.shields.io/badge/Storage-JSON-ff69b4) ![OOP](https://img.shields.io/badge/Design-OOP-brightgreen)

---

## 🎨 UI Gallery
| Feature | Screenshot |
|---------|------------|
| **Login Page** | <img src="/images/Login.png" width="400"> |
| **Registration** | <img src="/images/Register Account.png" width="400"> |
| **Vehicle Entry** | <img src="/images/VEntry.png" width="400"> |
| **Vehicle Exit** | <img src="/images/VExit.png" width="400"> |
| **Admin Settings** | <img src="/images/SettingsAdmin.png" width="400"> |
| **Employee Settings** | <img src="/images/SettingsEmployee.png" width="400"> |

---

## 🌟 Key Features
### 🛠️ Core Functionality
- **Dynamic Parking Management**
  - Real-time slot adjustment
  - Automatic fee calculation
- **Role-Based Access**
  - Admin: Full system control
  - Employee: Limited permissions
- **Vehicle Tracking**
  - Timestamped entry/exit logs
  - Parking slip generation

### 🔐 Secure Data Handling
```json
// accounts.json example
{
  "employeeId": "ENCRYPTED",
  "password": "ENCRYPTED",
  "role": "ENCRYPTED"
}

🚀 Getting Started
Prerequisites
  -Qt 4.8.1
  -C++17 compiler
  -qmake


🤝 Contribution
Fork the repository
Create your feature branch (git checkout -b feature/improvement)
Commit changes (git commit -m 'Add new payment module')
Push to branch (git push origin feature/improvement)
Open a Pull Request

git clone https://github.com/PROPRINCE1/Parking_Management_System.git
cd Parking_Management_System
qmake ParkingSystem.pro
make
./Parking_Management_System


Parking_Management_System/
├── src/
│   ├── Core/
│   │   ├── ParkingLot.cpp     # Slot management
│   │   ├── logmanager.cpp     # File I/O operations
│   │   ├── mainwindow.cpp     # Core file to manage UI
|   |   ├── createAcc.cpp      # Account Registration
|   |   └── SignIn.cpp         # Sign In functions managing file
│   ├── UI/
│   │   ├── mainwindow.ui      # base UI file
│   │   └── signin.ui          # Sign in window file
├── data/                      # JSON storage
│   ├── slots.json             # 
│   ├── accounts.json          # 
│   └── logdata.json          # Activity Records
└── ParkingSystem.pro         # Qt project file
