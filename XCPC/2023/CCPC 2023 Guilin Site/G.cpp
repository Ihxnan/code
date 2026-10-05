#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    string str;
    cin >> str;
    string s, t;
    for (auto &p : str)
        if (p == '(')
            s.push_back('('), t.push_back(')');
        else
        {
            if (t.size() && t.back() == ')')
                s.push_back(t.back()), t.pop_back();
            else
                s.push_back(')');
        }
    reverse(t.begin(), t.end());
    if (s + t == str)
        cout << str << endl;
    else
        cout << "impossible" << endl;
}
