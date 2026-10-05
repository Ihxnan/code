#include <ihxnan>
#include <Point>

void solve()
{
    int cnt = 0;
    int n;
    cin >> n;
    ll u1, v1, u2, v2;
    cin >> u1 >> v1 >> u2 >> v2;
    Point<ll> A(u1, v1);
    Point<ll> B(u2, v2);
    Line<ll> L1(A, B);

    vl p12 = {u2 - u1, v2 - v1};

    auto work = [&](const vl &px2) -> ll { return p12[0] * px2[1] - p12[1] * px2[0]; };

    for (ll i = 0, a, b, c, d, x, y; i < n; ++i)
    {
        cin >> a >> b >> c >> d;
        Point<ll> C(a, b);
        Point<ll> D(c, d);
        Line<ll> L2(C, D);
        x = work({a - u1, b - v1});
        y = work({c - u1, d - v1});
        if (x < 0 && y > 0)
        {
            if (get<0>(segmentIntersection(L1, L2)) == 1)
                ++cnt;
        }
        else if (x > 0 && y < 0)
        {
            if (get<0>(segmentIntersection(L1, L2)) == 1)
                --cnt;
        }
    }

    cout << cnt << endl;
}
