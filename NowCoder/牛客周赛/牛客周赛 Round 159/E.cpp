#include <ihxnan>
#include <StrHash>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    unordered_map<ul, int> hash;
    char op;
    string str;
    for (int i = 0; i < n; ++i)
    {
        cin >> op >> str;
        StrHash sh(str);
        if (op == '+')
            for (int j = 0; j < str.size(); ++j)
                ++hash[sh.get(0, j)];
        else
            for (int j = 0; j < str.size(); ++j)
                if (--hash[sh.get(0, j)] == 0)
                    hash.erase(sh.get(0, j));
        cout << hash.size() << endl;
    }
}
