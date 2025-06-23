#include <iostream>
#include <limits> //to check the the length and invalid inputs for menu, phone number
#include <fstream> // for files
#include <sstream> // for string stream function to read the files
#include <string> //for string functions like stoll, stod
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
  const double minimum_balance = 0;

public:
  void createAccount()
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
    ofstream fout("accounts.txt", ios::app);
    if (fout)
    {
      fout << Account_Number << "|" << Holder_name << "|" << Holder_PhoneNumber << "|" << balance << "|" << Holder_Address << "\n";
    }
    else
    {
      cout << "Error saving acount to file.\n";
    }
  }

  void displayAccount(long long accNo)
  {
    ifstream inFile("accounts.txt");
    if (!inFile)
    {
      cout << "File cpuld not be opened.\n";
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

  void deposit(double amount)
  {
    balance += amount;
    cout << "Deposit Success" << endl;
  }
  void withdraw(double amount)
  {

    if (amount > balance)
    {
      cout << "Insufficient Balance" << endl;
    }
    else if ((balance - amount) <= minimum_balance)
    {
      cout << "Account balance cannot be zero" << endl;
    }
    else
    {
      balance -= amount;
      cout << "Withdraw Successful" << endl;
    }
  }
  long long getAccountNumber()
  {
    return Account_Number;
  }
  bool modifyAccount()
  {
    bool modified = false;
    cout << "Current Acount Details" << endl;
    cout << "Name: " << Holder_name << endl;
    cout << "Phone: " << Holder_PhoneNumber << endl;
    cout << "Address: " << Holder_Address << endl;
    cout << "Which field do you want to modify?" << endl;
    cout << "1.Name" << endl;
    cout << "2.Phone" << endl;
    cout << "3.Address" << endl;
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
        modified = true;
        break;
      case 3:
        cout << "Enter new Address: ";
        cin.ignore();
        getline(cin, Holder_Address);
        modified = true;
        break;

      default:
        cout << "Invalid choice,. Please enter 1, 2, or 3.";
        break;
      }
      char ch;
      cout << "Modify another field? (y/n):";
      cin >> ch;
      if (tolower(ch) == 'n')
        break;
    }
    return modified;
  }
};
long long BankAccount::last_account_number = 10000000;

int main()
{
  BankAccount obj;
  while (true)
  {
    cout << "----- BANK ACCOUNT MANAGEMENT SYSTEM -----" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Display Account Details" << endl;
    cout << "3.Deposit Money" << endl;
    cout << "4.Withdraw Money" << endl;
    cout << "5.Modify Account" << endl;
    cout << "6.Exit" << endl;
    cout << "------------------------------------------------" << endl;
    int choice;
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
      obj.createAccount();
      break;

    case 2:
      long long accNo;
      cout << "Enter account Number: " << endl;
      cin >> accNo;
      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter digits only.\n";
        continue;
      }
      obj.displayAccount(accNo);
      break;
    case 3:
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
      obj.deposit(amt);
      break;
    case 4:
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
      obj.withdraw(amt1);
      break;
    case 5:
      obj.modifyAccount();
      break;

    case 6:
      cout << "Thank you for using the system. Goodbye!" << endl;
      return 0; // exits the program

    default:

      cout << "Invalid Input. Please enter from 1 to 6" << endl;
      break;
    }
  }

  return 0;
}