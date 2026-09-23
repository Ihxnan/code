#include <ihxnan>
#include <StrHash>

int is_prime[500001];
int fac[500001];
vi primes;

int euler = []() {
    memset(is_prime, 1, sizeof is_prime);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= 500000; ++i)
    {
        if (is_prime[i])
            primes.push_back(i), fac[i] = i;
        for (auto &p : primes)
        {
            if (p * i > 500000)
                break;
            fac[p * i] = p;
            is_prime[p * i] = 0;
            if (i % p == 0)
                break;
        }
    }
    return 0;
}();

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    str = '^' + str;
    StrHash hash(str);
    int q;
    cin >> q;
    for (int i = 0, l, r; i < q; ++i)
    {
        cin >> l >> r;
        int res = r - l + 1, len = r - l + 1;
        while (len > 1)
        {
            if (hash.get(l + res / fac[len], r) == hash.get(l, r - res / fac[len]))
                res /= fac[len];
            len /= fac[len];
        }
        cout << res << endl;
    }
}
