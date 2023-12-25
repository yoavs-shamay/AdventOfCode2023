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

#define stinitial 0
#define stoperation(A, B) ((A)+(B))
typedef struct SegmentTree
{
    v st;
    ll N;
    SegmentTree(ll n) 
    {
        N = pow(2, ceil(log2(n)));
        st = v(2 * N, stinitial);
    }
    SegmentTree(ll n, v &arr)
    {
        N = pow(2, ceil(log2(n)));
        st = v(2 * N, stinitial);
        for (ll i = N; i < N + n; i++)
        {
            st[i] = arr[i - N];
        }
        for (ll i=  N - 1; i > 0; i--) st[i] = stoperation(st[2 * i], st[2 * i + 1]);
    }
    void update(ll index, ll value)
    {
        st[index + N] = value;
        ll i = (index + N) / 2;
        while (i > 0)
        {
            st[i] = stoperation(st[2 * i], st[2 * i + 1]);
            i /= 2;
        }
    }
    ll query(ll l, ll r)
    {
        l += N;
        r += N;
        ll sum = stinitial;
        while (l <= r)
        {
            if (l % 2 == 1)
            {
                sum = stoperation(sum, st[l]);
                l++;
            }
            if (r % 2 == 0)
            {
                sum = stoperation(sum, st[r]);
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return sum;
    }
} SegmentTree;

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vector<vector<bool>> in;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        vector<bool> cur;
        for (char c : str) cur.pb(c == '#');
        in.pb(cur);
    }
    ll n = in.size(), m = in[0].size();
    SegmentTree doubleRow(n);
    for (ll i = 0; i < n; i++)
    {
        bool doubled = true;
        for (ll j = 0; j < m; j++) if(in[i][j]) doubled = false;
        if (doubled) doubleRow.update(i, 1e6 - 1);
    }
    SegmentTree doubleCol(m);
    for (ll i = 0; i < m; i++)
    {
        bool doubled = true;
        for (ll j = 0; j < n; j++) if(in[j][i]) doubled = false;
        if (doubled) doubleCol.update(i, 1e6 - 1);
    }
    vvb temp;
    for (ll i = 0; i < n; i++)
    {
        temp.pb(in[i]);
        bool doubled = true;
        for (ll j = 0; j < m; j++) if(in[i][j]) doubled = false;
        if (doubled) temp.pb(in[i]);
    }
    vp galaxies;
    for (ll i =0 ; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (in[i][j]) galaxies.eb(i, j);
        }
    }
    ll sum = 0;
    for (ll i = 0 ;i < galaxies.size(); i++)
    {
        for (ll j = i + 1; j < galaxies.size(); j++)
        {
            sum += abs(galaxies[i].f - galaxies[j].f) + abs(galaxies[i].s - galaxies[j].s);
            ll miniX = min(galaxies[i].f, galaxies[j].f), maxiX = max(galaxies[i].f, galaxies[j].f), miniY = min(galaxies[i].s, galaxies[j].s), maxiY = max(galaxies[i].s, galaxies[j].s);
            sum += doubleRow.query(miniX, maxiX);
            sum += doubleCol.query(miniY, maxiY);
        }
    }
    cout << sum << "\n";
    input.close();
    return 0;
}