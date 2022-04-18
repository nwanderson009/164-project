#include "FifteenPuzzle.h"

string FifteenPuzzle::move(string start, char m)
{ // assumes start is a valid board state or is -1
	if (start == "-1")
		return "-1";

	int pos = start.find("0");
	int row = pos / 4;
	int col = pos % 4;
	string result = start;

	switch (m)
	{
	case 'u':
		if (row == 0)
			return "-1";
		result[pos] = result[pos - 4];
		result[pos - 4] = '0';
		return result;
	
	case 'd':
		if (row == 3)
			return "-1";
		result[pos] = result[pos + 4];
		result[pos + 4] = '0';
		return result;

	case 'l':
		if (col == 0)
			return "-1";
		result[pos] = result[pos - 1];
		result[pos - 1] = '0';
		return result;

	case 'r':
		if (col == 3)
			return "-1";
		result[pos] = result[pos + 1];
		result[pos + 1] = '0';
		return result;

	default:
		break;
	}

	return "-1"; // move was not a valid character
}

int FifteenPuzzle::calcOutOfPlace(string s)
{
	int d = 0;
	for (auto c : { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" })
	{
		int pos1 = s.find(c);
		int pos2 = goalState.find(c);
		if (pos1 != pos2)
			d++;
	}
	return d;
}

int FifteenPuzzle::calcManhattanDistance(string s)
{
	int md = 0;
	for (auto c : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"})
	{
		int pos1 = s.find(c);
		int pos2 = goalState.find(c);
		md += abs(pos1 % 4 - pos2 % 4) + abs(pos1 / 4 - pos2 / 4);
	}
	return md;
}

FifteenPuzzle::FifteenPuzzle(string start, string goal)
{
	startState = start;
	goalState = goal;
}
