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

// <dist, numer_wierzcholka, kolor_ostatnio_uzytej_krawedzi>
typedef tuple<int, int, int> TIII;

int main() {
	ios_base::sync_with_stdio(false);
	int n, m, a, b, k;
	cin >> n >> m;
	VVI czerwone(n), zielone(n);

	REP(i, m) {
		cin >> a >> b >> k;
		--a, --b;
		if (k == 0) {
			czerwone[a].PB(b);
			czerwone[b].PB(a);
		}
		else {
			zielone[a].PB(b);
			zielone[b].PB(a);
		}
	}

	int dist_czerwony[n], dist_zielony[n];
	
	set<TIII> Q;
	REP(i, n) 

}