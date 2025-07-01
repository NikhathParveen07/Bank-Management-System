#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <string>
using namespace std;

class TransactionManager
{
private:
    static string TRANSACTION_FILE;

public:
    static void logTransaction(long long accNo, const string &type, double amount);
    static void viewTransactionLog(long long accNo);
};

#endif
