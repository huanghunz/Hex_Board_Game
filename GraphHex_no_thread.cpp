#include "GraphHex.h"


// ---------------- Graph ---------------------------------
// A defualt constructor for HEX board
// pre :		nothing
// post :		graph is initialzied
//
Graph::Graph()
{
	//NODE_SZ = 11 by default, GRAPH_SZ = NODE_SZ * NODE_SZ

	adj_list.resize(GRAPH_SZ, list<Vertex>(0));
	// resize to n has a vector out of range error

	for (int x = 0; x < GRAPH_SZ; x++)	{

		insert(x, x, EMPTY); // dummy node

		if (x % NODE_SZ == 0){ // lett side	
			if (x == LAST_LINE) // left down conner
				_buildEdges(2, x);
			else if (x > 0) // middle of left edge
				_buildEdges(1, x);
			else // the first node : 
				_buildEdges(0, x);
		}
		else if (x % NODE_SZ == NODE_SZ - 1){ // far right side
			if (x == GRAPH_SZ - 1) // right down conner
				_buildEdges(3, x);
			else if (x > NODE_SZ) // middle nodes of right edge
				_buildEdges(4, x);
			else
				_buildEdges(5, x); // right up conner
		}
		else if (x < NODE_SZ){ //first line
			_buildEdges(6, x);
		}
		else if (x > LAST_LINE) { // last line
			_buildEdges(7, x);
		}
		else
			_buildEdges(8, x); // all middles
	}
}

// ---------------- Graph ---------------------------------
// Another constructor for HEX board
// pre :		origin: the data that this graph is going to initilized with
// post :		graph is initialized
//
Graph::Graph(const Graph& origin)
{
	adj_list = origin.adj_list;
}
// ---------------- Graph:: insert ---------------------------------
// A mutator function to insert data to the list if it's not 
// out of range
// pre :		u - start node
//				v - destination node
//				c - player/color
// post :		data inserted
//
void Graph::insert(int u, int v, char c = EMPTY)
{
	assert((u < GRAPH_SZ && "Vertex out-of-bound"));
	assert((v < GRAPH_SZ && "Vertex out-of-bound"));

	Graph::_Vertex node_v(u, v, c); // creating a vertex with from node and to node

	adj_list[u].push_back(node_v);
}

// ---------------- operator<< ---------------------------------
// A Friend I/O Function to print out the filled graph
// pre :		out - reference of cout
//				graph - adj_list
// post :		graph gets printed out
//
ostream& operator<< (ostream &out, Graph &graph)
{

	list<Graph::_Vertex> tempLst;
	list<Vertex>::iterator node;
	int line;

	out << endl << "User move: " << PLAYER_1 << "; Computer move: " << PLAYER_2 << endl;
	out << "User Path: East to West" << endl << endl;

	for (int v = 0; v < graph.GRAPH_SZ; v++){
		node = graph.adj_list[v].begin();
		out << "\\ ";
		if (node->player == -1){
			out << setfill('0') << setw(3) << v << "";
		}
		else{
			out << "  " << (char)(node->player);
		}
		if ((v + 1) % graph.NODE_SZ == 0){
			cout << "\\" << endl;
			line = v;
			while ((line + 1) / graph.NODE_SZ != 0){
				out << " ";
				line -= graph.NODE_SZ;
			}
		}
	}
	return out;

}



// ---------------- _buildEdges ---------------------------------
// A helper function to call the insert function
// just want to make the constructor less messy :)
// pre :		caseNum - the posistion of the nodes
//				x       - starting node
// post :		call the insert function depends on the determined location
//
void Graph::_buildEdges(int caseNum, int x)
{
	switch (caseNum)
	{
	case 0: // node 0
		insert(x, x + 1);
		insert(x, x + NODE_SZ);
		break;

	case 1: // middle nodes of left side
		insert(x, x - NODE_SZ);
		insert(x, x - NODE_SZ + 1);
		insert(x, x + 1);
		insert(x, x + NODE_SZ);
		break;

	case 2: // left down corner
		insert(x, x - NODE_SZ);
		insert(x, x - NODE_SZ + 1);
		insert(x, x + 1);

		break;

	case 3: // right up corner
		insert(x, x - NODE_SZ);
		insert(x, x - 1);

		break;

	case 4: // middle nodes of right side
		insert(x, x - NODE_SZ);
		insert(x, x - 1);
		insert(x, x - 1 + NODE_SZ);
		insert(x, x + NODE_SZ);
		break;
	case 5:  // right up corner
		insert(x, x - 1);
		insert(x, x + NODE_SZ - 1);
		insert(x, x + NODE_SZ);
		break;
	case 6: // middle nodes of the first line 
		insert(x, x - 1);
		insert(x, x + 1);
		insert(x, x + NODE_SZ - 1);
		insert(x, x + NODE_SZ);

		break;
	case 7:  // middle nodes of the last line
		insert(x, x - NODE_SZ);
		insert(x, x - NODE_SZ + 1);
		insert(x, x - 1);
		insert(x, x + 1);

		break;
	case 8: // nodes with 6 connected edges

		insert(x, x - NODE_SZ);
		insert(x, x - NODE_SZ + 1);
		insert(x, x - 1);
		insert(x, x + 1);
		insert(x, x + NODE_SZ - 1);
		insert(x, x + NODE_SZ);

		break;
	default:
		break;
	}
}

