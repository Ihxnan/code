#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
vi primes = {0, 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

vi cnt;
vi prime;
vb is_prime;

void euler_prime(int n)
{
    cnt.resize(n + 1, 1);
    is_prime.resize(n + 1, true);
    for (int i = 2; i <= n; ++i)
    {
        if (is_prime[i])
            prime.push_back(i);
        for (auto &p : prime)
        {
            if (p * i > n)
                break;
            cnt[i * p] = cnt[i] + 1;
            is_prime[i * p] = false;
            if (i % p == 0)
                break;
        }
    }
}

void solve()
{
    ll n, c;
    cin >> n >> c;

    euler_prime(n);

    ll p = c, ans = 0;
    for (int i = 1; i <= n; ++i, p = p * c % mod)
        ans = (ans + primes[cnt[i]] * p) % mod;
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
