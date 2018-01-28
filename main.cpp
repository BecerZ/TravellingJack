//--------------------------------------------------------------------
// Title: main.cpp
// Author: Bora Ecer
// ID: 21501757
// Section: 02
// Assignment: 4
// Description: cpp file which includes the main method.
//--------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include "AdjMatrix.h"

using namespace std;

int main()
{
  AdjMatrix *a = new AdjMatrix("input.txt");
  a->findShortestPath();
  delete a;
}