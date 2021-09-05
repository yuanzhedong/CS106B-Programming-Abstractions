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
int digitalRootOf(int n);

int main() {
    while (true) {
        int val = getInteger("For this trick, I need a number! ");
        cout << "Its digit sum is " << sumOfDigitsOf(val) << endl;
        cout << "Its digital root is " << digitalRootOf(val) << endl << endl;
    }
}

/* Given a number n, returns the sum of the digits of n. */
int sumOfDigitsOf(int n) {
    /* Base case: If n is a single digit, then it's its own digit sum. */
    if (n < 10) {
        return n;
    }
    /* Recursive case: The sum of the digits of n is formed by summing
     * the digits of the number formed by dropping the last digit of n
     * (that is, n / 10) with the last digit (n % 10).
     */
    else {
        return sumOfDigitsOf(n / 10) + (n % 10);
    }
}


/* Given a number n, returns its digital root. This is the number you get
 * by repeatedly summing the digits of n until you reach a single number.
 */
int digitalRootOf(int n) {
    /* Base case: Any single-digit number is its own digital root. */
    if (n < 10) {
        return n;
    }
    /* Recursive case: The digital root of n, when n is multiple digits long,
     * is the digital root of its digit sum.
     */
    else {
        return digitalRootOf(sumOfDigitsOf(n));
    }
}

