// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "maze.h"
#include "mazegraphics.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "vector.h"
#include "SimpleTest.h"
#include "mazegraphics.h"

using namespace std;


/* Given a maze represented as a Grid<bool> and a current location cur,
 * this function returns a Set of all valid next moves (GridLocations)
 * that can be reached by taking one step in the four cardinal directions
 * (north, south, east, or west).
 *
 * A move is considered valid if:
 * - It is within the bounds of the grid.
 * - It leads to an open corridor (i.e. maze[location] == true).
 * The function constructs a list of the four possible neighboring locations,
 * checks whether each one is in bounds and open, and if so, adds it to
 * the  result set.
 */
Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {
    Set<GridLocation> neighbors;
    /* TODO: Fill in the remainder of this function. */


    GridLocation above = {cur.row - 1, cur.col};
    GridLocation below = {cur.row + 1, cur.col};
    GridLocation left  = {cur.row, cur.col - 1};
    GridLocation right = {cur.row, cur.col + 1};
    Set<GridLocation> directions = {above, below, left, right};

    for (GridLocation currloc : directions) {
        if (maze.inBounds(currloc) && maze[currloc]) {
            neighbors.add(currloc);
        }
    }

    return neighbors;
}
/*
 * This function checks whether a given path is a valid solution through a maze.

 * A valid path must satisfy the following conditions:
 * - The path is not empty.
 * - The first location in the path is the maze entry at (0, 0).
 * - The last location in the path is the maze exit at (maze.numRows() - 1, maze.numCols() - 1).
 * - All moves from one location to the next are valid (within bounds, not a wall, and one step in cardinal direction).
 * - No location appears more than once in the path (no loops).
 *If all conditions are met, the function completes without error.
 * The function uses the helper function `generateValidMoves` to determine legal steps from
 * each position in the path and a Set to track visited locations.
 */
void validatePath(Grid<bool>& maze, Vector<GridLocation>& path) {
    if (path.isEmpty()) {
        error("Path is empty!");
    }
    /* TODO: Fill in the remainder of this function. */
    if (path[0] != GridLocation{0, 0}) {
        error(" Should start from (0, 0)！");
    }
    /* If you find a problem with the path, call error() to report it.
     * If the path is a valid solution, then this function should run to completion
     * without raising any errors.
     */

    GridLocation mazeExit = {maze.numRows() - 1, maze.numCols() - 1};
    if (path[path.size() - 1] != mazeExit) {
        error("Not vaild exit path！");

    }
    for (int i = 0; i < path.size() - 1; i++) {
        Set<GridLocation> validMoves = generateValidMoves(maze, path[i]);
        if (!validMoves.contains(path[i + 1])) {
            error("Path includes Not vaild move！");
        }
    }
    Set<GridLocation> seen;
    for (GridLocation loc : path) {
        if (seen.contains(loc)) {
            error("Contain a loop！");
        }
        seen.add(loc);
    }

}



// a BFS traversal where each element in the BFS
/* queue is a path (a vector of GridLocations) representing a route from the start
 position to a current location.
At each step, the function dequeues the current path, explores all valid moves
*  up/down/left/right from the current end of the path.
* If the goal is reached, it assigns the full path to soln and returns true. */
bool solveMazeBFS(Grid<bool>& maze, Vector<GridLocation>& soln) {
    initGraphicsForMaze(maze, true);
    Queue<Vector<GridLocation>> allPaths;
    /* TODO: Fill in the remainder of this function. */
    Set<GridLocation> visited;
    GridLocation start = {0, 0};

    //Create a length-one path containing just the entry location. Enqueue that path.
    GridLocation end = {maze.numRows() - 1, maze.numCols() - 1};
    cout << "Start: " << start << ", End: " << end << endl;

    if (start == end && maze.get(start)) {
        soln.add(start);
        cout << "Start equals end and is open. Solution: " << start << endl;
        return true;
    }
    if (!maze.get(start)) return false;

    Vector<GridLocation> startPath = {start};
    allPaths.enqueue(startPath);
    visited.add(start);

    while (!allPaths.isEmpty()) {
        cout << "Allpaths: " << allPaths << endl;
        Vector<GridLocation> currentPath = allPaths.dequeue();


        GridLocation curr = currentPath[currentPath.size() - 1];
        highlightPath(currentPath, "blue");

        cout << "Dequeued path: ";
        for (auto& loc : currentPath) cout << loc << " ";
        cout << endl;
        if (curr == end) {
            soln = currentPath;
            highlightPath(soln, "green");

            return true;
        }

        for (GridLocation neighbor : generateValidMoves(maze, curr)) {

            if (!visited.contains(neighbor)) {
                visited.add(neighbor);
                Vector<GridLocation> newPath = currentPath;
                newPath.add(neighbor);
                allPaths.enqueue(newPath);
            }
        }
    }

    return false;
}

