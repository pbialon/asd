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
#include <tuple>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;
typedef pair<int, int> PI;
typedef vector<PI> VPI;
typedef tuple<int, int, int> TIII;
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

#define DIST 0
#define COLOR 1
#define VERTEX 2

int main() {
	//ios_base::sync_with_stdio(false);

	int n, m;
	scanf("%d %d", &n, &m);
	//cin >> n >> m;

	/**
	 * E[w] = [<v1, k1>, <v2, k2>...] : sasiedzi wierzcholka v
	 * gdzie vi - i-ty sasiad, ki - kolor krawedzi do vi
	 */
	int a, b, k;
	vector<VPI> E(n);
	int dist[n][2];
	REP(i, m) {
		//cin >> a >> b >> k;
		scanf("%d %d %d", &a, &b , &k);
		a--; b--;
		E[a].PB(make_pair(b, k));
		E[b].PB(make_pair(a, k));
	}


	// zmodyfikowana dijkstra
	priority_queue<TIII, vector<TIII>, greater<TIII>> Q;
	REP(i, n) dist[i][0] = dist[i][1] = INF;
	dist[0][0] = dist[0][1] = 0;

	bool processed[n][2];
	REP(i, n) processed[i][0] = processed[i][1] = false;

	Q.push(make_tuple(dist[0][0], 0, 0));
	Q.push(make_tuple(dist[0][1], 1, 0));

	while (!Q.empty()) {
		auto t = Q.top();
		Q.pop();
		int v = get<VERTEX>(t);
		int color = get<COLOR>(t);

		if (!processed[v][color]) {
			for (auto edge : E[v]) {
				int w = edge.ST, color_w = edge.ND;
				if (color_w != color) {
					// mozna przejsc sciezka z v
					if (dist[v][color] + 1 < dist[w][color_w]) {
						dist[w][color_w] = dist[v][color] + 1;
						Q.push(make_tuple(dist[w][color_w], color_w, w));
					}
				}
			}
			processed[v][color] = true;
		}
	}
	FOR(i, 1, n - 1) {
		int d = min(dist[i][0], dist[i][1]);
		if (d < INF)
			printf("%d\n", d);
		//cout << d << endl;
		else
			//cout << -1 << endl;
			printf("%d\n", -1);
	}
}