#include <iostream>
#include "AccountManager.h"
#include "Utils.h"
#include <limits> //to check the the length and invalid inputs for menu, phone number

using namespace std;

int main()
{
  AccountManager manager;
  while (true)
  {
    long long accNo;
    double amount;
    cout << "----- BANK ACCOUNT MANAGEMENT SYSTEM -----" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Display Account Details" << endl;
    cout << "3. Deposit Money" << endl;
    cout << "4. Withdraw Money" << endl;
    cout << "5. Modify Account" << endl;
    cout << "6. View Transaction Log" << endl;
    cout << "7. Exit" << endl;
    cout << "------------------------------------------------" << endl;
    int choice;
    while (true)
    {
      cout << "Enter your choice: ";
      if (getValidInput(choice))
      {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        break;
      }
    }
    cout << "press Enter" << endl;
    switch (choice)
    {
    case 1:
      manager.createAccount();
      break;

    case 2:
      cout << "Enter account Number: " << endl;
      while (!getValidInput(accNo))
        ;
      manager.displayAccount(accNo);
      break;

    case 3:
      cout << "Enter account Number: " << endl;
      while (!getValidInput(accNo))
        ;
      do
      {
        cout << "Enter the amount to be deposited: ";
        while (!getValidInput(amount))
          ;
        if (amount <= 0)
          cout << "Amount must be greater than 0.\n";
      } while (amount <= 0);
      manager.deposit(accNo, amount);
      break;

    case 4:
      cout << "Enter account Number: ";
      while (!getValidInput(accNo))
        ;
      do
      {
        cout << "Enter amount to be withdrawn: ";
        while (!getValidInput(amount))
          ;
        if (amount <= 0)
          cout << "Invalid amount.\n";
        else if (amount > 50000)
          cout << "You can withdraw maximum 50000 per day.\n";
      } while (amount <= 0 || amount > 50000);
      manager.withdraw(accNo, amount);
      break;

    case 5:
      cout << "Enter Account Number: ";
      while (!getValidInput(accNo))
        ;
      if (!manager.modifyAccount(accNo))
      {
        cout << "failed to modify amount or account not found.\n";
      }
      break;

    case 6:
      cout << "Enter account Number: " << endl;
      while (!getValidInput(accNo))
        ;
      manager.viewTransactionLog(accNo);
      break;

    case 7:
      cout << "Thank you for using the system. Goodbye!" << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Press Enter to exit...";
      cin.get();
      return 0;

    default:
      cout << "Invalid Input. Please enter from 1 to 7" << endl;
      break;
    }
  }

  return 0;
}