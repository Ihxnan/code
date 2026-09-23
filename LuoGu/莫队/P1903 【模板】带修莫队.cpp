#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    vi arr(n + 1);
    rd1(arr);

    char op;
    int t = 0;
    int dn = 0;
    vi tmp = arr;
    vector<ti> func;
    vector<tuple<int, int, int, int>> qry;
    for (int i = 0, l, r; i < m; ++i)
    {
        cin >> op >> l >> r;
        if (op == 'Q')
            qry.emplace_back(l, r, t, dn++);
        else
            func.emplace_back(l, r, tmp[l]), tmp[l] = r, ++t;
    }

    int blen = pow(n, 0.66);
    sort(qry.begin(), qry.end(), [&](auto &x, auto &y) {
        auto &[l1, r1, t1, id1] = x;
        auto &[l2, r2, t2, id2] = y;
        if (bi(l1) != bi(l2))
            return bi(l1) < bi(l2);
        if (bi(r1) != bi(r2))
            return bi(l1) & 1 ? r1 > r2 : r1 < r2;
        return bi(l1) + bi(r1) & 1 ? t1 > t2 : t1 < t2;
    });

    vi ans(dn);
    int sum = 0;
    vi cnt(1000001);
    int left = 1, right = 0, time = 0;

    auto ins = [&](int x) -> void { sum += ++cnt[arr[x]] == 1; };

    auto del = [&](int x) -> void { sum -= !--cnt[arr[x]]; };

    auto front = [&](int x) -> void {
        auto &[pos, after, before] = func[x];
        arr[pos] = after;
        if (left <= pos && pos <= right)
        {
            sum -= !--cnt[before];
            sum += ++cnt[after] == 1;
        }
    };

    auto back = [&](int x) -> void {
        auto &[pos, after, before] = func[x];
        arr[pos] = before;
        if (left <= pos && pos <= right)
        {
            sum -= !--cnt[after];
            sum += ++cnt[before] == 1;
        }
    };

    for (auto &[l, r, t, id] : qry)
    {
        while (left < l)
            del(left++);
        while (left > l)
            ins(--left);
        while (right < r)
            ins(++right);
        while (right > r)
            del(right--);
        while (time < t)
            front(time++);
        while (time > t)
            back(--time);
        ans[id] = sum;
    }

    for (auto &p : ans)
        cout << p << endl;
}
