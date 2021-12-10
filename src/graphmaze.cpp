#include "floodfill.h"

namespace FloodFill {
    void GraphMaze::initializeMaze(std::vector<std::vector<SquareType>> tiles, int size) {
        for (auto i(0); i < size; ++i)
            for (auto j(0); j < size; ++j)
                nodes[i][j].type = tiles[i][j];
    }
    
    bool GraphMaze::adjacentTo(int x, int y, SquareType tile) {
        if ((nodeExists(x,y-1) && nodes[x][y-1].type == tile) ||
            (nodeExists(x-1,y) && nodes[x-1][y].type == tile) || 
            (nodeExists(x+1,y) && nodes[x+1][y].type == tile) || 
            (nodeExists(x,y+1) && nodes[x][y+1].type == tile)) return true;

        return false;
    }

    std::pair<int, int> GraphMaze::lowerAdjacent(int x, int y) {
        int xlower = x, ylower = y;
        
        if (nodeExists(x,y-1) 
            && nodes[x][y-1].level < nodes[xlower][ylower].level
            && nodes[x][y-1].type == SquareType::PATH)
            ylower = y-1;
        
        if (nodeExists(x-1,y) 
            && nodes[x-1][y].level < nodes[xlower][ylower].level
            && nodes[x-1][y].type == SquareType::PATH)
            xlower = x-1;
        
        if (nodeExists(x+1,y) 
            && nodes[x+1][y].level < nodes[xlower][ylower].level
            && nodes[x+1][y].type == SquareType::PATH)
            xlower = x+1;
        
        if (nodeExists(x,y+1) 
            && nodes[x][y+1].level < nodes[xlower][ylower].level
            && nodes[x][y+1].type == SquareType::PATH)
            ylower = y+1;

        std::pair<int,int> result(xlower, ylower);
        return result;
    }

    std::vector<std::vector<SquareType>> GraphMaze::getMazeSolution(int xstart, int ystart) {
        std::vector<std::vector<SquareType>> maze(msize, std::vector<SquareType>(msize));
        for (auto i(0); i < msize; ++i)
            for (auto j(0); j < msize; ++j) 
                maze[i][j] = nodes[i][j].type;

        int x = xstart, y = ystart;
        while (!adjacentTo(x,y,SquareType::END)) {
            std::pair<int,int> xy = lowerAdjacent(x,y);
            x = xy.first;
            y = xy.second;
            maze[x][y] = SquareType::SOLUTION;
        }

        return maze;
    }
    
    void GraphMaze::markOffNodes() {
        for (auto i(0); i < msize; ++i)
            for (auto j(0); j < msize; ++j) {
                nodes[i][j].visited = false;
                nodes[i][j].level = -1;
            }
    }
    
    bool GraphMaze::nodeExists(int x, int y) {
        if (x < 0 || y < 0) return false;
        if (x >= msize || y >= msize) return false;

        return true;
    }
    
    void GraphMaze::DFSMaze(int x, int y) {
        markOffNodes();
        DFSMazeAux(x, y, nodes[x][y].level);
    }
    
    void GraphMaze::DFSMazeAux(int x, int y, int previousLevel) {
        nodes[x][y].level = previousLevel + 1;
        nodes[x][y].visited = true;

        // if the node is connected with the maze's start, don't continue
        if (nodes[x][y].type == SquareType::START) return;

        // north
        if (nodeExists(x,y-1)) {
            if ((nodes[x][y-1].type == SquareType::PATH || nodes[x][y-1].type == SquareType::START) 
                && (nodes[x][y-1].visited == false || (nodes[x][y].level + 1) < nodes[x][y-1].level))

                DFSMazeAux(x,y-1,nodes[x][y].level);
        }

        // west
        if (nodeExists(x-1,y)) {
            if ((nodes[x-1][y].type == SquareType::PATH || nodes[x-1][y].type == SquareType::START)
                && (nodes[x-1][y].visited == false  || (nodes[x][y].level + 1) < nodes[x-1][y].level))

                DFSMazeAux(x-1,y,nodes[x][y].level);
        }

        // east
        if (nodeExists(x+1,y)) {  
            if ((nodes[x+1][y].type == SquareType::PATH || nodes[x+1][y].type == SquareType::START)
                && (nodes[x+1][y].visited == false || (nodes[x][y].level + 1) < nodes[x+1][y].level))

                DFSMazeAux(x+1,y,nodes[x][y].level);
        }

        // south
        if (nodeExists(x,y+1)) { 
            if ((nodes[x][y+1].type == SquareType::PATH || nodes[x][y+1].type == SquareType::START)
                && (nodes[x][y+1].visited == false || (nodes[x][y].level + 1) < nodes[x][y+1].level))

                DFSMazeAux(x,y+1,nodes[x][y].level);
        }
    }
}

