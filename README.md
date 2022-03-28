# Directed Graph Analyzer

This program is made for anlysis of different directed graph algorithms, the edges weight is measured in time from vertex to vertex. vertex's allowed are A-Z so limit of vertex's for this program is 26 for the time being.

This is a simple program to read certian text files to translate them into a adjacency list effectivley making a directed graph for the user to analyze visually through 
the terminal, current analysis options are:

1.) adjacency list analysis when chosen outputs the adjacency list in a clean format then prompts user to select a vertex "A-Z"
to look up specifically its out degree, the adjacent vertex's and the amount of time it would take to travel to such vertex (# located in the paranthesis).

2.) create a "shortest path table" through the use of Dijkstra's algorithm that allows the user to construct the table and look up specific paths and the shortest amount of time from vertex to vertex.

3.) visualizations of a Depth first iteration through the use of a stack data structure that shows step by step of the visit iterations of how a DFS traversal visits certain vertex's, depending on the chosen vertex to act as the root. 

4.) visualizations of a Breadth first iteration through the use of a queue data structure that shows step by step of the visit iterations of how a BFS traversal visits certain vertex's, depending on the chosen vertex to act as the root.

##**Additional features include:

1.) The option to switch text files during runtime.

2.) option to create your own directed graph or randomize one during runtime, both of these options create new text files which are ready to be used.

#**Files descriptions and functionalities:

  ##**DirectedGraphAnalyzerClient.cpp

  *Purpose:

  -This file houses the main function that implements a switch statement to serve as the main menu for users to select given options, options include:

  1.) change input file
  
  2.) create a new directed graph
  
  3.) analysis of vertex's through an adjacency list
  
  4.) visual of Dijkstra's algorithm through table
  
  5.) visualization of DFS through stack data structure
  
  6.) visualization of BFs through queue data structure
  
  7.) exit program
  
  ##**LinkedList.h / LinkedList.cpp
  
  *Purpose:
  
  *Functions:
  
  ##**AdajacencyList.h / AdjacencyList.cpp
  
  *Purpose:
  
  *Functions:
  
  ##**Stack.h / Stack.cpp
  
  *Purpose:
  
  *Functions:
  
  ##**DirectedGraph.h / DirectedGraph.cpp
  
  *Purpose:
  
  *Functions:
  
This project is still very much a work in progress, thank you for viewing!
