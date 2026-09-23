#include <ihxnan>
#include <AhoCorasick>

void solve()
{
    string txt;
    cin >> txt;
    int n;
    cin >> n;
    string str;
    AhoCorasick ac;
    vector<string> ends(100001);
    for (int i = 0; i < n; ++i)
        cin >> str, ends[ac.add(str)] = str;
    ac.work();
    swap(str, txt);
    int p = 1;
    vi stk;
    vi cnt(ac.size());
    string ans;
    for (int i = 0; i < str.size(); ++i)
    {
        ans += str[i];
        stk.push_back(p);
        ++cnt[p = ac.next(p, str[i] - 'a')];

        if (ends[p].size())
            for (int j = ends[p].size() - 1; j >= 0; --j)
            {
                --cnt[p];
                p = stk.back();
                stk.pop_back();
                ans.pop_back();
            }
    }
    cout << ans << endl;
}
