#include <ihxnan>

bool is_prime(int x)
{
    if (x < 2)
        return false;
    for (int i = 2; i <= sqrt(x); ++i)
        if (x % i == 0)
            return false;
    return true;
}

void solve()
{
    string str;
    cin >> str;
    map<char, vi> memo;
    for (int i = 0; i < str.size(); ++i)
        memo[str[i]].push_back(i);
    int b = 1;
    for (int i = 1; i < str.size(); ++i)
        b *= 10;

    for (int i = b + 1; i < b * 10; i += 2)
    {
        set<int> s;
        int t = i;
        vi arr;
        while (t)
            s.insert(t % 10), arr.push_back(t % 10), t /= 10;
        if (s.size() != memo.size())
            continue;
        reverse(arr.begin(), arr.end());
        bool flag = true;
        for (auto &[k, v] : memo)
            if (flag && v.size() > 1)
            {
                for (int j = 1; j < v.size(); ++j)
                    if (arr[v[j]] != arr[v[j - 1]])
                    {
                        flag = false;
                        break;
                    }
            }
        if (flag && is_prime(i))
            return cout << i << endl, void();
    }
    cout << -1 << endl;
}