// Solves a maze using Depth-First Search (DFS) algorithm
//Using a stack to explore paths (LIFO order)
// Tracking visited locations to avoid cycles
// Validating moves through generateValidMoves()
bool solveMazeDFS(Grid<bool>& maze, Vector<GridLocation>& soln) {
    Stack<Vector<GridLocation>> allPaths;

        initGraphicsForMaze(maze, true);

        /* TODO: Fill in the remainder of this function. */
        Set<GridLocation> visited;
        GridLocation start = {0, 0};

        //Create a length-one path containing just the entry location. Enqueue that path.
        GridLocation end = {maze.numRows() - 1, maze.numCols() - 1};
        cout << "Start: " << start << ", End: " << end << endl;

        if (start == end && maze.get(start)) {
            soln.add(start);
            cout << "Start equals end and is open. Solution: " << start << endl;
            return true;
        }
        if (!maze.get(start)) return false;

        Vector<GridLocation> startPath = {start};
        allPaths.push(startPath);
        visited.add(start);

        while (!allPaths.isEmpty()) {
            cout << "Allpaths: " << allPaths << endl;
            Vector<GridLocation> currentPath = allPaths.pop();


            GridLocation curr = currentPath[currentPath.size() - 1];
            highlightPath(currentPath, "blue");

            cout << "Dequeued path: ";
            for (auto& loc : currentPath) cout << loc << " ";
            cout << endl;
            if (curr == end) {
                soln = currentPath;
                highlightPath(soln, "green");

                return true;
            }

            for (GridLocation neighbor : generateValidMoves(maze, curr)) {

                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    Vector<GridLocation> newPath = currentPath;
                    newPath.add(neighbor);
                    allPaths.push(newPath);
                }
            }
        }

        return false;
    }


/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readMazeFile(string filename, Grid<bool>& maze) {
    /* The following code reads data from the file into a Vector
     * of strings representing the lines of the file.
     */
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines = readLines(in);

    /* Now that the file data has been read into the Vector, populate
     * the maze grid.
     */
    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        if (lines[r].length() != numCols) {
            error("Maze row has inconsistent number of columns");
        }
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                error("Maze location has invalid character: '" + charToString(ch) + "'");
            }
        }
    }
    if (!maze[0][0] || !maze[numRows-1][numCols-1]) {
        error("Maze entrance and exit must be both be open corridors");
    }
}

/* The given readSolutionFile correctly reads a path from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readSolutionFile(string filename, Vector<GridLocation>& soln) {
    ifstream in;

    if (!openFile(in, filename)) {
        error("Cannot open file named " + filename);
    }

    if (!(in >> soln)) {// if not successfully read
        error("Maze solution did not have the correct format.");
    }
}


/* * * * * * Test Cases * * * * * */

// TODO: add your STUDENT_TEST test cases here!

STUDENT_TEST("solveMazeDFS on file 3x3") {
    Grid<bool> maze;
    readMazeFile("res/3x3.maze", maze);
    Vector<GridLocation> soln;
    initGraphicsForMaze(maze, true); //optional, you can remove this line if you do not wish to animate
    EXPECT(solveMazeDFS(maze, soln));
    EXPECT_NO_ERROR(validatePath(maze, soln));
}

STUDENT_TEST("solveMazeDFS: on file 2x2") {
    Grid<bool> maze;
    readMazeFile("res/1_copy.maze", maze);
    Vector<GridLocation> soln;
    initGraphicsForMaze(maze, true);
    EXPECT(solveMazeDFS(maze, soln));
    EXPECT_NO_ERROR(validatePath(maze, soln));
}
STUDENT_TEST("solveMazeBFS on file 2x2") {
    Grid<bool> maze;
    readMazeFile("res/1_copy.maze", maze);
    Vector<GridLocation> soln;
    initGraphicsForMaze(maze, true);
    EXPECT(solveMazeBFS(maze, soln));
    EXPECT_NO_ERROR(validatePath(maze, soln));
}
STUDENT_TEST("solveMazeBFS on file 3x3") {
    Grid<bool> maze;
    readMazeFile("res/3x3.maze", maze);
    Vector<GridLocation> soln;
    initGraphicsForMaze(maze, true);
    EXPECT(solveMazeBFS(maze, soln));
    EXPECT_NO_ERROR(validatePath(maze, soln));
}

STUDENT_TEST("generateValidMoves from edge cell with some walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, false, true},
                       {true, true, true}};
    GridLocation start = {1, 0};
    Set<GridLocation> expected = {{0, 0}, {2, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, start), expected);
}

