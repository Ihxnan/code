#include <ihxnan>
#include <AhoCorasick>

void solve()
{
    int n;
    cin >> n;
    AhoCorasick ac;
    string str;
    vi ends;
    for (int i = 0; i < n; ++i)
        cin >> str, ends.push_back(ac.add(str));
    ac.work();

    cin >> str;
    vi cnt(ac.size());
    int p = 1;
    for (auto &ch : str)
        ++cnt[p = ac.next(p, ch - 'a')];

    vi order(ac.size() - 1);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int a, int b) { return ac.len(a) > ac.len(b); });

    for (auto &p : order)
        cnt[ac.link(p)] += cnt[p];

    for (auto &p : ends)
        cout << cnt[p] << endl;
}
