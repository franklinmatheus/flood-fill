#ifndef _SQUARE_H_
#define _SQUARE_H_

namespace FloodFill {
    typedef enum {
        WALL,
        PATH,
        START,
        END,
        SOLUTION
    } SquareType;

    struct Square {
        SquareType type = SquareType::PATH;
        int level = -1;
        bool visited = false;
    };
}

#endif