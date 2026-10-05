#include <ihxnan>

string dp[201][201][22][2][2];
#define lazy dp[a][b][n][p]

int nxt_a, nxt_b;
void dfs(int a, int b, int n, int p, int ball)
{
    if (n == 0)
        return;

    // miss
    if (dp[a][b][n][p ^ 1][0] == "NA")
    {
        dp[a][b][n][p ^ 1][0] = lazy[ball] + '/';
        dfs(a, b, n, p ^ 1, 0);
    }

    if (ball) // just hit red, will hit color
        for (int c = 2; c <= 7; ++c)
        {
            nxt_a = a + (p == 0) * c;
            nxt_b = b + (p == 1) * c;

            if (dp[nxt_a][nxt_b][n][p][0] == "NA")
            {
                dp[nxt_a][nxt_b][n][p][0] = lazy[ball] + to_string(c);
                dfs(nxt_a, nxt_b, n, p, 0);
            }
        }

    else if (n > 6) // hit red
    {
        nxt_a = a + (p == 0);
        nxt_b = b + (p == 1);
        if (dp[nxt_a][nxt_b][n - 1][p][1] == "NA")
        {
            dp[nxt_a][nxt_b][n - 1][p][1] = lazy[ball] + to_string(1);
            dfs(nxt_a, nxt_b, n - 1, p, 1);
        }
    }

    else // clear color
    {
        nxt_a = a + (p == 0) * (8 - n);
        nxt_b = b + (p == 1) * (8 - n);
        if (dp[nxt_a][nxt_b][n - 1][p][ball] == "NA")
        {
            dp[nxt_a][nxt_b][n - 1][p][ball] = lazy[ball] + to_string(8 - n);
            dfs(nxt_a, nxt_b, n - 1, p, ball);
        }
    }
}

int init = [] {
    for (int a = 0; a <= 200; ++a)
        for (int b = 0; b <= 200; ++b)
            for (int n = 0; n <= 21; ++n)
                for (int p = 0; p <= 1; ++p)
                    for (int m = 0; m <= 1; ++m)
                        lazy[m] = "NA";
    dp[0][0][21][0][0] = "";
    dfs(0, 0, 21, 0, 0);
    return cin >> t, 0;
}();

void solve()
{
    int a, b, n, p;
    cin >> a >> b >> n >> p;
    cout << (lazy[0] == "NA" ? lazy[1] : lazy[0]) << endl;
}
