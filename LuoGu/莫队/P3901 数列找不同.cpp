#include <ihxnan>

void solve()
{
    int n, q;
    cin >> n >> q;
    vi arr(n + 1);
    rd1(arr);

    int blen = sqrt(n);

    vector<ti> qry(q);
    int cnt = 0;
    for (auto &[l, r, id] : qry)
        cin >> l >> r, id = cnt++;

    sort(qry.begin(), qry.end(), [&](auto &x, auto &y) {
        auto &[l1, r1, id1] = x;
        auto &[l2, r2, id2] = y;
        if (bi(l1) != bi(l2))
            return bi(l1) < bi(l2);
        return bi(l1) & 1 ? r1 < r2 :  r1 > r2;
    });

    vi vis(n + 1);

    int sum = 0;

    auto ins = [&](int x) -> void {
        if (++vis[arr[x]] == 1)
            ++sum;
    };

    auto del = [&](int x) -> void {
        if (!--vis[arr[x]])
            --sum;
    };

    vector<string> ans(q);
    int left = 1, right = 0;
    for (auto &[l, r, id] : qry)
    {
        while (right < r)
            ins(++right);
        while (right > r)
            del(right--);
        while (left < l)
            del(left++);
        while (left > l)
            ins(--left);
        ans[id] = sum == r - l + 1 ? "Yes" : "No";
    }

    for (auto &p : ans)
        cout << p << endl;
}
