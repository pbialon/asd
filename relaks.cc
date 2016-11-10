#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <assert.h>
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
#define PB push_back
#define ST first
#define ND second

const int M = 500;
const int N = 40;
int A[M][N];

LL opt[4][N][4][N]; // zainicjalizowane na 0

inline int next(int x) {
	assert(0 <= x && x < 4);
	x++;
	if (x >= 4)
		return 0;
	return x;
}
inline int prev(int x) {
	assert(0 <= x && x < 4);
	x--;
	if (x < 0)
		return 3;
	return x;
}

// znajdz maksimum z sposrod liczb opt[a][bl..br][c][d]
LL maksPoPierwszejSciezce(int a, int bl, int br, int c, int d) {
	assert(bl <= br);
	LL maks = opt[a][bl][c][d];
	FOR(i, bl + 1, br) {
		LL akt = opt[a][i][c][d];
		if (akt > maks)
			maks = akt;
	}
	return maks;
}
// znajdz maksimum z sposrod liczb opt[a][b][c][d]
LL maksPoDrugiejSciezce(int a, int b, int c, int dl, int dr) {
	assert(dl <= dr);
	LL maks = opt[a][b][c][dl];
	FOR(i, dl + 1, dr) {
		LL akt = opt[a][b][c][i];
		if (akt > maks)
			maks = akt;
	}
	return maks;
}

void wyliczOpt(int m, int n) {
	// dla kazdego wiersza
	FOR(i, 0, m - 1) {
		// rozwazaj 3 ostatnie wiersze w kolejnosci od najdalszego
		int a = i % 4;
		int ostatniWiersz = next(a); // tablica jest cykliczna
		for (int c = ostatniWiersz; c != a; c++) {
			REP(b, n) REP(d, n) {
				// dla kazdej pary pol (a, b) i (c, d) w wierszach a i c
				// znajdz maksymalna wartosc w wierszu a-1, po polach b-2,b-1,..., b+2 i (c,d)
				int maks = maksPoPierwszejSciezce(a - 1, max(0, b - 2), min(b + 2, n - 1), c, d);
				opt[a][b][c][d] = maks + A[a][b];
			}
		}

		// c == a
		REP(b, n) REP(d, n) {
			if (b == d)
				opt[a][b][a][d] = 0;
			else {
				// b != d
				int wierszDwaNizej = prev(prev(a)); // ostatniWiersz = prev(prev(prev(a)));
				LL maksDwaNizej = maksPoDrugiejSciezce(a, b, wierszDwaNizej, max(0, d - 1), min(d + 1, n - 1));
				LL maksTrzyNizej = maksPoDrugiejSciezce(a, b, ostatniWiersz, max(0, d - 1), min(d + 1, n - 1));
				LL maks = max(maksDwaNizej, maksTrzyNizej);
				opt[a][b][a][d] = maks + A[a][d];
			}
		}
	}
}

LL znajdzMax(int m, int n) {
	LL maximum = -1;
	int i = (m - 1) % 4;
	REP(a, n) REP(b, n) {
		LL aktualny = opt[i][a][i][b];
		if(aktualny > maximum)
			maximum = aktualny;
	}
	return maximum;
}


int main() {
	ios_base::sync_with_stdio(false);
	int m, n;
	cin >> m >> n;
	REP(i, m) REP(j, n) cin >> A[i][j];

	return 0;
}