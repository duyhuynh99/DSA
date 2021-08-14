#include <iostream>
#include <list>
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
	int dd[1000];
	int tt=0;
	
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
	
	void DQDFS(int v){
	    this->tt++;
	    dd[v]=this->tt;
        for (int i=0;i<adj[v].getSize();i++)
            if (dd[adj[v].getElement(i)]==0) {
                DQDFS(adj[v].getElement(i));
            }
	}
	
	Adjacency *DFS(int v)
    {
        for (int i=0;i<1000;i++) dd[i]=0;
        DQDFS(v);
        /*while (this->tt<this->V){
            for (int i=0;i<this->V;i++) 
                if (dd[i]==0) DQDFS(i);
        }*/
        Adjacency *kq=new Adjacency(this->V);
        for (int i=1;i<=this->tt;i++)
            for (int j=0;j<this->V;j++)
                if (dd[j]==i) {
                    kq->push(j);
                    break;
                }
        return kq;
	}
};
int main(){
int V = 8, visited = 0;

Graph g(V);
Adjacency *arr;
int edge[][2] = {{0,1}, {0,2}, {0,3}, {0,4}, {1,2}, {2,5}, {2,6}, {4,6}, {6,7}};
for(int i = 0; i < 9; i++)
{
	g.addEdge(edge[i][0], edge[i][1]);
}

// g.printGraph();
// cout << endl;
arr = g.DFS(visited);
arr->printArray();
delete arr;
}