//#define MULTIT
#include <ihxnan>

void solve()
{
    int n, k;
    cin >> n >> k;
    vi arr;
    vb sta(n + 1);
    auto dfs = [&](auto &&self, int pos) -> void {
        if (pos > k)
        {
            for (auto &p : arr)
                cout << p << ' ';
            cout << endl;
            return;
        }
        for (int i = 1; i <= n; ++i)
            if (!sta[i])
            {
                sta[i] = true;
                arr.push_back(i);
                self(self, pos + 1);
                arr.pop_back();
                sta[i] = false;
            }
    };
    dfs(dfs, 1);
}
