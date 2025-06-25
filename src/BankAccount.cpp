#include "BankAccount.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>  //for tolower()
#include <cstring> // for strlen()

using namespace std;

const string ACCOUNTS_FILE = "accounts.txt";
const string TEMP_FILE = "temp.txt";
const string TRANSACTION_FILE = "transaction.txt";
const double minimum_balance = 0.0;

long long BankAccount::last_account_number = 10000000;

void BankAccount::setLastAccountNumber(long long num)
{
  last_account_number = num;
}
long long BankAccount::getAccountNumber()
{
  return Account_Number;
}
void BankAccount::createAccount()
{
  Account_Number = ++last_account_number;
  cin.ignore();
  cout << "Enter name: ";
  getline(cin, Holder_name);
  while (true)
  {
    cout << "Enter Phone Number: ";
    cin >> Holder_PhoneNumber;
    if (cin.fail())
    {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid input. Please enter digits only.\n";
      continue;
    }
    if (getLength(Holder_PhoneNumber) == 10)
    {
      break;
    }
    else
    {
      cout << "The phone Number should have 10 digits please try again\n";
    }
  }

  balance = 0;
  cout << "Enter Address: ";
  cin.ignore();
  getline(cin, Holder_Address);

  // file append
  ofstream fout(ACCOUNTS_FILE, ios::app);
  if (fout)
  {
    fout << Account_Number << "|" << Holder_name << "|" << Holder_PhoneNumber << "|" << balance << "|" << Holder_Address << "\n";
  }
  else
  {
    cout << "Error saving acount to file.\n";
  }
}

void BankAccount::displayAccount(long long accNo)
{
  ifstream inFile(ACCOUNTS_FILE);
  if (!inFile)
  {
    cout << "File could not be opened.\n";
    return;
  }
  string line;
  bool found = false;

  while (getline(inFile, line))
  {
    stringstream ss(line);
    string token;

    getline(ss, token, '|');
    long long accountNo = stoll(token);

    getline(ss, token, '|');
    string name = token;

    getline(ss, token, '|');
    long long phoneNo = stoll(token);

    getline(ss, token, '|');
    double balance = stod(token);

    getline(ss, token, '|');
    string address = token;

    if (accountNo == accNo)
    {
      cout << "*****Account Details*****" << endl;
      cout << "Account Number : " << accountNo << endl;
      cout << "Account Holder Name : " << name << endl;
      cout << "Account Holder Phone Number : " << phoneNo << endl;
      cout << "Account Holder Address : " << address << endl;
      cout << "Balance : " << balance << endl;
      cout << "*******************************" << endl;
      found = true;
      break;
    }
  }

  if (!found)
  {
    cout << "Account not found.\n";
  }
}

void BankAccount::deposit(long long accNo, double amount)
{
  ifstream inFile(ACCOUNTS_FILE);
  ofstream tempFile(TEMP_FILE);
  if (!inFile || !tempFile)
  {
    cout << "File error." << endl;
    return;
  }
  bool found = false;
  string line;
  while (getline(inFile, line))
  {
    stringstream ss(line);
    string token;
    getline(ss, token, '|');
    long long accountNo = stoll(token);

    if (accountNo == accNo)
    {
      found = true;

      string name, address;
      long long phoneNo;
      double balance;

      getline(ss, token, '|');
      name = token;
      getline(ss, token, '|');
      phoneNo = stoll(token);
      getline(ss, token, '|');
      balance = stod(token);
      getline(ss, token, '|');
      address = token;

      balance += amount;

      tempFile << accountNo << "|" << name << "|" << phoneNo << "|" << balance << "|" << address << endl;

      if (Account_Number == accNo)
        this->balance = balance;

      logTransaction(accNo, "deposit", amount);
      cout << "Deposit Success" << endl;
    }
    else
    {
      tempFile << line << endl;
    }
  }

  inFile.close();
  tempFile.close();

  if (!found)
  {
    cout << "Account not found." << endl;
    remove(TEMP_FILE.c_str());
  }
  else
  {
    if (remove(ACCOUNTS_FILE.c_str()) != 0 ||
        rename(TEMP_FILE.c_str(), ACCOUNTS_FILE.c_str()) != 0)
    {
      cout << "Error updating account file." << endl;
    }
  }
}
void BankAccount::withdraw(long long accNo, double amount)
{
  ifstream inFile(ACCOUNTS_FILE);
  ofstream tempFile(TEMP_FILE);
  if (!inFile || !tempFile)
  {
    cout << "File Error." << endl;
    return;
  }

  bool found = false;
  bool insufficient = false;
  string line;
  while (getline(inFile, line))
  {
    stringstream ss(line);
    string token;
    getline(ss, token, '|');
    long long accountNo = stoll(token);
    if (accountNo == accNo)
    {
      found = true;

      string name, address;
      long long phoneNo;
      double balance;

      getline(ss, token, '|');
      name = token;
      getline(ss, token, '|');
      phoneNo = stoll(token);
      getline(ss, token, '|');
      balance = stod(token);
      getline(ss, token, '|');
      address = token;

      if (amount > balance)
      {
        cout << "Insufficient Balance" << endl;
        tempFile << line << endl;
        insufficient = true;
        break;
      }
      else if ((balance - amount) <= minimum_balance)
      {
        cout << "Account balance cannot be zero" << endl;
        tempFile << line << endl;
        insufficient = true;
        break;
      }
      balance -= amount;

      tempFile << accountNo << "|" << name << "|" << phoneNo << "|" << balance << "|" << address << endl;

      if (Account_Number == accNo)
      {
        this->balance = balance;
      }
      logTransaction(accNo, "withdraw", amount);
      cout << "Withdraw Successful" << endl;
    }
    else
    {
      tempFile << line << endl;
    }
  }
  inFile.close();
  tempFile.close();

  if (!found)
  {
    cout << "Account not found." << endl;
    remove(TEMP_FILE.c_str());
  }
  else if (!insufficient)
  {
    if (remove(ACCOUNTS_FILE.c_str()) != 0 ||
        rename(TEMP_FILE.c_str(), ACCOUNTS_FILE.c_str()) != 0)
    {
      cout << "Error updating account file." << endl;
    }
  }
}

