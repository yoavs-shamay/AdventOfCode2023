#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> p;
typedef pair<ll, p> tri;
typedef vector<ll> v;
typedef vector<v> vv;
typedef vector<p> vp;
typedef vector<tri> vtri;
typedef vector<vtri> vvtri;
typedef vector<vvtri> vvvtri;
typedef vector<vv> vvv;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef vector<p> vp;
typedef vector<vp> vvp;
typedef vector<vvp> vvvp;
typedef vector<vvvp> vvvvp;

const ll mod = 1e9 + 7;
const ll INF = 1e15;

#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define loop(a) for (ll i = 0; i < a; i++)
#define setmin(a, b) a = min(a, b)
#define setmax(a, b) a = max(a, b)
#define all(v) v.begin(), v.end()

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll sum = 0;
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    map<string, ll> written = {{"one",1},{"two",2},{"three",3},{"four",4},{"five",5},{"six",6},{"seven",7},{"eight",8},{"nine",9}};
    while(!input.eof())
    {
        string str;
        input >> str;
        ll firstDigit = -1, lastDigit = -1;
        for (ll i = 0; i < str.size(); i++)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                firstDigit = str[i] - '0';
            }
            for (auto x : written)
            {
                if (i < str.size() - x.f.size() && str.substr(i, x.f.size()) == x.f)
                {
                    firstDigit = x.s;
                }
            }
            if (firstDigit != -1) break;
        }
        for (ll i = str.size() - 1; i >= 0; i--)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                lastDigit = str[i] - '0';
            }
            for (auto x : written)
            {
                if (i >= x.f.size() - 1 && str.substr(i - x.f.size() + 1, x.f.size()) == x.f)
                {
                    lastDigit = x.s;
                }
            }
            if (lastDigit != -1) break;
        }
        sum += firstDigit * 10 + lastDigit;
    }
    input.close();
    cout << sum << "\n";
    return 0;
}