#include <iostream>
#include "ShortestPath.h"

int main(){
    Area a(8);
    a.read_table();
    a.display_table();
    char value;
    while(true){
        std::cout<<"Please enter Vertex name to search up data or type '/' to exit: "<<std::endl;
        std::cin>>value;
        if(value == '/'){break;}
        else{
            try{
            std::cout<<"Vertex: "<<value<<" Out-Degree: "<<a.find_out_degree(value)<<" Adjacent: ";
            a.display_linked_list(a.find_adjacent(value));
            }
            catch(Area::BadVertex){std::cerr<<"no such vertex exists"<<std::endl;}
        }
    }
    a.create_shortest_path_table('B','F');
    a.display_shortest_path_table();
    a.display_table();
    std::cout<<"check";
}