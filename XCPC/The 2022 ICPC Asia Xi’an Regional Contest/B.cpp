#include <bits/stdc++.h>
#include <dbg>
using namespace std;
#define int long long

const int MAXN = 250 * 250 * 2 + 1000;
const int INF = 1e18;

int n, m, c, d;
vector<string> grid;

struct Edge {
    int to, cap, rev;
};

vector<Edge> G[MAXN];
int level[MAXN], iter[MAXN];

void add_edge(int from, int to, int cap)
{
    if (cap <= 0)
        return;
    G[from].push_back({to, cap, (int)G[to].size()});
    G[to].push_back({from, 0, (int)G[from].size() - 1});
}

bool bfs(int s, int t)
{
    for (int i = 0; i < MAXN; i++)
        level[i] = -1;
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (auto &e : G[v])
        {
            if (e.cap > 0 && level[e.to] < 0)
            {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] >= 0;
}

int dfs(int v, int t, int f)
{
    if (v == t)
        return f;
    for (int &i = iter[v]; i < (int)G[v].size(); i++)
    {
        Edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to])
        {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    int flow = 0;
    while (bfs(s, t))
    {
        for (int i = 0; i < MAXN; i++)
            iter[i] = 0;
        while (true)
        {
            int f = dfs(s, t, INF);
            if (!f)
                break;
            flow += f;
        }
    }
    return flow;
}

int max_cover(int k)
{
    for (int i = 0; i < MAXN; i++)
        G[i].clear();

    int S = 0;
    int T = 1;
    int node_cnt = 2;

    vector<vector<int>> node(n, vector<int>(m, -1));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
            {
                node[i][j] = node_cnt++;
            }
        }
    }

    int row_start = node_cnt;
    node_cnt += n;

    int col_start = node_cnt;
    node_cnt += m;

    for (int i = 0; i < n; i++)
    {
        add_edge(S, row_start + i, k);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
            {
                add_edge(row_start + i, node[i][j], 1);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
            {
                add_edge(node[i][j], col_start + j, 1);
            }
        }
    }

    for (int j = 0; j < m; j++)
    {
        add_edge(col_start + j, T, k);
    }

    int result = max_flow(S, T);
    return result;
}

int calc_cost(int k)
{
    int ecnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
                ecnt++;
        }
    }

    if (k == 0)
    {
        return d * ecnt;
    }

    int covered = max_cover(k);
    int z = ecnt - covered;
    return c * k + d * z;
}

void solve()
{
    cin >> n >> m >> c >> d;
    grid.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    int ecnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
                ecnt++;
        }
    }

    int L = 0, R = min({n, m, ecnt});
    int ans = INF;

    ans = min(ans, calc_cost(0));

    while (R - L > 7)
    {
        int mid1 = L + (R - L) / 3;
        int mid2 = R - (R - L) / 3;
        int cost1 = calc_cost(mid1);
        int cost2 = calc_cost(mid2);
        if (cost1 < cost2)
        {
            R = mid2;
        }
        else
        {
            L = mid1;
        }
    }

    gdb(calc_cost(5));

    // for (int k = L; k <= R; k++)
    // {
    //     ans = min(ans, calc_cost(k));
    // }

    cout << ans << endl;
}

signed main()
{
    solve();
    return 0;
}
