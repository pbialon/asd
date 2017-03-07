#include <cstdio>
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


int main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	VI s(n);
	REP(i, n) cin >> s[i];

	sort(ALL(s));

	int last = s[0], current_length = 0;
	int max_length = 0;

	REP(i, n) {
		if (s[i] - last > 1) {
			max_length = max(max_length, current_length);
			current_length = 0;
		}
		last = s[i];
		current_length++;
	}
	max_length = max(max_length, current_length);


	cout << max_length << endl;
}