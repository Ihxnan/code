#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    if (str[n - 1] == '0' && str[n - 2] == '0')
        cout << "Yes" << endl;
    else if (str[n - 1] == '1' && str[n - 2] == '0')
    {
        if (n < 4)
            cout << "No" << endl;
        else if (str[n - 4] == '1' && str[n - 3] == '1')
            cout << "Yes" << endl;
        else
        {
            int cnt = 0;
            vb sta(n);
            for (int i = 0; i < n - 2; ++i)
            {
                if (str[i] == '1')
                    ++cnt;
                if (cnt)
                    if (!i || !sta[i - 1])
                        --cnt, sta[i] = true;
            }
            for (int i = n - 3; i >= 0 && cnt > 0; --i)
                if (!sta[i])
                    sta[i] = true, --cnt;

            cnt = 0;
            for (int i = n - 3; i >= 0 && i >= n - 5; --i)
                if (sta[i])
                    ++cnt;

            if (cnt >= 2)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    }
    else
    {
        if (n < 4)
            cout << "No" << endl;
        else if (str[n - 4] == '1')
            cout << "Yes" << endl;
        else
        {
            int cnt = 0;
            vb sta(n);
            for (int i = 0; i < n - 3; ++i)
            {
                if (str[i] == '1')
                    ++cnt;
                if (cnt)
                    if (!i || !sta[i - 1])
                        --cnt, sta[i] = true;
            }
            for (int i = n - 4; i >= 0 && cnt > 0; --i)
                if (!sta[i])
                    sta[i] = true, --cnt;

            if (sta[n - 4])
                cout << "Yes" << endl;
            else if (n >= 5)
            {
                int cnt = 0;
                vb sta(n);
                for (int i = 0; i < n - 2; ++i)
                {
                    if (str[i] == '1')
                        ++cnt;
                    if (cnt)
                        if (!i || !sta[i - 1])
                            --cnt, sta[i] = true;
                }
                for (int i = n - 3; i >= 0 && cnt > 0; --i)
                    if (!sta[i])
                        sta[i] = true, --cnt;
                if (sta[n - 3] && sta[n - 5])
                    cout << "Yes" << endl;
                else
                    cout << "No" << endl;
            }
            else
                cout << "No" << endl;
        }
    }
}
