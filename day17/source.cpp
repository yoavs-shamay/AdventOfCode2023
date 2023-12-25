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
typedef vector<vvv> vvvv;
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
    vv lose;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        v cur;
        for (char x : str) cur.pb(x - '0');
        lose.pb(cur);
    }
    ll n = lose.size(), m = lose[0].size();
    vvvv minDistance(n, vvv(m, vv(4, v(10, -1)))); //up,right,down,left
    priority_queue<pair<ll,pair<p,p>>,vector<pair<ll,pair<p,p>>>, greater<pair<ll,pair<p,p>>>> dij;
    dij.emplace(0, pair<p,p>(p(0,0),p(-11,0)));
    map<ll,p> convert{{0,p(-1,0)},{1,p(0,1)},{2,p(1,0)},{3,p(0,-1)}};
    while (!dij.empty())
    {
        auto top = dij.top();
        dij.pop();
        if (top.s.f.f < 0 || top.s.f.f >= n || top.s.f.s < 0 || top.s.f.s >= m) continue;
        if (top.s.s.s >= 10) continue;
        if (top.s.s.f != -11)
        {
            if (minDistance[top.s.f.f][top.s.f.s][top.s.s.f][top.s.s.s] > -1) continue;
            minDistance[top.s.f.f][top.s.f.s][top.s.s.f][top.s.s.s] = top.f;
        }
        if (top.s.f.f == n - 1 && top.s.f.s == m - 1 && top.s.s.s >= 3)
        {
            cout << top.f << "\n";
            break;
        }
        for (ll i = 0; i < 4; i++)
        {
            if (i == (top.s.s.f + 2) % 4) continue;
            p newPoint(top.s.f.f + convert[i].f, top.s.f.s + convert[i].s);
            if (newPoint.f < 0 || newPoint.f >= n || newPoint.s < 0 || newPoint.s >= m) continue;
            if (i == top.s.s.f) dij.emplace(top.f + lose[newPoint.f][newPoint.s], pair<p,p>(newPoint, p(i, top.s.s.s+1)));
            else if(top.s.s.s >= 3 || top.s.s.f < 0) dij.emplace(top.f + lose[newPoint.f][newPoint.s], pair<p,p>(newPoint, p(i, 0)));
        }
    }
    input.close();
    return 0;
}