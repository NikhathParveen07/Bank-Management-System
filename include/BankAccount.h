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

public:
  BankAccount();
  BankAccount(long long accNo, string &name, long long phone, string &addr, double bal);

  long long getAccountNumber();
  string getHolderName();
  long long getPhoneNumber();
  string getAddress();
  double getBalance();

  void setAccountNumber(long long accNo);
  void setHolderName(string &name);
  void setPhoneNumber(long long phone);
  void setAddress(string &addr);
  void setBalance(double bal);

  void inputDetails();
  string toFileString();
  static BankAccount fromFileString(string &line);

  void displayDetails();
  bool modifyDetails();
  bool deposit(double amount);
  bool withdraw(double amount);
};

#endif