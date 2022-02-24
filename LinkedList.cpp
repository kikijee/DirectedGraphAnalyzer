#include "LinkedList.h"

void LinkedList::display_list(){
    Node* p;
    p = front_;
    if(front_ == nullptr){
        std::cout<<"[ EMPTY ]";
    }
    else{
        std::cout<<"[ ";
        while(p != nullptr){
            std::cout<<p->vertex_;
            if(p->next_ != nullptr){std::cout<<" -> ";}
            p = p->next_;
        }
        std::cout<<" ]";
    }
}

void LinkedList::add_front(char vertex){
    Node* p = new Node;
    p->vertex_ = vertex;
    p->next_ = nullptr;
    if(front_ == nullptr){front_ = p;}
    else{
        p->next_ = front_;
        front_ = p;
    }
    count_++;
}

        
void LinkedList::addRear(){}

void LinkedList::delete_front(){
    if(this->isEmpty()){return;}
    else{
        Node* p = front_;
        front_ = front_->next_;
        delete p;
        count_--;
    }
}

void LinkedList::deleteRear(){}

LinkedList::~LinkedList(){
    std::cout<<"...Adjacent List Destructor Called..."<<std::endl;
    while(front_ != nullptr){
        this->delete_front();
        count_--;
    }
}