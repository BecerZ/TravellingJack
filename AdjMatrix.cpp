//--------------------------------------------------------------------
// Title: AdjMatrix.cpp
// Author: Bora Ecer
// ID: 21501757
// Section: 02
// Assignment: 4
// Description: Implementation of AdjMatrix, which includes the shortest path algorithm
//--------------------------------------------------------------------

#include "AdjMatrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//Constructor For AdjMatrix
AdjMatrix::AdjMatrix( string fileName)
{
    ifstream file;
    file.open(fileName.c_str());
    if( file.fail())
    {
        cerr << "Opening the inputFile failed." << endl;
    }
    else
    {
        int a = 0;
        int b = 0;
        //Getting the first line
        file >> numOfCountries >> wantedCountries >> pathCount;
        
        //declearing the adj matrix, paths
        paths = new int*[numOfCountries];
        int counter1 = 0;
        while(counter1 <= numOfCountries-1)
        {
            paths[counter1] = new int[numOfCountries];
            counter1++;
        }  
        //setting all to 0
        counter1 = 0;
        int counter2 = 0;
        while(counter1 <= numOfCountries-1)
        {
            counter2 = 0;
            while(counter2 <= numOfCountries-1)
            {
                paths[counter1][counter2] = 0;
                counter2++;
            }
            counter1++;
        }
        
        int counterForPaths = 0;
        //Read from the file and assign the corresponding location on the matrix 1.
        while( file >> a >> b)
        {
            paths[a][b] = 1;
            counterForPaths++;
        }
        //to check there are same amount of paths which is provided in the input text
        if(counterForPaths == pathCount)
        {
            cout << "AdjMatrix created successfully" << endl;
        }
        //To print the adj matrix
        counter1 = 0;
        counter2 = 0;
        cout << "AdjMatrix:" << endl;
        while(counter1 <= numOfCountries-1)
        {
            counter2 = 0;
            while(counter2 <= numOfCountries-1)
            {
                cout << paths[counter1][counter2] << " ";
                counter2++;
            }
            cout << endl;
            counter1++;
        }
    }   
}
//Default contstructor
AdjMatrix::AdjMatrix(){}
//Destructor
AdjMatrix::~AdjMatrix()
{
    int counter1 = 0;
    while(counter1 <= numOfCountries-1)
    {
        delete [] paths[counter1];
        delete [] allProperPaths[counter1];
        counter1++;
    }
    delete[] paths;
    delete[] allProperPaths;
}

void AdjMatrix::breathFirst(string **pathsMap,int pos){
    // Traverses a graph beginning at vertex v 
    // by using breadth-first strategy: Iterative Version
    //Pseudo code is taken from the slides.
    queue<int> q;
    //visited list
    int visitedList[numOfCountries];
    int counter1 = 0;
    //initially all of them are not visited
    while(counter1 < numOfCountries)
    {
        visitedList[counter1] = 0;
        counter1++;
    }
	// add v to the queue and mark it as visited
    q.push(pos);
    visitedList[pos] = 1;
    int w = 0;
    int count = 0;
	while (!q.empty())
    {
        w = q.front();
	    q.pop();
        int counter = 0;
        while(counter < numOfCountries)
        {
              if(visitedList[counter] != 1)
              {
                  if(paths[w][counter] != 0)
                  {
                    //Lengths of all proper paths  
                    allProperPaths[pos][counter]=allProperPaths[pos][w]+paths[w][counter];  
                    ostringstream oString;
                    //Cities that has to pass was marked
                    oString <<"->"  << counter ;
                    istringstream iString(oString.str());
                    pathsMap[pos][counter] = pathsMap[pos][w] + iString.str();
                    //mark as visited
                    visitedList[counter] = 1;
                    q.push(counter);
                }
             }    
            counter++;
        }
    }
}
//Find Shortest Path
void AdjMatrix::findShortestPath()
{
    //matrix to keep all lengths of all proper paths
    allProperPaths = new int*[numOfCountries];
    int counter1 = 0;
    int counter2 = 0;
    //initially they all 0
    while(counter1 < numOfCountries)
    {
        allProperPaths[counter1] = new int[numOfCountries];
        counter2 = 0;
        while(counter2 < numOfCountries)
        {
            allProperPaths[counter1][counter2] = 0;
            counter2++;
        }
        counter1++;
    }
    //Matrix to keep the cities that for all proper paths visits individually
     string **pathsMap = new string*[numOfCountries];
     counter1 = 0;
     counter2 = 0;
     //initially they all ""
     while(counter1 <= numOfCountries-1)
     {
        counter2 = 0;
        pathsMap[counter1] = new string[numOfCountries];
        while(counter2 <= numOfCountries-1)
        {
            pathsMap[counter1][counter2] = "";
            counter2++;
        }
        counter1++;
    }
    int cityNo = 0;
    //breathFirst traversal for each city
    while(cityNo < numOfCountries)
    {
        breathFirst(pathsMap,cityNo);
        cityNo++;
    }  
    //the cities which is going to be visited
    int path[wantedCountries];
    //the array which is going to be used to save the wanted cities
    int shortestPathLocation[wantedCountries];
    int shortestLength = 1000; //default value
    int length = 0; //default value
    counter1 = 0;
    //set wanted cities
    while(counter1 <= wantedCountries-1)
    {
        path[counter1] = counter1;
        counter1++;
    }
    //while loop which determines the shortest path, which begins with 0, ends with the cities which are adjacent to city 0
    while(std::next_permutation(path+1, path+wantedCountries))
    {
        length = 0;
        int i = 0;
        //deterimes the lenghts of each proper path, which ends with the cities which are adjacent to city 0
        while(i<wantedCountries-1)
        {
            length = length + allProperPaths[path[i]][path[i+1]];
            i++;
        }
        //determines the total length from the first, to city 0
        length = length + allProperPaths[path[wantedCountries-1]][path[0]];
        //if current length is shorter than the shortestLength, then assigns it as the new shortest length
        if(length < shortestLength)
        {
            shortestLength = length;
            int counter = 0;
            while(counter < wantedCountries)
            {
                shortestPathLocation[counter] = path[counter];
                counter++;
            }
        }
    }
    counter1 = 0;
    //pushes the first city to the vector, shortestPath
    theShortestPath.push_back("0");
    while(counter1 < wantedCountries-1)
    {
        //selects the shortest path from the pathsMap, and pushes it to theShortestPath, 
        //this starts with the first city that we visited, not city 0
        //and ends with the city from which the next destination is city 0. 
        theShortestPath.push_back(pathsMap[shortestPathLocation[counter1]][shortestPathLocation[counter1+1]]);
        counter1++;
    }
    theShortestPath.push_back(pathsMap[shortestPathLocation[wantedCountries-1]] [shortestPathLocation[0]]);
    //print the results
    cout << "the shortest path length is " << shortestLength << endl;
    cout << "shortestPath: ";
    counter1 = 0;
    while(counter1 < theShortestPath.size())
    {
        cout << theShortestPath[counter1];
        counter1++;
    }
    cout << endl;
    //delete pathsMap.
    counter1 = 0;
    while(counter1 <= numOfCountries-1)
    {
        delete [] pathsMap[counter1]; 
        counter1++;
    }
    delete [] pathsMap;
}
