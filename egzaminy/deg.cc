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
#define INF 100000001


int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	VVI E(n);
	int deg[n];
	REP(i, n) deg[i] = 0;
	REP(i, m) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		E[a].PB(b);
		E[b].PB(a);
		deg[a]++; deg[b]++;
	}

	priority_queue<PI, VPI, greater<PI> > Q;

	REP(i, n) Q.push(make_pair(deg[i], i));

	int current_degenerate = 0;
	while (!Q.empty()) {
		int w, degree;
		auto p = Q.top();
		Q.pop();
		w = p.ND; degree = p.ST;
		if (deg[w] > 0) {
			current_degenerate = max(degree, current_degenerate);
			//cout << w << " " << degree << " " << "degenerate: " << current_degenerate << endl;
			deg[w] = 0;
			//usun wierzcholek z grafu
			for (int v : E[w]) {
				deg[v]--;
				Q.push(make_pair(deg[v], v));
			}
		}
	}

	cout << current_degenerate << endl;
}
