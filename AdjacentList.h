#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<iostream>
#include"LinkedList.h"

//typedef char el_t;

// structure for the adjacency list, contains: vertex, number of adjacents and the head of a linked list
// adjacency list that holds 3 items (vertex, out degree, head pointer to adjacent verticies linked list)
// constructor initializes defualt values
class AdjacentList : public LinkedList{    
    public:
        AdjacentList(){}
        //~AdjacentList();

        // getters 
        int return_outDegree(){return outDegree_;}
        int return_visit(){return visit_;}
        char return_vertex(){return vertex_;}

        // setters
        void set_vertex(char vertex){vertex_ = vertex;}
        void set_outDegree(int outDegree){outDegree_ = outDegree;}
        void set_visit(int visit){visit_ = visit;}

        // returns true if LList is empty, else returns false
        //bool isEmpty();
        
        // displays all LList elements
        void display_list();

        // adds new Node to the front of the linked list
        void add_front(char, int);

        // adds new Node to rear of the linked list
        void addRear();

        //void delete_front();

        void deleteRear();

        AdjacentList(const AdjacentList&);

        AdjacentList& operator=(const AdjacentList);

        // searches and returns time of linked list
        int return_time(el_t value);
};

// displays linked list from given Node pointer
void display_linked_list(Node*);
#endif