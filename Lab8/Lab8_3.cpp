#include<iostream> 
#include <list>
using namespace std; 
class DirectedGraph 
{ 
	int V;
	list<int> *adj;
	int dd[1000];
	int tt=0;
	bool isCyclicUtil(int v, bool visited[], bool *rs);
public: 
	DirectedGraph(){
        V = 0;
        adj = NULL;
    }
	DirectedGraph(int V)
	{
		this->V = V; 
		adj = new list<int>[V];
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}
	
	int getElement(int i,int idx) 
	{
		auto it = adj[i].begin();
		advance(it, idx);
		return *it;
	}
	
	int getSize(int i){
	    return adj[i].size();
	}
	
    void DQDFS(int v,bool &kt,int hs){
	    dd[v]=this->tt;
        for (int i=0;i<getSize(v);i++){
            if (getElement(v,i)==hs) {
                kt=true;
                return;
            }
            if (dd[getElement(v,i)]!=this->tt) {
                DQDFS(getElement(v,i),kt,hs);
            }
        }
	}
	
	bool isCyclic(){
	    for (int i=0;i<this->V;i++) dd[i]=0;
	    bool kt=false;
	    for (int i=0;i<this->V;i++){
	        this->tt=i+1;
	        DQDFS(i,kt,i);
	        if (kt==true) break;
	    }
	    return kt;
	};
}; 
int main(){
    DirectedGraph g(8); 
int edege[][2] = {{0,6}, {1,2}, {1,4}, {1,6}, {3,0}, {3,4}, {5,1}, {7,0}, {7,1}};

for(int i = 0; i < 9; i++)
	g.addEdge(edege[i][0], edege[i][1]);

if(g.isCyclic()) 
	cout << "Graph contains cycle"; 
else
	cout << "Graph doesn't contain cycle"; 
}