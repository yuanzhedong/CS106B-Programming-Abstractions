/* File: Permutations.cpp
 *
 * Functions to list off all permutations of a collection of elements.
 */
#include <iostream>
#include <string>
#include "hashset.h"
#include "console.h"
using namespace std;

/* Given a string of letters we haven't yet considered, along with the partial
 * string built up so far, prints out all permutations that can be made from
 * those characters.
 */
void listPermutationsRec(const string& str, const string& chosen) {
    /* Base case: If we've already committed to every character, then print out
     * the permutation we made.
     */
    if (str == "") {
        cout << chosen << endl;
    }
    /* Recursive case: Some character must come next in the ordering. Try all
     * possible choices of what it can be.
     */
    else {
        for (int i = 0; i < str.size(); i++) {
            /* Form a new string by dropping out the character at this index.
             * Note that getting a substring from an index that's equal to the
             * length of the string is perfectly legal; it just gives back the
             * empty string.
             */
            char ch = str[i];
            string remaining = str.substr(0, i) + str.substr(i + 1);

            listPermutationsRec(remaining, chosen + ch);
        }
    }
}

void listPermutationsOf(const string& str) {
    listPermutationsRec(str, "");
}

int main() {
    listPermutationsOf("AHI");
    return 0;
}