STUDENT_TEST("generateValidMoves from top-left corner (0, 0) with open space") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation start = {0, 0};
    Set<GridLocation> expected = {{0, 1}, {1, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, start), expected);
}
STUDENT_TEST("generateValidMoves from center surrounded by walls") {
    Grid<bool> maze = {{true, false, true},
                       {false, true, false},
                       {true, false, true}};
    GridLocation start = {1, 1};
    Set<GridLocation> expected = {};

    EXPECT_EQUAL(generateValidMoves(maze, start), expected);
}

STUDENT_TEST("Test for validatePath1: validatePath rejects empty path") {
    Grid<bool> maze = {
        {true, true},
        {true, true}
    };
    Vector<GridLocation> path;
    EXPECT_ERROR(validatePath(maze, path));
}

STUDENT_TEST("Test for validatePath2: validatePath accepts valid path") {
    Grid<bool> maze = {
        {true, true},
        {false, true}
    };
    Vector<GridLocation> path = {
        {0, 0},
        {0, 1},
        {1, 1}
    };
    EXPECT_NO_ERROR(validatePath(maze, path));
}



STUDENT_TEST("Test for validatePath 3:validatePath rejects path with illegal jump") {
    Grid<bool> maze = {
        {true, true, true},
        {true, false, true},
        {true, true, true}
    };
    Vector<GridLocation> path = {
        {0, 0},
        {0, 1},
        {0, 2},
        {2, 2}
    };
    EXPECT_ERROR(validatePath(maze, path));
}

STUDENT_TEST("validatePath should error when path contains a loop in 4x4 maze") {
    Grid<bool> maze = {
        {true,  false,  false,  true},
        {true,  true, true,  true},
        {true,  true,  true, true},
        {false,  true,  true,  true}
    };

    Vector<GridLocation> path = {
        {0, 0},  // start
        {1, 0},
        {2, 0},
        {2, 1},
        {1, 1},
        {1, 2},
        {2, 2},
        {2, 1},  // repeated: loop
        {3, 1},
        {3, 2},
        {3, 3}
    };

    EXPECT_ERROR(validatePath(maze, path));
}
/* Please not add/modify/remove the PROVIDED_TEST entries below.
 * Place your student tests cases above the provided tests.
 */

PROVIDED_TEST("generateValidMoves on location in the center of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation center = {1, 1};
    Set<GridLocation> expected = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
}

PROVIDED_TEST("generateValidMoves on location on the side of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation side = {0, 1};
    Set<GridLocation> expected = {{0, 0}, {0, 2}, {1, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, side), expected);
}

PROVIDED_TEST("generateValidMoves on corner of 2x2 grid with walls") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    GridLocation corner = {0, 0};
    Set<GridLocation> expected = {{1, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}

PROVIDED_TEST("validatePath on correct solution, hand-constructed maze") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Vector<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution read from file, medium maze") {
    Grid<bool> maze;
    Vector<GridLocation> soln;
    readMazeFile("res/5x7.maze", maze);
    readSolutionFile("res/5x7.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on invalid path should raise error") {
    Grid<bool> maze = {{true, false},
                       {true, true},
                       {true, true}};
    Vector<GridLocation> notBeginAtEntry = { {1, 1}, {2, 1} };
    Vector<GridLocation> notEndAtExit = { {0, 0}, {1, 0}, {2, 0} };
    Vector<GridLocation> moveThroughWall = { {0 ,0}, {0, 1}, {1, 1}, {2, 1} };

    EXPECT_ERROR(validatePath(maze, notBeginAtEntry));
    EXPECT_ERROR(validatePath(maze, notEndAtExit));
    EXPECT_ERROR(validatePath(maze, moveThroughWall));
}

PROVIDED_TEST("solveMazeBFS on file 5x7") {
    Grid<bool> maze;
    readMazeFile("res/5x7.maze", maze);
    Vector<GridLocation> soln;
    initGraphicsForMaze(maze, true); //optional, you can remove this line if you do not wish to animate
    EXPECT(solveMazeBFS(maze, soln));
    EXPECT_NO_ERROR(validatePath(maze, soln));
}


PROVIDED_TEST("solveMazeDFS on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Vector<GridLocation> soln;
    initGraphicsForMaze(maze, true); //optional, you can remove this line if you do not wish to animate
    EXPECT(solveMazeDFS(maze, soln));
    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("Attempt to solve maze with no solution") {
    Grid<bool> maze(4, 4, false); // all grid elements initialized to false (walls)
    maze[0][0] = maze[3][3] = true; // set entrance and exit to true (open corridors)
    Vector<GridLocation> soln;
    EXPECT(!solveMazeBFS(maze, soln));
    EXPECT(!solveMazeDFS(maze, soln));
}
