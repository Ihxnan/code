#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    int cnt = 0;
    for (int i = 0; i < n / k; ++i)
    {
        bool flag = true;
        for (int j = i * k; j < (i + 1) * k; ++j)
            if (str[j] == '0')
                flag = false;
        cnt += flag;
    }
    cout << cnt << endl;
}
