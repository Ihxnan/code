#include <ihxnan>

int init = [] { return cin >> t, 0; }();

int tx[] = {1, -1, 0, 0};
int ty[] = {0, 0, 1, -1};
int dx[] = {2, 2, -2, -2, 1, -1, 1, -1};
int dy[] = {1, -1, 1, -1, 2, 2, -2, -2};

void solve()
{
    int mx, my, jx, jy;
    cin >> mx >> my >> jx >> jy;
    for (int i = 0; i < 8; ++i)
        if (mx + dx[i] == jx && my + dy[i] == jy)
            return cout << "NO" << endl, void();

    for (int i = 0; i < 4; ++i)
    {
        int ta = mx + tx[i];
        int tb = my + ty[i];

        if (ta != jx || tb != jy)
        {
            int a = mx + dx[2 * i];
            int b = my + dy[2 * i];
            if (a >= 1 && a <= 9)
                if (b >= 1 && b <= 10)
                    if (a != jx && b != jy)
                        return cout << "NO" << endl, void();

            a = mx + dx[2 * i + 1];
            b = my + dy[2 * i + 1];
            if (a >= 1 && a <= 9)
                if (b >= 1 && b <= 10)
                    if (a != jx && b != jy)
                        return cout << "NO" << endl, void();
        }
    }

    cout << "YES" << endl;
}
