#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    int cur = 0;
    int point = 0;
    vl score(m + 1);
    vector<set<int>> t2(m + 1), t3(m + 1);
    for (int i = 0, op, id, x; i < q; ++i)
    {
        cin >> op;
        if (op == 1)
            cin >> cur, point = m;
        else
        {
            cin >> id >> x;
            if (x != cur)
                continue;
            if (t2[id].count(x) || t3[id].count(x))
                continue;
            if (op == 2)
            {
                t2[id].insert(x);
                score[id] += point--;
            }
            else
                t3[id].insert(x);
        }
    }
    vi per(m);
    iota(per.begin(), per.end(), 1);
    sort(per.begin(), per.end(), [&](int x, int y) {
        if (score[x] != score[y])
            return score[x] > score[y];
        return x < y;
    });
    for (auto &id : per)
        cout << id << ' ' << score[id] << endl;
}
