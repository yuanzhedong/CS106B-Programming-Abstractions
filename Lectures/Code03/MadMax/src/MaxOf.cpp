/* File: MaxOf.cpp
 *
 * A program showing off several ways to find the maximum element of a Vector.
 */
#include <iostream>
#include <algorithm>
#include "vector.h"
#include "console.h"
using namespace std;

int maxOf(Vector<int> elems);

int main() {
    Vector<int> v = { 137, 106, 107, 166, 103, 261, 109 };
    cout << maxOf(v) << endl;
    return 0;
}

/* Returns the maximum value in a Vector<int>. This is one of two
 * implementations we discussed in class.
 *
 * Great exercise: add in another base case that calls error()
 * in the event that the vector is empty.
 */
int maxOf(Vector<int> elems) {
    /* Base case: If there is exactly one element of the Vector, it's the
     * largest element.
     */
    if (elems.size() == 1) {
        return elems[0];
    }
    /* Recursive case: Split the vector in half. Find the maximum value of
     * each subvector, then return the larger of the two.
     * 
     * Can you explain how this is similar to an elimination tournament?
     */
    else {
        int half = elems.size() / 2;
        Vector<int> left  = elems.subList(0, half);
        Vector<int> right = elems.subList(half);
        return max(maxOf(left), maxOf(right));
    }
}
