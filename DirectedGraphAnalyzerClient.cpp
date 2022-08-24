#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <filesystem>
#include <time.h>
#include <limits>
#include "LinkedList.h"
#include "AdjacentList.h"
#include "DirectedGraph.h"
#include "Stack.h"
// client purpose to provide main menu and give analysis options to user based on table selected to use as graph
// current analysis options: Adjacency list analysis, dikstra's analysis, and depth first search
int main(){
    std::string fname = "No file selected";
    std::string file;    
    std::string var;
    char choice;
    int vertex_num;
    int case_num;
    int time_complexity;        // used when counting loop iterations and comparisons
    Area* a_ptr = nullptr;      // when program first runs there is no defualt file selected, user must first select file
    Stack* stack_ptr = nullptr;
    LinkedList* queue_ptr = nullptr;
    LinkedList* linked_list_ptr = nullptr;
    Node *n_ptr = nullptr;
    srand(time(NULL));
    system("CLS");
    while(true){
        std::cout<<"...WELCOME TO THE DIRECTED GRAPH ANALYZER..."<<std::endl;
        std::cout<<"Please select from the options below"<<std::endl;
        std::cout<<"1.) change input file\n2.) create a new directed graph\n3.) analysis of any given vertex through the adjacency list\n4.) visual of dijkstra algorithm through tables\n5.) visualization of DFS\n6.) visualization of BFS\n7.) exit analyzer"<<std::endl;
        std::cout<<"Current File: "<<fname<<std::endl;
        std::cout<<"=> ";
        std::cin.sync();
        std::cin >> case_num;
        switch(case_num){
            case 1:     // file select
                while(true){
                    std::cout<<"Please enter the file name that you would like to process, other wise type '/' to exit"<<std::endl;
                    std::cout<<"=> ";
                    std::cin >> file;
                    if(file == "/"){system("CLS");break;}
                    std::fstream fin (file.c_str(),std::ios::in);
                    if(fin.is_open()){
                        std::cout<<"You have selected: \""<<file<<"\" is this correct? (y/n)"<<std::endl<<"=> ";
                        std::cin >> choice;
                        if(choice == 'y' || choice == 'Y'){
                            fname = file;
                            if(a_ptr != nullptr){delete a_ptr;} // if there was already a previous file selected, delete current area object and have the pointer point to a new one
                            fin>>vertex_num;
                            a_ptr = new Area(vertex_num);
                            a_ptr->read_table(fin);
                            std::cout<<"...file read was a success, returning to main menu..."<<std::endl;
                            fin.close();
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
            case 2:     // user to create their own directed graph or generate a random one 
                system("CLS");
                int case_num2;
                while(true){
                    std::cout<<"Please select from the options below"<<std::endl;
                    std::cout<<"1.) Create your own directed graph\n2.) Generate a random directed graph\n3.) Return to main menu"<<std::endl;
                    std::cout<<"=> ";
                    std::cin >> case_num2;
                    switch(case_num2){
                        case 1:     // option to create their own directed graph
                            while(true){
                                std::cout<<"Please enter a unique file name (include the .txt at the end) or type '/' to exit:"<<std::endl<<"=> ";
                                std::cin >> file;
                                if(file == "/"){break;}
                                else if(!std::filesystem::exists(file)){              
                                    std::cout<<"You have chosen \""<<file<<"\" is this correct? (y/n)"<<std::endl<<"=> ";
                                    std::cin >> choice;                              
                                    if(choice == 'Y' || choice == 'y'){                  
                                        std::cout<<"How many vertices would you like to have(NOTE: LIMIT IS 26) or type '/' to exit:"<<std::endl<<"=> ";
                                        std::cin >> var;                          
                                        try{                                     
                                            if(var == "/"){break;}              
                                            else if(stoi(var) > 0 && stoi(var) <= 26){
                                                std::string outDegree;        // variable to hold outdegrees
                                                char vertex;                 // variable to hold vertex choices
                                                int time;                   // variable to hold time choices
                                                std::fstream fin (file.c_str(),std::ios::out);
                                                fin<<var<<std::endl;      
                                                for(int i = 0; i < stoi(var); i++){
                                                    fin<<char(i+65)<<" ";
                                                    std::cout<<"What is the out degree of vertex \""<<char(i+65)<<"\":"<<std::endl<<"=> ";
                                                    std::cin>>outDegree;
                                                    fin<<outDegree<<" ";
                                                    for(int j = 0; j < stoi(outDegree); j++){
                                                        std::cout<<"Adjacency "<<j+1<<", vertex "<<char(i+65)<<" to:"<<std::endl<<"=> ";
                                                        std::cin>>vertex;
                                                        if(int(vertex) >= 65 && int(vertex) <= 65 + stoi(var)){
                                                            fin<<vertex<<" ";
                                                            std::cout<<"Enter the amount of time to take:"<<std::endl<<"=> ";
                                                            std::cin>>time;
                                                            if(time >= 0){fin<<time<<" ";}
                                                        }
                                                        else{
                                                            std::cout<<"Error: vertex \""<<vertex<<"\" does not exist within the number of verticies that you have chosen, please try again"<<std::endl;
                                                            j--;
                                                        }
                                                    }
                                                    fin<<std::endl;
                                                }
                                                break;
                                            }
                                            else{system("CLS");std::cout<<"...Invalid choice, please try again..."<<std::endl;}
                                        }
                                        catch(std::invalid_argument){system("CLS");std::cerr<<"...Invalid choice, please try again..."<<std::endl;}
                                    }
                                    else{std::cout<<"..Please try again..."<<std::endl;}
                                }
                                else{std::cout<<"Error: file \""<<file<<"\" already exists, please try again"<<std::endl;}
                            }
                            system("CLS");
                            break;
                        case 2:     // option to randomize a directced graph
                            while(true){
                                std::cout<<"Please enter a unique file name (include the .txt at the end) or type '/' to exit:"<<std::endl<<"=> ";
                                std::cin >> file;
                                if(file == "/"){break;}
                                else if(!std::filesystem::exists(file)){              
                                    std::cout<<"You have chosen \""<<file<<"\" is this correct? (y/n)"<<std::endl<<"=> ";
                                    std::cin >> choice;
                                    if(choice == 'y' || choice == 'Y'){
                                        std::cout<<"How many vertices would you like to have(NOTE: LIMIT IS 26) or type '/' to exit:"<<std::endl<<"=> ";
                                        std::cin >> var;                          
                                        try{                                     
                                            if(var == "/"){break;}              
                                            else if(stoi(var) > 0 && stoi(var) <= 26){
                                                std::fstream fin (file.c_str(),std::ios::out);
                                                int lowOut;     // lower bound out degree
                                                int upOut;      // upper bound out degree
                                                int lowTime;    // lower bound time 
                                                int upTime;     // upper bound time
                                                int outDegree;  // out degree to output to file
                                                int verticies = stoi(var);
                                                std::cout<<"What would you like the lower bound of out-degree be?"<<std::endl<<"=> ";
                                                std::cin>>lowOut;
                                                std::cout<<"Upper bound?"<<std::endl<<"=> ";
                                                std::cin>>upOut; 
                                                std::cout<<"What would you like the lower bound of time be?"<<std::endl<<"=> ";
                                                std::cin>>lowTime;
                                                std::cout<<"Upper bound?"<<std::endl<<"=> ";
                                                std::cin>>upTime;
                                                fin<<var<<std::endl;
                                                for(int i = 0; i < stoi(var); i++){
                                                    fin<<char(i+65)<<" ";
                                                    outDegree = rand() % upOut + lowOut;
                                                    fin<<outDegree<<" ";
                                                    for(int j = 0; j < outDegree; j++){
                                                        fin<<char(rand() % (verticies) + 65)<<" ";
                                                        fin<<rand() % upTime + lowTime<<" ";
                                                    }
                                                    fin<<std::endl;
                                                }
                                                //system("CLS");
                                                break;
                                            }
                                            else{system("CLS");std::cout<<"...Invalid choice, please try again..."<<std::endl;}
                                        }
                                        catch(std::invalid_argument){system("CLS");std::cerr<<"...Invalid choice please try again..."<<std::endl;}
                                    }
                                    else{std::cout<<"...Please try again..."<<std::endl;}
                                }
                                else{std::cout<<"Error: file \""<<file<<"\" already exists, please try again"<<std::endl;}    
                            }                          
                        case 3:     // exit option               
                            system("CLS");
                            break;
                        default:
                            std::cout<<"Error: Invalid choice, please try again..."<<std::endl;
                            break;
                    }
                    if(case_num2 == 3){break;}
                }
                break;
            case 3:     // Adjacency table analysis
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
                            display_linked_list(a_ptr->find_adjacent(choice));
                        }
                        catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                    }
                }
                system("CLS");
                break;
            case 4:     // Dikstra's Algorithm
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
            case 5:     // Depth-First search
                if(a_ptr == nullptr){std::cout<<"...Please select file to read from first..."<<std::endl;break;}
                a_ptr->display_table();
                //Node *n_ptr;
                stack_ptr = new Stack(vertex_num);
                time_complexity = 0;
                while(true){
                    int visit_num = 1;
                    std::cout<<"Please enter element to act as root or type '/' to exit\n=>";
                    std::cin>>choice;
                    if(choice == '/'){break;}
                    else{
                        try{
                            linked_list_ptr = new LinkedList;
                            stack_ptr->push(choice);    // choosing element to act as the root 
                            while(!stack_ptr->stack_is_empty()){
                                try{
                                    time_complexity++;
                                    stack_ptr->pop(choice);
                                    std::cout<<"removed "<<choice<<" from stack"<<std::endl;
                                    if(!a_ptr->is_marked(choice)){
                                        linked_list_ptr->add_rear(choice);
                                        a_ptr->visit(visit_num,choice);
                                        std::cout<<"Visit "<<choice<<" as "<<visit_num<<std::endl;
                                        visit_num++;
                                        if(a_ptr->find_out_degree(choice) == 0){std::cout<<"Deadend reached - backup."<<std::endl;}
                                        else{
                                            n_ptr = a_ptr->find_adjacent(choice);
                                            while(n_ptr != nullptr){
                                                stack_ptr->push(n_ptr->vertex_);
                                                n_ptr = n_ptr->next_;
                                            }
                                        }
                                    }    
                                    else{std::cout<<choice<<" has been visited already - backup."<<std::endl;}
                                    std::cout<<"stack is:"<<std::endl;
                                    stack_ptr->display_stack();
                                }
                                catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                            }
                            a_ptr->display_table();
                            a_ptr->clear_visit_numbers();
                            std::cout<<std::endl<<"Elements in ascending visit number order:"<<std::endl;
                            linked_list_ptr->display_list(); std::cout<<std::endl;
                            std::cout<<"\nNumber of loop iterations: "<<time_complexity<<std::endl;
                            time_complexity = 0;
                            delete linked_list_ptr;
                            linked_list_ptr = nullptr;
                        }
                        catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                    }
                }
                if(linked_list_ptr != nullptr){
                    delete linked_list_ptr;
                    linked_list_ptr = nullptr;
                }
                if(n_ptr != nullptr){n_ptr = nullptr;}
                delete stack_ptr;
                a_ptr->clear_visit_numbers();
                system("CLS");
                break;
            case 6:     // Breadth-First search
                if(a_ptr == nullptr){system("CLS");std::cout<<"...Please select file to read from first..."<<std::endl;break;}
                a_ptr->display_table();
                //Node *n_ptr;
                queue_ptr = new LinkedList;
                time_complexity = 0;
                while(true){
                    int visit_num = 1;
                    std::cout<<"Please enter element to act as root or type '/' to exit:\n=>";
                    std::cin>>choice;
                    if(choice == '/'){break;}
                    else{
                        try{
                            linked_list_ptr = new LinkedList;
                            queue_ptr->add_rear(choice);
                            while(!queue_ptr->isEmpty()){
                                try{
                                    time_complexity++;
                                    choice = queue_ptr->delete_front();
                                    std::cout<<"removed "<<choice<<" from the queue"<<std::endl;
                                    if(!a_ptr->is_marked(choice)){
                                        linked_list_ptr->add_rear(choice);
                                        a_ptr->visit(visit_num,choice);
                                        std::cout<<"Visit "<<choice<<" as "<<visit_num<<std::endl;
                                        visit_num++;
                                        if(a_ptr->find_out_degree(choice) == 0){std::cout<<"Deadend reached - backup."<<std::endl;}
                                        else{
                                            n_ptr = a_ptr->find_adjacent(choice);
                                            while(n_ptr != nullptr){
                                                queue_ptr->add_rear(n_ptr->vertex_);
                                                n_ptr = n_ptr->next_;
                                            }
                                        }
                                    }    
                                    else{std::cout<<choice<<" has been visited already - backup."<<std::endl;}
                                    std::cout<<"queue is:"<<std::endl;
                                    queue_ptr->display_list();
                                }
                                catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}

                            }
                            a_ptr->display_table();
                            a_ptr->clear_visit_numbers();
                            std::cout<<std::endl<<"Elements in ascending visit number order:"<<std::endl;
                            linked_list_ptr->display_list(); std::cout<<std::endl;
                            std::cout<<"\nNumber of loop iterations: "<<time_complexity<<std::endl;
                            time_complexity = 0;
                            delete linked_list_ptr;
                            linked_list_ptr = nullptr;
                        }
                        catch(Area::BadVertex){std::cerr<<"Error: no such vertex exists"<<std::endl;}
                    }
                }
                if(linked_list_ptr != nullptr){
                    delete linked_list_ptr;
                    linked_list_ptr = nullptr;
                }
                if(n_ptr != nullptr){n_ptr = nullptr;}
                delete queue_ptr;
                a_ptr->clear_visit_numbers();
                system("CLS");
                break;
            case 7:     // Exit option
                if(a_ptr != nullptr){delete a_ptr;}
                system("CLS");
                break;
            default:
                std::cout<<"Error: Invalid choice please try again..."<<std::endl;
                break;
        }
        if(case_num == 7){break;}
    }
}