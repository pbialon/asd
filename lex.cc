#include <cstdio>
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
typedef long long LL;
typedef vector<LL> VLL;
typedef pair<int, int> PI;
typedef vector<PI> VPI;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define PB push_back
#define ST first
#define ND second

// http://www.geeksforgeeks.org/palindrome-substring-queries/
// http://acm.timus.ru/problem.aspx?space=1&num=1517

VLL prefix_hash;
const LL p = 1009;
const LL q = 1000000007;

int n, m;

VLL powers_of_p;

LL multiply_mod(LL a, LL b, LL n)
{
	LL res = 0; // Initialize result
	a = a % n;
	while (b > 0)
	{
		if (b % 2 == 1)
			res = (res + a) % mod;
		a = (a * 2) % mod;
		b /= 2;
	}
	return res % mod;
}



void computePrefixHashes(const string & s) {
	LL current_hash = s[0];
	LL current_position_hash;
	prefix_hash[0] = current_hash;
	for (int i = 1; i < n; i++) {
		current_hash += multiply_mod(s[i], powers_of_p[i], q);
		current_hash %= q;
		assert(current_hash > 0);
		prefix_hash[i] = current_hash;
	}
}


void computePowersOfp() {
	LL power = 1;
	for (int i = 0; i < n; i++) {
		powers_of_p[i] = power;
		power = multiply_mod(power, p, q);
	}
}

LL getHash(int i, int j) {
	assert(0 <= i && i <= j && j <= n);
	if (i == 0) return prefix_hash[j];

	LL hash = ((prefix_hash[j] - prefix_hash[i - 1]) % q) * powers_of_p[n - i];
	LL hash = prefix_hash[j]
	hash %= q;
	return hash;
}

// zwracac int cyz interator?
void findFirstDifference(int a, int b, int c, int d) {
	//binsearch - jak wykorzystac to z stla?
	// komparator?
}

int main() {
	string s = "ababababaaa";
	n = s.length();
	powers_of_p.resize(n);
	prefix_hash.resize(n);
	computePowersOfp();
	computePrefixHashes(s);
	cout << getHash(1, 4) << " " << getHash(5, 8) << endl;
}


/*
int main() {
	ios_base::sync_with_stdio(false);

	int a, b, c, d;
	string s;
	cin >> n >> m;
	cin >> s;

	// zrob haszowanie
	powers_of_p.resize(n);
	prefix_hash.resize(n);
	computePowersOfp();
	computePrefixHashes(s);

	REP(i, m) {
		cin >> a >> b >> c >> d;
		// znajdz pierwsza pozycje na ktorej sie roznia - binsearch
	}


}*/