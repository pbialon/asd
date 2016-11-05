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

const int MOD = 1000000000;


int main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	int T[n];
	REP(i, n) cin >> T[i];
	/* ile[l][r][0] = ile jest ciagow ktore generuja ciag T[l..r] i ostatnim wstawianym elementem jest T[l]
	 * ile[l][r][1] = ile jest ciagow ktore generuja ciag T[l..r] i ostatnim wstawianym elementem jest T[r]
	 */
	if (n == 1) {
		cout << 1;
		return 0;
	}
	LL ile[n][n][2];
	REP(i, n) ile[i][i + 1][0] = ile[i][i + 1][1] = (T[i] < T[i + 1]);

	FOR(j, 2, n - 1) {
		FOR(l, 0, n - j - 1) {
			int r = l + j;
			ile[l][r][0] = ile[l][r][1] = 0;
			if (T[l] < T[r])
				ile[l][r][1] += ile[l][r - 1][0];
			if (T[r - 1] < T[r])
				ile[l][r][1] = (ile[l][r][1] + ile[l][r - 1][1]) % MOD;
			if (T[l + 1] > T[l])
				ile[l][r][0] += ile[l + 1][r][0];
			if (T[r] > T[l])
				ile[l][r][0] = (ile[l][r][0] + ile[l + 1][r][1]) % MOD;
		}
	}
	cout << (ile[0][n - 1][0] + ile[0][n - 1][1]) % MOD << '\n';
	/*
	cout << "=======================" << endl;
	FOR(j, 1, n - 1) FOR(l, 0, n - j - 1) {
		int r = l + j;
		cout << l << ".." << r << ": " << ile[l][r][0] << ", " << ile[l][r][1] << endl;
	}*/

	return 0;
}