#include <iostream>
#include <string>
#include <fstream>
#include "ShortestPath.h"

void AdjacentList::display_list(){
    AdjacentNode* p;
    p = headLL_;
    if(headLL_ == nullptr){
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

void AdjacentList::add_front(char t_vertex, int t_out){
    AdjacentNode* p = new AdjacentNode;
    p->vertex_ = t_vertex;
    p->time_ = t_out;
    p->next_ = nullptr;
    if(headLL_ == nullptr){
        headLL_ = p;
    }
    else{
        p->next_ = headLL_;
        headLL_ = p;
    }
}

void Area::read_table(std::fstream &fin){
    char x;
    int y;
    while(fin >> arr_adjacency[count_used_].vertex_){
        fin >> arr_adjacency[count_used_].outDegree_;
        for(int i = 0; i < arr_adjacency[count_used_].outDegree_; i++){
            fin>>x;
            fin>>y;
            arr_adjacency[count_used_].add_front(x,y);
        }
        count_used_++;
    }
}

void Area::display_table(){
    for(int i = 0; i < num_verticies_; i++){
        std::cout<<"Vertex: "<<arr_adjacency[i].vertex_<<"\tOut-Degree: "<<arr_adjacency[i].outDegree_<<"\tVisit number: "<<arr_adjacency[i].visit_<<"\t\t";
        arr_adjacency[i].display_list();
        std::cout<<std::endl;
    }
}

int Area::find_out_degree(char temp){
    int index = int(temp)-65;
    if(index > num_verticies_-1 || 0 > index){throw BadVertex();}
    else{return arr_adjacency[index].outDegree_;}
}

AdjacentNode* Area::find_adjacent(char temp){
    int index = int(temp)-65;
    if(index > num_verticies_-1 || 0 > index){throw BadVertex();}
    else{return arr_adjacency[index].headLL_;}
}

void Area::display_linked_list(AdjacentNode* p){
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

void Area::create_shortest_path_table(char from){
    if(int(from)-65 >= num_verticies_ || int(from)-65 < 0){throw BadVertex();}
    arr_shortest_path_table[int(from)-65].state_ = 'T';
    AdjacentNode* p = arr_adjacency[int(from)-65].headLL_; // points to head of adjacencys of current tree value
    if(p != nullptr){   // if tree value has no adjacencys then skip to checking the table part
        while(p != nullptr){    // if so then goes through the linked list marking all U as F and checking if there is a shorter time for values already marked F
            if(arr_shortest_path_table[int(p->vertex_)-65].state_ != 'T'){  // if marked T already dont do anything
                if(arr_shortest_path_table[int(p->vertex_)-65].state_ == 'F'){  // if marked F check if there is a shorter time availible, and if so update the time and from
                    if(arr_shortest_path_table[int(p->vertex_)-65].time_ > arr_shortest_path_table[int(from)-65].time_+arr_adjacency[int(from)-65].return_time(p->vertex_)){
                        arr_shortest_path_table[int(p->vertex_)-65].time_ = arr_shortest_path_table[int(from)-65].time_+arr_adjacency[int(from)-65].return_time(p->vertex_);
                        arr_shortest_path_table[int(p->vertex_)-65].from_ = from;
                    }
                }
                else{   // else that the vertex is U
                    arr_shortest_path_table[int(p->vertex_)-65].state_ = 'F';
                    arr_shortest_path_table[int(p->vertex_)-65].from_ = from;
                    arr_shortest_path_table[int(p->vertex_)-65].time_ = arr_shortest_path_table[int(from)-65].time_+arr_adjacency[int(from)-65].return_time(p->vertex_);
                }
            }
            p = p->next_;
        }
    }   
    //else{arr_shortest_path_table[int(p->vertex_)-65].from_ = ' ';}
    // checking table for F's
    char smallest = ' ';
    for(int i = 0; i < num_verticies_; i++){
        if(arr_shortest_path_table[i].state_ == 'F' && smallest == ' '){smallest = char(i+65);}
        else if(arr_shortest_path_table[i].state_ == 'F'){
            if(arr_shortest_path_table[i].time_ < arr_shortest_path_table[int(smallest)-65].time_){smallest = char(i+65);}
        }
    }
    if(smallest != ' '){
        //arr_shortest_path_table[int(smallest)-65].state_ = 'T';
        create_shortest_path_table(smallest);
    }
    return;
}

int AdjacentList::return_time(char value){
    if(this->headLL_ == nullptr){throw EmptyList();}
    else{
        AdjacentNode* p = this->headLL_;
        while(p != nullptr){
            if(p->vertex_ == value){return p->time_;}
            p = p->next_;
        }
        throw Area::BadVertex();
    }
}

void Area::display_shortest_path_table(){
    std::cout<<"--------------------------"<<std::endl;
    for(int i = 0; i < num_verticies_; i++){
        std::cout<<arr_shortest_path_table[i].state_<<" "<<char(i+65)<<" "<<arr_shortest_path_table[i].time_<<" from: "<<arr_shortest_path_table[i].from_<<std::endl;
    }
    std::cout<<"--------------------------"<<std::endl;
}

void Area::display_path(char to){
    if(int(to)-65 >= num_verticies_ || int(to)-65 < 0){throw BadVertex();}
    std::cout<<"Amount of time: "<<arr_shortest_path_table[int(to)-65].time_<<std::endl;
    std::cout<<"Path: "<<to;
    if(to == tree_){std::cout<<"\t:0"<<std::endl;return;}
    else if(arr_shortest_path_table[int(to)-65].time_ == 0){std::cout<<"...No path found..."<<std::endl;return;}
    else{
        while(arr_shortest_path_table[int(to)-65].from_ != '/'){
            std::cout<<"<-"<<arr_shortest_path_table[int(to)-65].from_;
            to = arr_shortest_path_table[int(to)-65].from_;
        }
        std::cout<<std::endl;
    }
}

void Area::clear_sp_table(){
    for(int i = 0; i < num_verticies_; i++){
        arr_shortest_path_table[i].from_ = '/';
        arr_shortest_path_table[i].state_ = 'U';
        arr_shortest_path_table[i].time_ = 0; 
    }
}

Area::~Area(){
    std::cout<<"...Area Destructor Called..."<<std::endl;
    delete [] arr_shortest_path_table;
    delete [] arr_adjacency;
    delete [] stack;
}

AdjacentList::~AdjacentList(){
    std::cout<<"...Adjacent List Destructor Called..."<<std::endl;
    while(headLL_ != nullptr){
        this->delete_front();
    }
}

void AdjacentList::delete_front(){
    if(headLL_ == nullptr){return;}
    AdjacentNode* p = headLL_;
    headLL_ = headLL_->next_;
    delete p;
}

char Area::pop(){
    if(this->stack_is_empty()){throw StackUnderflow();}
    else{top_--;return stack[top_+1];}
}

void Area::push(char elem){
    if(int(elem)-65 >= num_verticies_ || int(elem)-65 < 0){throw BadVertex();}
    if(this->stack_is_full()){throw StackOverflow();}
    else{top_++;stack[top_] = elem;}
}

void Area::display_stack(){
    if(this->stack_is_empty()){
        std::cout<<"|\tEMPTY\t|"<<std::endl;
    }
    else{
        for(int i = top_; i < 0; i--){
            std::cout<<"|\t"<<stack[i]<<"\t|"<<std::endl;
        }
    }
    std::cout<<"----------"<<std::endl;
}

bool Area::stack_is_empty(){
    if(top_ == -1){return true;}
    else{return false;}
}

bool Area::stack_is_full(){
    if(top_ == num_verticies_-1){return true;}
    else{return false;}
}

void Area::clear_stack(){top_ = -1;}

void Area::visit(int num, char vertex){
    if(int(vertex)-65 >= num_verticies_ || int(vertex)-65 < 0){throw BadVertex();}
    if(!is_marked(vertex)){
        arr_adjacency[int(vertex)-65].visit_ = num;
    }
    else{return;}
}

bool Area::is_marked(char vertex){
    if(arr_adjacency[int(vertex)-65].visit_ == 0){return false;}
    else{return true;}
}