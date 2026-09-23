#include <ihxnan>

struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len, link;
        array<int, ALPHABET> next;
        Node() : len(0), link(0), next{}
        {
        }
    };

    vector<Node> tree;

    void init()
    {
        tree.assign(2, Node());
        tree[0].next.fill(1);
        tree[0].len = -1;
    }

    AhoCorasick()
    {
        init();
    }

    int newNode()
    {
        tree.emplace_back();
        return tree.size() - 1;
    }

    int add(const string &str)
    {
        int p = 1;
        for (auto &c : str)
        {
            int x = c - 'a';
            if (tree[p].next[x] == 0)
            {
                tree[p].next[x] = newNode();
                tree[tree[p].next[x]].len = tree[p].len + 1;
            }
            p = tree[p].next[x];
        }
        return p;
    }

    void work()
    {
        queue<int> que;
        que.push(1);
        while (que.size())
        {
            int x = que.front();
            que.pop();

            for (int i = 0; i < ALPHABET; ++i)
                if (tree[x].next[i] == 0)
                    tree[x].next[i] = tree[tree[x].link].next[i];
                else
                {
                    tree[tree[x].next[i]].link = tree[tree[x].link].next[i];
                    que.push(tree[x].next[i]);
                }
        }
    }

    int next(int p, int x)
    {
        return tree[p].next[x];
    }

    int link(int p)
    {
        return tree[p].link;
    }

    int len(int p)
    {
        return tree[p].len;
    }

    int size()
    {
        return tree.size();
    }
};

void solve()
{
    int n;
    string str;
    while (cin >> n, n)
    {
        AhoCorasick ac;
        vector<pair<int, string>> ends;
        for (int i = 0; i < n; ++i)
            cin >> str, ends.emplace_back(ac.add(str), str);
        ac.work();
        cin >> str;
        int p = 1;
        vi cnt(ac.size());
        for (auto &ch : str)
            ++cnt[p = ac.next(p, ch - 'a')];

        vi order(ac.size() - 1);
        iota(order.begin(), order.end(), 1);
        sort(order.begin(), order.end(), [&](int x, int y) { return ac.len(x) > ac.len(y); });

        for (auto &p : order)
            cnt[ac.link(p)] += cnt[p];

        stable_sort(ends.begin(), ends.end(), [&](auto &x, auto &y) { return cnt[x.first] > cnt[y.first]; });

        cout << cnt[ends[0].first] << endl;

        for (auto &[e, s] : ends)
            if (cnt[e] == cnt[ends[0].first])
                cout << s << endl;
            else
                break;
    }
}
