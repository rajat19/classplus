#include <vector>
#include <iostream>
#include <list>
#include <set>

using namespace std;
#define pii pair<int,int>
#define INF 1000001

class Graph {
	int V;
	list<pii> *adj;
	vector<vector<int>> demons;
public:
	Graph(int V);
	void addEdge(int u, int v, int w);
	void addDemons(vector<vector<int>> &demons);
	vector<int> shortestPath(int s);
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<pii>[V];
}

void Graph::addDemons(vector<vector<int>> &demons) {
	this->demons = demons;
}

void Graph::addEdge(int u, int v, int w) {
	adj[u].push_back(make_pair(v,w));
	adj[v].push_back(make_pair(u,w));
}

vector<int> Graph::shortestPath(int src) {
	set<pii> sets;
	vector<int> dist(V, INF);
	sets.insert(make_pair(0, src));
	dist[src] = 0;
	while (!sets.empty()) {
		pii tmp = *(sets.begin());
		sets.erase(sets.begin());
		int u = tmp.second;
		list<pii>::iterator i;
		for(i=adj[u].begin(); i != adj[u].end(); ++i) {
			int v = (*i).first;
			int weight = (*i).second;
			vector<int> demon = this->demons[v];
			int newPath = dist[u] + weight;
			int demonTime = 0;
			if (newPath < demon.size()) {
				demonTime = demon[newPath];
			}
			if (dist[v] > newPath + demonTime) {
				if(dist[v] != INF) {
					sets.erase(sets.find(make_pair(dist[v], v)));
				}
				dist[v] = dist[u] + weight + demonTime;
				sets.insert(make_pair(dist[v], v));
			}
		}
	}
	return dist;
}

int main3() {
	int a, b, c, n, m, k, t;
	cin>>n>>m;
	Graph g(n+1);
	for(int i=0; i<m; i++) {
		cin>>a>>b>>c;
		g.addEdge(a, b, c);
	}
	vector<vector<int>> demons(n+1);
	for(int i=0; i<n; i++) {
		cin>>k;
		vector<int> dem(k+1, 0);
		if (k>0) {
			for(int j=0; j<k; j++) {
				cin>>dem[j+1];
			}
		}
		demons[i+1] = dem;
	}
	g.addDemons(demons);
	vector<int> ans = g.shortestPath(1);
	cout<<ans[n];
	return 0;
}