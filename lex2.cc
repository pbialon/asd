#include <cstdio>
#include <cstdlib>
#include <cassert>
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
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef unsigned long long ULL;
typedef pair<int, int> PI;
typedef vector<PI> VPI;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) typeof(n) v = (n)
#define AULL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define PB push_back
#define ST first
#define ND second

const ULL p = 1009;
//const ULL q = 101111111111;
//const ULL q = 1000000000000037;
const ULL q = 4076863487;

int a, b, c, d, n, m;
vector<ULL> HASH, P;
string s;

ULL multiply_mod(ULL a, ULL b, ULL mod)
{
	ULL res = 0; // Initialize result
	a = a % mod;
	while (b > 0)
	{
		if (b % 2 == 1)
			res = (res + a) % mod;
		a = (a * 2) % mod;
		b /= 2;
	}
	return res % mod;
}


void computePowers() {
	ULL power = 1;
	REP(i, n) {
		P[i] = power;
		power = (power * p) % q;
	}
}



void calculateHashArray() {
	int n = static_cast<int>(s.length());
	ULL curr = 0;
	FORD(i, n - 1, 0) {
		curr  = ((curr * p) % q + s[i]) % q;
		HASH[i] = curr;
	}
}

// hash slowa s[i..j]
ULL getHash(int i, int j) {
	//assert(i <= j);
	if (j == n - 1)
		return HASH[i];
	//ULL hash = q + HASH[i] - multiply_mod(P[j - i + 1], HASH[j + 1], q);
	ULL hash = q + HASH[i] - (P[j - i + 1] * HASH[j + 1]) % q;
	hash %= q;
	return hash;
}

// stringi s[a..b], s[c..d]
int binsearch() {
	//assert(b - a == d - c);
	int l = 0, r = b - a;
	while (l < r) {
		int mid = (l + r) / 2;
		if (getHash(a, a + mid) != getHash(c, c + mid))
			r = mid;
		else
			l = mid + 1;/*
		if(r - l > 1)
			cout << l << " " << r << endl;*/
	}
	return l;
}

char compare() {
	--a; --b; --c; --d;
	int length1 = b - a + 1, length2 = d - c + 1;
	int length = min(length1, length2);
	b = a + length - 1;
	d = c + length - 1;

	int first_difference_pos = binsearch();

	int first_char = s[a + first_difference_pos];
	int second_char = s[c + first_difference_pos];

	if (first_char == second_char) {
		if (length1 > length2)
			return '>';
		else if (length1 < length2)
			return '<';
		else
			return '=';
	} else {
		if (first_char > second_char)
			return '>';
		else
			return '<';
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	cin >> s;

	HASH.resize(n);
	P.resize(n);
	computePowers();
	calculateHashArray();

	REP(i, m) {
		cin >> a >> b >> c >> d;
		// znajdz pierwsza pozycje na ktorej sie roznia - binsearch
		cout << compare() << endl;
	}
}
