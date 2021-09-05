#include <iostream>
#include "console.h"
#include "vector.h"
#include "string.h"
#include "hashset.h"
using namespace std;

void main() {
    Vector<int> left = {1};
    Vector<int> right = {3, 5};
    int leftCounter = 0;
    int rightCounter = 0;
    Vector<int> mergedVec = {};
    while (leftCounter < left.size() || rightCounter < right.size()) {
        if (leftCounter == left.size()) {
            mergedVec += right[rightCounter];
            rightCounter++;
        } else if (left[leftCounter] < right[rightCounter]) {
            mergedVec += left[leftCounter];
            leftCounter++;
        } else {
            mergedVec += right[rightCounter];
            rightCounter++;
        }
    }
}

