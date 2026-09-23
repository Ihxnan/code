#include<bits/stdc++.h>
#define int long long
#define ll long long
#define  db double
#define PII pair<int,int>
#define read(a,n) for_each(a,a+n,[](int &x){cin >>x;})
#define rep(i, a, b) for(int i = a; i <= (b); ++i)
#define per(i, a, b) for(int i = a; i >= (b); --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using namespace std;
#ifdef LOCAL
void dbg_out() { cerr << endl; }

template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << H << (sizeof...(T) ? ", " : ""); 
    dbg_out(T...);
}
#define dbg(...) cerr << "Line " << __LINE__ << ": [" << #__VA_ARGS__ << "] = ", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 
#endif
// #define endl '\n'
const int N=1e5+10,mod=998244353,inf = 1e18 +10;
class SegTree {
private:
    struct Node {
        long long mx;
        Node() :  mx(0) {} 
        Node(long long v) :  mx(v) {}
    };

    int n;
    vector<Node> tr;
    static constexpr int lc(int i){
        return i << 1;
    }
    static constexpr int rc(int i){
        return i << 1 | 1;
    }
    Node merge(const Node& a, const Node& b) {
        Node res;
        res.mx = max(a.mx, b.mx);
        return res;
    }

    void apply(int u, int l, int r, long long v) {
        tr[u].mx = v;
    }


    void build(int u, int l, int r, const vector<long long>& a) {
        if (l == r) { tr[u] = Node(a[l]); return; }
        int mid = l + r >> 1;
        build(lc(u), l, mid, a);
        build(rc(u), mid + 1, r, a);
        tr[u] = merge(tr[lc(u)], tr[rc(u)]);
    }

    void modify(int u, int l, int r, int ql, int qr, long long v) {
        if (ql <= l && r <= qr) return apply(u, l, r, v);
        int mid = l + r >> 1;
        if (ql <= mid) modify(lc(u), l, mid, ql, qr, v);
        if (qr > mid) modify(rc(u), mid + 1, r, ql, qr, v);
        tr[u] = merge(tr[lc(u)], tr[rc(u)]);
    }

    Node query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[u];
        int mid = l + r >> 1;
        if (qr <= mid) return query(lc(u), l, mid, ql, qr);
        if (ql > mid) return query(rc(u), mid + 1, r, ql, qr);
        return merge(query(lc(u), l, mid, ql, qr), query(rc(u), mid + 1, r, ql, qr));
    }

public:
    SegTree(int n) : n(n), tr((n << 2) + 1) {}
    SegTree(const vector<long long>& a) : SegTree(a.size() - 1) { build(1, 1, n, a); }

    void add(int l, long long v) { modify(1, 1, n, l, l, v); }
    long long get_max(int l, int r) { return query(1, 1, n, l, r).mx; }
};
void solve(){
    int n,q;
    cin >> n >> q;
    vector<int> l(n),r(n),ql(q),qr(q),id1(n),id2(q),ans(q),tmp;
    set<int> hash;
    rep(i,0,n-1){
        cin >> l[i] >> r[i];
        if (l[i] == r[i]) hash.insert(l[i]);
        tmp.push_back(l[i]);
        tmp.push_back(r[i]);
    }
    rep(i,0,q-1){
        cin >> ql[i] >> qr[i];
        tmp.push_back(ql[i]);
        tmp.push_back(qr[i]);
    }
    iota(all(id1),0);
    iota(all(id2),0);
    sort(all(id1),[&](int &x,int & y){
        return l[x] < l[y];
    });
    sort(all(id2),[&](int &x,int & y){
        return ql[x] < ql[y];
    });
    sort(all(tmp));
    tmp.erase(unique(all(tmp)),tmp.end());
    SegTree tr(tmp.size() + 5);
    auto f = [&](int x){
        return lower_bound(all(tmp),x) - tmp.begin() + 1;
    };
    int wl = 0,wr = n-1;
    rep(i,0,n-1){
        tr.add(f(r[i]),r[i]-l[i]+1);
    }
    rep(i,0,q-1){
        while(wl <= n - 1 && l[id1[wl]] < ql[id2[i]]){
            tr.add(f(r[id1[wl]]),0);
            wl++;
        }
        ans[id2[i]] = tr.get_max(1,f(qr[id2[i]]));
    }
    rep(i,0,q-1){
        cout << ans[i] << endl;
    }
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T = 1;
    cin >> T;
    while(T--){
        solve();
    }
	return 0;
}
