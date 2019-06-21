#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <map>
#include <climits>
#include "Q1functions.h"
#define INF 99999
#define NULL 99999
using namespace std;

bool errorCheck(string fileName)
{
  fstream file;
  file.open(fileName);
  if (file.is_open())
    return true;
  else
    return false;
  file.close();
}

int ** createAdjacencyMatrix(string fileName, int numNames)
{
  int ** adjMatrix = new int * [numNames];
  for (int i = 0; i < numNames; i++)
  {
    adjMatrix[i] = new int[numNames];
  }

  // Initialize all matrix entries to 0
  for (int i = 0; i < numNames; i++)
  {
    for (int j = 0; j < numNames; j++)
    {
      adjMatrix[i][j] = 0;
    }
  }

  ifstream f;
  int follows, followed;
  f.open(fileName);
  for (follows; f >> follows >> followed;)
  {
    adjMatrix[follows][followed] = 1;
  }
  f.close();

  // Check matrix.
  cout << endl << "ADJMATRIX:" << endl;
  for (int i = 0; i < numNames; i++)
  {
    for (int j = 0; j < numNames; j++)
    {
      cout << adjMatrix[i][j] << " ";
    }
    cout << endl;
  }

  return adjMatrix;
}

tuple <vector<string>, map<string,int>, int> createNamesVector(string fileName)
{
  ifstream f;
  vector<string> names;
  map<string,int> namesMap;
  string personName;
  int index;

  f.open(fileName);
  // Runs through file and adds all names to a vector.
  for (index; f >> index >> personName;)
  {
    names.push_back(personName);
    namesMap[personName] = index;
  }
  f.close();

  tuple <vector<string>, map<string,int>, int> namesTuple;
  namesTuple = make_tuple(names, namesMap, index + 1);

  return namesTuple;
}

tuple <int **, int **> floydWarshall(int ** adjMatrix, int numNames)
{
  // Create Matrices
  int ** piMatrix = new int * [numNames];
  int ** distMatrix = new int * [numNames];
  for (int i = 0; i < numNames; i++)
  {
    piMatrix[i] = new int[numNames];
    distMatrix[i] = new int[numNames];
  }
  // Setting top left to bottom right entries to 0 and NULL
  for (int i = 0; i < numNames; i++)
  {

  }
  // If there is a connection between nodes set entry to 1,
  // else set to INF
  for (int i = 0; i < numNames; i++)
  {
    for (int j = 0; j < numNames; j++)
    {
      if (i == j)
      {
        distMatrix[i][j] = 0;
        piMatrix[i][j] = NULL;
      }
      else if (adjMatrix[i][j] == 1)
      {
        distMatrix[i][j] = 1;
        piMatrix[i][j] = i;
      }
      else
      {
        distMatrix[i][j] = INF;
        piMatrix[i][j] = NULL;
      }
    }
  }

  cout << endl << "DMATRIX BEFORE:" << endl;
  for (int i = 0; i < numNames; i++)
  {
    for (int j = 0; j < numNames; j++)
    {
      if (distMatrix[i][j] == INF)
        cout << "I" << " ";
      else
        cout << distMatrix[i][j] << " ";
    }
    cout << endl;
  }

  // Floyd-Warshall
  for (int k = 0; k < numNames; k++)
  {
    for (int i = 0; i < numNames; i++)
    {
      for (int j = 0; j < numNames; j++)
      {
        if (distMatrix[i][k] + distMatrix[k][j] < distMatrix[i][j])
        {
          distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];
          piMatrix[i][j] = k;
        }
      }
    }
  }


  // Checks matrix
  cout << endl << "DMATRIX AFTER:" << endl;
  for (int i = 0; i < numNames; i++)
  {
    for (int j = 0; j < numNames; j++)
    {
      if (distMatrix[i][j] == INF)
        cout << "I" << " ";
      else
        cout << distMatrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl << "PIMATRIX:" << endl;
  for (int i = 0; i < numNames; i++)
  {
    for (int j = 0; j < numNames; j++)
    {
      if (piMatrix[i][j] == NULL)
        cout << "N" << " ";
      else
        cout << piMatrix[i][j] << " ";
    }
    cout << endl;
  }

  tuple <int **, int **> output;
  output = make_tuple(distMatrix, piMatrix);
  return output;
}

bool isPath(int startNum, int endNum)
{

}

tuple <vector<int>, int> shortestPath(int ** shortestDistMatrix, int ** shortestPiMatrix, int startNum, int endNum)
{
  cout << "SHORTEST PATH PROGRAM BEGIN!!!" << endl;;
  int pathLength = shortestDistMatrix[startNum][endNum];
  vector<int> path;
  int prev, curr;
  prev = startNum;
  curr = shortestPiMatrix[startNum][endNum];
  cout << curr << endl;
  path.push_back(startNum);
  while (prev != curr)
  {
    path.push_back(prev);
    cout << curr << endl;
    prev = curr;
    curr = shortestPiMatrix[prev][endNum];
  }
  path.push_back(endNum);
  tuple <vector<int>, int> shortestPathTuple;
  shortestPathTuple = make_tuple(path, pathLength);

  return shortestPathTuple;
}

void printShortestPath(vector<int> path, vector<string> namesVector, int pathLength)
{
  cout << "Shortest path between " << namesVector[path[0]] << " to ";
  cout << namesVector[path[path.size()-1]] << " takes " << pathLength << " steps takes the following route:" << endl;
  cout << namesVector[path[0]];
  for (int i = 1; i < path.size(); i++)
  {
    cout << "->" << namesVector[path[i]];
  }
  cout << endl;
}

vector<int> longestPath(int ** shortestDistMatrix, int yourNum, int numNames)
{
  vector<int> longestNum;
  int furthestNum = yourNum;
  int max = 0;
  for (int i = 0; i < numNames; i++)
  {
    if (shortestDistMatrix[yourNum][i] > max && shortestDistMatrix[yourNum][i] < INF)
    {
      max = shortestDistMatrix[yourNum][i];
      furthestNum = i;
    }
  }
  for (int i = 0; i < numNames; i++)
  {
    if (shortestDistMatrix[yourNum][i] == max)
      longestNum.push_back(i);
  }
  return longestNum;
}

void printLongestPath(vector<int> furthestNum, vector<string> namesVector)
{
  cout << namesVector[furthestNum[0]];
  for (int i = 1; i < furthestNum.size(); i++)
  {
    cout << " and "<< namesVector[furthestNum[i]];

  }
  cout << " is the furthest person from you!" << endl;

}
