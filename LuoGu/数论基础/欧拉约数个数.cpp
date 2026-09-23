#include <ihxnan>

vb is_prime;
vi primes, num, c1;

void prime(int n)
{
    c1.resize(n + 1);

    num.resize(n + 1);
    num[1] = 1;

    is_prime.resize(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; ++i)
    {
        if (is_prime[i])
            primes.push_back(i), num[i] = 2, c1[i] = 1;
        for (auto &p : primes)
        {
            if (i * p > n)
                break;
            is_prime[i * p] = false;
            if (i % p == 0)
            {
                c1[i * p] = c1[i] + 1;
                num[i * p] = num[i] / (c1[i] + 1) * (c1[i * p] + 1);
                break;
            }
            c1[i * p] = 1;
            num[i * p] = num[i] * num[p];
        }
    }
}

int init = [] { return cin >> t, prime(1e7), 0; }();

void solve()
{
    int n;
    cin >> n;
    cout << num[n] << endl;
}
