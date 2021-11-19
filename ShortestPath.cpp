#include <iostream>
#include <string>
#include <fstream>
#include "ShortestPath.h"

void AdjacentList::display_list(){
    AdjacentNode* p;
    p = headLL_;
    if(headLL_ == nullptr){
        std::cout<<"[ EMPTY ]"<<std::endl;
    }
    else{
        std::cout<<"[ ";
        while(p != nullptr){
            std::cout<<p->vertex_;
            std::cout<<"("<<p->time_<<") ";
            p = p->next_;
        }
        std::cout<<" ]"<<std::endl;
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

void Area::read_table(){
    std::string fname;
    std::cout<<"please enter a file name: ";
    std::cin>> fname;
    std::fstream fin (fname.c_str(),std::ios::in);
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
        std::cout<<"Vertex: "<<arr_adjacency[i].vertex_<<" Out-Degree: "<<arr_adjacency[i].outDegree_<<'\t';
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

void Area::create_shortest_path_table(char from, char to){
    if(tree_ == ' '){arr_shortest_path_table[int(from)-65].state_ = 'T';}   // first call of function to automatically mark from as tree
    tree_ = from;
    AdjacentNode* p = arr_adjacency[int(tree_)-65].headLL_; // points to head of adjacencys of current tree value
    if(p != nullptr){   // if tree value has no adjacencys then skip to checking the table part
        while(p != nullptr){    // if so then goes through the linked list marking all U as F and checking if there is a shorter time for values already marked F
            if(arr_shortest_path_table[int(p->vertex_)-65].state_ != 'T'){  // if marked T already dont do anything
                if(arr_shortest_path_table[int(p->vertex_)-65].state_ == 'F'){  // if marked F check if there is a shorter time availible, and if so update the time and from
                    if(arr_shortest_path_table[int(p->vertex_)-65].time_ > arr_shortest_path_table[int(tree_)-65].time_+arr_adjacency[int(tree_)-65].return_time(p->vertex_)){
                        arr_shortest_path_table[int(p->vertex_)-65].time_ = arr_shortest_path_table[int(tree_)-65].time_+arr_adjacency[int(tree_)-65].return_time(p->vertex_);
                        arr_shortest_path_table[int(p->vertex_)-65].from_ = tree_;
                    }
                }
                else{   // else that the vertex is U
                    arr_shortest_path_table[int(p->vertex_)-65].state_ = 'F';
                    arr_shortest_path_table[int(p->vertex_)-65].from_ = tree_;
                    arr_shortest_path_table[int(p->vertex_)-65].time_ = arr_shortest_path_table[int(tree_)-65].time_+arr_adjacency[int(tree_)-65].return_time(p->vertex_);
                }
            }
            p = p->next_;
        }
    }   
    // checking table for F's
    char smallest = ' ';
    for(int i = 0; i < num_verticies_; i++){
        if(arr_shortest_path_table[i].state_ == 'F' && smallest == ' '){smallest = char(i+65);}
        else if(arr_shortest_path_table[i].state_ == 'F'){
            if(arr_shortest_path_table[i].time_ < arr_shortest_path_table[int(smallest)-65].time_){smallest = char(i+65);}
        }
    }
    if(smallest != ' '){
        arr_shortest_path_table[int(smallest)-65].state_ = 'T';
        create_shortest_path_table(smallest, to);
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