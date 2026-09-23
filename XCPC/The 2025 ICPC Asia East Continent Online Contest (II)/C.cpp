#include <ihxnan>
#include <MaxFlow>

int init = [] { return cin >> t, 0; }();

MaxFlow<int> mf;
void solve()
{
    int s;
    cin >> s;
    int a, b, c, ab, ac, bc, abc;
    cin >> a >> b >> ab >> c >> ac >> bc >> abc;

    auto check = [&](int x) -> bool {
        int s = 0, t = 8;
        mf.init(t + 1);
        mf.addEdge(s, 1, a);
        mf.addEdge(s, 2, b);
        mf.addEdge(s, 3, ab);
        mf.addEdge(s, 4, c);
        mf.addEdge(s, 5, ac);
        mf.addEdge(s, 6, bc);
        mf.addEdge(s, 7, abc);
        mf.addEdge(3, 1, ab);
        mf.addEdge(3, 2, ab);
        mf.addEdge(5, 1, ac);
        mf.addEdge(5, 4, ac);
        mf.addEdge(6, 2, bc);
        mf.addEdge(6, 4, bc);
        mf.addEdge(7, 1, abc);
        mf.addEdge(7, 2, abc);
        mf.addEdge(7, 4, abc);
        mf.addEdge(1, t, x);
        mf.addEdge(2, t, x);
        mf.addEdge(4, t, x);
        return mf.flow(s, t) == 3 * x;
    };

    int l = -1, r = s, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? l = mid : r = mid;

    cout << l << endl;
}
