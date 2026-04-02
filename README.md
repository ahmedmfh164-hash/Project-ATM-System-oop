# Project-ATM-System-oop

# 🏦 ATM System - C++ Console Application

## 📌 Overview

The **ATM System** is a console-based banking application developed in **C++** using **Object-Oriented Programming (OOP)** concepts.

This project simulates the basic functionality of an **Automated Teller Machine (ATM)** where users can log in using their account number and PIN, perform transactions such as withdrawing money, depositing funds, and checking their account balance.

All client data is stored and managed using **text files**.

---

## 🚀 Features

✔ Secure login with **Account Number & PIN**  
✔ **Quick Withdraw** with predefined amounts  
✔ **Normal Withdraw** with custom amount  
✔ **Deposit money into account**  
✔ **Check account balance**  
✔ **Logout system**  
✔ Data stored in **Bank Clients file**  
✔ Colored console interface  

---

## 🧠 Concepts Used

This project demonstrates several important C++ concepts:

* Object-Oriented Programming (OOP)
* Encapsulation
* Inheritance
* File Handling
* Static Methods
* Vectors (STL)
* Console UI Design
* Data Validation

---

## 🏗 Project Architecture

The system is divided into multiple classes, each responsible for a specific functionality.

| Class               | Responsibility                        |
| ------------------- | ------------------------------------- |
| `clsLoginScreen`    | Handles login process                 |
| `clsMainMenue`      | Displays the ATM main menu            |
| `clsQuickWithdraw`  | Quick withdrawal with fixed amounts   |
| `clsNormalWithdraw` | Withdrawal with custom amount         |
| `clsDeposit`        | Deposit money into account            |
| `clsTotalBalances`  | Display user balance                  |
| `clsBankClient`     | Manages bank clients and file storage |
| `clsPerson`         | Base class for personal information   |
| `clsUtil`           | Utility functions                     |
| `clsDate`           | Date and time operations              |
| `clsScreen`         | Base class for UI screens             |

---

## 🔐 Login System

The user must enter:

```
Account Number
PIN Code
```

The system allows **3 attempts only** before locking access.

---

## 📋 Main Menu

After successful login:

```
**** ATM Main Menu ****

1. Quick Withdraw
2. Normal Withdraw
3. Deposit
4. Check Balance
5. Logout
```

---

## 💰 Quick Withdraw Options

```
1 → 50
2 → 100
3 → 200
4 → 400
5 → 500
6 → 600
7 → 800
8 → 1000
```

---

## 💾 Data Storage

Client information is stored in:

```
Bank Clients.txt
```

Example record format:

```
FirstName#//#LastName#//#Email#//#Phone#//#AccountNumber#//#PinCode#//#Balance
```

---

## 🖥 Example Output

```
========================================
        ATM Main Menu Screen
========================================

Account Name : Ahmed Mohamed
Date Today   : Monday, April, 02/04/2026

1. Quick Withdraw
2. Normal Withdraw
3. Deposit
4. Check Balance
5. Logout
```

---

## ⚙ How to Run the Project

1. Open the project in **Visual Studio**
2. Make sure all `.h` and `.cpp` files are included
3. Ensure the file:

```
Bank Clients.txt
```

exists in the project directory.

4. Run the program.

---

## 📈 Possible Improvements

Future enhancements could include:

* Transfer between accounts
* Transaction history
* Admin panel
* Password encryption
* GUI interface
* Database instead of text files

---

## 👨‍💻 Author

Ahmed Mohamed
