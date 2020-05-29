/**
 * File: life.cpp
 * --------------
 * Implements the Game of Life.
 */

#include <iostream>  // for cout
#include "simpio.h"
using namespace std;

#include "console.h" // required of all files that contain the main function
/**
 * Function: welcome
 * -----------------
 * Introduces the user to the Game of Life and its rules.
 */
static void welcome() {
    cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells live and die by the following rules:" << endl << endl;
    cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
    cout << "\tLocations with 2 neighbors remain stable" << endl;
    cout << "\tLocations with 3 neighbors will spontaneously create life" << endl;
    cout << "\tLocations with 4 or more neighbors die of overcrowding" << endl << endl;
    cout << "In the animation, new cells are dark and fade to gray as they age." << endl << endl;
    getLine("Hit [enter] to continue....   ");
}

/**
 * Function: main
 * --------------
 * Provides the entry point of the entire program.
 */
#include "simpio.h"  // for getLine
#include "gevents.h" // for mouse event detection
#include "strlib.h"
#include "random.h" // for random number
#include <fstream> // for reading the file
#include "life-constants.h"  // for kMaxAge
#include "life-graphics.h"   // for class LifeDisplay
#include "grid.h" // for printing cells

void getRowsAndCols (int& rows, int& cols, ifstream& infile);
void randRowsAndCols (int& rows, int& cols);
void fileRowsAndCols (ifstream& infile, int& rows, int& cols);
Grid<int> extractCellsFromFile (int& rows, int& cols, ifstream& infile);
void drawCells (Grid<int>& cells, int& rows, int& cols, LifeDisplay& display);

int main() {
    LifeDisplay display;
    display.setTitle("Game of Life");
    welcome();
    int rows, cols;
    Grid<int> cells;
    ifstream infile;
    getRowsAndCols(rows, cols, infile);
    display.setDimensions(rows, cols);
    cells = extractCellsFromFile (rows, cols, infile);
    drawCells (cells, rows, cols, display);
    display.repaint();
    getLine("baobao chou!!!!");
    return 0;
}

void getRowsAndCols(int& rows, int& cols, ifstream& infile) {
    cout << "You can start your colony with random cells or read from a prepared file." << endl;
    string fileName = getLine("Enter name of colony file (or RETURN to seed randomly):");
    while  (true) {
        if (fileName == "") {
            randRowsAndCols(rows, cols);
            break;
        }
        fileName = "files/" + fileName;
        infile.open(fileName.c_str());
        if (!infile.fail()) {
            fileRowsAndCols (infile, rows, cols);
            break;
        }
        infile.clear();
        cout << "Unable to open the file named \"" << fileName << "\". Try again." << endl;
        fileName = getLine("Enter name of colony file (or RETURN to seed randomly):");
    }
}
void randRowsAndCols (int& rows, int& cols) {
     rows = randomInteger(40, 60);
     cols = randomInteger(40, 60);
     rows = 2;
     cols = 2;
}
void fileRowsAndCols (ifstream& infile, int& rows, int& cols) {
    while (!infile.eof()) {
        string line;
        getline(infile, line);
        if (!startsWith(line,"#")){
           rows = stringToInteger(line);
           getline(infile, line);
           cols = stringToInteger(line);
           break;
        }
    }
}

Grid<int> extractCellsFromFile (int& rows, int& cols, ifstream& infile) {
    Grid<int> cells(rows, cols);
    int i;
    for (i=0; i<rows; i++) {
        string line;
        getline(infile, line);
        int j; char value;
        for (j=0; j<cols; j++) {
             value = line[j];
             if (value=='-') {
                 cells.set(i,j,0);
             } else {
                 cells.set(i,j,1);
             }
        }
        cout << i << endl;
        cout << line << endl;
     }
     return cells;
 }


void drawCells (Grid<int>& cells, int& rows, int& cols, LifeDisplay& display) {
    int i, j, cellValue;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            cellValue=cells.get(i,j);
            display.drawCellAt(i,j,cellValue);
        }
    }
}
