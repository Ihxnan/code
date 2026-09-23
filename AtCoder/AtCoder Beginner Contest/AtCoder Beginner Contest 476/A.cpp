#include <ihxnan>

void solve()
{
    string str;
    cin >> str;
    if (str.back() == 'e')
        str += 'r';
    else
        str += "er";
    cout << str;
}
