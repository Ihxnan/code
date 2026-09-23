//#define MULTIT
#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    string str; 
    for (int i = 0; i < 1 << n; ++i)
    {
        for (int j = n - 1; j >= 0; --j)
            cout << (i >> j & 1 ? 'Y' : 'N');
        cout << endl;
    }
}
