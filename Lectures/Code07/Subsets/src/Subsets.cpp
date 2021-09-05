/* File: Subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>
#include "hashset.h"
#include "console.h"
using namespace std;

/* Code to list all subsets of a hashset. The first parameter
 * represents the elements we haven't yet considered. The second
 * parameter represents which integers we have already chosen.
 */
void listSubsetsRec(const HashSet<int>& elems,
                    const HashSet<int>& chosen) {
    /* Base case: If there are no more decisions to be made, then we've
     * committed to a specific set.
     */
    if (elems.isEmpty()) {
        cout << chosen << endl;
    }
    /* Recursive case: Pick an element. Then we either include that element
     * or exclude that element.
     */
    else {
        int elem = elems.first();

        /* Option 1: Include this element. */
        listSubsetsRec(elems - elem, chosen + elem);

        /* Option 2: Exclude this element. */
        listSubsetsRec(elems - elem, chosen);
    }
}
void listSubsetsOf(const HashSet<int>& s) {
    listSubsetsRec(s, {});
}


/* Recursive function to return all subsets of a string. The first parameter is
 * the remaining characters in the string. The second is the set of characters
 * that we've already committed to.
 */
HashSet<string> subsetsRec(const string& str,
                           const string& chosen) {
    /* Base case: If we have no decisions left, we're locked into our choice. */
    if (str == "") {
        /* We have only one string we can form, which is the one we've already formed.
         * We need to return a set of everything we can make. That will be the set
         * that just consists of that one string.
         */
        return { chosen };
    } else {
        string remaining = str.substr(1);

        /* Our decision: do we include the first character, or do we exclude it?
         * Try both options, and gather the result together.
         */
        return subsetsRec(remaining, chosen + str[0]) +
               subsetsRec(remaining, chosen);
    }
}

HashSet<string> subsetsOf(const string& str) {
    return subsetsRec(str, "");
}


int main() {
    cout << "Let's list all subsets of {1, 2, 3}." << endl;
    listSubsetsOf({1, 2, 3});

    HashSet<string> subsets = subsetsOf("AHI");
    cout << "There are " << subsets.size() << " subsets of AHI." << endl;
    cout << "Here they are!" << endl;

    for (string subset: subsets) {
        cout << "  \"" << subset << "\"" << endl;
    }
    return 0;
}

