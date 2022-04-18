#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
#include <fstream>
#include <tuple>
#include "EightPuzzle.h"
#include "FifteenPuzzle.h"

using namespace std;

struct NodeData
{
    char m = '0'; // move used to get to state
    int length = 0; // number of moves used to get to state
};

struct Node 
{
    string state;
    int f; // f = g + h, either manhattan distance or out of place + number of moves
    Node(string s, int d) { state = s; f = d; }
};

// comparison operators for nodes so that they can be used in a priority queue
bool operator<(Node n1, Node n2) { return n1.f < n2.f; }
bool operator<=(Node n1, Node n2) { return n1.f <= n2.f; }
bool operator>(Node n1, Node n2) { return n1.f > n2.f; }
bool operator>=(Node n1, Node n2) { return n1.f >= n2.f; }
bool operator==(Node n1, Node n2) { return n1.f == n2.f; }
bool operator!=(Node n1, Node n2) { return n1.f != n2.f; }

string bFS(EightPuzzle* p, int& nodes)// uses BFS to find solution to puzzle p, returning solution string and giving number of nodes visited using pass by reference
{
    nodes = 0; // number of nodes visited
    map<string, NodeData> visited; // maps possible states to move used to reach that state if they have been visited, automatically initializes to 0 otherwise
    queue<string> frontier; // fifo queue of nodes to visit, represented by their state strings

    visited[p->startState].m = ' ';
    visited[p->startState].length = 0;
    visited["-1"].m = '_'; // invalid states will be ignored since they are "visited"
    frontier.push(p->startState); 

    while (frontier.size() > 0) // shouldnt terminate
    {
        string current = frontier.front();
        frontier.pop();
        for (char c : { 'u', 'd', 'l', 'r' })
        {
            string childState = p->move(current, c);
            nodes++;
            if (childState != "-1" && visited[childState].m == '0')
            {
                NodeData currentStateData = visited[current]; // temp store to prevent multiple lookups in map
                if (childState == p->goalState)
                {// reconstruct the best found path to get to goal 
                    string path = "";
                    path.reserve(currentStateData.length);
                    path.insert(0, 1, c);

                    string stateIterator = current;
                    char nextMove = visited[stateIterator].m;

                    while (stateIterator != p->startState)
                    {
                        path.insert(0, 1, nextMove);
                        stateIterator = p->reverseMove(stateIterator, nextMove);
                        nextMove = visited[stateIterator].m;

                    }
                    return path;
                }

                visited[childState].m = c;
                visited[childState].length = currentStateData.length + 1;
                frontier.push(childState);
            }
        }
    }
    cout << "something went wrong." << endl; // no valid solution was found
    return "-1";
}

string dFS(EightPuzzle* p, int& nodes) // almost identical to bfs, just using stack for frontier instead of queue
{
    nodes = 0; // number of nodes visited
    map<string, NodeData> visited;
    stack<string> frontier; // FILO stack of nodes to visit, represented by their state strings

    visited[p->startState].m = ' ';
    visited[p->startState].length = 0;
    visited["-1"].m = '_'; // invalid states will be ignored since they are "visited"
    frontier.push(p->startState);

    while (frontier.size() > 0) // shouldnt terminate
    {
        string current = frontier.top();
        frontier.pop();
        for (char c : { 'u', 'd', 'l', 'r' })
        {
            string childState = p->move(current, c);
            nodes++;
            if (childState != "-1" && visited[childState].m == '0')
            {
                NodeData currentStateData = visited[current]; // temp store to prevent multiple lookups in map
                if (childState == p->goalState)
                {// reconstruct the best found path to get to goal 
                    string path = "";
                    path.reserve(currentStateData.length);
                    path.insert(0, 1, c);

                    string stateIterator = current;
                    char nextMove = visited[stateIterator].m;

                    while (stateIterator != p->startState)
                    {
                        path.insert(0, 1, nextMove);
                        stateIterator = p->reverseMove(stateIterator, nextMove);
                        nextMove = visited[stateIterator].m;

                    }
                    return path;
                }

                visited[childState].m = c;
                visited[childState].length = currentStateData.length + 1;
                frontier.push(childState);
            }
        }
    }
    cout << "something went wrong." << endl; // no valid solution was found
    return "-1";
}

