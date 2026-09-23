#include <ihxnan>

int init = [] { return cin >> t, 0; }();

vi primes;
vb is_prime;

void prime(int n)
{
    is_prime.resize(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i)
    {
        if (is_prime[i])
            primes.push_back(i);
        for (auto &p : primes)
        {
            if (p * i > n)
                break;
            is_prime[i * p] = false;
            if (i % p == 0)
                break;
        }
    }
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
