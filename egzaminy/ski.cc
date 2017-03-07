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

// WHITE - not processed, RED = first group, BLACK = second one
enum COLOR {WHITE, RED, BLACK};

COLOR other(COLOR c) {
	return c == RED ? BLACK : RED;
}

bool BFS(int s, COLOR color[], const VVI & E) {
	if (color[s] != WHITE)
		return true;
	queue<int> Q;
	Q.push(s);
	color[s] = RED;
	while (Q.size() != 0) {
		int v = Q.front();
		Q.pop();
		// dla kazdego sasiada
		for (int w : E[v])
			if (color[w] == WHITE) {
				color[w] = other(color[v]);
				Q.push(w);
			} else if (color[w] == color[v]) return false;
	}
	return true;
}


int main() {
ios_base::sync_with_stdio(false);
	int n, m, a, b;
	cin >> n >> m;
	VVI neighbours(n);
	REP(i, m) {
		cin >> a >> b;
		a--; b--;
		neighbours[a].PB(b);
		neighbours[b].PB(a);
	}

	COLOR color[n];
	REP(i, n) color[i] = WHITE;

	bool is_bipartide = true;

	REP(i, n) is_bipartide = is_bipartide && BFS(i, color, neighbours);

	if (is_bipartide) cout << "TAK" << endl;
	else cout << "NIE" << endl;}