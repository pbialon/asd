#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> VI;
typedef long long LL;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push back
#define ST first
#define ND second

// oblicza potegi dwojki od 2^0 do 2^k i zapisuje w pow2
void calculate_powers_of_2(int k, LL pow2[]) {
	LL pow = 1;
	REP(i, k + 1) {
		pow2[i] = pow;
		pow *= 2;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	int matches[m][n + 1];
	LL pow2[m + 1], f[n + 1];
	REP(i, m) FOR(j, 1, n) cin >> matches[i][j];
	calculate_powers_of_2(m, pow2);
	FOR(i, 1, n) f[i] = 0;
	REP(i, m) FOR(j, 1, n / 2) f[matches[i][j]] += pow2[i];
	// posortuj tablice w przedziale [1..n]
	sort(f + 1, f + n + 1);
	// sprawdz czy sa dwie takie same wartosci -> oznacza to ze dwaj gracze zawsze grali w tej samej druzynie
	LL previous = f[1]; // n >= 4 wiec ok
	bool condition = true;
	FOR(i, 2, n) {
		if (f[i] == previous) {
			condition = false;
			break;
		}
		previous = f[i];
	}
	if (condition)
		cout << "TAK" << '\n';
	else
		cout << "NIE" << '\n';

	return 0;
}