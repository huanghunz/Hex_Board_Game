#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <omp.h>

const char PLAYER_1 = 'B';
const char PLAYER_2 = 'W';
const int EMPTY = -1;

using namespace std;
class Vertex{
public:
	// constructors
	Vertex(){};
	Vertex(int frNode, int toNode) : from(frNode), to(toNode), player(EMPTY) {  };
	Vertex(int frNode, int toNode, int c) : from(frNode), to(toNode), player(c){};

	// public members
	int from, to;
	int player;
};

class Graph
{
public:

public:
	static const int  LOOP = 1000; 
    	static const int  NODE_SZ = 11;
	static const int  GRAPH_SZ = NODE_SZ*NODE_SZ;
	static const int  LAST_LINE = NODE_SZ* (NODE_SZ - 1);
	static const int  NUM_THREADS = 4;


	typedef Vertex _Vertex; 
	// with typedef, Graph can use the functions/constructor from Vertex class

	// Construtor
	Graph();
	Graph(const Graph&);

	//  Mutator Function
	void	insert(int u, int v, char c);
	void	playGame();
	void	fillGraph();
	int	userInput();
	int     monteCalo();



	//Friend I / O Functions
	friend	std::ostream& operator<<(std::ostream &out, Graph &graph);

	// Access Function
	int	findGameWinner(); // return 1 if wins
	int findAIMoves(int start); // fill the possible moves

private:
	vector<std::list<Vertex>> adj_list;
	vector<int> probability;
	int match;
	

	// Helper iterator
	list<Vertex>::iterator node;

	// Helper Function
	void _buildEdges(int caseNum, int from);
	bool _findGameWinner(int, int, std::vector<int>&);
	bool _checkWin(int, int);

	int _findAIMoves(int, int, std::vector<int>&, int, int); // a helper to fill the possible moves
	int  _findMaxProb(); // find the best move
};