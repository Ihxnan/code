#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    for (int i = 1; i <= n; ++i)
        if (arr[i] == 1)
            break;
        else if (arr[i] == -1)
        {
            arr[i] = 1;
            break;
        }
    for (int i = n; i > 0; --i)
        if (arr[i] == 1)
            break;
        else if (arr[i] == -1)
        {
            arr[i] = 1;
            break;
        }

    for (int i = 1; i <= n; ++i)
        cout << (arr[i] == 1 ? 1 : 0) << ' ';
    cout << endl;
}
