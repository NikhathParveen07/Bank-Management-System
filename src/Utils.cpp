#include "Utils.h"

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

