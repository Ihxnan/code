#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, x;
    cin >> n >> x;

    vi fact;
    for (int i = 1; i <= sqrt(x); ++i)
        if (x % i == 0)
            fact.push_back(i), fact.push_back(x / i);
    sort(fact.begin(), fact.end());
    fact.erase(unique(fact.begin(), fact.end()), fact.end());

    vl ans(fact.size());
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        for (int j = 1; j < fact.size(); ++j)
            if (t % fact[j] == 0)
                ans[j] += t;
    }

    cout << *max_element(ans.begin(), ans.end()) << endl;
}
