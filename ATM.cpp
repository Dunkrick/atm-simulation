#include "ATM.h"
#include <cstdio>
#include <ios>
#include <iosfwd>
#include <limits>

ATM::ATM() { loadAccounts(); }

void ATM::loadAccounts() {
  accounts.clear();

  ifstream fin("accounts.txt");

  if (!fin) {
    cout << "No account file found.\n";
    return;
  }

  long long accountNumber;
  string accountHolder;
  int pin;
  long long balance;

  while (fin >> accountNumber >> accountHolder >> pin >> balance) {
    Account account(accountNumber, accountHolder, pin, balance);
    accounts.push_back(account);
  }

  fin.close();
}

void ATM::saveAccounts() {
  const string tempFile = "accounts_temp.txt";
  const string targetFile = "accounts.txt";

  ofstream fout(tempFile);

  if (!fout) {
    cout << "Error: Unable to open temporary file for writing.\n";
    return;
  }

  for (Account &account : accounts) {
    fout << account.getAccountNumber() << " " << account.getAccountHolder()
         << " " << account.getPIN() << " " << account.getBalance() << endl;
  }

  fout.close();

  std::remove(targetFile.c_str());

  if (std::rename(tempFile.c_str(), targetFile.c_str()) != 0) {
    cout << "Error: Failed to commit account changes to storage.\n";
  }
}

int ATM::findAccount(long long accountNumber) {
  for (int i = 0; i < accounts.size(); i++) {
    if (accounts[i].getAccountNumber() == accountNumber) {
      return i;
    }
  }

  return -1;
}

void ATM::login() {
  long long accountNumber;
  int enteredPin;

  cout << "\n===== ATM LOGIN =====\n";

  cout << "Enter Account Number: ";
  cin >> accountNumber;

  if (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input! Account number must be numeric.\n";
    return;
  }

  int index = findAccount(accountNumber);

  if (index == -1) {
    cout << "Account not found.\n";
    return;
  }

  int attempts = 0;

  while (attempts < 3) {
    cout << "Enter PIN: ";
    cin >> enteredPin;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      attempts++;
      cout << "Invalid input! Please enter a valid PIN.\n";
      continue;
    }

    if (accounts[index].verifyPIN(enteredPin)) {
      cout << "\nLogin successful!\n";

      string displayName = accounts[index].getAccountHolder();
      for (char &c : displayName) {
        if (c == '_')
          c = ' ';
      }
      cout << "Welcome, " << displayName << "!\n";

      performTransaction(accounts[index]);
      return;
    }

    attempts++;

    cout << "Incorrect PIN.\n";
  }

  cout << "Too many incorrect attempts. Access denied.\n";
}

void ATM::showMenu() {
  cout << "\n===== ATM MENU =====\n";
  cout << "1. Check Balance\n";
  cout << "2. Deposit Money\n";
  cout << "3. Withdraw Money\n";
  cout << "4. Change PIN\n";
  cout << "5. Exit\n";
  cout << "Enter your choice: ";
}

void ATM::performTransaction(Account &account) {
  int choice;

  do {
    showMenu();
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "\nInvalid choice. Please enter a number (1-5).\n";
      continue;
    }

    switch (choice) {
    case 1:
      account.checkBalance();
      break;

    case 2: {
      long long inputRupees;

      cout << "Enter deposit amount: ";
      cin >> inputRupees;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid amount entered!\n";
        break;
      }

      long long amountInPaise = llround(inputRupees * 100.0);
      long long oldBalance = account.getBalance();

      account.deposit(amountInPaise);

      if (account.getBalance() != oldBalance) {
        saveAccounts();
        cout << "Transaction completed successfully.\n";
      }

      break;
    }

    case 3: {
      long long inputRupees;

      cout << "Enter withdrawal amount: ";
      cin >> inputRupees;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid amount entered!\n";
        break;
      }

      long long amountInPaise = llround(inputRupees * 100.0);
      long long oldBalance = account.getBalance();

      account.withdraw(amountInPaise);

      if (account.getBalance() != oldBalance) {
        saveAccounts();
        cout << "Transaction completed successfully.\n";
      }

      break;
    }

    case 4: {
      int oldPin;
      int newPin;

      cout << "Enter old PIN: ";
      cin >> oldPin;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid input for old PIN!\n";
        break;
      }
      cout << "Enter new PIN: ";
      cin >> newPin;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid input for new PIN!\n";
        break;
      }

      int previousPin = account.getPIN();

      account.changePIN(oldPin, newPin);

      if (account.getPIN() != previousPin) {
        saveAccounts();
      }

      break;
    }

    case 5:
      cout << "Thank you for using the ATM.\n";
      break;

    default:
      cout << "Invalid choice. Please try again.\n";
    }

  } while (choice != 5);
}

void ATM::start() { login(); }