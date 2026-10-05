#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    map<int, int> memo;
    for (int i = 0, t; i < 2 * n; ++i)
        cin >> t, ++memo[t];

    set<int> odd;
    vi even;
    for (auto &[k, v] : memo)
    {
        for (int i = 0; i < v / 2; ++i)
            even.push_back(k);
        if (v % 2)
            odd.insert(k);
    }

    if (odd.size() > 2)
        return cout << "Bot" << endl, void();

    int sum = 0;
    for (auto &p : even)
        sum ^= p;

    if (odd.size() == 0)
    {
        if (!sum)
            cout << "Menji" << endl;
        else
            cout << "Bot" << endl;
        return;
    }

    if (odd.count(sum))
        cout << "Menji" << endl;
    else
        cout << "Bot" << endl;
}
