#ifndef STACK_H
#define STACK_H
#include<iostream>

typedef char el_t;

class Stack{
    private:
        int top_;
        el_t* stack_;
        int max_;
    public:
        // constructor
        Stack(int max):max_(2*max),top_(-1){stack_ = new el_t[max_];}
        // destructor
        ~Stack(){delete [] stack_;}

        class StackUnderflow{};
        class StackOverflow{};
        class BadVertex{};

        //STACK FUNCTIONS//
        // pops top element in stack and then returns it
        void pop(char &);
        // pushes element to stack
        void push(char);
        // displays all stack elements vertically
        void display_stack();
        // returns true if stack is empty otherwise returns false
        bool stack_is_empty();
        // returns true if stack is full otherwise returns false
        bool stack_is_full();
        // clears stack
        void clear_stack();
        //END STACK FUNCTIONS//
};
#endif