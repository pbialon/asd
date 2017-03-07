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
VVI E;
VI visited;

enum COLOR {WHITE, GRAY, BLACK};
//czy jest cykl
bool DFS(int v, COLOR visited[]) {
	visited[v] = GRAY;
	for (int w : E[v]) {
		if (visited[w] == BLACK)
			return true;
		else if (visited[w] == WHITE) {
			if (DFS(w, visited)) {
				return true;
			}
		}
	}
	visited[v] = BLACK;
	return false;
}


int main() {
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	int a, b;
	E.resize(n);
	REP(i, m) {
		cin >> a >> b;
		a--; b--;
		E[a].PB(b);
		E[b].PB(a);
	}

	COLOR visited[n];
	REP(i, n) visited[i] = WHITE;
	bool cyclic = false;
	REP(i, n) {
		if (visited[i] == WHITE)
			cyclic = cyclic || DFS(i, visited);
	}
	if (cyclic)
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
}
