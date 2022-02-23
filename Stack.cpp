#include "Stack.h"

void Stack::pop(char &elem){
    if(this->stack_is_empty()){throw StackUnderflow();}
    else{top_--;elem = stack_[top_+1];}
}

void Stack::push(char elem){
    if(int(elem)-65 >= max_ || int(elem)-65 < 0){throw BadVertex();}
    if(this->stack_is_full()){throw StackOverflow();}
    else{top_++;stack_[top_] = elem;}
}

void Stack::display_stack(){
    if(this->stack_is_empty()){
        std::cout<<"|\tEMPTY\t|"<<std::endl;
    }
    else{
        for(int i = top_; i >= 0; i--){
            std::cout<<"|\t"<<stack_[i]<<"\t|"<<std::endl;
        }
    }
    std::cout<<"----------"<<std::endl;
}

bool Stack::stack_is_empty(){
    if(top_ == -1){return true;}
    else{return false;}
}

bool Stack::stack_is_full(){
    if(top_ == max_-1){return true;}
    else{return false;}
}

void Stack::clear_stack(){top_ = -1;}