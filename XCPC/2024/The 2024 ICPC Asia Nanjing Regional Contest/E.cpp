#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;

    auto work = [&](string str) -> int {
        int res = 0;
        size_t idx = 0;
        while ((idx = str.find("nanjing", idx)) != string::npos)
            ++res, idx += 7;
        return res;
    };

    int ans = 0;
    for (int i = 0; i <= min(k, 6); ++i)
    {
        ans = max(ans, work(str));
        str = str.substr(1) + str[0];
    }

    cout << ans << endl;
}
