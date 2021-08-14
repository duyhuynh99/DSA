#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) 
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph
{
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}
	
	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	#include <queue>
	Adjacency *BFS(int v)
    {
        // v is a vertex we start BFS
        queue<int>tan;
		vector<int> mark(V);
		tan.push(v);
		Adjacency* arr = new Adjacency();
		while (!tan.empty()) {
			int n = tan.front();
			int size = adj[n].getSize();
			tan.pop();
			arr->push(n);
			mark[n] = 1;
			for (int i = 0; i < size; i++) {
				if (mark[adj[n].getElement(i)] == 0) {
					tan.push(adj[n].getElement(i)); mark[adj[n].getElement(i)] = 1;
				}
			}

		}
		return arr;
	}
};
int main(){
    int V = 6;
int visited = 0;

Graph g(V);
Adjacency* arr = new Adjacency(V);
int edge[][2] = {{0,1},{0,2},{1,3},{1,4},{2,4},{3,4},{3,5},{4,5}};
    
for(int i = 0; i < 8; i++)
{
    g.addEdge(edge[i][0], edge[i][1]);
}
    
arr = g.BFS(visited);
arr->printArray();
delete arr;
}