// ---------------- playGame ---------------------------------
// A mutator function to change the player-member-field
// ( to fill the board)
// pre :		nothing
// post :		prints out the winner
//

void Graph::playGame()
{
	probability.resize(GRAPH_SZ, 0);

	cout << *this << endl;
	for (int runGraph = 0; runGraph < GRAPH_SZ; runGraph++)	{

		if (runGraph % 2 == 0){ // user turn
			int input = userInput();
			node = adj_list[input].begin();
			node->player = PLAYER_1;

			if (findGameWinner()){
				cout << "Winner is user" << endl;
				return;
			}
		}

		else {
			fill(probability.begin(), probability.end(), 0);

			int  ai = monteCalo();// return an index

			node = adj_list[ai].begin();
			node->player = PLAYER_2;
			cout << *this << endl;
			if (findGameWinner()){
				cout << "Winner is compuer" << endl;
				return;
			}
		}
	}

}

// ---------------- findWiner ---------------------------------
// Find the winer side.
// pre :		nothing
// post :		print out the winner
//

int Graph::findGameWinner()
{
	vector<int> visited(GRAPH_SZ, 0);

	for (int i = 0; i < GRAPH_SZ; i++){
		if (i < NODE_SZ || i% NODE_SZ == 0 || i >= LAST_LINE
			|| i % NODE_SZ == NODE_SZ - 1){
			if (_findGameWinner(i, i, visited)){
				return 1;
			}
		}
	}
	return 0;
}

// ---------------- _find ---------------------------------
// Find the winer side. A helper recursive function
// pre :		frNode - the starting node
//			    toNode - the next node choosen by same player
//              visited - array that keeps track of the status of nodes
// post :		return true if the player wins
//
bool Graph::_findGameWinner(int frNode, int toNode, vector<int>& visited)
{
	if (visited[toNode])
		return false;
	visited[toNode] = 1;

	node = adj_list[frNode].begin();
	char frPlayer = node->player;
	if (frPlayer == EMPTY)
		return false;
	for (auto walk : adj_list[toNode]){ // access the Vertex
		if ((walk.from != walk.to) && !visited[walk.to]){ // not the dummy node
			list<Vertex>::iterator next = adj_list[walk.to].begin();
			if (frPlayer == next->player)	{
				if (_checkWin(frNode, walk.to))
					return true;
				else if (_findGameWinner(frNode, walk.to, visited))
					return true;
			}
		}
	}

	return false;
}

// ---------------- _checkWin ---------------------------------
// Find the winer side. A helper function
// pre :		frNode - the starting node
//			    end    - the end node
// post :		return true if the nodes reach the opposite end
//

bool Graph::_checkWin(int frNode, int end)
{
	node = adj_list[frNode].begin();

	if (node->player == PLAYER_2){
		if (frNode < NODE_SZ && end >= LAST_LINE) // start from upper line // north to south
			return true;
		else if (frNode >= LAST_LINE && end < NODE_SZ) // start from last line // south to north
			return true;
		else
			return false;
	}
	else if (node->player == PLAYER_1){
		if (frNode %  NODE_SZ == 0 && end %  NODE_SZ == NODE_SZ - 1) // start from left side // west to east
			return true;
		else if (frNode %  NODE_SZ == NODE_SZ - 1 && end %  NODE_SZ == 0) // statr from right side // east to west
			return true;
		else
			return false;
	}
	else
		return false;
}


// ---------------- fillGraph ---------------------------------
// A mutator function to change the player-member-field
// ( to fill the board)
// pre :		nothing
// post :		board gets filled
//
void Graph::fillGraph()
{
	for (int i = 0; i < GRAPH_SZ; i++)	{
		int count = 0;
		do{
			count++;
			int ranNum = rand() % (GRAPH_SZ);
			node = adj_list[ranNum].begin();
			if (count == GRAPH_SZ)
				return;
		} while (node->player == PLAYER_1 || node->player == PLAYER_2);

		if (i % 2 == 0)
			node->player = PLAYER_1;
		else
			node->player = PLAYER_2;
	}

}
// ---------------- userInput ---------------------------------
// A function handling the user's input
// pre :		nothing
// post :		return index


