/* File: DigitalDigits.cpp
 *
 * A program that explores properties of digits of
 * numbers!
 */
#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

int sumOfDigitsOf(int n);

int main() {
  int n = getInteger("Enter an integer: ");
  int digitSum = sumOfDigitsOf(n);
  cout << n << " sums to " << digitSum << endl;  
  return 0;
}

/* Returns the sum of the digits of the number n. This function assumes
 * that n is nonnegative.
 */
int sumOfDigitsOf(int n) {
  int result = 0;
  
  while (n > 0) {
    result += (n % 10); // n % 10 gives the last digit of n - do you see why?
    n /= 10; // In C++, dividing two integers always rounds down.
  }
  
  return result;
}

