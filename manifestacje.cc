#include <cstdio>
#include <iostream>
#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <utility>
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


const int N = 100000;
// w kazdym wezle (reprezentujacym przedzial czasu [l, r]
//trzymamy mape nr_manifestacji -> liczba uczestnikow w czasie [l,r]
map<int, int> T[2 * N + 1];


void insertToMap(int t, int m) {
	auto it = T[t].find(m);
	int participantsNumber = 0;
	if (it != T[t].end()) {
		participantsNumber = it->second;
		T[t].erase(it);
	}
	participantsNumber++;
	T[t].insert(make_pair(m, participantsNumber));
}

// przedzial a, b; manifestacja numer m
void insert(int a, int b, int m, const VI & time) {
	int l = N + (lower_bound(time.begin(), time.end(), a) - time.begin()); //ok
	int r = N + (upper_bound(time.begin(), time.end(), b) - time.begin()) - 1; //ok
	//[l,r] = przedzial numerow lisci drzewa przedzialowego, dla ktorego
	//lisc reprezentuje moment nalezacy do przedzialu czasowego [a, b]
	//nalezy zwiekszyc na tym przedziale (lisci i w gore) liczbe
	//uczestniczacych w manifestacji m
	if (r < l)
		return;
	// wez wpis o <manifestacja, liczbaUczestnikow> w chwili time[l] z tablicy T
	insertToMap(l, m);
	if (l < r)
		insertToMap(r, m);

	while (l / 2 != r / 2) {
		if (l % 2 == 0)
			insertToMap(l + 1, m);
		if (r % 2 == 1)
			insertToMap(r - 1, m);
		l /= 2;
		r /= 2;
	}
}


void processIntervalTree() {
	FOR(i, 2, 2 * N) {
		// "Złacz" dane o manifestacjach od ojca aktualnego
		// wierzchołka z danymi w tym wierzchołku
		map<int, int> & currentMap = T[i];
		for (auto & it : T[i / 2]) {
			if (currentMap[it.ST])
				currentMap[it.ST] += it.ND;
			else
				currentMap[it.ST] = it.ND;
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> m >> n;

	/* (L[i], R[i], A[i]) = i-ty mieszkaniec w przedziale czasu
	 * (L[i], R[i]) uczestniczy w manifestacji numer A[i]
	 */
	int L[m], R[m], A[m];
	REP(i, m) cin >> L[i] >> R[i] >> A[i];

	// T[i] = i-ty moment czasu w ktorym bedzie ujecie
	VI time(n);
	REP(i, n) cin >> time[i];
	// posortuj momenty od poczatku do konca
	sort(time.begin(), time.end());

	// wsadz dane do drzewa przedzialowego
	REP(i, m) insert(L[i], R[i], A[i], time);
	// spropaguj dane o manifestacjach do lisci
	processIntervalTree();

	// dla kazdego elementu w tablicy time[] znajdz manifestacje 
	// o najwiekszej liczbe uczestnikow i wsadz do mapy <chwilaCzasu, numerManifestacji>
	REP(i, )

}




