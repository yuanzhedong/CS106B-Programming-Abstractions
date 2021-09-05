#include <iostream>
#include "console.h"
using namespace std;

/* This forward declaration allows us to call cheer(3) from main, even
 * though at that point the function won't have been defined.
 */
void cheer(int numTimes);

int main() {
  cheer(3);
  return 0;
}

void cheer(int numTimes) {
  for (int i = 0; i < numTimes; i++) {
    cout << "Hip hip, hooray!" << endl;
  }
}
