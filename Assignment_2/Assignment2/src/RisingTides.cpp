#include "RisingTides.h"
#include "Testing/RisingTidesTests.h"
#include "queue.h"
using namespace std;

/* Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height) {
}
*/
double height = 3;
const Grid<double>& terrain = {
    {0, 0, 0},
    {1, 1, 1},
    {0, 1, 2}
};

void TestRun(const Vector<GridLocation>& sources) {
    Queue<GridLocation> loop;
    for (GridLocation i: sources) {
        if (terrain[i.row][i.col] <= height) {
            cout << i.row << endl;
        }
    }
}

