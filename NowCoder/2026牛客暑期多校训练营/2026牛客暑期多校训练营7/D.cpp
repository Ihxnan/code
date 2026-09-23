#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, x;
    cin >> n >> x;
    vi a, b;
    bool have = false;
    set<int> hash;
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        if (have)
            hash.insert(t);
        else if (t == x)
            have = true;
        else
            a.push_back(t);
    }
    have = false;
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        if (have)
        {
            if (hash.count(t))
                return cout << "NO" << endl, void();
            else
                hash.insert(t);
        }
        else if (t == x)
            have = true;
        else if (!have)
            b.push_back(t);
    }
    if (a.size() && b.size() && a[0] == b[0])
        return cout << "NO" << endl, void();

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    gdb(a, b);
    vb sta(n + 1);
    vi ans;
    while (a.size() && b.size())
    {
        while (a.size() && sta[a.back()])
            a.pop_back();
        while (b.size() && sta[b.back()])
            b.pop_back();

        if (a.size())
        {
            int tmp = a.back();
            a.pop_back();
            while (a.size() && sta[a.back()])
                a.pop_back();
            a.push_back(tmp);
        }

        if (b.size())
        {
            int tmp = b.back();
            b.pop_back();
            while (b.size() && sta[b.back()])
                b.pop_back();
            b.push_back(tmp);
        }

        if (a.empty() || b.empty())
            break;

        if (a.size() > 1 && a[a.size() - 2] == b.back() && b.size() > 1 && b[b.size() - 2] == a.back())
            return cout << "NO" << endl, void();

        if (a.size() > 1 && a[a.size() - 2] == b.back())
            ans.push_back(b.back()), sta[b.back()] = true, b.pop_back();
        else if (b.size() > 1 && b[b.size() - 2] == a.back())
            ans.push_back(a.back()), sta[a.back()] = true, a.pop_back();
        else if (hash.count(a.back()))
            ans.push_back(b.back()), sta[b.back()] = true, b.pop_back();
        else
            ans.push_back(a.back()), sta[a.back()] = true, a.pop_back();
    }

    while (a.size())
    {
        if (!sta[a.back()])
            ans.push_back(a.back());
        a.pop_back();
    }
    while (b.size())
    {
        if (!sta[b.back()])
            ans.push_back(b.back());
        b.pop_back();
    }

    cout << "YES" << endl;
    for (auto &p : ans)
        cout << p << ' ';
}
