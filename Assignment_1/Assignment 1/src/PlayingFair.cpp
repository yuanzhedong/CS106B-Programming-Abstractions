/* File: PlayingFair.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 */
#include "PlayingFair.h"
#include "Testing/PlayingFairTests.h"
#include "error.h"
using namespace std;

/* Function: aSequenceOfOrder
 * --------------------------
 * Takes an integer n as input, and returns the sequence of As and Bs that correspond to the sequence where A is the first mover.
 * The first lines of the code handle exceptions when the inputs are negative numbers and return an error. The base case follows,
 * where in case the integer is 0, the sequence is just one move by A. The last line of the code calls two different recursive functions,
 * aSequenceOfOrder and bSequenceOfOrder, taking as input an integer that is one less than the original input.
 */

string aSequenceOfOrder(int n) {
    if (n < 0) {
        error("You shall not pass negative values!");
    }
    else if (n == 0) {
        return "A";
    }
    else {
        return aSequenceOfOrder(n-1) + bSequenceOfOrder(n-1);
    }
}


/* Function: bSequenceOfOrder
 * --------------------------
 * Takes an integer n as input, and returns the sequence of As and Bs that correspond to the sequence where B is the first mover.
 * The first lines of the code handle exceptions when the inputs are negative numbers and return an error. The base case follows,
 * where in case the integer is 0, the sequence is just one move by B. The last line of the code calls two different recursive functions,
 * aSequenceOfOrder and bSequenceOfOrder, taking as input an integer that is one less than the original input.
 */

string bSequenceOfOrder(int n) {
    if (n < 0) {
        error("You shall not pass negative values!");
    }
    else if (n == 0) {
        return "B";
    }
    else {
        return bSequenceOfOrder(n-1) + aSequenceOfOrder(n-1);
    }
}

/* * * * * * Tests Below This Point * * * * * */

ADD_TEST("Sequences of order 3 are correct.") {
    /* Some very basic checks. */
    EXPECT_EQUAL(aSequenceOfOrder(3), "ABBABAAB");
    EXPECT_EQUAL(bSequenceOfOrder(3), "BAABABBA");
}

ADD_TEST("Only characters should be As and Bs.") {
    for (int i = 0; i < 10; i++) {
        for (char ch: aSequenceOfOrder(i)) {
            EXPECT(ch == 'A' || ch == 'B');
        }
    }
}

ADD_TEST("A-sequence of positive order should have equal As and Bs.") {
    /* Exclude the sequence of order 0, which is just a single character. */
    for (int i = 1; i < 10; i++) {
        int as = 0;
        int bs = 0;
        for (char ch: aSequenceOfOrder(i)) {
            if (ch == 'A') as++;
            else bs++;
        }

        EXPECT_EQUAL(as, bs);
    }
}

ADD_TEST("Triggers error on negative inputs.") {
    /* The EXPECT_ERROR macro expects the given expression to call error(). Remember that
     * you need to guard against invalid inputs.
     */
    EXPECT_ERROR(aSequenceOfOrder(-137));
    EXPECT_ERROR(bSequenceOfOrder(-137));
}

ADD_TEST("Sequences of order 0 are correct") {
    EXPECT_EQUAL(aSequenceOfOrder(6 % 3), "A");
    EXPECT_EQUAL(bSequenceOfOrder(0), "B");
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

