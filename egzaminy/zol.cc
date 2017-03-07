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

VI lewy, prawy;

void go_away(int i) {
	if (lewy[i] != -1)
		prawy[lewy[i]] = prawy[i];
	if (prawy[i] != -1)
		lewy[prawy[i]] = lewy[i];
	int l = lewy[i] == -1 ? -1 : lewy[i] + 1;
	int r = prawy[i] == -1 ? -1 : prawy[i] + 1;
	cout << l << " " << r << endl;
}

int main() {
	ios_base::sync_with_stdio(false);

	int n; cin >> n;

	lewy.resize(n); prawy.resize(n);

	REP(i, n) {
		lewy[i] = i - 1;
		prawy[i] = i + 1;
	}
	prawy[n - 1] = -1;

	int a;
	REP(i, n) {
		cin >> a;
		go_away(a - 1);
	}


}