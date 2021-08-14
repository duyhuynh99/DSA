#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;

struct Graph
{
    int V, E;
    vector< pair<int, pair<int, int>> > edges;
    // Constructor 
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w)
    {
        edges.push_back({ w, {u, v} });
    }
    
    //YOUR CODE HERE

int kruskalMST() {
		// TODO: return weight of the minimum spanning tree.
		sort(edges.begin(), edges.end());
		vector<int>  mark(V);
		for (int i = 0; i < V; i++) mark[i] = i;
		int n = 0;
		int count =0;
		while (count!=V-1) {
			if (mark[edges[0].second.first] != mark[edges[0].second.second]) {
				n += edges[0].first;
				int tmp = mark[edges[0].second.second];
				int tmp2 = mark[edges[0].second.first];
				mark[edges[0].second.second] = mark[edges[0].second.first];
				for (int i = 0; i < V; i++) {
					if (mark[i] == tmp) mark[i] = tmp2;
				}
				edges.erase(edges.begin());
				count++;
			}
			else {
				edges.erase(edges.begin());
			}
		}
		return n;
	}
};
int main(){
    int V = 2, E = 1;
Graph g(V, E);
g.addEdge(0, 1, 2);
cout << g.kruskalMST();
}
