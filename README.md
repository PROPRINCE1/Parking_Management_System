# 🚗 Qt Parking Management System

**A secure desktop application** built with C++17 and Qt framework featuring dynamic lot management, JSON data storage, and encrypted user credentials.

---

## 🌟 Key Features

### 🛠️ Core Functionality
- **Real-time Parking Lot Resizing**
  - Admins can dynamically expand/reduce available slots
  - UI automatically updates to reflect changes

- **Role-Based Access Control**
  - **Admin Portal**: Password-protected dashboard (add/remove slots, view employees)
  - **User Interface**: Vehicle parking/exit with automatic fee calculation

- **Vehicle Lifecycle Tracking**
  - Entry/exit timestamp logging
  - Duration-based payment processing
  - Parking Slip generation

### 🔐 Data Management
- **JSON Database System**
  - `slots.json`: Tracks slot availability and configurations
  - `accounts.json`: Stores encrypted admin/user credentials
  - `logdata.json`: Records vehicle activity history

- **Security Layer**
  - Encoding and Decoding through functions in C++
  - Protected file read/write operations

### 🖥️ Qt Components
- **Responsive UI** with real-time slot visualization
- **Model-View Architecture** for clean data presentation
- **Signal-Slot System** for event handling

---

## 🚀 Getting Started

### Prerequisites
- Qt 4.8.1 Follow this tutorial -> https://www.youtube.com/watch?v=yyIUgBvBpqE&ab_channel=HabitTechHorizons
- C++17 compatible compiler
- qmake

### Installation
```bash
git clone https://github.com/PROPRINCE1/Parking_Management_System.git
cd Parking_Management_System
# Qt Creator:
# 1. Open ParkingSystem.pro
# 2. Select kit (Desktop Qt + compiler)
# 3. Build & Run (Ctrl+R)


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
│   ├── slots.json             # {
│   │                              {
│   │                               "Bike": 30,
│   │                               "Car": 26,
│   │                               "Electric Bike": 20,
│   │                               "Electric Car": 20,
│   │                               "Truck": 10
│   │                              }
│   │                            }
│   ├── accounts.json             # {
│   │                                 [
│   │                                   {
│   │                                     "employeeId": "369<?8",
│   │                                     "password": "viy|;47:=",
│   │                                     "role": "gqvty{ik",
│   │                                     "username": "viy|Kegu}xv"
│   │                                   }
│   │                                 ]
│   │                               }
│   └── logdata.json          # Activity Records
└── ParkingSystem.pro         # Qt project file


🤝 Contribution
Fork the repository
Create your feature branch (git checkout -b feature/improvement)
Commit changes (git commit -m 'Add new payment module')
Push to branch (git push origin feature/improvement)
Open a Pull Request
