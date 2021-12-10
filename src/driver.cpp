#include "floodfill.h"
#include <sstream>
#include <fstream>
#include <math.h>
#include <chrono>

using namespace FloodFill;
using namespace std;

int mainCanvas(int argc, char **argv);
int mainMaze(int argc, char **argv);

// main function that directs execution according to the flood fill approach
int main(int argc, char **argv) {  
    if (argc < 2) {
        printf("wrong arguments!");
        printf("\nyou need to inform the flood fill algorithm approach");
        printf("\n1 for paiting or 2 for maze");
        return EXIT_FAILURE;
    }

    int approach = atoi(argv[1]);

    if (approach == 1) return mainCanvas(argc, argv);
    if (approach == 2) return mainMaze(argc, argv);
    printf("you need to inform the flood fill algorithm approach");
    printf("\n1 for paiting or 2 for maze");
    return EXIT_FAILURE;
}

// flood fill algorithm based on canvas
int mainCanvas(int argc, char **argv) {
    if (argc != 7) {
        printf("six arguments are required:");
        printf("\n<type of flood fill approach [int]: 1 for painting>");
        printf("\n<size of canvas (a square) [int]>");
        printf("\n<X coordinate of clicked pixel [int]>");
        printf("\n<Y coordinate of clicked pixel [int]>");
        printf("\n<new color [int]>");
        printf("\n<input file name [string]>");
        return EXIT_FAILURE;
    }
    
    std::ifstream infile("./data_canvas/" + (string) argv[6]);
    if(infile.fail()){
        printf("%s does not exist", argv[6]);
        return EXIT_FAILURE;
    }

    const int csize = atoi(argv[2]);
    int px = atoi(argv[3]);
    int py = atoi(argv[4]);
    int newColor = atoi(argv[5]);

    std::vector<std::vector<int>> canvas(csize, std::vector<int>(csize));

    for (auto i(0); i < csize; ++i)
        for (auto j(0); j < csize; ++j)
            infile >> canvas[i][j];

    infile.close();

    GraphCanvas G(csize);
    G.initializeColors(canvas,csize);
    G.DFSPaint(px,py,newColor);
    canvas = G.getCanvas();

    std::ofstream outfile("./data_canvas/" + (string)argv[3] + '-' + (string)argv[4] + (string)argv[6]);
    for (auto i(0); i < csize; ++i) {
        for (auto j(0); j < csize; ++j)
            outfile << canvas[i][j] << " ";
        outfile << "\n";
    }

    outfile.close();

    return EXIT_SUCCESS;
}

// flood fill algorithm based on maze
int mainMaze(int argc, char **argv) {
    if (argc != 4) {
        printf("three arguments are required:");
        printf("\n<type of flood fill approach [int]: 2 for maze>");
        printf("\n<size of maze (a square) [int]>");
        printf("\n<input file name [string]>");
        return EXIT_FAILURE;
    }

    std::ifstream infile("./data_maze/" + (string) argv[3]);
    if(infile.fail()){
        printf("%s does not exist", argv[3]);
        return EXIT_FAILURE;
    }

    const int msize = atoi(argv[2]);
    int xend;
    int yend;
    int xstart;
    int ystart;

    std::vector<std::vector<SquareType>> maze(msize, std::vector<SquareType>(msize));

    for (auto i(0); i < msize; ++i)
        for (auto j(0); j < msize; ++j) {
            char temp;
            infile >> temp;

            if (temp == '.') maze[i][j] = SquareType::PATH;
            else if (temp == '#') maze[i][j] = SquareType::WALL;
            else if (temp == '@') {
                maze[i][j] = SquareType::START;
                xstart = i;
                ystart = j;
            } else if (temp == '$') {
                maze[i][j] = SquareType::END;
                xend = i;
                yend = j;
            } else {
                printf("%s has a unsupported maze", argv[3]);
                return EXIT_FAILURE;
            }
        }
    infile.close();

    GraphMaze G(msize);
    G.initializeMaze(maze,msize);
    G.DFSMaze(xend,yend);
    maze = G.getMazeSolution(xstart,ystart);
    
    std::ofstream outfile("./data_maze/out" + (string)argv[3]);
    for (auto i(0); i < msize; ++i) {
        for (auto j(0); j < msize; ++j) {
            char temp;
            
            if (maze[i][j] == SquareType::PATH) temp = '.';
            else if (maze[i][j] == SquareType::WALL) temp = '#';
            else if (maze[i][j] == SquareType::START) temp = '@';
            else if (maze[i][j] == SquareType::END) temp = '$';
            else if (maze[i][j] == SquareType::SOLUTION) temp = '*';

            outfile << temp << ' ';
        }
        outfile << "\n";
    }

    outfile.close();

    return EXIT_SUCCESS;
}