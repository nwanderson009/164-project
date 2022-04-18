#pragma once
#include <string>
#include <math.h>

using namespace std;
class EightPuzzle
{
public:
	string startState;
	string goalState;
	virtual int calcManhattanDistance(string s); // returns the MD of state s from goal state
	virtual int calcOutOfPlace(string s); // returns the out of place distance value from goal state
	virtual string move(string start, char m); // returns the result of move m from state start
	string reverseMove(string end, char m);  // returns the start state that results in state end with move m
	string moves(string ms); // returns result of set of moves ms on startState
	string moves(string start, string ms); // returns the result of set of moves ms on state start
	bool isSolution(string ms); // is set of moves ms a solution 
	EightPuzzle(string start, string goal);
	EightPuzzle() {};
};

