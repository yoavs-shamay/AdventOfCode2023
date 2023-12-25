#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

typedef struct Module
{
    ll type;
    vector<string> destinations;
    unordered_map<string,bool> memory;
    bool on;
} Module;

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    unordered_map<string, Module> modules;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        ll type = 0;
        ll i = 0;
        if (str[0] == '%') {type = 1; i++;}
        else if (str[0] == '&') {type = 2; i++;}
        string name = "";
        while (!isspace(str[i])) {name += str[i]; i++;}
        i += 4;
        vector<string> destinations;
        ll destCount = count(all(str),',') + 1;
        for (ll t = 0; t < destCount; t++)
        {
            string curDest;
            while (i < str.size() && str[i] != ',')
            {
                curDest += str[i]; i++;
            }
            i += 2;
            destinations.pb(curDest);
        }
        Module cur{type,destinations,unordered_map<string,bool>(),false};
        modules[name] = cur;
    }
    for (auto x : modules) for (auto y : x.s.destinations) if (modules[y].type == 2) modules[y].memory[x.f] = false;
    string src;
    for (auto x : modules) for (auto y : x.s.destinations) if (y == "rx") src = x.f;
    map<string, ll> cycleSize;
    for (ll i = 1; true; i++)
    {
        queue<pair<string, pair<bool, string>>> signals;
        signals.emplace("broadcaster", pair<bool, string>{false, "button"});
        while (!signals.empty())
        {
            auto top = signals.front();
            signals.pop();
            if (top.f == src && top.s.f && cycleSize.count(top.s.s) == 0)
            {
                cycleSize[top.s.s] = i;
            }
            if (top.f == "broadcaster")
            {
                for (auto &x : modules[top.f].destinations) signals.emplace(x,pair<bool,string>(top.s.f, top.f));
            }
            else if (modules[top.f].type == 1)
            {
                if (top.s.f) continue;
                modules[top.f].on = !modules[top.f].on;
                for (auto &x : modules[top.f].destinations) signals.emplace(x, pair<bool,string>(modules[top.f].on, top.f));
            }
            else if (modules[top.f].type == 2)
            {
                modules[top.f].memory[top.s.s] = top.s.f;
                bool transmit = false;
                for (auto &x : modules[top.f].memory) if (!x.s) transmit = true;
                for (auto &x : modules[top.f].destinations) signals.emplace(x, pair<bool,string>(transmit, top.f));
            }
        }
        if (cycleSize.size() == modules[src].memory.size()) break;
    }
    ll cur = 1;
    for (auto x : cycleSize) cur = lcm(cur, x.s);
    cout << cur << "\n";
    input.close();
    return 0;
}