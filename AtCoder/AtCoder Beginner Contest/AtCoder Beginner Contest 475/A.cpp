#include <ihxnan>

void solve()
{
    string str;
    cin >> str;
    cout << str[0];
    for (int i = 1; i < str.size(); ++i)
        cout << 'o' << str[i];
}
