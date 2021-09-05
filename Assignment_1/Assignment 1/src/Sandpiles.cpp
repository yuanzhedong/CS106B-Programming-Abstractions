/* File: Sandpile.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 */
#include "Sandpiles.h"
#include "Testing/SandpileTests.h"
using namespace std;

/* Function: dropSandOn
 * ----------------------
 * Takes a world, int and col as inputs. In the base case, if the cell where a grain of sand is being dropped on has lower than 3 grains there,
 * it simply adds one grain of sand. In case the cell does have 3 or more grains of sand, the function reinitializes that cell to 0 and then drops
 * a grain of sand in each of the surrounding cells by calling the dropSandOn function recursively.
 */

void dropSandOn(Grid<int>& world, int row, int col) {
    if (world.inBounds(row,col)) {
        if (world[row][col] < 3) {
            world[row][col] += 1;
        }
        else {
            world[row][col] = 0;
            dropSandOn(world, row, col+1);
            dropSandOn(world, row, col-1);
            dropSandOn(world, row+1, col);
            dropSandOn(world, row-1, col);
        }
    }
}

/* * * * * * Tests Below This Point * * * * * */

ADD_TEST("Dropping into an empty cell only changes that cell.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

ADD_TEST("Non-chaining topples work.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0 },
        { 1, 3, 1 },
        { 0, 2, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 2, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

ADD_TEST("Two topples chain.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

ADD_TEST("World is empty.") {
    /* Create a simple source grid */
    Grid<int> before = {};
    Grid<int> after = {};
    dropSandOn(before,0,0);
    EXPECT_EQUAL(before,after);
}

ADD_TEST("Out of bounds call") {
    Grid<int> before = {
        { 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3 },
    };

    dropSandOn(before,4,7);
    EXPECT_EQUAL(before,after);
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
