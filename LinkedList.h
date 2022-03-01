#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
typedef char el_t;
// nodes of linked list, for the functionality of the adjacency list
struct Node{
    el_t vertex_;
    int time_;
    Node *next_;

    Node():vertex_(' '),time_(0),next_(nullptr){}
};

class LinkedList{
    protected:
        Node *front_;
        int count_;
        //int outDegree_;
        //int visit_;
        //char vertex_;
    public:
        // constructor
        LinkedList():front_(nullptr), count_(0)/*,outDegree_(-1),visit_(0),vertex_(' ')*/{}

        // destructor
        ~LinkedList();

        // getters
        Node* return_front(){return front_;}
        int return_count(){return count_;}

        // exception handling cases
        class EmptyList{};
        class BadVertex{};
        class Underflow{};
        class OutOfRange{};

        // returns true if LList is empty, else returns false
        bool isEmpty(){if(front_ == nullptr){return true;}else{return false;}}
        
        // displays all LList elements
        void display_list();

        // adds new Node to the front of the linked list
        void add_front(char);

        // adds new Node to rear of the linked list
        void addRear();

        void delete_front();

        void deleteRear();

        //LinkedList(const AdjacentList&);

        //LinkedList& operator=(const AdjacentList);


};

#endif