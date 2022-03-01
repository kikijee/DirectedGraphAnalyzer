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

void LinkedList::add_front(el_t vertex){
    Node* p = new Node;
    p->vertex_ = vertex;
    p->next_ = nullptr;
    if(front_ == nullptr && rear_ == nullptr){front_ = p; rear_ = p;}
    else{
        p->next_ = front_;
        front_ = p;
    }
    count_++;
}

        
void LinkedList::add_rear(el_t vertex){
    Node* p = new Node;
    p->vertex_ = vertex;
    p->next_ = nullptr;
    if(front_ == nullptr && rear_ == nullptr){front_ = p; rear_ = p;}
    else{
        rear_->next_ = p;
        rear_ = p;
    }
    count_++;
}

void LinkedList::delete_front(){
    if(this->isEmpty()){return;}
    else if(front_->next_ == nullptr){
        delete front_;
        front_ = nullptr;
        rear_ = nullptr;
    }
    else{
        Node* p = front_;
        front_ = front_->next_;
        delete p;
    }
    count_--;
}

void LinkedList::deleteRear(){}

LinkedList::~LinkedList(){
    std::cout<<"...Adjacent List Destructor Called..."<<std::endl;
    while(front_ != nullptr){
        this->delete_front();
    }
}