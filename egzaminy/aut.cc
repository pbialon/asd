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
#include <tuple>
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


const int N = 524288;

//paths possible to pass through
bool UU[2 * N + 1]; //up->up
bool UD[2 * N + 1]; //up->down
bool DU[2 * N + 1]; //down->up
bool DD[2 * N + 1]; //down->down

//barricade
bool barricade[N][3];

void init() {
	REP(i, 2 * N + 1) {
		UU[i] = UD[i] = DU[i] = DD[i] = true;
	}
	REP(i, N) {
		barricade[i][0] = barricade[i][1] = barricade[i][2] = false;
	}
}


int update(int i, int t) {
	barricade[i][t] = !barricade[i][t];

	int v = N + i);
}




int main() {
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	//stworz drzewo przedzialowe
	init();
	REP(j, m) {
		cin >> i >> t;
	}

}