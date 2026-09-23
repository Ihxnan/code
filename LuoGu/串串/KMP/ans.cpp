#include <stdio.h>
#include <string.h>

int fail[1000017], nxt[1000017][27];
char s[1000017];

inline void kmp()
{
    int n = strlen(&s[1]);
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j >= 1 && s[i] != s[j + 1])
            j = fail[j];
        if (s[i] == s[j + 1])
            j++;
        fail[i] = j;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= 26; j++)
        {
            nxt[i][j] = nxt[fail[i]][j];
        }
        nxt[i][s[i + 1] - 'a' + 1] = i;
    }
}

int main()
{
    int n, ni, q;
    scanf("%s", &s[1]);
    n = strlen(&s[1]);
    ni = n + 1;
    kmp();
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        int m;
        scanf("%s", &s[ni]);
        m = n + strlen(&s[ni]);
        for (int j = ni, k = fail[n]; j <= m; j++)
        {
            int jd = j - 1;
            k = nxt[k][s[j] - 'a' + 1];
            if (s[j] == s[k + 1])
                k++;
            fail[j] = k;
            printf("%d ", k);
            for (int l = 1; l <= 26; l++)
            {
                nxt[jd][l] = nxt[fail[jd]][l];
            }
            nxt[jd][s[j] - 'a' + 1] = jd;
        }
        printf("\n");
    }
    return 0;
}
