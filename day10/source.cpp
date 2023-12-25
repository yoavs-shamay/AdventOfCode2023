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
#define setmin(a, b) a = min(a, b)
#define setmax(a, b) a = max(a, b)
#define all(v) v.begin(), v.end()

typedef struct Vertex
{
    ll x;
    ll y;
    bool verticalEdge;
    bool horizontalEdge;

    bool operator<(const Vertex &other) const
    {
        return v{x,y,verticalEdge,horizontalEdge} < v{other.x,other.y,other.verticalEdge,other.horizontalEdge};
    }
    bool operator==(const Vertex &other) const
    {
        return v{x,y,verticalEdge,horizontalEdge} == v{other.x,other.y,other.verticalEdge,other.horizontalEdge};
    }
} Vertex;

ll polygonArea(vector<Vertex> vertices)
{
    // Initialize area
    ll area = 0;
    ll n = vertices.size();
 
    // Calculate value of shoelace formula
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (vertices[j].x + vertices[i].x) * (vertices[j].y - vertices[i].y);
        j = i;  // j is previous vertex to i
    }
 
    // Return absolute value
    return abs(area / 2.0);
}

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vector<vector<pair<Vertex,Vertex>>> pipes;
    map<char, pair<Vertex,Vertex>> convert{
        {'|',{{0,0, false, true},{0,1, false, true}}},
        {'-',{{0,0, true, false},{1,0, true, false}}},
        {'L',{{0,0, false, true},{1,0, true, false}}},
        {'J',{{0,0, false, true},{0,0, true, false}}},
        {'7',{{0,1, false, true},{0,0, true, false}}},
        {'F',{{0,1, false, true},{1,0, true, false}}},
        {'.',{{0,0, false, false},{0,0, false, false}}},
        {'S',{{0,0, false, false},{0,0, false, false}}}
    };
    p start;
    ll i = 0;
    while(!input.eof())
    {
        ll j = 0;
        string str;
        getline(input, str);
        vector<pair<Vertex,Vertex>> cur;
        for (char c : str)
        {
            if (c == 'S') start = p(i, j);
            cur.pb(convert[c]);
            cur.back().f.x += j;
            cur.back().f.y += i;
            cur.back().s.x += j;
            cur.back().s.y += i;
            j++;
        }
        pipes.pb(cur);
        i++;
    }
    input.close();
    map<Vertex,vector<Vertex>> graph;
    vector<Vertex> allVertices;
    for (ll i = 0; i < pipes.size(); i++)
    {
        for (ll j=  0; j < pipes[i].size(); j++)
        {
            //Create a graph from tiles to edges, and from edges to tiles
            Vertex from = {j,i,false,false};
            auto cvrt = pipes[i][j];
            graph[from].pb(cvrt.f);
            graph[cvrt.f].pb(from);
            graph[from].pb(cvrt.s);
            graph[cvrt.s].pb(from);
            allVertices.pb({j,i,false,false});
            allVertices.pb({j,i,false,true});
            allVertices.pb({j,i,true,false});
        }
    }
    vector<Vertex> outside;
    for (ll i = 0; i < pipes[0].size(); i++)
    {
        allVertices.pb(Vertex{i,(ll)pipes.size(),false,true});
        outside.pb(Vertex{i,(ll)pipes.size(),false,true});
        outside.pb(Vertex{i,0,false,true});
    }
    for (ll i = 0; i < pipes.size(); i++)
    {
        allVertices.pb(Vertex{(ll)pipes[0].size(),i,true,false});
        outside.pb(Vertex{(ll)pipes[0].size(),i,true,false});
        outside.pb(Vertex{0, i,true,false});
    }
    set<Vertex> visited;
    map<Vertex, ll> comp;
    vector<vector<Vertex>> byComp;
    ll component = 0;
    for (auto v : allVertices)
    {
        if (visited.count(v) > 0) continue;
        stack<Vertex> dfs;
        dfs.push(v);
        byComp.pb(vector<Vertex>());
        while (!dfs.empty())
        {
            auto top = dfs.top();
            dfs.pop();
            if (visited.count(top) > 0) continue;
            visited.insert(top);
            comp[top] = component;
            byComp.back().pb(top);
            for (auto x : graph[top]) dfs.push(x);
        }
        component++;
    }
    vector<Vertex> adj = {{0,0,false,true},{0,0,true,false},{0,1,false,true},{1,0,true,false}};
    Vertex startVer = {start.s,start.f,false,false};
    for (auto v : adj)
    {
        for (auto v2 : adj)
        {
            if (v == v2) continue;
            Vertex newV{v.x + start.s, v.y + start.f, v.verticalEdge, v.horizontalEdge};
            Vertex newV2{v2.x + start.s, v2.y + start.f, v2.verticalEdge, v2.horizontalEdge};
            if (comp[newV] == comp[newV2])
            {
                graph[startVer].pb(newV);
                graph[newV].pb(startVer);
                graph[startVer].pb(newV2);
                graph[newV2].pb(startVer);
                break;
            }
        }
    }
    stack<Vertex> dfs;
    dfs.push(startVer);
    set<Vertex> loop;
    visited = set<Vertex>();
    ll loopCount = 0;
    while (!dfs.empty())
    {
        auto top = dfs.top();
        dfs.pop();
        if (visited.count(top) > 0) continue;
        visited.insert(top);
        loop.insert(top);
        if (!top.horizontalEdge && !top.verticalEdge) loopCount++;
        for (auto x : graph[top]) dfs.push(x);
    }
    set<Vertex> isVertex;
    for (auto x : allVertices) isVertex.insert(x);
    for (auto x : outside) dfs.push(x);
    ll count = 0;
    visited = set<Vertex>();
    vector<Vertex> horizontalAdj{{0,0,false,false},{0,-1,false,false},{0,0,true,false},{1,0,true,false},{0,-1,true,false},{1,-1,true,false},{-1,0,false,true},{1,0,false,true}};
    vector<Vertex> verticalAdj{{0,0,false,false},{-1,0,false,false},{0,0,false,true},{0,1,false,true},{-1,0,false,true},{-1,1,false,true},{0,-1,true,false},{0,1,true,false}};
    while (!dfs.empty())
    {
        auto top = dfs.top();
        dfs.pop();
        if ((visited.count(top) > 0) || (isVertex.count(top) == 0) || (loop.count(top) > 0)) continue;
        visited.insert(top);
        if (top.horizontalEdge)
        {
            for (auto x : horizontalAdj)
            {
                dfs.push({x.x + top.x, x.y + top.y, x.verticalEdge, x.horizontalEdge});
            }
        }
        else if (top.verticalEdge)
        {
            for (auto x : verticalAdj)
            {
                dfs.push({x.x + top.x, x.y + top.y, x.verticalEdge, x.horizontalEdge});
            }
        }
        else
        {
            count++;
            for (auto x : adj)
            {
                dfs.push({x.x + top.x, x.y + top.y, x.verticalEdge, x.horizontalEdge});
            }
        }
    }
    ll cnt = 0;
    cout << (ll)pipes.size() * pipes[0].size() - count - loopCount << "\n";
    return 0;
}