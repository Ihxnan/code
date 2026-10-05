#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, q;
    cin >> n >> q;

    vi arr(n);
    rd0(arr);
    sort(arr.begin(), arr.end());

    vi ans;
    ans.push_back(arr.back() - arr.front());

    vi qry(q);
    int ma = 0;
    for (auto &p : qry)
        cin >> p, ma = max(ma, p);

    while (arr.back() && ans.size() < ma + 1)
    {
        vi tmp;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                tmp.push_back(arr[i] ^ arr[j]);
        sort(tmp.begin(), tmp.end());
        for (int i = 0; i < n; ++i)
            arr[i] = tmp[i];
        ans.push_back(arr.back() - arr.front());
    }

    for (auto &p : qry)
        if (p < ans.size())
            cout << ans[p] << endl;
        else
            cout << 0 << endl;
}
