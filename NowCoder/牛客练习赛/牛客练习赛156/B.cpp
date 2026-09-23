#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    string s, t;
    cin >> n >> s >> t;
    pair<char, char> r0{'0', 'R'}, r1{'1', 'R'}, b0{'0', 'B'}, b1{'1', 'B'};
    map<pair<char, char>, int> hash;
    for (int i = 0; i < n; ++i)
        ++hash[{s[i], t[i]}];
    int tmp = hash[r0] + hash[b1];
    tmp %= 2;
    if (tmp)
    {
        if (hash[b0] + 2 < hash[r1])
            cout << "Flower" << endl;
        else if (hash[b0] >= hash[r1])
            cout << "Rainbow" << endl;
        else
            cout << "Draw" << endl;
    }
    else
    {
        if (hash[b0] + 1 < hash[r1])
            cout << "Flower" << endl;
        else if (hash[b0] > hash[r1])
            cout << "Rainbow" << endl;
        else
            cout << "Draw" << endl;
    }
}
