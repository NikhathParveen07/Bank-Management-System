#include <iostream>
#include <limits>  //to check the the length and invalid inputs for menu, phone number
#include <fstream> // for files
#include <sstream> // for string stream function to read the files
#include <string>  //for string functions like stoll, stod
#include "BankAccount.h"
#include "Utils.h"
using namespace std;

int main()
{
  ifstream inFile("accounts.txt");
  string line;
  long long maxAccountNo = 10000000;
  while (getline(inFile, line))
  {
    stringstream ss(line);
    string token;
    getline(ss, token, '|');
    long long accountNo = stoll(token);
    if (accountNo > maxAccountNo)
    {
      maxAccountNo = accountNo;
    }
  }
  inFile.close();
  BankAccount::setLastAccountNumber(maxAccountNo);

  BankAccount account;
  int choice;
  long long accNo;
  while (true)
  {
    cout << "----- BANK ACCOUNT MANAGEMENT SYSTEM -----" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Display Account Details" << endl;
    cout << "3.Deposit Money" << endl;
    cout << "4.Withdraw Money" << endl;
    cout << "5.Modify Account" << endl;
    cout << "6.View Transaction Log" << endl;
    cout << "7.Exit" << endl;
    cout << "------------------------------------------------" << endl;

    cout << "Enter your choice: " << endl;
    cin >> choice;
    if (cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter digits only.\n";
      continue;
    }

    switch (choice)
    {
    case 1:
      account.createAccount();
      break;

    case 2:

      cout << "Enter account Number: " << endl;
      cin >> accNo;
      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter digits only.\n";
        continue; //--
      }
      account.displayAccount(accNo);
      break;
    case 3:
      long long accountNo;
      cout << "Enter account Number: " << endl;
      cin >> accountNo;
      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter digits only.\n";
        break; //--
      }
      double amt;
      while (true)
      {
        cout << "Enter the amount to be deposited: ";
        cin >> amt;
        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a valid number.\n";
          continue;
        }
        if (amt > 0)
        {
          break;
        }
        else
        {
          cout << "Enter valid amount" << endl;
        }
      }
      account.deposit(accountNo, amt);
      break;
    case 4:
      long long actNo;
      cout << "Enter account Number: " << endl;
      cin >> actNo;
      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter digits only.\n";
        break; //--
      }
      double amt1;
      while (true)
      {
        cout << "Enter amount to be withdrawn: ";
        cin >> amt1;
        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a valid number.\n";
          continue;
        }
        if (amt1 > 0 && amt1 <= 50000)
          break;
        else if (amt1 < 0)
        {
          cout << "Invalid amount " << endl;
        }
        else if (amt1 > 50000)
        {
          cout << "you can withdraw maximum 50000 per day" << endl;
        }
      }
      account.withdraw(actNo, amt1);
      break;
    case 5:
      account.modifyAccount();
      break;

    case 6:
      cout << "Enter account Number: " << endl;
      cin >> accNo;
      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter digits only.\n";
        continue; //--
      }
      account.viewTransactionlog(accNo);
      break;

    case 7:
      cout << "Thank you for using the system. Goodbye!" << endl;
      return 0; // exits the program

    default:

      cout << "Invalid Input. Please enter from 1 to 7" << endl;
      break;
    }
  }

  return 0;
}