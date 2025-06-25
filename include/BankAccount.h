#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>
using namespace std;

class BankAccount
{
private:
  long long Account_Number;
  string Holder_name;
  long long Holder_PhoneNumber;
  double balance;
  string Holder_Address;
  static long long last_account_number;
  const double minimum_balance = 0;

public:
  static void setLastAccountNumber(long long num);
  void createAccount();
  void displayAccount(long long accNo);
  void deposit(long long accNo, double amount);
  void withdraw(long long accNo, double amount);
  long long getAccountNumber();
  bool modifyAccount();
  void viewTransactionlog(long long accNo);
  

private:
  bool updateAccountInFile();
  void logTransaction(long long accNo, const string& type, double amount);
};

#endif