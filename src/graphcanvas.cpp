#include "floodfill.h"

namespace FloodFill {
    
    void GraphCanvas::initializeColors(std::vector<std::vector<int>> colors, int size) {
        for (auto i(0); i < size; ++i)
            for (auto j(0); j < size; ++j) 
                nodes[i][j].color = colors[i][j];
    }

    std::vector<std::vector<int>> GraphCanvas::getCanvas() {
        std::vector<std::vector<int>> canvas(csize, std::vector<int>(csize));
        for (auto i(0); i < csize; ++i)
            for (auto j(0); j < csize; ++j) 
                canvas[i][j] = nodes[i][j].color;

        return canvas;
    }

    void GraphCanvas::markOffNodes() {
        for (auto i(0); i < csize; ++i)
            for (auto j(0); j < csize; ++j) 
                nodes[i][j].visited = false;
    }

    bool GraphCanvas::nodeExists(int x, int y) {
        if (x < 0 || y < 0) return false;
        if (x >= csize || y >= csize) return false;

        return true;
    }

    void GraphCanvas::DFSPaint(int x, int y, int newColor) {
        markOffNodes();
        DFSPaintAux(x, y, newColor);
    }

    void GraphCanvas::DFSPaintAux(int x, int y, int newColor) {
        nodes[x][y].visited = true;
        
        // north
        if (nodeExists(x,y-1)) {    
            if (nodes[x][y-1].visited == false && nodes[x][y].color == nodes[x][y-1].color)
                DFSPaintAux(x,y-1,newColor);
        }

        // west
        if (nodeExists(x-1,y)) {    
            if (nodes[x-1][y].visited == false && nodes[x][y].color == nodes[x-1][y].color)
                DFSPaintAux(x-1,y,newColor);
        }

        // east
        if (nodeExists(x+1,y)) {    
            if (nodes[x+1][y].visited == false && nodes[x][y].color == nodes[x+1][y].color)
                DFSPaintAux(x+1,y,newColor);
        }

        // south
        if (nodeExists(x,y+1)) {    
            if (nodes[x][y+1].visited == false && nodes[x][y].color == nodes[x][y+1].color)
                DFSPaintAux(x,y+1,newColor);
        }

        nodes[x][y].color = newColor;
    }
}
