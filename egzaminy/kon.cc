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


// WHITE - not processed, RED = first group, BLACK = second one
enum COLOR {WHITE, RED, BLACK};

vector<LL> x, y;
VVI E;
vector<COLOR> color;

// c != WHITE
COLOR other(COLOR c) {
	return c == RED ? BLACK : RED;
}


//dist^2
LL dist(int i, int j) {
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}


bool BFS(int s) {
	if (color[s] != WHITE)
		return true;
	queue<int> Q;
	Q.push(s);
	if (s % 2 == 0)
		color[s] = RED;
	else
		color[s] = BLACK;
	while (Q.size() > 0) {
		int v = Q.front();
		Q.pop();
		// dla kazdego sasiada
		for (int w : E[v]) {
			if (color[w] == WHITE) {
				color[w] = other(color[v]);
				Q.push(w);
			} else if (color[w] == color[v]) return false;
		}
	}
	return true;
}

bool is_bipartide(int n) {
	bool bipartide = true;
	REP(i, n) color[i] = WHITE;
	REP(i, n) bipartide = bipartide && BFS(i);
	return bipartide;
}


int main() {
	ios_base::sync_with_stdio(false);

	int n; LL d;
	cin >> n >> d;
	x.resize(n);
	y.resize(n);
	color.resize(n);
	E.resize(n);

	REP(i, n) {
		cin >> x[i] >> y[i];
	}

	REP(i, n) FOR(j, i + 1, n - 1) {
		if (dist(i, j) > d * d) {
			E[i].PB(j);
			E[j].PB(i);
		}
	}
	// sprawdz czy graf jest dwudzielny
	if (!is_bipartide(n)) cout << "NIE" << endl;
	else {
		cout << "TAK" << endl;
		int count_red = 0;
		REP(i, n) if (color[i] == RED) count_red++;
		cout << count_red << " ";
		REP(i, n) if (color[i] == RED) cout << i + 1 << " ";
		cout << endl;
		cout << n - count_red << " ";
		REP(i, n) if (color[i] == BLACK) cout << i + 1 << " ";
		cout << endl;
	}

}