string dLS(EightPuzzle* p, int& nodes, int l) // does DFS algorithm, limiting depth to l, returns "-1" if no solution
{
    nodes = 0; // number of nodes visited
    map<string, NodeData> visited;
    stack<string> frontier; // FILO stack of nodes to visit, represented by their state strings

    visited[p->startState].m = ' ';
    visited[p->startState].length = 0;
    visited["-1"].m = '_'; // invalid states will be ignored since they are "visited"
    frontier.push(p->startState);

    while (frontier.size() > 0) // shouldnt terminate
    {
        string current = frontier.top();
        frontier.pop();
        for (char c : { 'u', 'd', 'l', 'r' })
        {
            string childState = p->move(current, c);
            nodes++;
            if (childState != "-1" && visited[childState].m == '0')
            {
                NodeData currentStateData = visited[current]; // temp store to prevent multiple lookups in map
                if (childState == p->goalState)
                {// reconstruct the best found path to get to goal 
                    string path = "";
                    path.reserve(currentStateData.length);
                    path.insert(0, 1, c);

                    string stateIterator = current;
                    char nextMove = visited[stateIterator].m;

                    while (stateIterator != p->startState)
                    {
                        path.insert(0, 1, nextMove);
                        stateIterator = p->reverseMove(stateIterator, nextMove);
                        nextMove = visited[stateIterator].m;

                    }
                    return path;
                }

                visited[childState].m = c;
                visited[childState].length = currentStateData.length + 1;
                if (currentStateData.length <= l) // only pushes nodes up to depth l
                    frontier.push(childState);
            }
        }
    }
    return "-1";
}

string iDS(EightPuzzle* p, int& nodes) // runs DLS with increasing depth till solution is found
{
    nodes = 0;
    int l = 0;
    string result = "-1";

    while (result == "-1")
    {
        result = dLS(p, nodes, l);
        l++;
    }
 
    return result;
}

string aStarMD(EightPuzzle* p, int& nodes)
{
    nodes = 0;
    unordered_map<string, NodeData> visited; 
    priority_queue<Node, vector<Node>, greater<Node>> frontier; // uses priority queue of nodes, where nodes are compared using their manhattan distances and the length of their solutions

    visited[p->startState].m = ' ';
    visited["-1"].m = '_'; // invalid states will be ignored since they are "visited"
    frontier.push(Node(p->startState, p->calcManhattanDistance(p->startState)));

    while (frontier.size() > 0) // shouldnt terminate
    {
        Node current = frontier.top();
        frontier.pop();
        for (char c : { 'u', 'd', 'l', 'r' })
        {
            string childState = p->move(current.state, c);
            nodes++;
            if (childState != "-1" && visited[childState].m == '0')
            {
                NodeData currentStateData = visited[current.state]; // temp store to prevent multiple lookups in map

                if (childState == p->goalState) 
                {// reconstruct the best found path to get to goal 
                    string path = "";
                    path.reserve(currentStateData.length);
                    path.insert(0, 1, c);

                    string stateIterator = current.state;
                    char nextMove = visited[stateIterator].m;

                   while(stateIterator != p->startState)
                   {
                       path.insert(0, 1, nextMove);
                       stateIterator = p->reverseMove(stateIterator, nextMove);
                       nextMove = visited[stateIterator].m;
                        
                   }
                    return path;
                }

                visited[childState].m =  c;
                visited[childState].length = currentStateData.length + 1;

                frontier.push(Node(childState, p->calcManhattanDistance(childState) + currentStateData.length));
            }
        }
    }
    cout << "something went wrong." << endl; // no valid solution was found
    return "-1";
}

