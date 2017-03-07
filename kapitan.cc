#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <numeric>
#include <set>
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

#define X first
#define Y second

const int INF = 1000000001;

VPI wyspy;
VVI sasiedzi;
set<PI> Q;


bool verticalComparator(int a, int b) {
	return wyspy[a].Y < wyspy[b].Y;
}

bool horizontalComparator(int a, int b) {
	return wyspy[a].X < wyspy[b].X;
}

bool contains(int a, int b) {
	return find(sasiedzi[a].begin(), sasiedzi[a].end(), b) != sasiedzi[a].end();
}

int distance(int a, int b) {
	return min(abs(wyspy[a].X - wyspy[b].X), abs(wyspy[a].Y - wyspy[b].Y));
}


// PRIORITY QUEUE
int pop() {
	PI p = *Q.begin();
	Q.erase(p);
	return p.ND;
}
// x = ostatnio wstawiony wierzcholek, v = dowolny z sasiadow
void relaxation(int x, int v, VI & dist) {
	int newDist = dist[x] + distance(x, v);
	if (newDist < dist[v]) {
		auto pair = make_pair(dist[v], v);
		Q.erase(pair);
		dist[v] = newDist;
		Q.insert(make_pair(newDist, v));
	}
}



int main() {
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	wyspy.resize(n); sasiedzi.resize(n);
	REP(i, n) cin >> wyspy[i].X >> wyspy[i].Y;

	//stworz graf
	VI pionowo(n), poziomo(n);
	iota(pionowo.begin(), pionowo.end(), 0);
	iota(poziomo.begin(), poziomo.end(), 0);

	sort(pionowo.begin(), pionowo.end(), verticalComparator);
	sort(poziomo.begin(), poziomo.end(), horizontalComparator);

	FOR(i, 1, n - 1) {
		int a = poziomo[i], b = poziomo[i - 1];
		sasiedzi[a].PB(b);
		sasiedzi[b].PB(a);
	}
	FOR(i, 1, n - 1) {
		int a = pionowo[i], b = pionowo[i - 1];
		if (!contains(a, b))
			sasiedzi[a].PB(b);
		if (!contains(b, a))
			sasiedzi[b].PB(a);
	}

	VI dist(n, INF);
	dist[0] = 0;
	REP(i, n) Q.insert(make_pair(dist[i], i));

	while (Q.size() > 0) {
		int x = pop();
		for (int v : sasiedzi[x])
			relaxation(x, v, dist);
	}
	// Wynik
	cout << dist[n - 1];

}