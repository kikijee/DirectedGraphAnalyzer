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