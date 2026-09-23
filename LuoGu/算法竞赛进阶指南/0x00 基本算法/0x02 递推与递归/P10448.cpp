//#define MULTIT
#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    vi arr;
    auto dfs = [&](auto &&self, int pos, int x) -> void {
        if (arr.size() == m)
        {
            for (auto &p : arr)
                cout << p << ' ';
            cout << endl;
            return;
        }
        for (int i = 1; x + i <= n; ++i)
        {
            arr.push_back(x + i);
            self(self, pos + 1, x + i);
            arr.pop_back();
        }
    };
    dfs(dfs, 0, 0);
}
