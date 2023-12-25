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

map<pair<p, set<p>>, ll> dp;

ll dfs(ll cur, vb &visited, ll end, vvp &graph)
{
    if (cur == end) return 0;
    if (visited[cur]) return -INF;
    visited[cur] = true;
    ll maxi = -INF;
    for (auto x : graph[cur]) maxi = max(maxi, x.s + dfs(x.f, visited, end, graph));
    visited[cur] = false;
    return maxi;
}

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vector<string> in;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        in.pb(str);
    }
    ll n = in.size(), m = in[0].size(); 
    vvvp graph(n, vvp(m));
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (in[i][j] == '#') continue;
            else
            {
                if (i > 0) graph[i][j].eb(i-1,j);
                if (j > 0) graph[i][j].eb(i,j-1);
                if (i < n - 1) graph[i][j].eb(i+1,j);
                if (j < m - 1) graph[i][j].eb(i,j+1);
            }
        }
    }
    vp centers;
    centers.eb(0, 1);
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (in[i][j] == '#') continue;
            ll cnt = 0;
            if ((i-1) >= 0 && (i - 1) < n && (j) >= 0 && (j) <= m && in[i-1][j] != '#') cnt++;
            if ((i+1) >= 0 && (i + 1) < n && (j) >= 0 && (j) <= m && in[i+1][j] != '#') cnt++;
            if ((i) >= 0 && (i) < n && (j - 1) >= 0 && (j - 1) <= m && in[i][j-1] != '#') cnt++;
            if ((i) >= 0 && (i) < n && (j + 1) >= 0 && (j + 1) <= m && in[i][j+1] != '#') cnt++;
            if (cnt > 2) centers.eb(i, j);
        }
    }
    centers.eb(n-1, m - 2);
    map<p,ll> centersRev;
    for (ll i= 0 ; i < centers.size(); i++) centersRev[centers[i]] = i;
    vvp graph2(centers.size());
    vvb visited(n, vb(m, false));
    for (ll c = 0; c < centers.size(); c++)
    {
        ll i=  centers[c].f, j = centers[c].s;
        visited[i][j] = true;
        if ((i-1) >= 0 && (i - 1) < n && (j) >= 0 && (j) <= m && in[i-1][j] != '#')
        {
            stack<tri> dfs;
            dfs.emplace(tri(1,p(i-1,j)));
            vp erase;
            while (!dfs.empty())
            {
                auto top = dfs.top();
                dfs.pop();
                if (visited[top.s.f][top.s.s]) continue;
                visited[top.s.f][top.s.s] = true;
                erase.pb(top.s);
                if (centersRev.count(top.s) > 0)
                {
                    graph2[c].eb(centersRev[top.s], top.f);
                    break;
                }
                for (auto x : graph[top.s.f][top.s.s]) dfs.emplace(top.f + 1, x);
            }
            for (auto x : erase) visited[x.f][x.s] = false;
        }
        if ((i+1) >= 0 && (i + 1) < n && (j) >= 0 && (j) <= m && in[i+1][j] != '#')
        {
            stack<tri> dfs;
            dfs.emplace(tri(1,p(i+1,j)));
            vp erase;
            while (!dfs.empty())
            {
                auto top = dfs.top();
                dfs.pop();
                if (visited[top.s.f][top.s.s]) continue;
                visited[top.s.f][top.s.s] = true;
                erase.pb(top.s);
                if (centersRev.count(top.s) > 0)
                {
                    graph2[c].eb(centersRev[top.s], top.f);
                    break;
                }
                for (auto x : graph[top.s.f][top.s.s]) dfs.emplace(top.f + 1, x);
            }
            for (auto x : erase) visited[x.f][x.s] = false;
        }
        if ((i) >= 0 && (i) < n && (j - 1) >= 0 && (j - 1) <= m && in[i][j-1] != '#')
        {
            stack<tri> dfs;
            dfs.emplace(tri(1,p(i,j-1)));
            vp erase;
            while (!dfs.empty())
            {
                auto top = dfs.top();
                dfs.pop();
                if (visited[top.s.f][top.s.s]) continue;
                visited[top.s.f][top.s.s] = true;
                erase.pb(top.s);
                if (centersRev.count(top.s) > 0)
                {
                    graph2[c].eb(centersRev[top.s], top.f);
                    continue;
                }
                for (auto x : graph[top.s.f][top.s.s]) dfs.emplace(top.f + 1, x);
            }
            for (auto x : erase) visited[x.f][x.s] = false;
        }
        if ((i) >= 0 && (i) < n && (j + 1) >= 0 && (j + 1) <= m && in[i][j+1] != '#')
        {
            stack<tri> dfs;
            dfs.emplace(tri(1,p(i,j+1)));
            vp erase;
            while (!dfs.empty())
            {
                auto top = dfs.top();
                dfs.pop();
                if (visited[top.s.f][top.s.s]) continue;
                visited[top.s.f][top.s.s] = true;
                erase.pb(top.s);
                if (centersRev.count(top.s) > 0)
                {
                    graph2[c].eb(centersRev[top.s], top.f);
                    break;
                }
                for (auto x : graph[top.s.f][top.s.s]) dfs.emplace(top.f + 1, x);
            }
            for (auto x : erase) visited[x.f][x.s] = false;
        }
        visited[i][j] = false;
    }
    ll start = 0, end = centers.size()-1;
    vb visited2(centers.size(), false);
    cout << dfs(start, visited2, end, graph2) << "\n";
    input.close();
    return 0;
}