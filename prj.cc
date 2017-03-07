#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cassert>
#include <utility>
using namespace std;
typedef vector<int> VI;
typedef long long LL;
typedef pair<int, int> PI;
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

#define WAGA first
#define NUMER second

/*
struct compare {
	bool operator()(const PI & l, const PI & r) {
		return l.WAGA > r.WAGA;
	}
};*/

int main() {
	ios_base::sync_with_stdio(0);
	int n, m, k;
	cin >> n >> m >> k;
	int a, b;
	int w[n];
	VI poprzednicy[n];
	VI nastepnicy[n];
	int ilu_nieobsluzonych_poprzednikow[n];
	REP(i, n) cin >> w[i];
	REP(i, m) {
		cin >> a >> b;
		a--; b--;

		poprzednicy[a].push_back(b);
		nastepnicy[b].push_back(a);
	}
	//policz tablice ile_nieobsluzonych poprzednikow
	REP(i, n) ilu_nieobsluzonych_poprzednikow[i] = poprzednicy[i].size();

	//REP(i, n) cout << i << " " <<  ilu_nieobsluzonych_poprzednikow[i] << endl;

	priority_queue<PI> Q;
	//wrzuc do Q wszystkie liscie <=> te o pustych poprzednikach
	REP(i, n)
	if (poprzednicy[i].size() == 0) {
		auto p = make_pair(-w[i], i);
		Q.push(p);
	}

	int liczba_programistow = 0;
	REP(i, k) {
		assert (Q.size() > 0);
		auto v = Q.top();
		Q.pop();
		int waga = -v.WAGA, numer = v.NUMER;
		//cout << numer + 1 <<  " " << waga << endl;
		liczba_programistow = max(liczba_programistow, waga);
		for (int nastepnik : nastepnicy[numer])
			if (--ilu_nieobsluzonych_poprzednikow[nastepnik] == 0) {
				auto p = make_pair(-max(w[nastepnik], waga), nastepnik);
				Q.push(p);
			}
	}
	cout << liczba_programistow << '\n';
}