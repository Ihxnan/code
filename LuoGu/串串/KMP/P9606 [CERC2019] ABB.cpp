#include <ihxnan>
#include <KMP>

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    auto tmp = str;
    reverse(tmp.begin(), tmp.end());
    str = '^' + tmp + '^' + str;
    vi fail = get_fail(str);
    cout << n - fail.back() << endl;
}
