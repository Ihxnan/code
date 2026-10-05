#include <ihxnan>
#include <StrHash>

void solve()
{
    int n;
    cin >> n;
    vector<string> arr(n);
    read(arr);
    sort(arr.begin(), arr.end(), [](auto &x, auto &b) { return x.size() < b.size(); });

    vector<StrHash> vec;
    for (auto &p : arr)
        vec.emplace_back(p);

    unordered_set<ul> hash;

    int idx = 0;
    while (idx < n && arr[idx].size() == 1)
        perfect.insert(arr[idx++]);

    for (; idx < n; ++idx)
        if (perfect.count())

            gdb(hash);
}
