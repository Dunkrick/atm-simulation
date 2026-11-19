# Automated Teller Machine (ATM) Simulation System

A robust, modular C++ console-based ATM Simulation System designed with Object-Oriented Programming (OOP) principles. The system models realistic banking operations including user authentication with brute-force lockout safeguards, account transactions (balance inquiry, deposit, withdrawal), dynamic PIN modifications, and real-time file-based ledger persistence.

---

## 🌟 Key Features

- **Multi-Account Support & In-Memory Store**: Manages multiple user bank accounts in memory using C++ Standard Template Library (`std::vector`).
- **Secure Authentication & Lockout Protection**: Validates 4-digit numeric PINs with a 3-attempt lockout mechanism to prevent unauthorized access.
- **Transactional Integrity & Input Validation**:
  - Rejects non-positive deposit/withdrawal quantities.
  - Enforces overdraft protection and balance sufficiency checks.
  - Verifies current PIN and enforces 4-digit format validation when changing credentials.
- **Real-Time Disk Persistence**: Automatically flushes account updates to persistent storage (`accounts.txt`) upon every balance or credential modification using C++ file streams (`std::ifstream`, `std::ofstream`).
- **Interactive CLI Interface**: User-friendly menu-driven terminal interface with immediate visual transaction receipts.

---

## 🏗️ Architecture & OOP Design

The codebase strictly adheres to modular design and clean Object-Oriented principles:

```
├── Account.h / Account.cpp   # Domain Entity / Model
│   └── Encapsulates account attributes, validation logic, and account-level mutations.
├── ATM.h / ATM.cpp           # System Controller / Service Layer
│   └── Manages collection of accounts (Composition: HAS-A), handles auth flow, menu loop, and disk persistence.
└── main.cpp                  # Application Entry Point
    └── Bootstraps ATM subsystem and triggers execution lifecycle.
```

### Core OOP Principles Applied:
- **Encapsulation**: Account attributes (`accountNumber`, `accountHolder`, `pin`, `balance`) are marked `private` to safeguard internal state. Access is strictly controlled via public interface methods (`deposit`, `withdraw`, `verifyPIN`, getters/setters).
- **Composition (HAS-A Relationship)**: The `ATM` class manages account collections via `std::vector<Account>`, demonstrating strong object relationships and separation of business logic from domain models.
- **Single Responsibility Principle (SRP)**:
  - `Account`: Handles core balance mechanics, PIN verification, and data integrity.
  - `ATM`: Coordinates user sessions, UI input/output, and stream serialization.

---

## 🛠️ Tech Stack & Prerequisites

- **Language**: C++ (C++11 or higher)
- **Standard Library Components**: `<iostream>`, `<fstream>`, `<vector>`, `<string>`
- **Compiler**: GCC / Clang / MSVC

---

## 🚀 Getting Started

### 1. Clone Repository
```bash
git clone https://github.com/Dunkrick/atm-simulation.git
cd atm-simulation
```

### 2. Configure Seed Data
Create an `accounts.txt` file in the project root directory with sample data format: `<accountNumber> <accountHolder> <pin> <balance>`:
```text
1001 Alice 1234 5000.00
1002 Bob 5678 12000.50
1003 Naresh 4321 7500.00
```

### 3. Build & Run
Compile using any C++11 compliant compiler:

```bash
g++ -std=c++11 -Wall -Wextra main.cpp ATM.cpp Account.cpp -o atm_simulation
./atm_simulation
```

---

## 📋 Project Structure

```
ATM_simulation/
├── Account.h         # Class declaration for Account entity
├── Account.cpp       # Business logic implementation for Account
├── ATM.h             # ATM class header with composition definition
├── ATM.cpp           # Implementation of session management & persistence
├── main.cpp          # Driver entry point
├── .gitignore        # Ignores build artifacts and sensitive ledger files
└── README.md         # Comprehensive technical documentation
```
