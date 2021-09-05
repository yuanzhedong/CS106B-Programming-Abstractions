#include "YouGotHufflepuff.h"
#include "Testing/YouGotHufflepuffTests.h"
using namespace std;

void administerQuiz(const HashSet<Question>& questions,
                    int numQuestions,
                    const HashSet<Person>& people) {
    /* TODO: Delete this comment and the next three lines, then implement this function. */
    (void) questions;
    (void) numQuestions;
    (void) people;
}


/* * * * *   Test Cases Below This Point   * * * * */

/* Because administerQuiz is a function that requires interaction with the user,
 * you won't be able to directly test that administerQuiz returns the correct
 * values. Similarly, you can't call the askPersonalityQuestion, displayScores,
 * or displayMessage functions, as those are wired into the demo and don't
 * work in testing.
 *
 * However, you are welcome to add test cases to test any helper functions you
 * write! To do so, use the ADD_TEST macro to define tests, just as you did in
 * Assignment 1 and for Rising Tides.
 *
 * You aren't required to include test cases in this part of the assignment,
 * though we definitely would encourage you to do so! This is a multistep
 * assignment that's going to require each individual function to work
 * correctly, and adding tests for the functions you write is a great way to
 * find and fix bugs early on.
 */

