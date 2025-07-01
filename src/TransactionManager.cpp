#include "TransactionManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstring> // for strlen()
using namespace std;
string TransactionManager::TRANSACTION_FILE = "transaction.txt";

void TransactionManager::logTransaction(long long accNo, const string &type, double amount)
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

void TransactionManager::viewTransactionLog(long long accNo)
{
  ifstream inFile(TRANSACTION_FILE);
  if (!inFile)
  {
    cout << "File Error." << endl;
    return;
  }

  string line;
  bool found = false;
  cout << "\n*** Transaction History for Account " << accNo << " ***\n";

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
