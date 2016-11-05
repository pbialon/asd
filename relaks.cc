#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
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

using Sciezka = vector<pair<int, int> >;

// przekazac odpowiedni wiersz tablicy! -> l = max(0, i - 2), r = min(n, i + 2)
int max_skok_wartosc(int l, int r, int X[]) {
	int max = -1;
	// przedzial kolumn ktory trzeba rozwazac
	for (int k = l; k <= r; k++)
		if (X[k] > max)
			max = X[k];
	return max;
}

int max_skok_indeks(int l, int r, int X[]) {
	int max = -1; int index = -1;
	// przedzial kolumn ktory trzeba rozwazac
	for (int k = l; k <= r; k++)
		if (X[k] > max) {
			max = X[k];
			index = k;
		}
	return index;
}

//wyznacz wektor na podstawie wartosci tablicy


int main() {
	ios_base::sync_with_stdio(false);
	int m, n;
	cin >> m >> n;
	int A[m][n];
	REP(i, m) REP(j, n) cin >> A[i][j];
	// optymalna_w_gore/dol[a][b][c] - optymalny zysk dla trasy idącej w
	// górę/dol od pola (0,a)/(m - 1, a) przebiegającej przez pole (b,c)
	int optymalna_w_gore[n][m][n], optymalna_w_dol[n][m][n];
	REP(a, n) REP(b, m) REP(c, n) {
		optymalna_w_gore[a][b][c] = 0;
		optymalna_w_dol[a][b][c] = 0;
	}
	REP(s, n) {
		// dla pola (0, s):
		// 1. oblicz tablice optymalna_w_gore
		// 2. wyznacz optymalna trase
		// 3. znajdz optymalna trase w dól bez trasy okreslonej za pomoca optymalna_w_gore
		REP(i, n) optymalna_w_gore[s][m - 1][i] = 0;
		optymalna_w_gore[s][m - 1][s] = A[m - 1][s];
		// zejdz w dół
		FORD(j, m - 2, 0) {
			REP(i, n) {
				int M = max_skok_wartosc(max(0, i - 2), min(n - 1, i + 2), optymalna_w_gore[s][j + 1]);
				optymalna_w_gore[s][j][i] = (M > 0 ? M + A[j][i] : 0);
			}
		}
		//... policz optymalna_w_dol
		REP(i, n) optymalna_w_dol[s][0][i] = optymalna_w_dol[s][1][i] = 0;
		optymalna_w_dol[s][0][s] = A[0][s];
		FOR(j, 2, m - 1) {
			REP(i, n) {
				int M1 = max_skok_wartosc(max(0, i - 1), min(n - 1, i + 1), optymalna_w_dol[s][j - 2]);
				int M2 = j > 2 ? max_skok_wartosc(max(0, i - 1), min(n - 1, i + 1), optymalna_w_dol[s][j - 3]) : 0;
				int M = max(M1, M2);
				optymalna_w_dol[s][j][i] = (M > 0 ? M + A[j][i] : 0);
			}
		}
	}
	// mamy obliczone optymalne trasy w górę i w dół z kazdego pola

	// dla kazdej optymalnej trasy liczymy trasę powrotną bez uzywania pól uzytych w poprzedniej trasie

	Sciezka optymalna_trasa_gora[n], optymalna_trasa_dol[n];
	// znajdz optymalne sciezki dla kazdego w gore
	REP(s, n) {
		int M = -1, k = -1;
		REP(i, n) {
			if (optymalna_w_gore[s][0][i] > M) {
				M = optymalna_w_gore[s][0][i];
				k = i;
			}
		}
		// mamy max
		optymalna_trasa_gora[s].PB(make_pair(0, k));
		// znajdz max w przedziale (i + 1, j - 2), (i + 1, j + 2)


		FOR(j, 1, m - 1) {
			k = max_skok_indeks(max(0, k - 2), min(n - 1, k + 2), optymalna_w_gore[s][j]);
			optymalna_trasa_gora[s].PB(make_pair(j, k));
		}
		reverse(ALL(optymalna_trasa_gora[s]));
	}
	// znajdz optymalne sciezki dla kazdego w dol
	REP(s, n) {
		//...
	}



	return 0;
}

/*
	REP(s, n) {
		REP(j, m) {
			REP(i, n) cout << optymalna_w_gore[s][j][i] << " ";
			cout << '\n';
		}
		cout << '\n';
		for (auto p : optymalna_trasa_gora[s]) {
			cout << p.ST << " " << p.ND << ": " << A[p.ST][p.ND] << '\n';
		}
		cout << "\n==================\n";
	}
*/

