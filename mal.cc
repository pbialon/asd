#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <assert.h>

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
#define INF 1000002


using Przedzial = pair<int, int>;

struct Komparator {
	bool operator() (const Przedzial &a, const Przedzial &b) {
		return a.ST < b.ST;
	}
};

set<Przedzial, Komparator> biala_autostrada = {{0, -1}, {INF, INF - 1}};
static int biale_pola = 0;

void print() {
	cout << "{";
	for (auto p : biala_autostrada)
		cout << "{" << p.ST << ", " << p.ND << "}" << ", ";
	cout << "}" << endl;
}

void wstaw(int x, int y) {
	biala_autostrada.insert({x, y});
	biale_pola += y - x + 1;
}


void usun(set<Przedzial, Komparator>::const_iterator start, set<Przedzial, Komparator>::const_iterator end) {
	for (auto it = start; it != end; it++)
		biale_pola -= (it->ND + 1 - it->ST);
	biala_autostrada.erase(start, end);
}

// dla bialych przedziałow
void wstaw_bialy(int a, int b) {
	assert(!biala_autostrada.empty());
	// lower_bound : zwraca iterator wskazujacy na pierwszy element (l,r) t, że a <= l
	auto start = lower_bound(ALL(biala_autostrada), make_pair(a, a));
	// start - 1 to iterator do elementu (l, r) takiego, ze l <= a - 1 (albo do {0,-1})
	// => trzeba sprawdzic czy r nie zachodzi na a
	if ((--start)->ND < a - 1)
		start++;
	// upper_bound : zwraca iterator wskazujacy na pierwszy element (l,r) t. że b + 1 < l
	// zatem jest to iterator na pierwszy przedział, który nas "nie interesuje"
	auto end = upper_bound(ALL(biala_autostrada), make_pair(b + 1, b + 1));
	end--;
	// end to iterator do elementu (l, r) takiego, ze l <= b + 1
	// zatem ten przedzial nalezy rowniez usunac o ile a <= l lub a <= r - to zalatwia juz *start
	int x = min(a, start->ST);
	int y = max(b, end->ND);
	//biala_autostrada.erase(start, ++end)
	usun(start, ++end);
	wstaw(x, y);
}


// dla czarnych przedziałów
void wstaw_czarny(int a, int b) {
	auto start = lower_bound(ALL(biala_autostrada), make_pair(a, a));
	if ((--start)->ND < a)
		start++;
	auto end = upper_bound(ALL(biala_autostrada), make_pair(b, b));
	end--;
	int x1 = start->ST, y1 = min(a - 1, start->ND);
	int x2 = max(b + 1, end->ST), y2 = end->ND;
	usun(start, ++end);

	if (x1 <= y1) wstaw(x1, y1);
	if (x2 <= y2) wstaw(x2, y2);
}


int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	int a, b;
	char c;
	REP(i, m) {
		cin >> a >> b >> c;
		if (c == 'C') wstaw_czarny(a, b);
		else wstaw_bialy(a, b);
		cout << biale_pola << '\n';
	}

	return 0;
}