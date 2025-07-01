#include <iostream>
#include <limits>
using namespace std;
#ifndef UTILS_H
#define UTILS_H

int getLength(long long n);

template <typename T>
bool getValidInput(T &input)
{
  cin >> input;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a valid number.\n";
    return false;
  }
  return true;
}

#endif

/*
Explanation:
- Including the same header file multiple times can cause redefinition errors.
- To avoid this, we use header guards:
  - #ifndef UTILS_H : Checks if UTILS_H is NOT defined.
  - #define UTILS_H : If not defined, defines UTILS_H to mark it included.
  - If UTILS_H is already defined, the preprocessor skips the content, avoiding multiple inclusion.
*/