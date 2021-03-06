#include "AdjacentList.h"

void AdjacentList::display_list(){
    Node* p;
    p = front_;
    if(front_ == nullptr){
        std::cout<<"[ EMPTY ]";
    }
    else{
        std::cout<<"[ ";
        while(p != nullptr){
            std::cout<<p->vertex_;
            std::cout<<"("<<p->time_<<") ";
            p = p->next_;
        }
        std::cout<<" ]";
    }
}

void AdjacentList::add_front(char vertex, int time){
    Node* p = new Node;
    p->vertex_ = vertex;
    p->time_ = time;
    p->next_ = nullptr;
    if(front_ == nullptr){
        front_ = p;
    }
    else{
        p->next_ = front_;
        front_ = p;
    }
    count_++;
}

void display_linked_list(Node* p){
    if(p == nullptr){std::cout<<"[ EMPTY ]"<<std::endl;}
    else{
        std::cout<<"[ ";
        while(p != nullptr){
            std::cout<<p->vertex_<<" ("<<p->time_<<") ";
            p = p->next_;
        }  
        std::cout<<"]"<<std::endl;
    }
}

int AdjacentList::return_time(char value){
    if(this->front_ == nullptr){throw EmptyList();}
    else{
        Node* p = front_;
        while(p != nullptr){
            if(p->vertex_ == value){return p->time_;}
            p = p->next_;
        }
        throw BadVertex();
    }
}


