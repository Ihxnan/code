#include <ihxnan>
#include <HLD>

template <class T> struct SegmentTree {
    int n;
    vector<T> in;
    vector<T> tree, tag;

    SegmentTree(int n) : n(n), in(n + 1), tree(4 * n), tag(4 * n, -1)
    {
    }

    SegmentTree(vector<T> &arr) : n(arr.size() - 1), in(arr), tree(4 * n), tag(4 * n)
    {
        build();
    }

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            tree[p] = in[l];
            return;
        }
        int mid = l + r >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);
    }

    void change(int p, int l, int r, T k)
    {
        tree[p] = k;
        tag[p] = k;
    }

    void push_down(int p, int l, int r)
    {
        if (tag[p] != -1)
        {
            int mid = l + r >> 1;
            change(ls(p), l, mid, tag[p]);
            change(rs(p), mid + 1, r, tag[p]);
            tag[p] = -1;
        }
    }

    void update(int ul, int ur, int p, int l, int r, T k)
    {
        if (ul <= l && r <= ur)
        {
            change(p, l, r, k);
            return;
        }
        push_down(p, l, r);
        int mid = l + r >> 1;
        if (ul <= mid)
            update(ul, ur, ls(p), l, mid, k);
        if (ur > mid)
            update(ul, ur, rs(p), mid + 1, r, k);
    }

    T query(int ql, int qr, int p, int l, int r)
    {
        if (ql <= l && r <= qr)
            return tree[p];
        push_down(p, l, r);
        T ans = 0;
        int mid = l + r >> 1;
        if (ql <= mid)
            ans += query(ql, qr, ls(p), l, mid);
        if (qr > mid)
            ans += query(ql, qr, rs(p), mid + 1, r);
        return ans;
    }

    void build()
    {
        build(1, 1, n);
    }

    void update(int ul, int ur, T k)
    {
        update(ul, ur, 1, 1, n, k);
    }

    T query(int ql, int qr)
    {
        return query(ql, qr, 1, 1, n);
    }
};
void solve()
{
    int n;
    cin >> n;
    HLD hld(n);
    for (int i = 1, u, v; i < n; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work();

    SegmentTree<int> segt(n);
    auto &in = hld.in, &fa = hld.fa, &dep = hld.dep, &top = hld.top, &out = hld.out;
    auto update1 = [&](int x) -> void { segt.update(in[x], out[x] - 1, 1); };
    auto update2 = [&](int u, int v) -> void {
        while (top[u] != top[v])
        {
            if (fa[top[u]] < fa[top[v]])
                swap(u, v);
            segt.update(in[top[u]], in[u], 0);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        segt.update(in[u], in[v], 0);
    };

    auto query = [&](int v) -> int { return segt.query(in[v], in[v]); };

    int q;
    cin >> q;
    for (int i = 0, c, v; i < q; ++i)
    {
        cin >> c >> v;
        if (c == 1)
            update1(v);
        else if (c == 2)
            update2(1, v);
        else
            cout << query(v) << endl;
    }
}