bool BankAccount::modifyAccount()
{
  bool modified = false;
  cout << "Current Acount Details" << endl;
  cout << "Name: " << Holder_name << endl;
  cout << "Phone: " << Holder_PhoneNumber << endl;
  cout << "Address: " << Holder_Address << endl;
  cout << "Which field do you want to modify?" << endl;
  cout << "1.Name\n2.Phone\n3.Address\n";

  while (true)
  {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter new Name: ";
      cin.ignore();
      getline(cin, Holder_name);
      modified = true;
      break;

    case 2:
      while (true)
      {
        cout << "Enter new Phone Number: ";
        cin >> Holder_PhoneNumber;
        if (cin.fail())
        {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "Invalid input. Please enter digits only.\n";
          continue;
        }
        if (getLength(Holder_PhoneNumber) == 10)
        {
          break;
        }
        else
        {
          cout << "The phone Number should have 10 digits please try again\n";
        }
      }
      modified = true;
      break;
    case 3:
      cout << "Enter new Address: ";
      cin.ignore();
      getline(cin, Holder_Address);
      modified = true;
      break;

    default:
      cout << "Invalid choice. Please enter 1, 2, or 3.";
      break;
    }
    char ch;
    cout << "Modify another field? (y/n):";
    cin >> ch;
    if (tolower(ch) == 'n')
      break;
  }
  if (modified)
    updateAccountInFile();

  return modified;
}

bool BankAccount::updateAccountInFile()
{
  ifstream inFile(ACCOUNTS_FILE);
  ofstream tempFile(TEMP_FILE);

  if (!inFile || !tempFile)
  {
    cout << "File Error.\n";
    return false;
  }

  string line;
  bool updated = false;

  while (getline(inFile, line))
  {
    stringstream ss(line);
    string token;

    getline(ss, token, '|');
    long long accountNo = stoll(token);

    if (accountNo == Account_Number)
    {
      tempFile << Account_Number << "|" << Holder_name << "|" << Holder_PhoneNumber << "|" << balance << "|" << Holder_Address << endl;
      updated = true;
    }
    else
    {
      tempFile << line << "\n";
    }
  }
  inFile.close();
  tempFile.close();
  if (updated)
  {
    if (remove(ACCOUNTS_FILE.c_str()) != 0 ||
        rename(TEMP_FILE.c_str(), ACCOUNTS_FILE.c_str()) != 0)
    {
      cout << "Error replacing account file.\n";
    }
  }
  else
  {
    remove(TEMP_FILE.c_str());
  }

  return updated;
}

void BankAccount::logTransaction(long long accNo, const string &type, double amount)
{
  ofstream logFile(TRANSACTION_FILE, ios::app);
  if (!logFile)
  {
    cout << "Could not open transaction file.\n";
    return;
  }

  time_t now = time(0);
  char *dt = ctime(&now);
  dt[strlen(dt) - 1] = '\0';

  logFile << accNo << "|" << type << "|" << amount << "|" << dt << "\n";

  logFile.close();
}

void BankAccount::viewTransactionlog(long long accNo)
{
  ifstream inFile(TRANSACTION_FILE);
  if (!inFile)
  {
    cout << "File Error." << endl;
    return;
  }

  string line;
  bool found = false;

  while (getline(inFile, line))
  {
    stringstream ss(line);
    string token;

    getline(ss, token, '|');
    long long accountNo = stoll(token);

    if (accountNo == accNo)
    {
      getline(ss, token, '|');
      string type = token;
      getline(ss, token, '|');
      double amount = stod(token);
      getline(ss, token, '|');
      string time = token;

      cout << type << "   " << amount << "   " << time << endl;
      found = true;
    }
  }
  if (!found)
  {
    cout << "Account not found.\n";
  }
}
