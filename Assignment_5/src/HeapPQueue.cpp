/* File: HeapPQueue.cpp
 * --------------------
 * This is the implementation of the HeapPQueue class. The HeapPQueue class is a queue that takes in DataPoints with weights, where the first element to come out
 * of the queue is the element with the smallest weight.
 */

#include "HeapPQueue.h"
#include "Testing/HeapTests.h"
#include "vector.h"
using namespace std;

/* Constant controlling the default size of our queue. */
const int kInitialSize = 4;

// Initialize a queue with a default initial size
HeapPQueue::HeapPQueue() {
    logicalSize = 0;
    allocatedSize = kInitialSize;
    elems = new DataPoint[allocatedSize];
}

// delete the HeapPQueue from memory
HeapPQueue::~HeapPQueue() {
    delete[] elems;
}

// enqueues a DataPoint. If the array is not large enough, it grows the space in memory. The function adds the DataPoint using the bubble-up method.
void HeapPQueue::enqueue(const DataPoint& data) {
    if (allocatedSize == logicalSize) {
        grow();
    }
    elems[logicalSize] = data;
    int lowerPos = logicalSize;
    int upperPos = (logicalSize + 1)/2 - 1;

    while (data.weight < elems[upperPos].weight && upperPos >= 0) {
        swap(elems[lowerPos], elems[upperPos]);
        lowerPos = upperPos;
        upperPos = (upperPos + 1)/2 - 1;
    }
    logicalSize++;
}

// returns the size of the heap
int HeapPQueue::size() const {
    return logicalSize;
}

// returns the first element in the array
DataPoint HeapPQueue::peek() const {
    if (isEmpty()) {
        error("HeapPQueue is empty");
    }
    return elems[0];
}

// Dequeues the DataPoint in the array with the smallest weight. It does so using the bubble-down method to maintain an ordered heap after dequeueing an element.
DataPoint HeapPQueue::dequeue() {
    DataPoint result = peek();
    logicalSize--;
    elems[0] = elems[logicalSize];
    // note that the calculations require the index of the heap to start at 1. However, the index of the array starts at 0. We calculate childOne and childTwo
    // accordingly to refer to the index of the heap.
    int position = 0;
    int childOne = 2*(position+1) - 1;
    int childTwo = 2*(position+1);
    // while the node has two children and the weight of both children is lower than the weight of the element, keep swapping
    while (logicalSize - 1 >= childTwo && (elems[position].weight > elems[childOne].weight || elems[position].weight > elems[childTwo].weight )) {
        // find which child has a lower weight and swap with that child. Then update the position and position of children
        if (elems[childOne].weight < elems[childTwo].weight) {
            swap(elems[position], elems[childOne]);
            position = childOne;
            childOne = 2*(position+1) - 1;
            childTwo = 2*(position+1);
        } else {
            swap(elems[position], elems[childTwo]);
            position = childTwo;
            childOne = 2*(position+1) - 1;
            childTwo = 2*(position+1);
        }
    }
    // if there is only one child in the node, swap with that child
    if (logicalSize - 1 == childOne) {
        if (elems[position].weight > elems[childOne].weight) {
            swap(elems[position], elems[childOne]);
        }
    }
    return result;
}

// isEmpty returns true if the heap is empty
bool HeapPQueue::isEmpty() const {
    return size() == 0;
}

// The function printDebugInfo prints out all of the elements in the queue
void HeapPQueue::printDebugInfo() {
    for (int i = 0; i < size(); i++ ) {
        cout << elems[i] << endl;
    }
}

/* Function: grow()
 * ------------------------
 * The function grow duplicates the size of the array by creating a new array that's twice as large and moving all of the elements
 * in the previous array into the new one
 */
void HeapPQueue::grow() {
    allocatedSize *= 2;
    DataPoint* newElems = new DataPoint[allocatedSize];
    for (int i = 0; i < logicalSize; i++) {
        newElems[i] = elems[i];
    }
    delete[] elems;
    elems = newElems;
}

/* * * * * * Test Cases Below This Point * * * * * */

ADD_TEST("User test: Enqueue and dequeue a heap when one of the nodes has a single child") {
    HeapPQueue pq;
    Vector<DataPoint> sequence = {
        { "A", 4 },
        { "B", 5 },
        { "C", 6 },
        { "D", 8 },
        { "E", 7 },
        { "F", 2 },
    };
    for (DataPoint elem: sequence) {
        pq.enqueue(elem);
    }
    EXPECT_EQUAL(pq.size(), sequence.size());
    Vector<DataPoint> solvedSequence = {
        { "F", 2 },
        { "A", 4 },
        { "B", 5 },
        { "C", 6 },
        { "E", 7 },
        { "D", 8 },
    };
    for (int i = 0; i < sequence.size(); i++) {
        auto elem = pq.dequeue();
        EXPECT_EQUAL(solvedSequence[i], elem);
    }
}

/* * * * * Provided Tests Below This Point * * * * */

ADD_TEST("Provided Test: Newly-created heap is empty.") {
    HeapPQueue pq;

    EXPECT(pq.isEmpty());
    EXPECT(pq.size() == 0);
}

ADD_TEST("Provided Test: Enqueue / dequeue single element") {
    HeapPQueue pq;
    DataPoint point = { "enqueue me!", 4 };
    pq.enqueue(point);
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.isEmpty(), false);

    EXPECT_EQUAL(pq.dequeue(), point);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);

    pq.enqueue(point);
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.isEmpty(), false);

    EXPECT_EQUAL(pq.dequeue(), point);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Dequeue / peek on empty heap throws error") {
    HeapPQueue pq;

    EXPECT(pq.isEmpty());
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());
}

