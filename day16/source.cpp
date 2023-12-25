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
typedef vector<vvvtri> vvvvtri;
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
    vector<string> grid;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        grid.pb(str);
    }
    input.close();
    ll n = grid.size(), m = grid[0].size();
    vvvvtri graph(n, vvvtri(m, vvtri(4))); //up,right,down,left
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
            {
                if (i-1>=0)
                    graph[i][j][0].eb(0,p(i-1,j));
                if (j+1<m)
                    graph[i][j][1].eb(1,p(i,j+1));
                if (i+1<n)
                    graph[i][j][2].eb(2,p(i+1,j));
                if (j-1>=0)
                    graph[i][j][3].eb(3,p(i,j-1));
            }
            else if (grid[i][j] == '/')
            {
                if (j+1<m)
                    graph[i][j][0].eb(1,p(i,j+1));
                if (i-1>=0)
                    graph[i][j][1].eb(0,p(i-1,j));
                if (j-1>=0)
                    graph[i][j][2].eb(3,p(i,j-1));
                if (i+1<n)
                    graph[i][j][3].eb(2,p(i+1,j));
            }
            else if (grid[i][j] == '\\')
            {
                if (j-1>=0)
                    graph[i][j][0].eb(3,p(i,j-1));
                if (i+1<n)
                    graph[i][j][1].eb(2,p(i+1,j));
                if (j+1<m)
                    graph[i][j][2].eb(1,p(i,j+1));
                if (i-1>=0)
                    graph[i][j][3].eb(0,p(i-1,j));
            }
            else if (grid[i][j] == '|')
            {
                if (i+1<n)
                {
                    graph[i][j][1].eb(2,p(i+1,j));
                    graph[i][j][3].eb(2,p(i+1,j));
                    graph[i][j][2].eb(2,p(i+1,j));
                }
                if (i-1>=0)
                {
                    graph[i][j][1].eb(0,p(i-1,j));
                    graph[i][j][3].eb(0,p(i-1,j));
                    graph[i][j][0].eb(0,p(i-1,j));
                }
            }
            else if (grid[i][j] == '-')
            {
                if (j+1<m)
                {
                    graph[i][j][1].eb(1,p(i,j+1));
                    graph[i][j][0].eb(1,p(i,j+1));
                    graph[i][j][2].eb(1,p(i,j+1));
                }
                if (j-1>=0)
                {
                    graph[i][j][3].eb(3,p(i,j-1));
                    graph[i][j][0].eb(3,p(i,j-1));
                    graph[i][j][2].eb(3,p(i,j-1));
                }
            }
        }
    }
    vvv comp(n, vv(m, v(4, -1)));
    vector<set<p>> byComp;
    ll curComp = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j= 0; j < m; j++)
        {
            for (ll k = 0; k < 4; k++)
            {
                if (comp[i][j][k] != -1) continue;
                tri start(k, p(i, j));
                stack<tri> dfs;
                dfs.push(start);
                set<p> cur;
                while (!dfs.empty())
                {
                    auto top = dfs.top();
                    dfs.pop();
                    if (comp[top.s.f][top.s.s][top.f] != -1) continue;
                    cur.insert(top.s);
                    comp[top.s.f][top.s.s][top.f] = curComp;
                    for (auto x : graph[top.s.f][top.s.s][top.f]) dfs.push(x);
                }
                byComp.pb(cur);
                curComp++;
            }
        }
    }
    ll maxi = -INF;
    vvvb visited(n, vvb(m, vb(4, false)));
    for (ll i=  0; i < n; i++)
    {
        auto cur = tri(1, p(i, 0));
        stack<tri> dfs;
        dfs.push(cur);
        vtri done;
        set<p> points;
        while (!dfs.empty())
        {
            auto top = dfs.top();
            dfs.pop();
            if (visited[top.s.f][top.s.s][top.f]) continue;
            visited[top.s.f][top.s.s][top.f] = true;
            done.pb(top);
            points.insert(top.s);
            for (auto x : graph[top.s.f][top.s.s][top.f]) dfs.push(x);
        }
        for (auto x : done) visited[x.s.f][x.s.s][x.f] = false;
        maxi = max(maxi, (ll)points.size());
        cur = tri(3, p(i, m - 1));
        dfs.push(cur);
        done = vtri();
        points = set<p>();
        while (!dfs.empty())
        {
            auto top = dfs.top();
            dfs.pop();
            if (visited[top.s.f][top.s.s][top.f]) continue;
            visited[top.s.f][top.s.s][top.f] = true;
            done.pb(top);
            points.insert(top.s);
            for (auto x : graph[top.s.f][top.s.s][top.f]) dfs.push(x);
        }
        for (auto x : done) visited[x.s.f][x.s.s][x.f] = false;
        maxi = max(maxi, (ll)points.size());
    }
    for (ll j = 0; j < m; j++)
    {
        auto cur = tri(2, p(0, j));
        stack<tri> dfs;
        dfs.push(cur);
        vtri done;
        set<p> points;
        while (!dfs.empty())
        {
            auto top = dfs.top();
            dfs.pop();
            if (visited[top.s.f][top.s.s][top.f]) continue;
            visited[top.s.f][top.s.s][top.f] = true;
            done.pb(top);
            points.insert(top.s);
            for (auto x : graph[top.s.f][top.s.s][top.f]) dfs.push(x);
        }
        for (auto x : done) visited[x.s.f][x.s.s][x.f] = false;
        maxi = max(maxi, (ll)points.size());
        cur = tri(0, p(n - 1, j));
        dfs.push(cur);
        done = vtri();
        points = set<p>();
        while (!dfs.empty())
        {
            auto top = dfs.top();
            dfs.pop();
            if (visited[top.s.f][top.s.s][top.f]) continue;
            visited[top.s.f][top.s.s][top.f] = true;
            done.pb(top);
            points.insert(top.s);
            for (auto x : graph[top.s.f][top.s.s][top.f]) dfs.push(x);
        }
        for (auto x : done) visited[x.s.f][x.s.s][x.f] = false;
        maxi = max(maxi, (ll)points.size());
    }
    cout << maxi << "\n";
    return 0;
}