#include <iostream>
using namespace std;

const int COMPLICATED = -2;
const int WHITE = 0;
const int BLACK = 1;
const int MAX = 1048576;

const int COUNT = 0;
const int STATE = 1;

const int LEFT = 0;
const int RIGHT = 1;

const int SUBSET = 0;
const int EMPTYSET = 1;
const int OTHER = 2;

int t[2 * MAX][2];
int range[2 * MAX][2];

int max (int a, int b)
{
	return a > b ? a : b;
}
int min (int a, int b)
{
	return a < b ? a : b;
}

int oblicz_zakres() {
	range[1][LEFT] = 1;
	range[1][RIGHT] = MAX;
	int parent;
	for(int i = 2; i < 2 * MAX; i += 2) {
		parent = i / 2;
		range[i][LEFT] = range[parent][LEFT];
		range[i][RIGHT] = (range[parent][RIGHT] + range[parent][LEFT]) / 2;
		range[i + 1][LEFT] = range[i][RIGHT] + 1;
		range[i + 1][RIGHT] = range[parent][RIGHT];
	}
}

int oblicz_przeciecie(int a1, int b1, int a2, int b2) {
	if(a1 == a2)
	{
		if(b1 <= b2)
			return SUBSET; // (a1, b1) podzbiór (a2, b2)
		else
			return OTHER;
	}
	if(a1 > a2){
		if(b2 < a1)
			return EMPTYSET; // puste przeciecie
		else
			if(b1 <= b2)
				return SUBSET; // (a1, b1) podzbiór (a2, b2)
			else
				return OTHER;
	}
	// a1 < a2
	if(b1 < a2)
		return EMPTYSET;
	return OTHER;
}

void wypelnij(int nr, int a, int b, int z) {
	int intersect = oblicz_przeciecie(range[nr][LEFT], range[nr][RIGHT], a, b);
	switch(intersect)
	{
		case EMPTYSET :
			return;
		case SUBSET :
			t[nr][STATE] = z;
			t[nr][COUNT] = (z == BLACK ? 0 : range[nr][RIGHT] - range[nr][LEFT] + 1);
			break;
		case OTHER :
			int tmp = t[nr][STATE] - z;
			// przedział jest w kolorze na który chcemy go pokolorowac
			if (tmp == 0)
				return;
			// przedział jest jednokolorowy, ale w przeciwnym kolorze
			if (tmp * tmp <= 1 && nr < MAX) {
				//UWAGA NA KONIEC TABLICY
				t[2 * nr][STATE] = t[2 * nr + 1][STATE] = t[nr][STATE];
				t[2 * nr][COUNT] = t[2 * nr + 1][COUNT] = t[nr][COUNT] / 2;
				t[nr][STATE] = COMPLICATED;
			}
			if(nr < MAX) {
				wypelnij(2 * nr, a, b, z);
				wypelnij(2 * nr + 1, a, b, z);
				t[nr][COUNT] = t[2 * nr][COUNT] + t[2 * nr + 1][COUNT];
			} 
	}
}

int liczba_zer() {
	return t[1][COUNT];
}

int main() {
	int n, m;
	cin >> n >> m;
	int przedzial[m][3];
	char c;
	oblicz_zakres();
	for(int i = 0; i < m; i++)
	{
		cin >> przedzial[i][0] >> przedzial[i][1];
		cin >> c;
		przedzial[i][2] = (c == 'B' ? WHITE : BLACK);
	}
	wypelnij(1, 1, n, BLACK);
	for(int i = 0; i < m; i++)
	{
		wypelnij(1, przedzial[i][0], przedzial[i][1], przedzial[i][2]);
		cout << liczba_zer() << endl;
	}
	return 0;
}