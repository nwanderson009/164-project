#include "EightPuzzle.h"

string EightPuzzle::move(string start, char m)
{ // assumes start is a valid board state or is -1
	if (start == "-1")
		return "-1";

	int pos = start.find("0");
	int row = pos / 3;
	int col = pos % 3;
	string result = start;

	switch (m)
	{
	case 'u':
		if (row == 0)
			return "-1";
		result[pos] = result[pos - 3];
		result[pos - 3] = '0';
		return result;

	case 'd':
		if (row == 2)
			return "-1";
		result[pos] = result[pos + 3];
		result[pos + 3] = '0';
		return result;

	case 'l':
		if (col == 0)
			return "-1";
		result[pos] = result[pos - 1];
		result[pos - 1] = '0';
		return result;

	case 'r':
		if (col == 2)
			return "-1";
		result[pos] = result[pos + 1];
		result[pos + 1] = '0';
		return result;

	default:
		break;
	}

	return "-1"; // move was not a valid character
}

string EightPuzzle::reverseMove(string end, char m)
{
	switch (m)
	{
	case 'u':
		return move(end, 'd');
	case 'd':
		return move(end, 'u');
	case 'l':
		return move(end, 'r');
	case 'r':
		return move(end, 'l');
	default:
		break;
	}
	return "-1";
}

string EightPuzzle::moves(string ms)
{
	return moves(startState, ms);
}

string EightPuzzle::moves(string start, string ms)
{
	if (ms == "" || start == "-1") // if no more moves to make || invalid move was made, return
		return start;

	string result = start;
	for (char m : ms)
	{
		result = move(result, m);
	}

	return result;
}

bool EightPuzzle::isSolution(string ms)
{
	return moves(ms) == goalState;
}

int EightPuzzle::calcOutOfPlace(string s)
{
	int d = 0;
	for (auto c : { "0", "1", "2", "3", "4", "5", "6", "7", "8" })
	{
		int pos1 = s.find(c);
		int pos2 = goalState.find(c);
		if (pos1 != pos2)
		{
			d++;
		}
	}
	return d;
}

int EightPuzzle::calcManhattanDistance(string s) 
{
	int md = 0;
	for (auto c: { "0", "1", "2", "3", "4", "5", "6", "7", "8" })
	{
		int pos1 = s.find(c);
		int pos2 = goalState.find(c);
		md += abs(pos1 % 3 - pos2 % 3) + abs(pos1 / 3 - pos2 / 3);
	}
	return md;
}

EightPuzzle::EightPuzzle(string start, string goal)
{
	startState = start;
	goalState = goal;
}