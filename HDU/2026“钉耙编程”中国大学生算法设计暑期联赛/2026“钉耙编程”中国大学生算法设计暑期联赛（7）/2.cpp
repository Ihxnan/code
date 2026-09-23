#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    string str;
    cin >> str;
    size_t p00 = str.find("00");
    size_t p01 = str.find("01");
    size_t p10 = str.find("10");
    size_t p11 = str.find("11");

    int cnt = 0;
    cnt += p01 != string::npos;
    cnt += p10 != string::npos;

    auto find = [&](string s) -> bool {
        int i = 0, j = 0;
        while (i < s.size() && j < str.size())
            if (s[i] == str[j++])
                ++i;
        return i == s.size();
    };

    if (p11 != string::npos)
    {
        if (p00 == string::npos)
            cout << (cnt == 0 ? 2 : cnt == 1 ? 3 : 4) << endl;
        else
            cout << (cnt == 1 ? 4 : find("00110") || find("10011") || find("11001") || find("01100") ? 5 : 6) << endl;
    }
    else if (p00 != string::npos)
        cout << (cnt == 0 ? 2 : cnt == 1 ? 3 : 4) << endl;
    else
        cout << cnt + 1 << endl;
}
