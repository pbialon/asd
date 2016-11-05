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
#define INF 1000000001

//Maxy od lewej, Miny od prawej
int fill_arrays(int ParzystaMax[], int ParzystaMin[], int NieparzystaMax[],
                int NieparzystaMin[], LL SumaSufiksowa[], int p[], int n) {
	int parzysta_max = -1, nieparzysta_max = -1, parzysta_min = INF, nieparzysta_min = INF;
	REP(i, n) {
		if (p[i] % 2 == 0 && p[i] > parzysta_max)
			parzysta_max = p[i];
		else if (p[i] % 2 == 1 && p[i] > nieparzysta_max)
			nieparzysta_max = p[i];

		ParzystaMax[i] = parzysta_max;
		NieparzystaMax[i] = nieparzysta_max;
	}
	FORD(i, n - 1, 0) {
		if (p[i] % 2 == 0 && p[i] < parzysta_min)
			parzysta_min = p[i];
		else if (p[i] % 2 == 1 && p[i] < nieparzysta_min)
			nieparzysta_min = p[i];
		ParzystaMin[i] = parzysta_min;
		NieparzystaMin[i] = nieparzysta_min;
	}
	LL suma = 0;
	FORD(i, n - 1, 0) {
		suma += p[i];
		SumaSufiksowa[i] = suma;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n;
	int p[n];
	REP(i, n) cin >> p[i];
	cin >> m;
	int k[m];
	REP(i, m) cin >> k[i];
	int ParzystaMax[n], ParzystaMin[n], NieparzystaMax[n], NieparzystaMin[n];
	LL SumaSufiksowa[n];
	fill_arrays(ParzystaMax, ParzystaMin, NieparzystaMax, NieparzystaMin, SumaSufiksowa, p, n);
	// zaluzmy ze zawsze mozna znalezc taka sume
	REP(i, m) {
		// wez ostatnie k kwot
		LL suma_produktow = SumaSufiksowa[n - k[i]];


		if (suma_produktow % 2 == 0) {
			// suma ostatnich k jest parzysta.
			// znajdz najwieksza parzysta - zakladamy ze ParzystaMax[n-k-1], NieparzystaMax[n-k-1] > 0
			//oraz ParzystaMin[n-k], NieparzystaMin[n-k] > 0
			if (k[i] == n)
				suma_produktow = -1;
				else {
					LL suma1 = -1, suma2 = -1;
					int parzysta_max = ParzystaMax[n - k[i] - 1];
					int nieparzysta_max = NieparzystaMax[n - k[i] - 1];
					int parzysta_min = ParzystaMin[n - k[i]];
					int nieparzysta_min = NieparzystaMin[n - k[i]];
					if (parzysta_max > 0 && nieparzysta_min < INF)
						suma1 = suma_produktow + parzysta_max - nieparzysta_min;
					if (nieparzysta_max > 0 && parzysta_min < INF)
						suma2 = suma_produktow + nieparzysta_max - parzysta_min;
					suma_produktow = suma1 > suma2 ? suma1 : suma2;
					/*
					cout << "========================" << endl;
					REP(i, n) cout << ParzystaMax[i] << " " << NieparzystaMax[i] << " " << ParzystaMin[i] << " " << NieparzystaMin[i] << endl;
					cout << "========================" << endl;*/
				}
		}
		cout << suma_produktow << '\n';
	}

	return 0;
}