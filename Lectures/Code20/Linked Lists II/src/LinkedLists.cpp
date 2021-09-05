/*************************************************
 * File: LinkedLists.cpp
 *
 * Our very second program using Linked Lists! :-D
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Type: Cell
 *
 * A cell in a linked list.
 */
struct Cell {
	string value;
	Cell* next;
};

/* Given a linked list, returns the length of that list. */
int lengthOf(Cell* list) {
    int result = 0;
    while (list != nullptr) {
        result++;
        list = list->next;
    }
    return result;
}

/* Prints the contents of a linked list, in order. */
void printList(Cell* list) {
    while (list != nullptr) {
        cout << list->value << endl;
        list = list->next;
    }
}

/* Frees all the memory used by a linked list. */
void deleteList(Cell* list) {
    while (list != nullptr) {
        /* Store where to go next, since we're about to blow up our linked
         * list cell.
         */
        Cell* next = list->next;
        delete list;
        list = next;
    }
}

/* Reads a linked list from the user one element at a time, stopping when
 * the user enters an empty list. This returns the list, constructed in
 * reverse order.
 */
Cell* readList() {
    Cell* result = nullptr;
    while (true) {
        string line = getLine("Next item: ");
        if (line == "") break;

        Cell* cell = new Cell;
        cell->value = line;

        cell->next = result;
        result = cell;
    }
    return result;
}

int main() {
    Cell* list = readList();

    cout << "This list contains " << lengthOf(list) << " cells." << endl;
    printList(list);
    deleteList(list);

    return 0;
}
