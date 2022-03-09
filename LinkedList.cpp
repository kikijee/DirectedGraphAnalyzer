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
    std::cout<<std::endl;
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

el_t LinkedList::delete_front(){
    el_t elem;
    if(this->isEmpty()){return elem;}
    else if(front_->next_ == nullptr){
        elem = front_->vertex_;
        delete front_;
        front_ = nullptr;
        rear_ = nullptr;
    }
    else{
        elem = front_->vertex_;
        Node* p = front_;
        front_ = front_->next_;
        delete p;
    }
    count_--;
    return elem;
}

void LinkedList::deleteRear(){}

LinkedList::~LinkedList(){
    std::cout<<"...Linked List Destructor Called..."<<std::endl;
    while(front_ != nullptr){
        this->delete_front();
    }
}