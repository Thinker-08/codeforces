#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <numeric>
#include <cstdio>
#include <list>
#include <cassert>
#include <climits>
using namespace std;
 
#define ll long long
#define pb push_back
#define loop(a) for(int i = 0; i < a; i++)
#define loopv(i,a) for (int i = 0; i < a; i++)
#define rep(i,a,b) for (int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
 
struct segtree {
    struct node {
        ll modify;
        ll value;
    };
 
    int size;
    vector<node> tree;
 
    const ll NO_OP = LLONG_MIN;
    const ll EMPTY = 0;
    const int MOD = 1e9+7;
 
    ll _modify(ll a, ll b) {
        if (a == NO_OP) return b;
        return (a * b) % MOD;
    }
 
    ll _get(ll a, ll b) {
        return (a + b) % MOD;
    }
 
    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2*size);
        build(0, 0, size);
    }
 
    void build(int x, int lx, int rx) {
        if (rx == lx + 1) {
            tree[x] = { NO_OP, 1 };
        } else {
            int m = (lx + rx) / 2;
            build(2*x+1, lx, m);
            build(2*x+2, m, rx);
            tree[x] = { NO_OP, tree[2*x+1].value + tree[2*x+2].value };
        }
    }
 
    void propagate(int x, int lx, int rx) {
        if (tree[x].modify == NO_OP || rx == lx + 1) return;
        tree[2*x+1].modify = _modify(tree[2*x+1].modify, tree[x].modify);
        tree[2*x+1].value = _modify(tree[2*x+1].value, tree[x].modify);
        tree[2*x+2].modify = _modify(tree[2*x+2].modify, tree[x].modify);
        tree[2*x+2].value = _modify(tree[2*x+2].value, tree[x].modify);
        tree[x].modify = NO_OP;
    }
 
    void update(int l, int r, int v) {
        update(l, r, v, 0, 0, size);
    }
 
    void update(int l, int r, int v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r) return;
        if (rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x].modify = _modify(tree[x].modify, v);
            tree[x].value = _modify(tree[x].value, v);
        } else {
            int m = (lx + rx) / 2;
            update(l, r, v, 2*x+1, lx, m);
            update(l, r, v, 2*x+2, m, rx);
            tree[x].value = _get(tree[2*x+1].value, tree[2*x+2].value);
        }
    }
 
    ll get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
 
    ll get(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r) return EMPTY;
        if (rx <= l) return EMPTY;
        if (lx >= l && rx <= r) {
            return tree[x].value;
        } else {
            int m = (lx + rx) / 2;
            ll v1 = get(l, r, 2*x+1, lx, m);
            ll v2 = get(l, r, 2*x+2, m, rx);
            return _get(v1, v2);
        }
    }
};
 
int main(void) {
    int n, m;
    cin >> n >> m;
 
    segtree st;
    st.build(n);
 
    int cmd, l, r, v;
    while (m--) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> l >> r >> v;
            st.update(l, r, v);
        } else {
            cin >> l >> r;
            cout << st.get(l, r) << endl;
        }
    }
 
    return 0;
}