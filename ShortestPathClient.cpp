#include <iostream>
#include <fstream>
#include "ShortestPath.h"

int main(){
    std::string fname = "No file selected";
    std::string file;
    bool fileSelect = false;
    char choice;
    int num;
    int case_num;
    Area* a_ptr = nullptr;
    while(true){
        std::cout<<"...WELCOME TO THE DIRECTED GRAPH ANALYZER..."<<std::endl;
        std::cout<<"Please select from the options below"<<std::endl;
        std::cout<<"1.) change input file\n2.) analysis of any given vertex through the adjacency list\n3.) visual of dijkstra algorithm through tables\n4.) exit analyzer"<<std::endl;
        std::cout<<"Current File: "<<fname<<std::endl;
        std::cout<<"=> ";
        std::cin >> case_num;
        switch(case_num){
            case 1:
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
                            if(a_ptr != nullptr){delete a_ptr;}
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
                break;
            case 2:
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
                        catch(Area::BadVertex){std::cerr<<"no such vertex exists"<<std::endl;}
                    }
                }
                break;
            case 3:
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
                                    catch(Area::BadVertex){std::cerr<<"no such vertex exists"<<std::endl;}
                                }
                            }
                        }
                        catch(Area::BadVertex){std::cerr<<"no such vertex exists"<<std::endl;}
                    }
                    a_ptr->clear_sp_table();
                }
                break;
            case 4:
                break;
            default:
                std::cout<<"Error: Invalid choice please try again..."<<std::endl;
                break;
        }
        if(case_num == 4){break;}
    }
}