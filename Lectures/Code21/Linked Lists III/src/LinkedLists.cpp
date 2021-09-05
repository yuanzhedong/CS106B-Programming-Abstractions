/*************************************************
 * File: LinkedLists.cpp
 *
 * Our very third program using Linked Lists! :-D
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

/* From last time! */
void printList(Cell* list) {
    while (list != nullptr) {
        cout << list->value << endl;
        list = list->next;
    }
}

/* From last time! */
void deleteList(Cell* list) {
    while (list != nullptr) {
        Cell* next = list->next;
        delete list;
        list = next;
    }
}

/* Question to ponder: Why do we take this list parameter by reference? */
void prependTo(Cell*& list, const string& value) {
    Cell* cell = new Cell;
    cell->value = value;

    /* Question to ponder: What happens if we swap these next two lines? */
    cell->next = list;
    list = cell;
}

/* Appends to a linked list represented as a pair of a head and tail pointer. */
void appendTo(Cell*& head, Cell*& tail, const string& value) {
    /* New cell goes at the end of the list. */
    Cell* cell = new Cell;
    cell->value = value;
    cell->next = nullptr;

    if (head == nullptr) {
        head = tail = cell;
    } else {
        /* Question to ponder: Why are both of these lines necessary? */
        tail->next = cell;
        tail = cell;
    }
}

int main() {
    Cell* head = nullptr;
    Cell* tail = nullptr;

    appendTo(head, tail, "Quokka");
    appendTo(head, tail, "Pudu");
    appendTo(head, tail, "Dikdik");

    printList(head);
    deleteList(head);
    return 0;
}




