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

typedef struct Dig
{
    ll dir, dis, r, g, b;
} Dig;

double polygonArea(vp points, ll n)
{
    ll area = 0;
    ll j = n - 1;
    for (ll i = 0; i < n; i++)
    {
        area += points[j].f * points[i].s - points[i].f * points[j].s;
        j = i;
    }
    return abs(area / 2.0);
}

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vector<Dig> plan;
    map<char,ll> convert{{'0',1},{'1',2},{'2',3},{'3',0}};
    while(!input.eof())
    {
        string str;
        getline(input, str);
        stringstream strstream;
        strstream << str;
        Dig cur;
        char dir;
        strstream >> dir;
        cur.dir = convert[dir];
        strstream >> cur.dis;
        //cur.dis++;
        string remaining;
        strstream >> remaining;
        cur.dis = stoi(remaining.substr(2,5), NULL, 16);
        cur.dir = convert[remaining[7]];
        plan.pb(cur);
    }
    ll boundary = 0;
    for (auto x : plan) boundary += x.dis;
    map<ll, p> move{{0,p(-1,0)},{1,p(0,1)},{2,p(1,0)},{3,p(0,-1)}};
    vp polygon(1, p(0, 0));
    for (auto x : plan) polygon.eb(polygon.back().f+move[x.dir].f*(x.dis), polygon.back().s+move[x.dir].s*(x.dis));
    polygon.pop_back();
    ll area = polygonArea(polygon, polygon.size());
    cout << area + boundary / 2 + 1 << "\n";
    input.close();
    return 0;
}