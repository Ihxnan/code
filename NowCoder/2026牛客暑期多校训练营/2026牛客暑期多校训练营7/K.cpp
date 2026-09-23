#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

#undef cin
void solve()
{
    int n;
    cin >> n;
    cin.get();
    vector<vector<string>> mp(n);
    string str;
    for (auto &p : mp)
    {
        getline(cin, str);
        int last = 0;
        for (int i = 1; i <= str.size(); ++i)
            if (str[i] == ' ' || !str[i])
                p.push_back(str.substr(last, i - last)), last = i + 1;
    }

    vi sta(n);

    auto check = [&] {
        map<string, int> cnt;
        for (int i = 0; i < n; ++i)
        {
            string str;
            for (int j = 0; j < mp[i].size(); ++j)
                str += j < sta[i] ? mp[i][j] : string(1, mp[i][j][0]);
            ++cnt[str];
        }
        bool flag = false;
        for (int i = 0; i < n; ++i)
        {
            string str;
            for (int j = 0; j < mp[i].size(); ++j)
                str += j < sta[i] ? mp[i][j] : string(1, mp[i][j][0]);
            if (cnt[str] > 1)
                ++sta[i], flag = true;
        }
        return flag;
    };

    while (check())
        ;

    for (int i = 0; i < n; ++i)
    {
        string str;
        for (int j = 0; j < mp[i].size(); ++j)
            str += j < sta[i] ? mp[i][j] : string(1, mp[i][j][0]);
        cout << str << endl;
    }
}
