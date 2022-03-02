#ifndef SHORTEST_PATH
#define SHORTEST_PATH
#include"AdjacentList.h"
// structure for the shortest path table, consist of amount of time, vertex from, and current state
// constructor initializes defualt values
// state can only be either U (unseen), F (fringe), T (tree)
struct ShortestPathTable{
    int time_;
    char from_;
    char state_;
    ShortestPathTable():time_(0),from_('/'),state_('U'){}
};

// class for the "area" of which the graph is taking place
// verticies will be A-Z (0-25) for array index
class Area{
private:
    int num_verticies_;
    char tree_;
    AdjacentList* arr_adjacency;                // pointer to AdjacenList to point to array holding AdjacentList objects
    ShortestPathTable* arr_shortest_path_table; // pointer to ShortestPathTable to point to array holding SPT objects
public:
// constructor takes one parameter being the total number of vertices which initializes num_vertices which then 
// allocates that certain amount of space in the heap for arr_adjacency and arr_shortest_path_table
    Area(int num):num_verticies_(num),tree_(' '){
        arr_adjacency = new AdjacentList[num_verticies_];
        arr_shortest_path_table = new ShortestPathTable[num_verticies_];
    }
    ~Area();
    // Vertex fault exception
    class BadVertex{};
    // Purpose: reads table from given text file and input values into the adjacency list
    void read_table(std::fstream&);
    // displays the adjacency list
    void display_table();
    // retruns degree of given vertex
    int find_out_degree(char);
    //  returns head pointer of linked list of given vertex
    Node* find_adjacent(char);
    // creates the shortest path table using dijkstra's algorithm
    void create_shortest_path_table(char);
    // displays the shortest path table
    void display_shortest_path_table();
    // displays the certain path from tree_ to char along with the amount of time it will take
    void display_path(char);
    // clears shortest path table and inserts defualt values
    void clear_sp_table();

    // DFS FUNCTIONS , BFS FUNCTIONS//
    // if given vertex has not been marked yet then mark it with num
    void visit(int,char);
    // if not marked yet then return false otherwise return true
    bool is_marked(char);
    // resets all visit numbers in the adjacency list
    void clear_visit_numbers();
    // END DFS FUNCTIONS , BFS FUNCTIONS//
};

#endif