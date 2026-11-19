#include "ATM.h"

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
  double balance;

  while (fin >> accountNumber >> accountHolder >> pin >> balance) {
    Account account(accountNumber, accountHolder, pin, balance);
    accounts.push_back(account);
  }

  fin.close();
}

void ATM::saveAccounts() {
  ofstream fout("accounts.txt");

  for (Account &account : accounts) {
    fout << account.getAccountNumber() << " " << account.getAccountHolder()
         << " " << account.getPIN() << " " << account.getBalance() << endl;
  }

  fout.close();
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

  int index = findAccount(accountNumber);

  if (index == -1) {
    cout << "Account not found.\n";
    return;
  }

  int attempts = 0;

  while (attempts < 3) {
    cout << "Enter PIN: ";
    cin >> enteredPin;

    if (accounts[index].verifyPIN(enteredPin)) {
      cout << "\nLogin successful!\n";
      cout << "Welcome, " << accounts[index].getAccountHolder() << "!\n";

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

    switch (choice) {
    case 1:
      account.checkBalance();
      break;

    case 2: {
      double amount;

      cout << "Enter deposit amount: ";
      cin >> amount;

      double oldBalance = account.getBalance();

      account.deposit(amount);

      if (account.getBalance() != oldBalance) {
        saveAccounts();
        cout << "Transaction completed successfully.\n";
      }

      break;
    }

    case 3: {
      double amount;

      cout << "Enter withdrawal amount: ";
      cin >> amount;

      double oldBalance = account.getBalance();

      account.withdraw(amount);

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

      cout << "Enter new PIN: ";
      cin >> newPin;

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