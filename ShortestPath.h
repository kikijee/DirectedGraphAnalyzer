#ifndef SHORTEST_PATH
#define SHORTEST_PATH
// structure for the shortest path table, consist of amount of time, vertex from, and current state
// constructor initializes defualt values
// state can only be either U (unseen), F (fringe), T (tree)
struct ShortestPathTable{
    int time_;
    char from_;
    char state_;
    ShortestPathTable():time_(0),from_('/'),state_('U'){}
};
// nodes of linked list, for the functionality of the adjacency list
struct AdjacentNode{
    char vertex_;
    int time_;
    AdjacentNode* next_;
    AdjacentNode():vertex_(' '),time_(0),next_(nullptr){}
};
// structure for the adjacency list, contains: vertex, number of adjacents and the head of a linked list
// adjacency list that holds 3 items (vertex, out degree, head pointer to adjacent verticies linked list)
// constructor initializes defualt values
struct AdjacentList{
    char vertex_;
    int outDegree_;
    AdjacentNode* headLL_;
    AdjacentList():vertex_(' '),outDegree_(-1),headLL_(nullptr){}
    ~AdjacentList();

// linked list functions
    void add_front(char,int);   // adds to front of the linked list
    void delete_front();        // deletes current front / head of linked list
    void display_list();        // displays list in a nice format
    int return_time(char);      // returns amount of time to travel to given vertex if it is adjacent 
    class EmptyList{};          // error throw if list is empty
};
// class for the "area" of which the graph is taking place
// verticies will be A-Z (0-25) for array index
class Area{
private:
    int num_verticies_;
    int count_used_;
    AdjacentList* arr_adjacency;                // pointer to AdjacenList to point to array holding AdjacentList objects
    char tree_;
    ShortestPathTable* arr_shortest_path_table; // pointer to ShortestPathTable to point to array holding SPT objects
public:
// constructor takes one parameter being the total number of vertices which initializes num_vertices which then 
// allocates that certain amount of space in the heap for arr_adjacency and arr_shortest_path_table
    Area(int num):num_verticies_(num),count_used_(0),tree_(' '){
        arr_adjacency = new AdjacentList[num_verticies_];
        arr_shortest_path_table = new ShortestPathTable[num_verticies_];
    }
    ~Area();
    class BadVertex{};
    //~Area();
    // Purpose: reads table from given text file and input values into the adjacency list
    void read_table(std::fstream&);
    // displays the adjacency list
    void display_table();
    // retruns degree of given vertex
    int find_out_degree(char);
    //  returns head pointer of linked list of given vertex
    AdjacentNode* find_adjacent(char);
    // uses return from above and displays linked list
    void display_linked_list(AdjacentNode*);
    // creates the shortest path table using dijkstra's algorithm
    void create_shortest_path_table(char);
    // displays the shortest path table
    void display_shortest_path_table();
    // displays the certain path from tree_ to char along with the amount of time it will take
    void display_path(char);
    // clears shortest path table and inserts defualt values
    void clear_sp_table();
};

#endif