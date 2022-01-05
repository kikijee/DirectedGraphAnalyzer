#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "ShortestPath.h"
// client purpose to provide main menu and give analysis options to user based on table selected to use as graph
// current analysis options: Adjacency list analysis, dikstra's analysis, and depth first search
int main(){
    std::string fname = "No file selected";
    std::string file;    
    char choice;
    int num;
    int case_num;
    Area* a_ptr = nullptr;      // when program first runs there is no defualt file selected, user must first select file
    while(true){
        std::cout<<"...WELCOME TO THE DIRECTED GRAPH ANALYZER..."<<std::endl;
        std::cout<<"Please select from the options below"<<std::endl;
        std::cout<<"1.) change input file\n2.) analysis of any given vertex through the adjacency list\n3.) visual of dijkstra algorithm through tables\n4.) visualization of DFS\n5.) exit analyzer"<<std::endl;
        std::cout<<"Current File: "<<fname<<std::endl;
        std::cout<<"=> ";
        std::cin >> case_num;
        switch(case_num){
            case 1:     // file select
                while(true){
                    std::cout<<"Please enter the file name that you would like to process, other wise type '/' to exit"<<std::endl;
                    std::cout<<"=> ";
                    std::cin >> file;
                    if(file == "/"){break;}
                    std::fstream fin (file.c_str(),std::ios::in);
                    if(fin.is_open()){
                        std::cout<<"You have selected: \""<<file<<"\" is this correct? (y/n)"<<std::endl<<"=> ";
                        std::cin >> choice;
                        if(choice == 'y' || choice == 'Y'){
                            fname = file;
                            if(a_ptr != nullptr){delete a_ptr;} // if there was already a previous file selected, delete current area object and have the pointer point to a new one
                            fin>>num;
                            a_ptr = new Area(num);
                            a_ptr->read_table(fin);
                            std::cout<<"...file read was a success, returning to main menu..."<<std::endl;
                            break;
                        }
                        else{std::cout<<"...Please try again..."<<std::endl;}
                    }
                    else{
                        std::cout<<"Error: file does not exist... please try again"<<std::endl;
                    }
                }
                system("CLS");
                break;
            case 2:     // Adjacency table analysis
                if(a_ptr == nullptr){std::cout<<"...Please select file to read from first..."<<std::endl;break;}
                std::cout<<"ADJACENCY TABLE:"<<std::endl;
                a_ptr->display_table();
                while(true){
                    std::cout<<"Please enter Vertex name to search up data or type '/' to exit: "<<std::endl;
                    std::cin>>choice;
                    if(choice == '/'){break;}
                    else{
                        try{
                            std::cout<<"Vertex: "<<choice<<" Out-Degree: "<<a_ptr->find_out_degree(choice)<<" Adjacent: ";
                            a_ptr->display_linked_list(a_ptr->find_adjacent(choice));
                        }
                        catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                    }
                }
                system("CLS");
                break;
            case 3:     // Dikstra's Algorithm
                if(a_ptr == nullptr){std::cout<<"...Please select file to read from first..."<<std::endl;break;}
                while(true){
                    std::cout<<"please enter vertex value to create shortest path table or type '/' to exit:"<<std::endl;
                    std::cin>>choice;
                    if(choice == '/'){break;}
                    else{
                        try{
                            a_ptr->create_shortest_path_table(choice);
                            a_ptr->display_shortest_path_table();
                            while(true){
                                std::cout<<"please enter the short path you would like to search or type '/' to exit:"<<std::endl;
                                std::cin>>choice;
                                if(choice == '/'){break;}
                                else{
                                    try{a_ptr->display_path(choice);}
                                    catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                                }
                            }
                        }
                        catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                    }
                    a_ptr->clear_sp_table();
                }
                system("CLS");
                break;
            case 4:     // Depth First search
                if(a_ptr == nullptr){std::cout<<"...Please select file to read from first..."<<std::endl;break;}
                a_ptr->display_table();
                AdjacentNode *n_ptr;
                while(true){
                    int visit_num = 1;
                    std::cout<<"Please enter element to act as root or type '/' to exit:"<<std::endl;
                    std::cin>>choice;
                    if(choice == '/'){break;}
                    else{
                        try{
                            a_ptr->push(choice);    // choosing element to act as the root 
                            while(!a_ptr->stack_is_empty()){
                                try{
                                    a_ptr->pop(choice);
                                    std::cout<<"removed "<<choice<<" from stack"<<std::endl;
                                    if(!a_ptr->is_marked(choice)){
                                        a_ptr->visit(visit_num,choice);
                                        std::cout<<"Visit "<<choice<<" as "<<visit_num<<std::endl;
                                        visit_num++;
                                        if(a_ptr->find_out_degree(choice) == 0){std::cout<<"Deadend reached - backup."<<std::endl;}
                                        else{
                                            n_ptr = a_ptr->find_adjacent(choice);
                                            while(n_ptr != nullptr){
                                                a_ptr->push(n_ptr->vertex_);
                                                n_ptr = n_ptr->next_;
                                            }
                                        }
                                    }    
                                    else{std::cout<<choice<<" has been visited already - backup."<<std::endl;}
                                    std::cout<<"stack is:"<<std::endl;
                                    a_ptr->display_stack();
                                }
                                catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                            }
                            a_ptr->display_table();
                            a_ptr->clear_visit_numbers();
                        }
                        catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                    }
                }
                a_ptr->clear_visit_numbers();
                system("CLS");
                break;
            case 5:     // Exit option
                system("CLS");
                break;
            default:
                std::cout<<"Error: Invalid choice please try again..."<<std::endl;
                break;
        }
        if(case_num == 5){break;}
    }
}