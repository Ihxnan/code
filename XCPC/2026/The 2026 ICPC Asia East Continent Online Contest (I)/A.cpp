#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vector<pair<char, int>> arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i].first >> arr[i].second;

    map<int, int> hash;
    for (int i = n; i >= 1; --i)
    {
        auto &[op, num] = arr[i];
        if (op == 'T')
            hash[num] = max(hash[num], i);
        else if (op == '+')
            ;
    }
}
