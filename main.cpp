#include <iostream>
using namespace std;

int getLength(long long n)
{
  if (n == 0)
    return 1;
  int length = 0;
  if (n < 0)
    n = -n;
  while (n > 0)
  {
    length += 1;
    n /= 10;
  }
  return length;
}

class BankAccount
{
private:
  long long Account_Number;
  string Holder_name;
  long long Holder_PhoneNumber;
  double balance;
  string Holder_Address;
  static long long last_account_number;

public:
  void createAccount()
  {
    Account_Number = ++last_account_number;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, Holder_name);
    while (true)
    {
      cout << "Enter Phone Number: ";
      cin >> Holder_PhoneNumber;
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
  }

  void displayAccount() {}

  void deposit(double amount) {}
  void withdraw(double amount) {}
  long getAccountNumber() { return 0; }
  void modifyAccount() {}
};
long long BankAccount::last_account_number = 10000000;

int main()
{
  BankAccount obj;
  obj.createAccount();
  return 0;
}