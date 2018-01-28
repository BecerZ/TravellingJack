//--------------------------------------------------------------------
// Title: AdjMatrix.h
// Author: Bora Ecer
// ID: 21501757
// Section: 02
// Assignment: 4
// Description: Header file of AdjMatrix class
//--------------------------------------------------------------------

#include <iostream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#ifndef ADJMATRIX_H__
#define ADJMATRIX_H__

class AdjMatrix
{
    public:
        AdjMatrix( string fileName);
        AdjMatrix();
        ~AdjMatrix();
        void breathFirst(string **, int i);
        void findShortestPath();

    private:
        int numOfCountries;
        int wantedCountries;
        int pathCount;
        int **paths;
        int **allProperPaths;
        std::vector<string> theShortestPath;
    
};

#endif