string lFSMD(EightPuzzle* p, int& nodes, int& l) // runs A* with MD, limiting f value to l
{
    map<string, NodeData> visited;
    priority_queue<Node, vector<Node>, greater<Node>> frontier; // uses priority queue of nodes, where nodes are compared using their manhattan distances and the length of their solutions

    int lowestF = INT_MAX;

    visited[p->startState].m = ' ';
    visited["-1"].m = '_'; // invalid states will be ignored since they are "visited"
    frontier.push(Node(p->startState, p->calcManhattanDistance(p->startState)));

    while (frontier.size() > 0) // shouldnt terminate
    {
        Node current = frontier.top();
        frontier.pop();
        for (char c : { 'u', 'd', 'l', 'r' })
        {
            string childState = p->move(current.state, c);
            nodes++;
            if (childState != "-1" && visited[childState].m == '0')
            {
                NodeData currentStateData = visited[current.state]; // temp store to prevent multiple lookups in map

                if (childState == p->goalState)
                {// reconstruct the best found path to get to goal 
                    string path = "";
                    path.reserve(currentStateData.length);
                    path.insert(0, 1, c);

                    string stateIterator = current.state;
                    char nextMove = visited[stateIterator].m;

                    while (stateIterator != p->startState)
                    {
                        path.insert(0, 1, nextMove);
                        stateIterator = p->reverseMove(stateIterator, nextMove);
                        nextMove = visited[stateIterator].m;

                    }
                    return path;
                }

                visited[childState].m = c;
                visited[childState].length = currentStateData.length + 1;
                int childF = p->calcManhattanDistance(childState) + currentStateData.length + 1;

                if (childF <= l)
                    frontier.push(Node(childState, childF)); // only push nodes with f values lower than limit
                else if (childF < lowestF)
                    lowestF = childF; // if over limit, check if its lowest value over limit so far
            }
        }
    }
    l = lowestF; // sets limit for next iteration using pass-by-reference 
    return "-1";
}

string iDASMD(EightPuzzle* p, int& nodes) // runs LFSMD with increasing f
{
    int l = p->calcManhattanDistance(p->startState);
    nodes = 0;
    string solution = "-1";
    while (solution == "-1")
    {
        solution = lFSMD(p, nodes, l);
    }
    return solution;
}

string aStarOP(EightPuzzle* p, int& nodes)// same as A*MD, but uses out-of-place heuristic
{
    nodes = 0;
    map<string, NodeData> visited;
    priority_queue<Node, vector<Node>, greater<Node>> frontier; // uses priority queue of nodes, where nodes are compared using their manhattan distances and the length of their solutions

    visited[p->startState].m = ' ';
    visited["-1"].m = '_'; // invalid states will be ignored since they are "visited"
    frontier.push(Node(p->startState, p->calcOutOfPlace(p->startState)));

    while (frontier.size() > 0) // shouldnt terminate
    {
        Node current = frontier.top();
        frontier.pop();
        for (char c : { 'u', 'd', 'l', 'r' })
        {
            string childState = p->move(current.state, c);
            nodes++;
            if (childState != "-1" && visited[childState].m == '0')
            {
                NodeData currentStateData = visited[current.state]; // temp store to prevent multiple lookups in map

                if (childState == p->goalState)
                {// reconstruct the best found path to get to goal 
                    string path = "";
                    path.reserve(currentStateData.length);
                    path.insert(0, 1, c);

                    string stateIterator = current.state;
                    char nextMove = visited[stateIterator].m;

                    while (stateIterator != p->startState)
                    {
                        path.insert(0, 1, nextMove);
                        stateIterator = p->reverseMove(stateIterator, nextMove);
                        nextMove = visited[stateIterator].m;

                    }
                    return path;
                }

                visited[childState].m = c;
                visited[childState].length = currentStateData.length + 1;

                frontier.push(Node(childState, p->calcOutOfPlace(childState) + currentStateData.length));
            }
        }
    }
    cout << "something went wrong." << endl; // no valid solution was found
    return "-1";
}

