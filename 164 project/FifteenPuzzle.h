#pragma once
#include "EightPuzzle.h"
class FifteenPuzzle :
    public EightPuzzle
{
public:
    virtual int calcManhattanDistance(string s); // redefined because of bigger board
    virtual int calcOutOfPlace(string s); // redefined because of bigger board 
    virtual string move(string start, char m); // redefined because of bigger board
    FifteenPuzzle(string start, string goal);
};

