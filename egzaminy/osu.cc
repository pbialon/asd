#include <cstdio>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;
typedef pair<int, int> PI;
typedef vector<PI> VPI;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define PB push_back
#define ST first
#define ND second

const int INF = 1000000001;


int n, m;
int A, B;
vector<VPI> E;

bool defined(int a, int b) {
	return 0 <= a && a < n && 0 <= b && b < m;
}

void create_edge(int v, int a, int b, string s[]) {
	if (!defined(a, b))
		return;
	int weight = 0;
	if (s[a][b] == '#')
		weight = 1;
	E[v].PB(make_pair(a * m + b, weight));
}

void findAB(string s[]) {
	REP(i, n) REP(j, m)
	if (s[i][j] == 'A')
		A = i * m + j;
	else if (s[i][j] == 'B')
		B = i * m + j;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	string s[n];
	REP(i, n) cin >> s[i];

	//stworz graf

	// E[v] = [<v1, p1>, <v2, p2>, ...] - vi - sasiad, pi - waga krawedzi
	E.resize(n * m);

	REP(i, n) REP(j, m) {
		int v = i * m + j;
		create_edge(v, i - 1, j, s);
		create_edge(v, i + 1, j, s);
		create_edge(v, i, j + 1, s);
		create_edge(v, i, j - 1, s);
	}
	findAB(s);

	//dijkstra z A
	int dist[n * m];
	bool processed[n * m];
	REP(i, n * m) {
		dist[i] = INF;
		processed[i] = false;
	}

	priority_queue<PI> Q;
	dist[A] = 0;
	REP(i, n * m) Q.push(make_pair(-dist[i], i));
	while (!Q.empty()) {
		int v = Q.top().ND;
		Q.pop();

		if (!processed[v]) {
			for (auto edge : E[v]) {
				int w = edge.ST;
				int weight = edge.ND;
				if (dist[v] + weight < dist[w]) {
					dist[w] = dist[v] + weight;
					Q.push(make_pair(-dist[w], w));
				}
			}
			processed[v] = true;
		}
	}
	cout << dist[B] << endl;

}