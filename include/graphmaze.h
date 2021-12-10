#ifndef _GRAPHMAZE_H_
#define _GRAPHMAZE_H_

#include "floodfill.h"

namespace FloodFill {

    class GraphMaze {
        
        std::vector<std::vector<FloodFill::Square>> nodes;
        int msize;

        public:
            GraphMaze(int _msize) {
                this->msize = _msize;
                this->nodes = std::vector<std::vector<FloodFill::Square>> (_msize, std::vector<FloodFill::Square>(_msize));
            }

            void initializeMaze(std::vector<std::vector<SquareType>> tiles, int size);
            bool adjacentTo(int x, int y, SquareType tile);
            std::pair<int, int> lowerAdjacent(int x, int y);
            std::vector<std::vector<SquareType>> getMazeSolution(int xstart, int ystart);
            void markOffNodes();
            bool nodeExists(int x, int y);
            void DFSMaze(int x, int y);
            void DFSMazeAux(int x, int y, int previousLevel);
    };

}

#endif