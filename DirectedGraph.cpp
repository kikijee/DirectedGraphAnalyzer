#include <iostream>
#include <string>
#include <fstream>
#include "DirectedGraph.h"

void Area::read_table(std::fstream &fin){
    char vertex;
    int outDegree, time;
    int count = 0;
    while(fin >> vertex){
        arr_adjacency[count].set_vertex(vertex);
        fin >> outDegree;
        arr_adjacency[count].set_outDegree(outDegree);
        num_edges_ += outDegree;
        for(int i = 0; i < arr_adjacency[count].return_outDegree(); i++){
            fin>>vertex;
            fin>>time;
            arr_adjacency[count].add_front(vertex,time);
        }
        count++;
    }
}

void Area::display_table(){
    for(int i = 0; i < num_verticies_; i++){
        std::cout<<"Vertex: "<<arr_adjacency[i].return_vertex()<<"\tOut-Degree: "<<arr_adjacency[i].return_outDegree()<<"\tVisit number: "<<arr_adjacency[i].return_visit()<<"\t\t";
        arr_adjacency[i].display_list();
        std::cout<<std::endl;
    }
    std::cout<<"Number of Verticies: "<<num_verticies_<<std::endl<<"Number of Edges: "<<num_edges_<<std::endl;
}

int Area::find_out_degree(char temp){
    int index = int(temp)-65;
    if(index > num_verticies_-1 || 0 > index){throw BadVertex();}
    else{return arr_adjacency[index].return_outDegree();}
}

Node* Area::find_adjacent(char temp){
    int index = int(temp)-65;
    if(index > num_verticies_-1 || 0 > index){throw BadVertex();}
    else{return arr_adjacency[index].return_front();}
}

void Area::create_shortest_path_table(char from){
    if(int(from)-65 >= num_verticies_ || int(from)-65 < 0){throw BadVertex();}
    arr_shortest_path_table[int(from)-65].state_ = 'T';
    Node* p = arr_adjacency[int(from)-65].return_front(); // points to head of adjacencys of current tree value
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

// START DESTRUCTOR FUNCTIONS //
Area::~Area(){
    std::cout<<"...Area Destructor Called..."<<std::endl;
    delete [] arr_shortest_path_table;
    delete [] arr_adjacency;
}
// END DESTRUCTOR FUNCTIONS //

// START DFS FUNCTIONS //
void Area::visit(int num, char vertex){
    if(int(vertex)-65 >= num_verticies_ || int(vertex)-65 < 0){throw BadVertex();}
    if(!is_marked(vertex)){
        arr_adjacency[int(vertex)-65].set_visit(num);
    }
    else{return;}
}

bool Area::is_marked(char vertex){
    if(arr_adjacency[int(vertex)-65].return_visit() == 0){return false;}
    else{return true;}
}

void Area::clear_visit_numbers(){
    for(int i = 0; i < num_verticies_; i++){
        arr_adjacency[i].set_visit(0);
    }
}
// END DFS FUNCTIONS // 