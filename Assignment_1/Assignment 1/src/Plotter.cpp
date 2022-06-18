#include "Plotter.h"
#include "strlib.h"
#include <iostream>
using namespace std;

void runPlotterScript(istream& input) {
    float current_x = 0, current_y = 0;
    bool pen_down = false;
    auto style = PenStyle{ 4, "black" };
    for(string line; getline(input, line); ) {
        cout << line << endl;
        Vector<string> tokens = stringSplit(line, " ");
        if (toLowerCase(tokens[0]) == "moveabs") {
            float target_x = stringToReal(tokens[1]);
            float target_y = stringToReal(tokens[2]);
            if (pen_down) {
                drawLine(current_x, current_y, target_x, target_y, style);
            }
            current_x = target_x;
            current_y = target_y;
        }
         if (toLowerCase(tokens[0]) == "pendown") {
             pen_down = true;
         }
         if (toLowerCase(tokens[0]) == "penup") {
             pen_down = false;
         }
         if (toLowerCase(tokens[0]) == "moverel") {
             float delta_x = stringToReal(tokens[1]);
             float delta_y = stringToReal(tokens[2]);
             if (pen_down) {
                 drawLine(current_x, current_y, current_x + delta_x, current_y + delta_y, style);
             }
             current_x += delta_x;
             current_y += delta_y;
         }
         if (toLowerCase(tokens[0]) == "pencolor") {
             auto col = tokens[1];
             style.color = col;
         }
         if (toLowerCase(tokens[0]) == "penwidth") {
             auto wid = stringToReal(tokens[1]);
             style.width = wid;
         }
        }
    /*
    PenStyle style = { 4, "black" }; // Pen style is initialized
    drawLine(0.5, 0.5, 0.1, 0.2, style);
    PenStyle style_dos = { 2, "#FF0000" }; // Pen style is initialized
    drawLine(0.2, 0.3, 0.7, 0.9, style_dos);
    PenStyle style_tres = { -5, "#FF0000" }; // Pen style is initialized
    drawLine(0.4, 0.4, -0.6, 0.9, style_tres);
    */
}

/* FUNCTIONS THAT WE HAVE TO DEFINE
 * --------------------------------
 * We'll need to define the current coordinate set at all times as: current_x, current_y
 * PenDown and PenUp --> when one of these is called, we'll change the width attribute of PenStyle. A width attribute of -5 is sufficient for
 *                       PenUp.
 * MoveAbs --> this will take the form of drawLine(current_x, current_y, new_x, new_y, PenStyle)
 * MoveRel --> This will take the form of drawLine(current_x, current_y, current_x + change_x, current_y + change_y)
 * Lets first start by reading the lines in a file
 */

