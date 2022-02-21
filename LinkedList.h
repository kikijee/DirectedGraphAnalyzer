#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include<iostream>
typedef char el_t;
struct Node{
    el_t vertex_;
    int time_;
    Node *next_;

    Node():vertex_(' '),time_(0),next_(nullptr){}
};
class LinkedList{
    private:
        Node *front_;
        int count_;
    public:
        LinkedList();
        ~LinkedList();

        class EmptyList{};
        class BadVertex{};

        class Underflow{};
        class OutOfRange{};

        // returns true if LList is empty, else returns false
        bool isEmpty();
        
        // displays all LList elements
        void display_list();

        // displays linked list from given Node pointer
        void display_linked_list(Node*&);

        // adds new Node to the front of the linked list
        void add_front(char, int);

        // adds new Node to rear of the linked list
        void addRear();

        void delete_front();

        void deleteRear();

        LinkedList(const LinkedList&);

        LinkedList& operator=(const LinkedList);

        // searches and returns time of linked list
        int return_time(el_t value);
};
#endif