#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
int rank_val[128];
int rank_id[128];
int suit_id[128];

auto _init_tbl = [] {
    const char *s = "AKQJT98765432";
    for (int i = 0; i < 13; i++)
    {
        rank_val[s[i]] = 13 - i;
        rank_id[s[i]] = i;
    }
    suit_id['C'] = 0;
    suit_id['D'] = 1;
    suit_id['H'] = 2;
    suit_id['S'] = 3;
    return 0;
}();

inline int gv(int c)
{
    return 13 - c / 4;
}

vector<char> se{'C', 'D', 'H', 'S'};
vector<char> num{'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

void solve()
{
    vb used(52);
    vi C(4), P(4);
    string str;
    for (auto &p : C)
    {
        cin >> str;
        p = rank_id[str[0]] * 4 + suit_id[str[1]];
        used[p] = true;
    }

    for (auto &p : P)
    {
        cin >> str;
        p = rank_id[str[0]] * 4 + suit_id[str[1]];
        used[p] = true;
    }

    auto calc = [](vi h) -> vi {
        sort(h.begin(), h.end(), [](int x, int y) { return gv(x) > gv(y); });

        bool flush = true;
        for (int i = 1; i < 5; ++i)
            if (h[i] % 4 != h[i - 1] % 4)
            {
                flush = false;
                break;
            }

        bool straight = false;
        if (gv(h[0]) == gv(h[1]) + 1 && gv(h[0]) == gv(h[2]) + 2 && gv(h[0]) == gv(h[3]) + 3 &&
            gv(h[0]) == gv(h[4]) + 4)
            straight = true;
        else if (gv(h[0]) == 13 && gv(h[1]) == 4 && gv(h[2]) == 3 && gv(h[3]) == 2 && gv(h[4]) == 1)
            straight = true;

        int cnt[13] = {0};
        for (int i = 0; i < 5; i++)
            cnt[h[i] / 4]++;
        bool quad = false, tri = false;
        int pairs = 0;
        for (int i = 0; i < 13; i++)
        {
            if (cnt[i] == 4)
                quad = true;
            else if (cnt[i] == 3)
                tri = true;
            else if (cnt[i] == 2)
                pairs++;
        }
        bool royal = flush && straight && h[0] / 4 == 0 && h[4] / 4 == 4;

        int level;
        if (royal)
            level = 100;
        else if (flush && straight)
            level = 99;
        else if (quad)
            level = 98;
        else if (tri && pairs == 1)
            level = 97;
        else if (flush)
            level = 96;
        else if (straight)
            level = 95;
        else if (tri)
            level = 94;
        else if (pairs == 2)
            level = 93;
        else if (pairs == 1)
            level = 92;
        else
            level = 91;

        if (quad)
        {
            if (h[0] / 4 != h[1] / 4)
                swap(h[0], h[4]);
        }
        else if (tri)
        {
            for (int i = 4; i >= 3; --i)
                if (h[i] / 4 == h[i - 1] / 4 && h[i] / 4 == h[i - 2] / 4)
                    swap(h[i], h[i - 3]);
        }
        else if (pairs == 1)
        {
            for (int i = 4; i >= 2; --i)
                if (h[i] / 4 == h[i - 1] / 4)
                    swap(h[i], h[i - 2]);
        }
        else if (pairs == 2)
        {
            for (int i = 0; i < 5; ++i)
            {
                int flag = 0;
                if (i > 0 && h[i] / 4 == h[i - 1] / 4)
                    flag++;
                if (i < 4 && h[i] / 4 == h[i + 1] / 4)
                    flag++;
                if (!flag)
                {
                    h.push_back(h[i]);
                    h.erase(h.begin() + i);
                    break;
                }
            }
        }
        else if (straight)
        {
            if (h[0] / 4 == 0 && h[4] / 4 != 4)
            {
                h.push_back(h[0]);
                h.erase(h.begin());
            }
        }

        vi res(6);
        res[0] = level;
        for (int i = 0; i < 5; i++)
        {
            int v = gv(h[i]);
            if (v == 13 && straight && h[4] / 4 == 0)
                v = 0;
            res[i + 1] = v;
        }
        return res;
    };

    auto check = [&](vi P, int s1, vi C, int s2) -> int {
        P.push_back(s1);
        C.push_back(s2);
        auto a = calc(P);
        auto b = calc(C);
        if (b > a)
            return 1;
        if (b < a)
            return 0;
        return 2;
    };

    vvi opp_score(52);
    for (auto &b1 : num)
        for (auto &b2 : se)
        {
            int s2 = rank_id[b1] * 4 + suit_id[b2];
            if (used[s2])
                continue;
            vi h = C;
            h.push_back(s2);
            opp_score[s2] = calc(h);
        }

    int c_p = 0, ping = 0, p_c = 0;
    for (auto &a1 : num)
        for (auto &a2 : se)
        {
            int s1 = rank_id[a1] * 4 + suit_id[a2];
            if (used[s1])
                continue;
            used[s1] = true;

            vi h = P;
            h.push_back(s1);
            auto v1 = calc(h);

            bool f1 = false, f2 = false;
            for (auto &b1 : num)
                for (auto &b2 : se)
                {
                    int s2 = rank_id[b1] * 4 + suit_id[b2];
                    if (used[s2])
                        continue;
                    auto &v2 = opp_score[s2];
                    if (v2 > v1)
                        f1 = true;
                    else if (v2 == v1)
                        f2 = true;
                }
            if (f1)
                ++c_p;
            else if (f2)
                ++ping;
            else
                ++p_c;
            used[s1] = false;
        }

    gdb(c_p, ping, p_c);
    if (p_c)
        cout << "GeiWoCaPiXie" << endl;
    else if (ping)
        cout << "PaiMeiYouWenTi" << endl;
    else
        cout << "WoYaoYanPai" << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
