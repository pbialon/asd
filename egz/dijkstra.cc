#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <numeric>
#include <tuple>
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
#define PB push_back
#define ST first
#define ND second

const int INF = 1000000001;

int main() {
	int n, m, a, b;
	cin >> n >> m;
	VVI sasiedzi(m);
	int dist[n];
	REP (i, m) {
		cin >> a >> b;
		sasiedzi[a].PB(b);
		sasiedzi[b].PB(a);
	}

	bool przetworzone[n];
	REP(i, n) przetworzone[i] = false;

	// PI = <dist, numer>
	priority_queue<PI> Q;
	REP(i, n) dist[i] = INF;
	dist[0] = 0;
	REP(i, n) Q.push(make_pair(-dist[i], i));
	while (!Q.empty()) {
		int v = Q.top().ND;
		Q.pop();
		//relaks
		if (!przetworzone[v]) {
			for (int w : sasiedzi[v]) {
				if (dist[v] + 1 < dist[w]) {
					dist[w] = dist[v] + 1;
					Q.push(make_pair(-dist[w], w));
				}
			}
			przetworzone[v] = true;
		}
	}
	cout << endl;
	REP(i, n) cout << i << " " << dist[i] << endl;


}