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

	int n, k;
	cin >> n >> k;
	int a[n];
	REP(i, n) cin >> a[i];

	int i = 0, j = 0; // przedzial [i, j)
	int map_size = 0;
	LL intervals_count = 0;
	map<int, int> elements;

	while (i < n) {
		// dla kazdego i - poczatku przedzialu
		while (map_size <= k && j < n) {
			//dodaj nastepny element
			int count = elements.count(a[j]);
			if (count == 0) {
				if (map_size == k)
					break;
				else
					map_size++;
			}
			elements[a[j]] = count + 1;
			//idz na prawo prawym koncem
			j++;
		}
		cout << i << " " << j << endl;
		// maksymalny przedzial [i, j) k-spojny : kazdy podprzedzial tez k-spojny
		intervals_count += static_cast<LL>(j - i);
		// jest k elementow w mapie wiec za duzo - zmien lewy koniec
		i++;
		while (map_size > k && i < j) {
			int count = elements.count(a[i - 1]);
			if (count == 1) {
				elements.erase(elements.find(a[i - 1]));
				map_size--;
			} else
				elements[a[i - 1]] = count - 1;
			//idz w prawo lewym koncem
			i++;
		}
	}
	cout << intervals_count << endl;
}