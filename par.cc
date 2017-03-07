#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
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

constexpr int log(int n) {
	return static_cast<int>(log2(n));
}
const int MAX_N = 500000;
const int LOG = log(MAX_N);

struct Node {
	int number, depth;
	int maxDistDown, maxDistDownNodeNumber;
	int maxDistUp, maxDistUpNodeNumber;
	int left, right, parent;
};

// Zwraca numer brata wezla i -> jezeli wezel i nie ma brata, to zwroci -1
int getBrotherNodeNumber(Node tree[], int i, int parent) {
	int l = tree[parent].left, r = tree[parent].right;
	if (l != i)
		return l;
	if (r != i)
		return r;
	return -1;
}

void createTree(Node tree[], int A[], int B[], int n) {
	FOR(i, 1, n) {
		tree[i].number = i;
		tree[i].left = A[i - 1];
		tree[i].right = B[i - 1];
		if (A[i - 1] > 0)
			tree[A[i - 1]].parent = i;
		if (B[i - 1] > 0)
			tree[B[i - 1]].parent = i;
	}
	tree[1].parent = -1;
}

void calculateDepth(Node tree[], int i) {
	if (i == -1)
		return;
	if (i == 1) {
		tree[1].depth = 0;
	} else {
		tree[i].depth = tree[tree[i].parent].depth + 1;
	}
	calculateDepth(tree, tree[i].left);
	calculateDepth(tree, tree[i].right);
}

int calculateMaxDistDown(Node tree[], int i) {
	if (i == -1)
		return -1;
	int l = calculateMaxDistDown(tree, tree[i].left);
	int r = calculateMaxDistDown(tree, tree[i].right);
	int node;
	if (l + r == -2) {
		// tree[i] to lisc
		tree[i].maxDistDown = 0;
		tree[i].maxDistDownNodeNumber = i;
	} else {
		//tree[i] to wezel wewnetrzny
		tree[i].maxDistDown = max(l, r) + 1;
		if (l > r)
			node = tree[tree[i].left].maxDistDownNodeNumber;
		else
			node = tree[tree[i].right].maxDistDownNodeNumber;
		tree[i].maxDistDownNodeNumber = node;
	}


	return tree[i].maxDistDown;
}

void calculateMaxDistUp(Node tree[], int i) {
	if (i == -1)
		return;
	if (i == 1) {
		tree[1].maxDistUp = 0;
		tree[1].maxDistUpNodeNumber = 1;
	}
	else {
		//zwykly wezel
		int parent = tree[i].parent;
		tree[i].maxDistUp = tree[parent].maxDistUp + 1;
		tree[i].maxDistUpNodeNumber = tree[parent].maxDistUpNodeNumber;
		int brother = getBrotherNodeNumber(tree, i, parent);
		if (brother > 0) {
			int brotherMaxDistDown = tree[brother].maxDistDown + 2;
			if (tree[i].maxDistUp < brotherMaxDistDown) {
				tree[i].maxDistUp = brotherMaxDistDown;
				tree[i].maxDistUpNodeNumber = tree[brother].maxDistDownNodeNumber;
			}
		}
	}
	calculateMaxDistUp(tree, tree[i].left);
	calculateMaxDistUp(tree, tree[i].right);
}

void calculatePointers(Node tree[], int ptr[][LOG + 1], int i) {
	if (i == -1)
		return;
	if (i == 1) {
		REP(j, LOG + 1) {
			ptr[i][j] = -1;
		}
	} else {
		int pointer = tree[i].parent;
		ptr[i][0] = pointer;
		FOR(j, 1, LOG) {
			if (pointer > 0)
				pointer = ptr[pointer][j - 1];
			ptr[i][j] = pointer;
		}
	}
	calculatePointers(tree, ptr, tree[i].left);
	calculatePointers(tree, ptr, tree[i].right);
}

int goUp(Node tree[], int ptr[][LOG + 1], int i, int steps) {
	int currentNode = i, currentStep = 0;
	while (steps > 0 && currentNode > 0) {
		if (steps % 2 == 1)
			currentNode = ptr[currentNode][currentStep];
		currentStep++;
		steps /= 2;
	}
	return currentNode;
}

int query(Node tree[], int ptr[][LOG + 1], int i, int d) {
	if (tree[i].maxDistDown >= d) {
		int start = tree[i].maxDistDownNodeNumber;
		int steps = tree[i].maxDistDown - d;
		return goUp(tree, ptr, start, steps);
	}
	if (tree[i].maxDistUp >= d) {
		int j = tree[i].maxDistUpNodeNumber;
		int depthLCA = (tree[i].depth + tree[j].depth - tree[i].maxDistUp) / 2;
		// tree[i].depth - depthLCA = dlugosc sciezki od tree[i] do LCA(i,j)
		if (tree[i].depth - depthLCA >= d)
			return goUp(tree, ptr, i, d);
		else
			return goUp(tree, ptr, j, tree[i].maxDistUp - d);
	}
	// nie ma tak odleglego wierzcholka
	return -1;
}


void print(Node tree[], int ptr[][LOG + 1], int n) {
	FOR(i, 1, n) {
		cout << i << " depth " << tree[i].depth <<
		     " max dist down (" << tree[i].maxDistDown << ", " << tree[i].maxDistDownNodeNumber << " )" <<
		     " max dist up (" << tree[i].maxDistUp << ", " << tree[i].maxDistUpNodeNumber << " )" << endl;
	}
	/*
	FOR(i, 1, n) {
		cout << i << ": ";
		REP(j, LOG + 1) {
			cout << "( 2^" << j << " ," << ptr[i][j] << ") ";
		}
		cout << endl;
	}*/

	FOR(i, 1, n) {
		cout << i << ": ";
		REP(j, 5) cout << query(tree, ptr, i, j) <<  " ";
		cout << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	// Wczytaj input
	int n, m;
	cin >> n;
	int A[n], B[n];
	REP(i, n) cin >> A[i] >> B[i];
	cin >> m;
	int S[m], D[m];
	REP(i, m) cin >> S[i] >> D[i];

	Node tree[n + 1];
	int ptr[n + 1][LOG + 1];
	createTree(tree, A, B, n);
	calculateDepth(tree, 1);
	calculateMaxDistDown(tree, 1);
	calculateMaxDistUp(tree, 1);
	calculatePointers(tree, ptr, 1);
	
	//print(tree, ptr, n);

	//odpowiadaj na pytania
	REP(i, m) cout << query(tree, ptr, S[i], D[i]) << endl;

	return 0;
}