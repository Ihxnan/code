#include <ihxnan>

void solve()
{
    string str;
    char ch;
    int idx;
    for (int i = 0; i < 9; ++i)
    {
        cin >> ch;
        str += ch;
        if (ch == 'x')
            idx = i;
    }
    string tar = "12345678x";
    queue<tuple<string, int, string>> que;
    que.emplace(str, idx, "");
    unordered_map<string, string> memo;
    while (que.size())
    {
        auto [x, id, res] = que.front();
        que.pop();
        if (x == tar)
            return cout << res << endl, void();
        if (memo.count(x))
            continue;
        memo[x] = res;
        if (id % 3 != 0)
            swap(x[id], x[id - 1]), que.emplace(x, id - 1, res + 'l'), swap(x[id], x[id - 1]);
        if (id % 3 != 2)
            swap(x[id], x[id + 1]), que.emplace(x, id + 1, res + 'r'), swap(x[id], x[id + 1]);
        if (id / 3 != 0)
            swap(x[id], x[id - 3]), que.emplace(x, id - 3, res + 'u'), swap(x[id], x[id - 3]);
        if (id / 3 != 2)
            swap(x[id], x[id + 3]), que.emplace(x, id + 3, res + 'd'), swap(x[id], x[id + 3]);
    }
    cout << "unsolvable" << endl;
}
