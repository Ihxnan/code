#include <ihxnan>
#include <Bit>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vector<bit<int>> arr(n);
    for (int i = 0, t; i < n; ++i)
        cin >> t, arr[i] = t;
    bit<int> mask = (1 << 30) - 1;
    auto work = [&](int &last, bit<int> x) -> bool {
        for (int i = 0; i < 30; ++i)
            if (mask[i])
                x.set(i);
        if (x.value < last)
            return true;
        for (int i = 29; i >= 0; --i)
            if (mask[i])
            {
                x.reset(i);
                if (x.value < last)
                    x.set(i);
            }
        last = x.value;
        return false;
    };
    for (int i = 29; i >= 0; --i)
    {
        mask.reset(i);
        int last = 0;
        for (auto &p : arr)
            if (work(last, p))
            {
                mask.set(i);
                break;
            }
    }
    cout << mask.value << endl;
}
