#include <ihxnan>

void solve()
{
    int n, m, c, t;
    cin >> n >> m >> c >> t;
    vb dong(n + 1);
    for (int i = 0, tmp; i < c; ++i)
        cin >> tmp, dong[tmp] = true;
    vb bao(n + 1);
    for (int i = 0, tmp; i < t; ++i)
        cin >> tmp, bao[tmp] = true;
    vvi adj(n + 1);
    for (int i = 0, u, v; i < m; ++i)
    {
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vi p(2 * n);
    for (auto &q : p)
        cin >> q;

    struct Node {
        int id;
        int pos;
        int step;
        Node(int id = 0, int pos = -1, int step = 0) : id(id), pos(pos), step(step)
        {
        }
        bool operator<(const Node &oth) const
        {
            if (pos != oth.pos)
                return pos > oth.pos;
            return step < oth.step;
        }
    };

    vb sta(n + 1);
    priority_queue<Node> que, que2;

    sta[1] = true;
    Node tmp{1, -1, 0};
    que.push(tmp);

    while (que.size())
    {
        auto [id, pos, step] = que.top();
        que.pop();
        for (auto &nxt : adj[id])
            if (!sta[nxt])
            {
                sta[nxt] = true;
                if (dong[nxt] && step >= 1)
                    tmp = {nxt, pos, 0};
                else if (dong[nxt] && step < 1)
                    tmp = {nxt, pos + 1, 0};
                else if (step >= 1)
                    tmp = {nxt, pos, step - 1};
                else
                    tmp = {nxt, pos + 1, p[pos + 1] - 1};
                que.push(tmp);
                if (bao[nxt])
                    que2.push(tmp);
            }
    }

    swap(bao, sta);
    swap(que, que2);

    tmp = Node();

    while (que.size())
    {
        auto [id, pos, step] = que.top();
        if (id == 1)
        {
            tmp = {id, pos, step};
            break;
        }
        que.pop();
        for (auto &nxt : adj[id])
            if (!sta[nxt])
            {
                sta[nxt] = true;
                if (dong[nxt] && step >= 1)
                    tmp = {nxt, pos, 0};
                else if (dong[nxt] && step < 1)
                    tmp = {nxt, pos + 1, 0};
                else if (step >= 1)
                    tmp = {nxt, pos, step - 1};
                else
                    tmp = {nxt, pos + 1, p[pos + 1] - 1};
                que.push(tmp);
            }
    }

    if (tmp.id != 1)
        return cout << -1 << endl, void();

    cout << tmp.pos + 1 << endl;
}
