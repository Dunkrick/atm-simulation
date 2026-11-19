# ATM Simulation System

A modular, console-based ATM simulation built in C++ emphasizing financial precision, defensive input validation, and object-oriented design.

## Features

- **Integer-Based Currency**: Stores balances as 64-bit integer paise (`long long`) to eliminate floating-point rounding errors (Stripe model), formatting output into standard Rupees and Paise.
- **Resilient Input Handling**: Intercepts `std::cin` stream failures with automatic clearing and buffer flushing, preventing infinite loops on invalid inputs.
- **Security & Lockout**: 3-attempt PIN verification safeguard to prevent brute-force access.
- **Transactional Persistence**: Syncs ledger state in real time to disk (`accounts.txt`) after every balance or credential mutation.
- **OOP Architecture**: Strict separation between domain model (`Account`) and controller (`ATM`) using composition.

## Quickstart

### 1. Seed Data
Create `accounts.txt` in the root directory:
```text
1001 Alice 1234 500000
1002 Bob 5678 1200050
1003 Naresh 4321 750000
```
*(Balances are stored in paise: 750000 paise = Rs. 7,500.00)*

### 2. Build & Run
```bash
g++ -std=c++11 -Wall -Wextra main.cpp ATM.cpp Account.cpp -o atm_simulation
./atm_simulation
```

## Project Structure

- `Account.h` / `Account.cpp`: Domain entity encapsulating account state, validations, and mutations.
- `ATM.h` / `ATM.cpp`: Controller orchestrating user sessions, menus, and disk persistence.
- `main.cpp`: Entry point initializing the ATM instance.
