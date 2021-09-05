/* File: FunWithStrings.cpp
 *
 * A program for playing around with C++ strings!
 */
#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

string reverseOf(string input);

int main() {
    while (true) {
        string text = getLine("Enter some text: ");
        cout << "Behold, it is now \"" << reverseOf(text) << ".\"" << endl << endl;
    }
}

string reverseOf(string input) {
    /* Base case: A string of no characters cannot be further simplified. */
    if (input == "") { // Or: input.length() == 0, input.size() == 0, input.empty()
        return "";
    }
    /* Recursive case: If the string has at least one character, then the
     * reverse of the string is formed by appending the first character to the
     * reverse of the remaining characters.
     */
    else {
        /* input.substr(1) is the string formed by dropping a character from
         * the front of the string input.
         */
        return reverseOf(input.substr(1)) + input[0];
    }
}
