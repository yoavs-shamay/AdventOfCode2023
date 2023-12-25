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
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vv parsed;
    map<char,ll> convert{{'.',0},{'O',1},{'#',2}};
    while(!input.eof())
    {
        string str;
        getline(input, str);
        v cur;
        for (char c : str) cur.pb(convert[c]);
        parsed.pb(cur);
    }
    ll n = parsed.size(), m = parsed[0].size();
    vv prev(n, v(m));
    for (ll i= 0 ; i < n; i++) copy(all(parsed[i]), prev[i].begin());
    ll done = 0;
    map<vv, ll> visited;
    vvv seq(1, prev);
    visited[parsed] = 0;
    while (done < 1e9)
    {
        vv afterTilt(n, v(m, 0));
        for (ll col = 0; col < m; col++)
        {
            ll cur = -1;
            for (ll i = 0; i < n; i++)
            {
                if (prev[i][col] == 1) {cur++;afterTilt[cur][col] = 1;}
                else if (prev[i][col] == 2) {cur = i;afterTilt[cur][col] = 2;}
            }
        }
        vv afterTilt2 = vv(n, v(m, 0));
        for (ll row = 0; row < n; row++)
        {
            ll cur = -1;
            for (ll i = 0; i < m; i++)
            {
                if (afterTilt[row][i] == 1) {cur++;afterTilt2[row][cur] = 1;}
                else if (afterTilt[row][i] == 2) {cur = i;afterTilt2[row][cur] = 2;}
            }
        }
        vv afterTilt3 = vv(n, v(m, 0));
        for (ll col = 0; col < m; col++)
        {
            ll cur = n;
            for (ll i = n - 1; i >= 0; i--)
            {
                if (afterTilt2[i][col] == 1) {cur--; afterTilt3[cur][col] = 1;}
                else if (afterTilt2[i][col] == 2) {cur = i;afterTilt3[cur][col] = 2;}
            }
        }
        vv afterTilt4 = vv(n, v(m, 0));
        for (ll row = 0; row < n; row++)
        {
            ll cur = m;
            for (ll i = m - 1; i >= 0; i--)
            {
                if (afterTilt3[row][i] == 1) {cur--;afterTilt4[row][cur] = 1;}
                else if (afterTilt3[row][i] == 2) {cur = i;afterTilt4[row][cur] = 2;}
            }
        }
        done++;
        seq.pb(afterTilt4);
        if (visited.count(afterTilt4) > 0)
        {
            ll start = visited[afterTilt4];
            ll cycleSize = done - start;
            ll index = start + ((ll)1e9 - start) % cycleSize;
            afterTilt4 = seq[index];
            done = 1e9;
        }
        else visited[afterTilt4] = done;
        for (ll i = 0; i < n; i++) copy(all(afterTilt4[i]), prev[i].begin());
    }
    ll res = 0;
    for (ll i=  0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (prev[i][j] == 1) res += n - i;
        }
    }
    cout << res << "\n";
    input.close();
    return 0;
}