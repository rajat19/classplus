#include <vector>
#include <iostream>
using namespace std;
#define pii pair<int,int>
#define INF 1000001

class Graph {
	int V;
	int threshold;
	vector<vector<int>> dist;
public:
	Graph(int V, int threshold);
	void addEdge(int u, int v);
	vector<vector<int>> allPairShortestPath();
	int cityCounts(vector<int> &c);
};

Graph::Graph(int V, int threshold) {
	this->V = V;
	this->threshold = threshold;
	dist.resize(V+1, vector<int>(V+1, INF));
	for(int i=1; i<=V; i++) dist[i][i] = 0;
}

void Graph::addEdge(int u, int v) {
	dist[u][v] = 1;
	dist[v][u] = 1;
}

vector<vector<int>> Graph::allPairShortestPath() {
	for(int k=1; k<=V; k++) {
		for(int j=1; j<=V; j++) {
			for(int i=1; i<=V; i++) {
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	return dist;
}

int Graph::cityCounts(vector<int> &c) {
	int count = 0;
	for(int i=1; i<=V; i++) {
		bool flag = true;
		for(int corona: c) {
			if (dist[i][corona] > threshold) {
				flag = false;
				break;
			}
		}
		if (flag) {
			count++;
		}
	}
	return count;
}

int main() {
	int n, h, x, u, v;
	cin>>n>>h>>x;
	vector<int> c(h,0);
	Graph g(n+1, x);
	for(int i=0; i<h; i++) cin>>c[i];
	for(int i=0; i<n-1; i++) {
		cin>>u>>v;
		g.addEdge(u, v);
	}
	vector<vector<int>> d = g.allPairShortestPath();
	int ans = g.cityCounts(c);
	cout<<ans;
	return 0;
}