string lFSOP(EightPuzzle* p, int& nodes, int& l) // same as LFSMD, but uses out-of-place heuristic
{
    map<string, NodeData> visited;
    priority_queue<Node, vector<Node>, greater<Node>> frontier; // uses priority queue of nodes, where nodes are compared using their manhattan distances and the length of their solutions

    int lowestF = INT_MAX;

    visited[p->startState].m = ' ';
    visited["-1"].m = '_'; // invalid states will be ignored since they are "visited"
    frontier.push(Node(p->startState, p->calcOutOfPlace(p->startState)));

    while (frontier.size() > 0) // shouldnt terminate
    {
        Node current = frontier.top();
        frontier.pop();
        for (char c : { 'u', 'd', 'l', 'r' })
        {
            string childState = p->move(current.state, c);
            nodes++;
            if (childState != "-1" && visited[childState].m == '0')
            {
                NodeData currentStateData = visited[current.state]; // temp store to prevent multiple lookups in map

                if (childState == p->goalState)
                {// reconstruct the best found path to get to goal 
                    string path = "";
                    path.reserve(currentStateData.length);
                    path.insert(0, 1, c);

                    string stateIterator = current.state;
                    char nextMove = visited[stateIterator].m;

                    while (stateIterator != p->startState)
                    {
                        path.insert(0, 1, nextMove);
                        stateIterator = p->reverseMove(stateIterator, nextMove);
                        nextMove = visited[stateIterator].m;

                    }
                    return path;
                }

                visited[childState].m = c;
                visited[childState].length = currentStateData.length + 1;
                int childF = p->calcOutOfPlace(childState) + currentStateData.length + 1;

                if (childF <= l)
                    frontier.push(Node(childState, childF)); // only push nodes with f values lower than limit
                else if (childF < lowestF)
                    lowestF = childF; // if over limit, check if its lowest value over limit so far
            }
        }
    }
    l = lowestF;
    return "-1";
}

string iDASOP(EightPuzzle* p, int& nodes) // runs LFSOP with increasing f 
{
    nodes = 0;
    int l = p->calcOutOfPlace(p->startState);
    string solution = "-1";
    while (solution == "-1")
    {
        solution = lFSOP(p, nodes, l);
    }
    return solution;
}

void toFile(vector<tuple<string,string,int>> s, string f) // sends stats to file with name f
{
    ofstream myfile;
    myfile.open(f);
    myfile << "Start, Solution, #Nodes" << endl;
    for (int i = 0; i < s.size(); i++)
    {
        myfile << get<0>(s[i]) << ", " << get<1>(s[i]) << ", " << get<2>(s[i]) << endl;
    }
    myfile.close();
}

int main()
{
    const string goal8 = "123456780"; 
    const string goal15 = "123456789ABCDEF0";
    vector<EightPuzzle*> p8; // 3x3 puzzles
    vector<FifteenPuzzle*> p15E; // 4x4 easy puzzles
    vector<FifteenPuzzle*> p15H; // 4x4 hard puzzles
    vector<tuple<string, string, int>> solutions;

    for (auto p : { "160273485" , "462301587" , "821574360" , "840156372" , "530478126" , "068314257" , "453207186" , "128307645" , "035684712" , "684317025" , "028514637" , "618273540" , "042385671" , "420385716" , "054672813" , "314572680" , "637218045" , "430621875" , "158274036" , "130458726" })
    {
        p8.push_back(new EightPuzzle(p, goal8));
    }
    for (auto p : { "16235A749C08DEBF" , "0634217859ABDEFC" , "012456379BC8DAEF" , "51246A38097BDEFC" , "12345678D9CFEBA0" })
    {
        p15E.push_back(new FifteenPuzzle(p, goal15));
    }
    for (auto p : { "71A92CE03DB4658F" , "02348697DF5A1EBC"  , "39A1D0EC7BF86452" , "EAB480FC19D56237" , "7DB13C52F46E80A9" })
    {
        p15H.push_back(new FifteenPuzzle(p, goal15));
    }
    int n = 0;
   // cout << aStarMD(p15H[4], n) << ", " << n << endl;
    
    for (auto p : p8)
    {
        int n;
        solutions.push_back({ p->startState, aStarMD(p, n), n});
    }
   
    for (auto p : p15E)
    {
        int n;
        string solution = aStarMD(p, n);
        //cout << p->startState << " , " << solution << n << endl;
        solutions.push_back({ p->startState, solution, n });
    }
    toFile(solutions, "AStarMD.txt");
     
}