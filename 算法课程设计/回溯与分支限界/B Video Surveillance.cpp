#include <ihxnan>

void solve()
{
    int n;
    int t = 0;
    while (cin >> n, n)
    {
        cout << "Floor #" << ++t << endl;
        ll sx, sy, lx, ly, cx, cy;
        cin >> sx >> sy;
        lx = sx, ly = sy;
        ll left = -lINF, right = lINF, down = -lINF, up = lINF;
        for (int i = 1; i < n; ++i)
        {
            cin >> cx >> cy;
            if (lx == cx)
            {
                if (ly < cy)
                    left = max(left, lx);
                else
                    right = min(right, lx);
            }
            else
            {
                if (lx < cx)
                    up = min(up, ly);
                else
                    down = max(down, ly);
            }
            lx = cx, ly = cy;
        }

        cx = sx, cy = sy;
        if (lx == cx)
        {
            if (ly < cy)
                left = max(left, lx);
            else
                right = min(right, lx);
        }
        else
        {
            if (lx < cx)
                up = min(up, ly);
            else
                down = max(down, ly);
        }

        cout << "Surveillance is " << (left <= right && down <= up ? "" : "im") << "possible." << endl << endl;
    }
}