ADD_TEST("Provided Test: Enqueue elements in sorted order.") {
    HeapPQueue pq;
    for (int i = 0; i < 10; i++) {
        pq.enqueue({ "elem" + to_string(i), i });
    }

    EXPECT_EQUAL(pq.size(), 10);
    for (int i = 0; i < 10; i++) {
        auto removed = pq.dequeue();
        DataPoint expected = {
            "elem" + to_string(i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Enqueue elements in reverse-sorted order.") {
    HeapPQueue pq;
    for (int i = 10; i >= 0; i--) {
        pq.enqueue({ "elem" + to_string(i), i });
    }

    EXPECT_EQUAL(pq.size(), 11);
    for (int i = 0; i <= 10; i++) {
        auto removed = pq.dequeue();
        DataPoint expected = {
            "elem" + to_string(i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Insert ascending and descending sequences.") {
    HeapPQueue pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ "a" + to_string(i), 2 * i });
    }
    for (int i = 19; i >= 0; i--) {
        pq.enqueue({ "b" + to_string(i), 2 * i + 1 });
    }

    EXPECT_EQUAL(pq.size(), 40);
    for (int i = 0; i < 40; i++) {
        auto removed = pq.dequeue();
        EXPECT_EQUAL(removed.weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Insert random permutation.") {
    Vector<DataPoint> sequence = {
        { "A", 0 },
        { "D", 3 },
        { "F", 5 },
        { "G", 6 },
        { "C", 2 },
        { "H", 7 },
        { "I", 8 },
        { "B", 1 },
        { "E", 4 },
        { "J", 9 },
    };

    HeapPQueue pq;
    for (DataPoint elem: sequence) {
        pq.enqueue(elem);
    }

    EXPECT_EQUAL(pq.size(), sequence.size());

    for (int i = 0; i < 10; i++) {
        auto removed = pq.dequeue();
        DataPoint expected = {
            string(1, 'A' + i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Insert duplicate elements.") {
    HeapPQueue pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ "a" + to_string(i), i });
    }
    for (int i = 19; i >= 0; i--) {
        pq.enqueue({ "b" + to_string(i), i });
    }

    EXPECT_EQUAL(pq.size(), 40);
    for (int i = 0; i < 20; i++) {
        auto one = pq.dequeue();
        auto two = pq.dequeue();

        EXPECT_EQUAL(one.weight, i);
        EXPECT_EQUAL(two.weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Handles data points with empty string name.") {
    HeapPQueue pq;
    for (int i = 0; i < 10; i++) {
        pq.enqueue({ "" , i });
    }
    EXPECT_EQUAL(pq.size(), 10);
}

ADD_TEST("Provided Test: Handles data points with negative weights.") {
    HeapPQueue pq;
    for (int i = -10; i < 10; i++) {
        pq.enqueue({ "" , i });
    }
    EXPECT_EQUAL(pq.size(), 20);
    for (int i = -10; i < 10; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
}

ADD_TEST("Provided Test: Interleave enqueues and dequeues.") {
    HeapPQueue pq;
    int n = 100;
    for (int i = n / 2; i < n; i++) {
        pq.enqueue({"", i});
    }
    EXPECT_EQUAL(pq.size(), 50);
    for (int i = n / 2; i < n; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);

    for (int i = 0; i < n / 2; i++) {
        pq.enqueue({"", i});
    }
    EXPECT_EQUAL(pq.size(), 50);
    for (int i = 0; i < n / 2; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
}

ADD_TEST("Provided Test: Stress test: cycle 250,000 elems (should take at most a few seconds)") {
    HeapPQueue pq;
    int n = 250000;
    for (int i = 0; i < n; i++) {
        pq.enqueue({ "", randomInteger(0, 100000) });
    }
    EXPECT_EQUAL(pq.size(), n);

    for (int i = 0; i < n; i++) {
        pq.dequeue();
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);

    for (int i = 0; i < n; i++) {
        pq.enqueue({ "", randomInteger(0, 100000) });
    }
    EXPECT_EQUAL(pq.size(), n);
}


ADD_TEST("Provided Test: Simple memory leak check.") {
    /* See how many unmatched allocations of DataPoint objects there are
     * before we perform any operations.
     */
    int allocationsBefore = netDataPointAllocations();

    HeapPQueue* pq = new HeapPQueue();
    delete pq;

    /* Net allocations now - net allocations at start = allocations leaked by
     * the HeapPQueue implementation. If this number is not zero, it might
     * indicate a memory leak.
     */
    int netAllocations = netDataPointAllocations() - allocationsBefore;
    EXPECT_EQUAL(netAllocations, 0);
}

ADD_TEST("Provided Test: More aggressive memory leak check.") {
    /* See how many unmatched allocations of DataPoint objects there are
     * before we perform any operations.
     */
    int allocationsBefore = netDataPointAllocations();

    HeapPQueue* pq = new HeapPQueue();

    /* Simulate a workflow on the priority queue. */
    for (int i = 0; i < 10000; i++) {
        pq->enqueue({ "", -i });
    }
    for (int i = 0; i < 5000; i++) {
        auto removed = pq->dequeue();
        removed.weight = -removed.weight;
        pq->enqueue(removed);
    }
    for (int i = 0; i < 9000; i++) {
        (void) pq->dequeue();
    }

    delete pq;

    /* Net allocations now - net allocations at start = allocations leaked by
     * the HeapPQueue implementation. If this number is not zero, it might
     * indicate a memory leak.
     */
    int netAllocations = netDataPointAllocations() - allocationsBefore;
    EXPECT_EQUAL(netAllocations, 0);
}
