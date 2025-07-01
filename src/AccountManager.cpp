#include "AccountManager.h"
#include "TransactionManager.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

string AccountManager::ACCOUNTS_FILE = "accounts.txt";
string AccountManager::TEMP_FILE = "temp.txt";

long long AccountManager::last_account_number = 10000000;

AccountManager::AccountManager() {}

long long AccountManager::generateAccountNumber()
{
  long long maxAccountNo = 10000000;
  ifstream inFile(ACCOUNTS_FILE);
  if (!inFile){
    return ++maxAccountNo;
  }

  string line;
  while (getline(inFile, line))
  {
    BankAccount temp = BankAccount::fromFileString(line);
    maxAccountNo = max(temp.getAccountNumber(), maxAccountNo);
  }

  inFile.close();
  return ++maxAccountNo;
  
}

void AccountManager::setLastAccountNumber(long long num)
{
  last_account_number = num;
}

long long AccountManager::getAccountNumber()
{
  return last_account_number;
}

void AccountManager::createAccount()
{
  BankAccount account;
  account.setAccountNumber(generateAccountNumber());
  account.inputDetails();

  // file append
  ofstream fout(ACCOUNTS_FILE, ios::app);
  if (!fout)
  {
    cout << "Error saving acount to file.\n";
    return;
  }

  fout << account.toFileString() << endl;
  fout.close();
  cout << "Account created successfully! Account Number :" << account.getAccountNumber() << endl;
  ;
}

void AccountManager::displayAccount(long long accNo)
{
  BankAccount account;
  if (loadAccount(accNo, account))
  {
    account.displayDetails();
  }
  else
  {
    cout << "Account Not found.\n";
  }
}

bool AccountManager::loadAccount(long long accNo, BankAccount &acc)
{
  ifstream inFile(ACCOUNTS_FILE);
  if (!inFile)
    return false;

  string line;
  while (getline(inFile, line))
  {
    BankAccount temp = BankAccount::fromFileString(line);
    if (temp.getAccountNumber() == accNo)
    {
      acc = temp;
      return true;
    }
  }
  return false;
}

void AccountManager::deposit(long long accNo, double amount)
{
  BankAccount acc;
  if (!loadAccount(accNo, acc))
  {
    cout << "Account Not found" << endl;
    return;
  }
  acc.deposit(amount);
  updateAccountInFile(acc);
  TransactionManager::logTransaction(accNo, "deposit", amount);
  cout << "Deposit Successful." << endl;
}
void AccountManager::withdraw(long long accNo, double amount)
{
  BankAccount acc;
  if (!loadAccount(accNo, acc))
  {
    cout << "Account not found." << endl;
    return;
  }
  if (acc.withdraw(amount))
  {
    updateAccountInFile(acc);
    TransactionManager::logTransaction(accNo, "withdraw", amount);
    cout << "Withdraw Successfull" << endl;
  }
  else
  {
    cout << "Insufficient balance" << endl;
  }
}

bool AccountManager::modifyAccount(long long accNo)
{
  BankAccount acc;
  if (!loadAccount(accNo, acc))
  {
    cout << "Account not found." << endl;
    return false;
  }
  if (acc.modifyDetails())
  {
    updateAccountInFile(acc);
    cout << "Account Modified." << endl;
    return true;
  }

  return false;
}

void AccountManager::updateAccountInFile(BankAccount &updatedAccount)
{
  ifstream inFile(ACCOUNTS_FILE);
  ofstream tempFile(TEMP_FILE);

  string line;
  while (getline(inFile, line))
  {
    BankAccount acc;
    acc.fromFileString(line);
    if (acc.getAccountNumber() == updatedAccount.getAccountNumber())
    {
      tempFile << updatedAccount.toFileString() << endl;
    }
    else
    {
      tempFile << line << "\n";
    }
  }
  inFile.close();
  tempFile.close();
  remove(ACCOUNTS_FILE.c_str());
  rename(TEMP_FILE.c_str(), ACCOUNTS_FILE.c_str());
}

void AccountManager::viewTransactionLog(long long accNo)
{
  TransactionManager::viewTransactionLog(accNo);
}
