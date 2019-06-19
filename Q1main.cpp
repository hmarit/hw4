#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include "Q1functions.h"
using namespace std;

int main()
{
  string namesFile, linksFile;
  do {
    cout << "Please input names file: ";
    cin >> namesFile;
  } while (!errorCheck(namesFile));
  do {
    cout << "Please input links file: ";
    cin >> linksFile;
  } while (!errorCheck(linksFile));

  // Reads in nicknames.txt and adds all names to a vector.
  tuple <vector<string>, map<string,int>, int> namesOutput;
  namesOutput = createNamesVector(namesFile);
  int numNames;
  vector<string> namesVector;
  map<string,int> namesMap;
  namesVector = get<0>(namesOutput);
  namesMap = get<1>(namesOutput);
  numNames = get<2>(namesOutput);

  // Creates adjacency matrix of all links.
  int ** adjMatrix;
  adjMatrix = createAdjacencyMatrix(linksFile, numNames);

  // Creates distance matrix and pi matrix
  // using the Floyd-Warshall Algorithm.
  int ** shortestDistMatrix;
  int ** shortestPiMatrix;
  tuple <int **, int **> floydWarshallOutput;
  floydWarshallOutput = floydWarshall(adjMatrix, numNames);
  shortestDistMatrix = get<0>(floydWarshallOutput);
  shortestPiMatrix = get<1>(floydWarshallOutput);

  // Can choose multiple programs.
  cout << "SELECT PROGRAM TO BEGIN:" << '\n';
  cout << "1. ";

  // Finds the shortest path from person A to person B
  tuple <vector<int>, int> shortestPathOutput;
  vector<int> pathNumbers;
  int numPeopleBtwn, startNum, endNum;
  string startName, endName;
  cout << "Please input starting name: ";
  cin >> startName;
  cout << "Please input ending name: ";
  cin >> endName;
  startNum = namesMap[startName];
  endNum = namesMap[endName];


  shortestPathOutput = shortestPath(shortestDistMatrix, shortestPiMatrix, startNum, endNum);
/*
  pathNumbers = get<0>(shortestPathOutput);
  numPeopleBtwn = get<1>(shortestPathOutput);
  printPath(pathNumbers, namesVector);
*/

  return 0;
}
