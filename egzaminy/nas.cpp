#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cassert>

#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define MP make_pair
#define SIZE(x) (int)x.size()

using namespace std;

typedef vector< vector<int> > tgraph;
typedef vector< vector< pair<int, int> > > twgraph;

int read_int() {
    int sres, value;
    sres = scanf("%d", &value);
    assert(sres == 1);
    return value;
}

vector<int> read_int_array(int size = -1) {
    int n, sres;
    vector<int> res;
    if (size == -1) {
        sres = scanf("%d", &n);
        assert(sres == 1);
    } else {
        n = size;
    }
    res.resize(n);
    for (int i = 0; i < n; i++) {
        sres = scanf("%d", &res[i]);
        assert(sres == 1);
    }
    return res;
}

// -----------------------------------

int solve(const vector< vector<int> > &v) {
    int n = SIZE(v);
    int l = SIZE(v[0]);
    vector< pair<int, int> > p;
    REP(i, n) REP(j, l) p.push_back(MP(v[i][j], j));
    sort(p.begin(), p.end());

    int res = 1;
    int last_value = -1;
    int last_idx = -1;
    int len = 0;
    FOREACH(it, p) {
        int value = it->first;
        int idx = it->second;
        if (last_idx == -1 || last_value != value || last_idx < idx - 1) {
            len = 1;
        } else if (last_idx == idx - 1) {
            len++;
            res = max(res, len);
        }
        last_idx = idx;
        last_value = value;
    }
    return res;
}

int main() {
    int n = read_int();
    int l = read_int();
    vector < vector<int> > v;
    REP(i, n) {
        v.push_back(read_int_array(l));
    }
    printf("%d\n", solve(v));
    return 0;
}