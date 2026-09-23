#include <ihxnan>

template <class T> struct SegmentTree {
    int n;
    vb sta;
    vector<T> in;
    vector<T> tree;

    SegmentTree(int n) : n(n), in(n + 1), tree(4 * n), sta(n + 1)
    {
    }

    void push_up(int p)
    {
        tree[p] = tree[ls(p)] + tree[rs(p)];
    }

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            tree[p] = sta[l];
            return;
        }
        int mid = l + r >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);
        push_up(p);
    }

    void update(int u, int p, int l, int r, T k)
    {
        if (l == u && u == r)
            return tree[p] += k, void();
        int mid = l + r >> 1;
        if (u <= mid)
            update(u, ls(p), l, mid, k);
        else
            update(u, rs(p), mid + 1, r, k);
        push_up(p);
    }

    T query(int ql, int qr, int p, int l, int r)
    {
        if (ql > qr)
            return 0;
        if (ql <= l && r <= qr)
            return tree[p];
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

    void update(int p, int x)
    {
        in[p] = x;
        if (p - 1 >= 1 && p + 1 <= n)
        {
            if (in[p] - in[p - 1] < in[p + 1] - in[p])
            {
                if (sta[p] != 1)
                    update(p, 1, 1, n, 1);
                sta[p] = 1;
            }
            else
            {
                if (sta[p])
                    update(p, 1, 1, n, -1);
                sta[p] = 0;
            }
        }

        --p;
        if (p - 1 >= 1 && p + 1 <= n)
        {
            if (in[p] - in[p - 1] < in[p + 1] - in[p])
            {
                if (sta[p] != 1)
                    update(p, 1, 1, n, 1);
                sta[p] = 1;
            }
            else
            {
                if (sta[p])
                    update(p, 1, 1, n, -1);
                sta[p] = 0;
            }
        }

        p += 2;
        if (p - 1 >= 1 && p + 1 <= n)
        {
            if (in[p] - in[p - 1] < in[p + 1] - in[p])
            {
                if (sta[p] != 1)
                    update(p, 1, 1, n, 1);
                sta[p] = 1;
            }
            else
            {
                if (sta[p])
                    update(p, 1, 1, n, -1);
                sta[p] = 0;
            }
        }
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    SegmentTree<ll> segt(n);
    for (int i = 1; i <= n; ++i)
        cin >> segt.in[i];
    for (int i = 2; i < n; ++i)
        segt.sta[i] = segt.in[i] - segt.in[i - 1] < segt.in[i + 1] - segt.in[i];
    segt.build();
    for (int i = 0, op, l, r; i < q; ++i)
    {
        cin >> op >> l >> r;
        if (op == 1)
            segt.update(l, r);
        else
            cout << segt.query(l + 1, r - 1, 1, 1, n) << endl;
    }
}
