#include <ihxnan>

int init = [] { return cin >> t, 0; }();

vb is_prime;

void prime(int n)
{
    is_prime.resize(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= n; ++i)
        if (is_prime[i])
            for (ll j = i * i; j <= n; j += i)
                is_prime[j] = false;
}

void solve()
{
    int n;
    cin >> n;
    prime(n);
    for (int i = 0; i <= n; ++i)
        if (is_prime[i])
            cout << i << ' ';
}
