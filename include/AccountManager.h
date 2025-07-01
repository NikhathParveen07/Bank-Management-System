#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "BankAccount.h"
#include <string>
using namespace std;

class AccountManager
{
private:
  static string ACCOUNTS_FILE;
  static string TEMP_FILE;
  static long long last_account_number;

public:
  AccountManager();

  long long generateAccountNumber();
  void createAccount();
  void displayAccount(long long accNo);
  void deposit(long long accNo, double amount);
  void withdraw(long long accNo, double amount);
  void updateAccountInFile(BankAccount &updatedAccount);
  bool loadAccount(long long accNo, BankAccount &acc);
  bool modifyAccount(long long accNo);
  void viewTransactionLog(long long accNo);

  static void setLastAccountNumber(long long num);
  static long long getAccountNumber();
};

#endif