#include "secondary_functions.h"

// Функция для нахождения минимального значения из двух
long min_pair(long a, long b) {
    if (a >= b) return b;
    else return a;
}

// Функция для вычисление логарифма по основанию 2
unsigned int func_log2(unsigned int x) {
  unsigned int ans = 0 ;
  while (x>>=1) ans++;
  return ans ;
}