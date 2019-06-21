#include <vector>
#include <string>
#include <tuple>
#include <map>
#ifndef Q1FUNCTIONS_H
#define Q1FUNCTIONS_H
using namespace std;

bool errorCheck(string);
int ** createAdjacencyMatrix(string, int);
tuple <vector<string>, map<string,int>, int> createNamesVector(string);
tuple <int **, int **> floydWarshall(int **, int);
bool isPath(int, int);
tuple <vector<int>, int> shortestPath(int **, int **, int, int);
vector<int> longestPath(int **, int, int);
void printShortestPath(vector<int>, vector<string>, int);
void printLongestPath(vector<int>, vector<string>);


#endif
