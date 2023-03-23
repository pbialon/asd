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
const int M = 32768;
const int K = 10;
int T[K + 1][2 * M + 1];

void insert(int k, int x, int val) {
	int v = M + x;
	T[k][v] = (T[k][v] + val) % MOD;
	while (v != 1) {
		v /= 2;
		T[k][v] = (T[k][2 * v] + T[k][2 * v + 1]) % MOD;
	}
}

int query(int k, int a, int b) {
	if(a > b)
		return 0;
	int l = M + a, r = M + b;
	int result = T[k][l];
	if (l != r)
		result = (result + T[k][r]) % MOD;
	while (l / 2 != r / 2) {
		if (l % 2 == 0) result = (result + T[k][l + 1]) % MOD;
		if (r % 2 == 1) result = (result + T[k][r - 1]) % MOD;
		l /= 2;
		r /= 2;
	}
	return result;
}

void init() {
	REP(i, K + 1) REP(j, 2 * M + 1) T[i][j] = 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	int p[n + 1];
	FOR(i, 1, n) cin >> p[i];
	// ile[t][i] = ile jest t-inwersji konczących się na liczbę i
	init();
	FOR(i, 1, n) {
		int x = p[i]; // i-ty element permutacji - zaczynamy od pierwszego
		insert(1, x, 1);
		FOR(j, 2, k) insert(j, x, query(j - 1, x + 1, n));
		// ile[k][i] = sum(j=i+1..n) ile[k-1][j] * (indeks(j) < indeks(i)? 1 : 0)
		// ale jezeli idziemy po kolejnych elementach permutacji to  ile[*][j]
		// dla elementów późniejszych w tablicy niż i (czyli tych co nie wchodza do sumy)
		// wynosi 0, bo jeszcze go nie liczyliśmy, a wszystkie ile[*][j] dla indeks(j) < indeks(i)
		// są juz policzone i bierzemy tylko te ktore są wieksze od i
		// zatem równosc upraszcza sie do ile[k][i] = sum(j=i+1..n) ile[k-1][j];
		// ile[j][x] = query(k, x + 1, n); insert(j, x, ile[j][x]);
	}
	cout << T[k][1] << '\n';

	return 0;
}
