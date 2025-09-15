# 🏧 ATM System (C++)

A simple **ATM simulation system** built in C++.  
This project demonstrates **file handling**, **login/authentication**, and **basic banking operations** in a console application.

---

## About the Project
The **ATM System** simulates how an Automated Teller Machine works.  
Clients can log in with their **account number** and **PIN code**, then access a set of banking services such as withdrawing money, depositing funds, and checking account balances.

The project is built for **educational purposes**, focusing on:
- Practicing **C++ fundamentals** (structs, enums, vectors).
- Implementing **file handling** to save and update client data (`Bank.txt`).
- Designing **menu-driven programs** in the console.

---

## Features
- **Login System**
  - Account number + PIN authentication.
  - Keeps client information in `Bank.txt`.

- **ATM Services**
  - 🔹 Quick Withdraw (fixed amounts: 20, 50, 100, … 1000).  
  - 🔹 Normal Withdraw (any multiple of 5).  
  - 🔹 Deposit (adds money to account).  
  - 🔹 Balance Check (displays current balance).  
  - 🔹 Logout (return to login screen).  

- **Data Persistence**
  - All client data is stored in a text file (`Bank.txt`).
  - Balances are updated after each transaction.

---

## Technologies
- **Language**: C++  
- **Compiler/IDE**: Microsoft Visual Studio 2022  
- **Concepts Used**:
  - Structs
  - Enums
  - Vectors
  - File handling (text files)
  - Menu-driven programming

---
