/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */

/* PUZZLE FOR SECTION LEADER
 * --------------------------
 * MMNT
 *
 * hint: memory
 */

#include "OnlyConnect.h"
#include "Testing/OnlyConnectTests.h"
#include <string>
#include "strlib.h"
using namespace std;

/* FUNCTION PROTOTYPES */
string getCons(char input);
string toString(char x);

/* RECURSIVE FUNCTION
 * Function: onlyConnectize
 * -------------------------
 * This function will take a string, remove all of the characters that are not consonants (excl. the letter y) and
 * return a string with the uppercase consonants of the original string. The program takes a base case in which if the
 * string is empty, it will return an empty string. It also includes a recursive part where getCons(phrase[0]) is
 * obtaining the first character of the phrase string, and if it is a consonant, returning the upper case version of that letter,
 * and if it is not a consonant, returning an empty string. The second part is a recursive call to the same function,
 * removing the first character from the string.
 */

string onlyConnectize(string phrase) {
    if (phrase == "") {
        return "";
    }
    else {
        return getCons(phrase[0]) + onlyConnectize(phrase.substr(1));
    }
}


/* Function: toString
 * -------------------
 * Takes a single character and returns an object of type string
 */

string toString(char x) {
    string s(1,x);
    return s;
}

/* Function: getCons
 * ---------------------
 * Verifies if the string is a consonant, if it is, returns the uppercase version of the consonant.
 * If it is not, returns an empty string
 */

string getCons(char input) {
    string cons = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
    if (cons.find(input) != string::npos) {
        int pos = cons.find(input);
        char ch = toUpperCase(cons[pos]);
        return toString(ch);
    }
    else {
        return "";
    }
}



/* * * * * * Test Cases * * * * * */

ADD_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

ADD_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

ADD_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

ADD_TEST("Handles extreme cases.") {
    EXPECT_EQUAL(onlyConnectize(""), "");
    EXPECT_EQUAL(onlyConnectize("{@hello w0rld}"), "HLLWRLD");
    EXPECT_EQUAL(onlyConnectize("           "), "");
    EXPECT_EQUAL(onlyConnectize(onlyConnectize(onlyConnectize("Chewbacca"))), "CHWBCC");
}


/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */






