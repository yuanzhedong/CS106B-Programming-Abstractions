/* File: Labyrinth.cpp
 * -----------------------
 * Given a maze and a set of directions, this file determines if there is any way to escape the maze whilst obtaining a spellbook,
 * wand and potion. The function isPathToFreedom is the main function, which calls on three helper functions:
 * validDirection - checks if the string contains only N, S, W and E
 * areTreasuresHere - checks to see if we captured all the treasures
 * doesPathExist - checks if we can follow the next path, or if it leads to a null pointer
 */

#include "Labyrinth.h"
#include "Demos/MazeGenerator.h"
#include "Testing/LabyrinthTests.h"
#include "hashset.h"
using namespace std;

bool validDirection(const string& directions);
bool areTreasuresHere(const HashSet<string>& treasures);
bool doesPathExist(MazeCell* start, char direction);

/* Function: isPathToFreedom
 * ---------------------------
 * Takes as inputs a pointer to a maze and a string with all of the moves the person will do. Returns true if that path is valid and if,
 * by the end of the path, all treasure items have been found. If the path is not valid or if the path doesn't pick up all treasure items,
 * it returns false.
 */
bool isPathToFreedom(MazeCell* start, const string& moves) {
    // if string contains an element that is not N, S, E or W, then return error
    if (!validDirection(moves)) {
        error("Not a valid direction");
    }
    // Initialize a container where we'll store the treasures we find
    HashSet<string> treasures;

    unsigned int numSteps = 0;
    while (start != nullptr && numSteps < moves.size()) {
        treasures.add(start->whatsHere);
        char direction = moves[numSteps];
        if(!doesPathExist(start, direction)) return false;

        if (direction == 'N') {
            start = start->north;
        }
        if (direction == 'S') {
            start = start->south;
        }
        if (direction == 'W') {
            start = start->west;
        }
        if (direction == 'E') {
            start = start->east;
        }
        numSteps++;
        }
    treasures.add(start->whatsHere);

    // Now we need to check if we picked up the three items
    return areTreasuresHere(treasures);
}

/* Function: validDirection
 * ----------------------------
 * Checks that the string of directions only contains the letters N, W, S or E. If any other characters are passed in, it returns false.
 */
bool validDirection(const string& directions) {
    for (char direction: directions) {
        if (direction != 'N' && direction != 'W' && direction != 'S' && direction != 'E') {
            return false;
        }
    }
    return true;
}

/* Function: areTreasuresHere
 * -----------------------------
 * Checks if all the treasures (Spellbook, Potion and Wand) are in the treasure chest
 */
bool areTreasuresHere(const HashSet<string>& chest) {
    return (chest.contains("Spellbook") && chest.contains("Potion") && chest.contains("Wand"));
}

/* Function: doesPathExist
 * -----------------------------
 * Given a position in the maze and a direction to follow, checks if the next step in the path is valid. If not, returns false.
 */
bool doesPathExist(MazeCell* start, char direction) {
    if (direction == 'N') {
        if (start->north == nullptr) return false;
    }
    if (direction == 'S') {
        if (start->south == nullptr) return false;
    }
    if (direction == 'W') {
        if (start->west == nullptr) return false;
    }
    if (direction == 'E') {
        if (start->east == nullptr) return false;
    }
    return true;
}

/* * * * * * Test Cases Below This Point * * * * * */

/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we delete maze, or empty maze, or something
     * along those lines?
     */
}

ADD_TEST("Provided Test: Checks paths in the sample maze.") {
    /* Make sure we don't leak any memory. */
    int allocs = instancesOf("MazeCell");

    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);

    EXPECT_EQUAL(allocs, instancesOf("MazeCell"));
}

ADD_TEST("Provided Test: Can't walk through walls.") {
    int allocs = instancesOf("MazeCell");

    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);

    EXPECT_EQUAL(allocs, instancesOf("MazeCell"));
}

ADD_TEST("Provided Test: Works when starting on an item.") {
    int allocs = instancesOf("MazeCell");

    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);

    EXPECT_EQUAL(allocs, instancesOf("MazeCell"));
}

ADD_TEST("Provided Test: Reports errors if given illegal characters.") {
    int allocs = instancesOf("MazeCell");

    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths contain characters that aren't even close to permissible. */
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Q"));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "X"));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "!"));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "?"));

    EXPECT_ERROR(isPathToFreedom(maze[0][0], "n"));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "s"));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "e"));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "w"));

    /* These are tricky - they're legal paths that happen to have an unexpected
     * character at the end.
     */
    EXPECT_ERROR(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWNQ"));
    EXPECT_ERROR(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES!!!"));
    EXPECT_ERROR(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES??"));

    deleteMaze(maze);

    EXPECT_EQUAL(allocs, instancesOf("MazeCell"));
}
