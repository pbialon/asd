#include <cstdio>
#include <iostream>
#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <utility>
#include <cassert>
using namespace std;
typedef vector<int> VI;
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
#define PB push_back
#define MP make_pair
#define ST first
#define ND second

const int M = 1000001;

// kopiec : wektor par <nr manifestacji, ile uczestnikow> w danej chwili
VPI uczestnicy = {make_pair(-1, -1), make_pair(1, 0)};
// wektor rozmiaru m pozycji w kopcu danych o liczbe uczestnikow danej manifestacji w kopcu
VI manifestacja(M);

bool lessThan (const PI & a, const PI & b) {
	if (a.ND != b.ND)
		return a.ND < b.ND;
	return a.ST > b.ST;
}

// zwraca max z kopca w postaci pary <nr, ile>
PI max() {
	assert(uczestnicy.size() > 1);
	return uczestnicy[1];
}

// zamienia pozycjami element i-ty z j-tym z kopca uczestnicy, oraz aktualizuje
// odpowiednio tablice manifestacja[]
void exchange(int i, int j) {
	// poniewaz zamieniamy pare <nr_manifestacji, uczestnicy> pomiedzy i-ta
	// a j-ta pozycja w kopcu to musimy zrobic swap w tablicy manifestacja
	// wskazujacej na pozycje danych o manifestacji nr i w kopcu uczestnicy
	swap(manifestacja[uczestnicy[i].ST], manifestacja[uczestnicy[j].ST]);
	swap(uczestnicy[i], uczestnicy[j]);
}

// poprawia kopiec "do góry" zaczynajac od `pozycja`
void heapifyUp(int pozycja) {
	while (pozycja > 1 && lessThan(uczestnicy[pozycja / 2], uczestnicy[pozycja])) {
		exchange(pozycja / 2, pozycja);
		pozycja /= 2;
	}
}

// wstawia na koniec kopca element <nr, ile> i poprawia kopiec w góre
void insert(int nr, int ile) {
	assert(manifestacja[nr] == -1);
	uczestnicy.PB(make_pair(nr, ile));
	manifestacja[nr] = uczestnicy.size() - 1;
	heapifyUp(uczestnicy.size() - 1);
}

// poprawia kopiec w dół
void heapifyDown(int pozycja) {
	int najwiekszy = pozycja;
	int size  = uczestnicy.size();
	if (2 * pozycja < size && lessThan(uczestnicy[najwiekszy], uczestnicy[2 * pozycja]))
		najwiekszy = 2 * pozycja;
	if (2 * pozycja + 1 < size && lessThan(uczestnicy[najwiekszy], uczestnicy[2 * pozycja + 1]))
		najwiekszy = 2 * pozycja + 1;
	if (najwiekszy != pozycja) {
		exchange(najwiekszy, pozycja);
		heapifyDown(najwiekszy);
	}
}

// aktualizuje licznik osob na manifestacji nr o ile.
void updateCount(int nr, int ile) {
	if (manifestacja[nr] == -1) {
		insert(nr, ile);
		return;
	}
	assert(manifestacja[nr] > 0);
	uczestnicy[manifestacja[nr]].ND += ile;
	if (ile > 0)
		heapifyUp(manifestacja[nr]);
	else
		heapifyDown(manifestacja[nr]);
}


int main() {
	ios_base::sync_with_stdio(false);

	int n, m, t;
	cin >> m >> n;

	/* (P[i], K[i], Nr[i]) = i-ty mieszkaniec w przedziale czasu
	 * (P[i], K[i]) uczestniczy w manifestacji numer Nr[i]
	 */
	int P[m], K[m], Nr[m];
	REP(i, m) cin >> P[i] >> K[i] >> Nr[i];

	// time(i) = <t, i> gdzie t to i-ty moment czasu : drugi element pary
	// potrzebny do odtworzenia poczatkowej sekwencji
	VPI time(n);
	REP(i, n) {
		cin >> t;
		time[i] = MP(t, i);
	}
	// posortuj momenty wg pierwszej wspolrzednej
	sort(time.begin(), time.end());

	// w wektorze @poczatki pary <t, nr> oznaczajace ze w chwili t
	// przyszedl ktos na manifestacje o numerze nr
	// analogicznie w @konce
	VPI poczatki, konce;
	REP(i, m) {
		poczatki.PB(MP(P[i], Nr[i]));
		konce.PB(MP(K[i], Nr[i]));
	}
	//posortuj po czasach
	sort(poczatki.begin(), poczatki.end());
	sort(konce.begin(), konce.end());

	REP(i, M) manifestacja[i] = -1;
	manifestacja[1] = 1;


	auto poczatkiIter = poczatki.begin();
	auto konceIter = konce.begin();
	// kontener na wyniki - wynik[i] = <nr, ile> : w czasie time[i].ST
	// "wygrala" manifestacja o numerze nr i uczestniczylo w niej wtedy @ile ludzi.
	PI wynik[n];
	// dla kazdej chwili time[i].ST
	REP(i, n) {
		//bierz wszystkie "przybycia" na manifestacje ktore odbyly sie pomiedzy poprzedim ujeciem a aktualnym
		while (poczatkiIter != poczatki.end() && poczatkiIter->ST <= time[i].ST) {
			updateCount(poczatkiIter->ND, 1);
			poczatkiIter++;
		}
		// analogicznie wszystkie opuszczenia manifestacji
		while (konceIter != konce.end() && konceIter->ST < time[i].ST) {
			updateCount(konceIter->ND, -1);
			konceIter++;
		}
		wynik[i] = max();
	}
	// wypisz w kolejnosci jaka byla przed posortowaniem momentow ujec
	PI wynikiPrzedSortowaniem[n];
	REP(i, n) wynikiPrzedSortowaniem[time[i].ND] = wynik[i];
	REP(i, n) cout << wynikiPrzedSortowaniem[i].ST << " " << wynikiPrzedSortowaniem[i].ND << endl;

	return 0;
}




/*

void test() {
	int m = 5;
	manifestacja.resize(m);
	REP(i, m) manifestacja[i] = -1;

	auto p = max();
	assert(p.ST == 1 && p.ND == 0);

	updateCount(3, 1);
	p = max();
	assert(p.ST == 3 && p.ND == 1);
	updateCount (1, 2);
	p = max();
	assert(p.ST == 1 && p.ND == 2);

	updateCount(3, 1);
	p = max();
	assert(p.ST == 1 && p.ND == 2);

	updateCount(1, -1);
	p = max();
	assert(p.ST == 3 && p.ND == 2);

	updateCount(2, 4);
	p = max();
	assert(p.ST == 2 && p.ND == 4);

	updateCount(3, 2);
	p = max();
	assert(p.ST == 2 && p.ND == 4);
	updateCount(3, 1);
	p = max();
	assert(p.ST == 3 && p.ND == 5);
}

int main() {
	test();
}
*/