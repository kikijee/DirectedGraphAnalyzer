#ifndef SHORTEST_PATH
#define SHORTEST_PATH
// state can only be either U (unseen), F (fringe), T (tree)
struct ShortestPathTable{
    int time_;
    char from_;
    char state_;
    ShortestPathTable():time_(0),from_('/'),state_('U'){}
};
// nodes of linked list of the adjacency list
struct AdjacentNode{
    char vertex_;
    int time_;
    AdjacentNode* next_;
    AdjacentNode():vertex_(' '),time_(0),next_(nullptr){}
};
// adjacency list that holds 3 items (vertex, out degree, head pointer to adjacent verticies linked list)
struct AdjacentList{
    char vertex_;
    int outDegree_;
    AdjacentNode* headLL_;
    AdjacentList():vertex_(' '),outDegree_(-1),headLL_(nullptr){}
    void add_front(char,int);
    void display_list();
    int return_time(char);
    class EmptyList{};
};
// verticies will be A-Z (0-25) for array index
class Area{
private:
    int num_verticies_;
    int count_used_;
    AdjacentList* arr_adjacency;
    char tree_;
    ShortestPathTable* arr_shortest_path_table;
public:
    Area(int num):num_verticies_(num),count_used_(0),tree_(' '){
        arr_adjacency = new AdjacentList[num_verticies_];
        arr_shortest_path_table = new ShortestPathTable[num_verticies_];
    }
    class BadVertex{};
    //~Area();
    // Purpose: reads table from given text file and input values into the adjacency list
    void read_table();
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
};

#endif