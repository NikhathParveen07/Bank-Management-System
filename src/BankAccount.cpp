#include "BankAccount.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
using namespace std;

// default constructor
BankAccount::BankAccount() : Account_Number(0), Holder_name(""), Holder_PhoneNumber(0), Holder_Address(""), balance(0.0) {}

// parameterized constructor

BankAccount::BankAccount(long long accno, string &name, long long phone, string &addr, double bal) : Account_Number(accno), Holder_name(name), Holder_PhoneNumber(phone), Holder_Address(addr), balance(bal) {}
// getters
long long BankAccount::getAccountNumber()
{
  return Account_Number;
}
string BankAccount::getHolderName()
{
  return Holder_name;
}
long long BankAccount::getPhoneNumber()
{
  return Holder_PhoneNumber;
}
string BankAccount::getAddress()
{
  return Holder_Address;
}
double BankAccount::getBalance()
{
  return balance;
}

// setters
void BankAccount::setAccountNumber(long long accNo)
{
  Account_Number = accNo;
}

void BankAccount::setHolderName(string &name)
{
  Holder_name = name;
}
void BankAccount::setPhoneNumber(long long phone)
{
  Holder_PhoneNumber = phone;
}
void BankAccount::setAddress(string &addr)
{
  Holder_Address = addr;
}
void BankAccount::setBalance(double bal)
{
  balance = bal;
}

void BankAccount::inputDetails()
{
  cin.ignore();
  cout << "Enter Account Holder Name: ";
  getline(cin, Holder_name);

  while (true)
  {
    cout << "Enter Phone number: ";
    cin >> Holder_PhoneNumber;
    if (cin.fail() || getLength(Holder_PhoneNumber) != 10)
    {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid phone number. Try again." << endl;
    }
    else
    {
      break;
    }
  }
  cin.ignore();
  cout << "Enter Address: ";
  getline(cin, Holder_Address);
}
string BankAccount::toFileString()
{
  return to_string(Account_Number) + "|" + Holder_name + "|" + to_string(Holder_PhoneNumber) + "|" + to_string(balance) + "|" + Holder_Address;
}
BankAccount BankAccount::fromFileString(string &line)
{
  stringstream ss(line);
  string token;

  getline(ss, token, '|');
  long long accNo = stoll(token);

  getline(ss, token, '|');
  string name = token;

  getline(ss, token, '|');
  long long phone = stoll(token);

  getline(ss, token, '|');
  double bal = stod(token);

  getline(ss, token, '|');
  string addr = token;

  return BankAccount(accNo, name, phone, addr, bal);
}

bool BankAccount::modifyDetails()
{
  bool modified = false;

  cout << "Current Account Details\n";
  displayDetails();

  cout << "\nWhich field do you want to modify?\n";
  cout << "1. Name\n2. Phone Number\n3. Address\n";

  while (true)
  {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cin.ignore();
      cout << "Enter new name: ";
      getline(cin, Holder_name);
      modified = true;
      break;
    case 2:
      while (true)
      {
        cout << "Enter new Phone Number: ";
        cin >> Holder_PhoneNumber;
        if (cin.fail() || getLength(Holder_PhoneNumber) != 10)
        {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "Invalid input. Try again.\n";
        }
        else
          break;
      }
      modified = true;
      break;
    case 3:
      cin.ignore();
      cout << "Enter new Address: ";
      getline(cin, Holder_Address);
      modified = true;
      break;
    default:
      cout << "Invalid choice.\n";
    }

    char ch;
    cout << "Modify another field? (y/n): ";
    cin >> ch;
    if (tolower(ch) == 'n')
      break;
  }

  return modified;
}

void BankAccount::displayDetails()
{
  cout << "\n***** Account Details *****\n";
  cout << "Account Number   : " << Account_Number << "\n";
  cout << "Holder Name      : " << Holder_name << "\n";
  cout << "Phone Number     : " << Holder_PhoneNumber << "\n";
  cout << "Address          : " << Holder_Address << "\n";
  cout << "Balance          : " << balance << "\n";
  cout << "***************************\n";
}

bool BankAccount::deposit(double amount)
{
  if (amount <= 0)
  {
    cout << "Amount must be positive.\n";
    return false;
  }
  balance += amount;
  return true;
}

bool BankAccount::withdraw(double amount)
{
  if (amount <= 0)
  {
    cout << "Amount must be positive.\n";
    return false;
  }
  if (amount > balance)
  {
    cout << "Insufficient balance.\n";
    return false;
  }
  balance -= amount;
  return true;
}
