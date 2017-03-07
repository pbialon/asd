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

const int INF = 1000000001;


int main() {
	ios_base::sync_with_stdio(false);

	int n, d;
	cin >> n >> d;
	if (d < 0) d = -d;
	int a[n];
	int different_numbers = 0;
	map<int, int> numbers;
	VI description;
	REP(i, n) {
		cin >> a[i];
		int r = a[i] % d;
		if (numbers.find(r) == numbers.end())
			different_numbers++;
		numbers[a[i] % d] = different_numbers - 1;
		description.PB(a[i] % d);
	}
	int different_numbers

}