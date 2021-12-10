#ifndef _GRAPHCANVAS_H_
#define _GRAPHCANVAS_H_

#include "floodfill.h"

namespace FloodFill {

    class GraphCanvas {
        
        std::vector<std::vector<FloodFill::Pixel>> nodes;
        int csize;

        public:
            GraphCanvas(int _csize) {
                this->csize = _csize;
                this->nodes = std::vector<std::vector<FloodFill::Pixel>> (_csize, std::vector<FloodFill::Pixel>(_csize));
            }

            void initializeColors(std::vector<std::vector<int>> colors, int size);
            std::vector<std::vector<int>> getCanvas();
            void markOffNodes();
            bool nodeExists(int x, int y);
            void DFSPaint(int x, int y, int newColor);
            void DFSPaintAux(int x, int y, int newColor);
    };

}

#endif