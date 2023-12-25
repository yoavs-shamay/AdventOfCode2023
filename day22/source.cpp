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

typedef struct Point
{
    ll x,y,z;
} Point;

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vector<pair<Point,Point>> bricks;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        ll x1=0,y1=0,z1=0,x2=0,y2=0,z2=0;
        sscanf(str.c_str(), "%d,%d,%d~%d,%d,%d", &x1, &y1, &z1, &x2, &y2, &z2);
        bricks.eb(Point{x1,y1,z1},Point{x2,y2,z2});
    }
    vector<vector<Point>> bricksVec;
    for (auto br : bricks)
    {
        vector<Point> cur;
        for (ll x = min(br.f.x, br.s.x); x <= max(br.f.x,br.s.x); x++)
        {
            for (ll y = min(br.f.y,br.s.y); y <= max(br.f.y,br.s.y); y++)
            {
                for (ll z = min(br.f.z, br.s.z); z <= max(br.f.z,br.s.z); z++)
                {
                    cur.pb(Point{x,y,z});
                }
            }
        }
        bricksVec.pb(cur);
    }
    ll maxX = -INF, maxY = -INF, maxZ = -INF;
    ll N = bricksVec.size();
    for (ll i = 0; i < N; i++)
    {
        for (auto p : bricksVec[i])
        {
            setmax(maxX, p.x);
            setmax(maxY, p.y);
            setmax(maxZ, p.z);
        }
    }
    vvv occupying(maxX + 1, vv(maxY + 1, v(maxZ + 1, -1)));
    for (ll i = 0; i <= maxX; i++) for (ll j = 0; j <= maxY; j++) occupying[i][j][0] = INF;
    for (ll i = 0; i < N; i++)
    {
        for (auto p : bricksVec[i]) occupying[p.x][p.y][p.z] = i;
    }
    vv restingOn(N);
    while (true)
    {
        bool moved = false;
        for (ll i = 0; i < bricksVec.size(); i++)
        {
            v resting;
            for (auto p : bricksVec[i])
            {
                if (occupying[p.x][p.y][p.z - 1] != -1 && occupying[p.x][p.y][p.z - 1] != i) resting.pb(occupying[p.x][p.y][p.z - 1]);
            }
            sort(all(resting));
            resting.erase(unique(all(resting)),resting.end());
            if (resting.empty())
            {
                moved = true;
                for (auto p : bricksVec[i]) occupying[p.x][p.y][p.z] = -1;
                for (auto &p : bricksVec[i]) p.z--;
                for (auto p : bricksVec[i]) occupying[p.x][p.y][p.z] = i;
            }
            restingOn[i] = resting;
        }
        if (!moved) break;
    }
    v cnt(N, 0);
    for (ll i = 0; i < N; i++)
    {
        set<ll> cur;
        cur.insert(i);
        while (true)
        {
            bool moved = false;
            for (ll j = 0; j < N; j++)
            {
                if (cur.count(j) > 0) continue;
                bool poss = true;
                for (ll x : restingOn[j]) if (cur.count(x) == 0) poss = false;
                if (poss) {cur.insert(j); moved = true;}
            }
            if (!moved) break;
        }
        cnt[i] = cur.size() - 1;
    }
    ll res = 0;
    for (auto x : cnt) res += x;
    cout << res << "\n";
    input.close();
    return 0;
}