int Graph::userInput()
{

	char input[256];
	int move;
	bool valid = false;
	cout << "Enter an integer from 0 to " << GRAPH_SZ - 1 << ": ";
	cin >> input;

	while (valid == false){
		valid = true;//assume input is good
		for (int i = 0; input[i] != '\0'; i++)
		{
			if ((int)(input[i]) < '0' || (int)(input[i]) > '9'){
				{
					cout << "Enter an integer between 0 and " << GRAPH_SZ - 1 << ", try again: ";
					cin >> input;
					valid = false; //bad input
					break;
				}
			}
		}
		if (valid)//check to see if int in bounds outside of while loop
		{
			move = atoi(input);//convert char to int 
			if (move < 0 || move > GRAPH_SZ - 1)
			{
				cout << "Enter an integer between 0 and " << GRAPH_SZ - 1 << ", try again: ";
				cin >> input;
				valid = false; //int not between 0 and Graph size
			}
			else {
				node = adj_list[move].begin();
				if (node->player != -1)
				{
					cout << "This spot is already taken. Please choose another spot." << endl;
					cout << "Enter an integer between 0 and " << GRAPH_SZ - 1 << ", try again: ";
					cin >> input;
					valid = false;
				}
			}
		}
	}
	return move;
}

// ---------------- _findMaxProb() ---------------------------------
// Finding the best move from all prossibilties
// pre :		nothing
// post :		return index

int Graph::_findMaxProb()
{
	int max = 0;
	int index = 0;
	for (int i = 0; i < GRAPH_SZ; i++)
	{
		if (max <= probability[i]){
			node = adj_list[i].begin();
			if (node->player != PLAYER_1 && node->player != PLAYER_2){
				max = probability[i];
				index = i;
			}

		}
	}
	return index;
}
// ---------------- computerInput ---------------------------------
// Looking for the best move of AI
// pre :		nothing
// post :		return the index of best move

int Graph::monteCalo()
{
	time_t rawtime, end;
	time(&rawtime);
	int i;

	for (i = 0; i < GRAPH_SZ; i++){
		node = adj_list[i].begin();
		if (node->player != PLAYER_1 && node->player != PLAYER_2){


			for (int loop = 0; loop < LOOP; loop++){

				Graph copy(*this); //  copy it everytime

				node = copy.adj_list[i].begin();
				node->player = PLAYER_2;
				copy.fillGraph();
				if (copy.findAIMoves(i))
					probability[i]++;
			}
		}
	}
	time(&end);
	cout << "It costs: " << end - rawtime << " seconds for AI response" << endl;
	return _findMaxProb();
}

// ---------------- findAIMoves ---------------------------------
// Checking if the spot makes a win path
// pre :		AIspot: a node that the AI tries to place chest.
// post :		return true if it's a proper win path

int Graph::findAIMoves(int AIspot)
{
	int m1;
	vector<int> visited(GRAPH_SZ, 0);

	for (int i = 0; i < GRAPH_SZ; i++){
		if (i < NODE_SZ || i% NODE_SZ == 0 || i >= LAST_LINE
			|| i % NODE_SZ == NODE_SZ - 1){
			m1 = 0;
			if (_findAIMoves(i, i, visited, AIspot, m1)){
				return 1;
			}
		}
	}
	return 0;
}
// ---------------- _findAIMoves ---------------------------------
// A Helper Function, Checking if the spot makes a win path
// pre :		frNode: the starting node
//				toNOde: a linked node, not neccessary to be the end node
//				visited: a vector of flag that makes sure same node will not be visisted twice
//				match : a flag that makes sure the path contains the start node.
//				AIspot: a node that the AI tries to place chest.
// post :		return true if it's a proper win path

int Graph::_findAIMoves(int frNode, int toNode, vector<int>& visited, int AIspot, int match)
{
	if (visited[toNode])
		return false;
	visited[toNode] = 1;

	node = adj_list[frNode].begin();
	char frPlayer = node->player;
	if (frPlayer == EMPTY)
		return false;
	for (auto walk : adj_list[toNode]){ // access the Vertex
		if ((walk.from != walk.to) && !visited[walk.to]){ // not the dummy node
			list<Vertex>::iterator next = adj_list[walk.to].begin();
			if (frPlayer == next->player)	{
				if (AIspot == toNode)
					match = 1;
				if (_checkWin(frNode, walk.to) && match)
					return true;
				else if (_findAIMoves(frNode, walk.to, visited, AIspot, match))
					return true;
			}
		}
	}
	return false;
}