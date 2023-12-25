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

#pragma GCC optimize("Ofast")

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    string instructions;
    input >> instructions;
    map<string, vector<string>> graph;
    map<char,ll> indices{{'L',0},{'R',1}};
    while(!input.eof())
    {
        string str;
        getline(input, str);
        vector<string> strs(3);
        ll index = 0;
        ll state = 0;
        for (;index<str.size(); index++)
        {
            if (isspace(str[index]) || str[index] == '=' || str[index] == ')') continue;
            if (str[index] == '(') {state++; continue;}
            if (str[index] == ',') {state++; continue;}
            strs[state] += str[index];
        }
        graph[strs[0]] = {strs[1],strs[2]};
    }
    map<pair<string, ll>, pair<string, ll>> graph2;
    for (auto state : graph)
    {
        for (ll i = 0; i < instructions.size(); i++)
        {
            graph2[{state.f, i}] = {state.s[indices[instructions[i]]], (i + 1) % instructions.size()};
        }
    }

    set<string> starts;
    for (auto ind : graph) if (ind.f.back() == 'A') starts.insert(ind.f);
    vector<pair<pair<v, ll>, pair<v, ll>>> startsInfo;
    for (auto start : starts)
    {
        map<pair<string, ll>, ll> visited;
        vector<pair<string, ll>> sequence;
        auto cur = make_pair(start, 0);
        ll pos = 0;
        while (visited.count(cur) == 0)
        {
            visited[cur] = pos;
            sequence.pb(cur);
            pos++;
            cur = graph2[cur];
        }
        ll repeatingPos = visited[cur];
        v before, after;
        for (ll i = 0; i < repeatingPos; i++)
        {
            if (sequence[i].f.back() == 'Z') before.pb(i);
        }
        for (ll i = repeatingPos; i < sequence.size(); i++) if (sequence[i].f.back() == 'Z') after.pb(i - repeatingPos);
        startsInfo.eb(pair<v,ll>{before, repeatingPos}, pair<v,ll>{after, sequence.size() - repeatingPos});
    }
    vector<pair<set<ll>, set<ll>>> tests;
    for (auto info : startsInfo)
    {
        set<ll> a, b;
        for (auto ind : info.f.f) a.insert(ind);
        for (auto ind : info.s.f) b.insert(ind);
        tests.eb(a, b);
    }
    ll maxi = 0;
    for (auto x : startsInfo) setmax(maxi, x.f.s);
    vp crt;
    for (auto x : startsInfo) crt.eb((x.s.f[0] - (maxi - x.f.s) + x.s.s) % x.s.s, x.s.s);
    ll l = 1;
    for (auto x : crt) l = lcm(l, x.s);
    cout << l << "\n";
    ll moves = 0;
    /*
    vector<pair<ll, bool>> states;
    for (auto start : starts) states.eb(0, false);
    while (true)
    {
        bool stop = true;
        for (ll i = 0; i < states.size(); i++)
        {
            if ((!states[i].s && tests[i].f.count(states[i].f) == 0) || (states[i].s && tests[i].s.count(states[i].f) == 0))
            {
                stop = false;
            }
        }
        if (stop) break;
        ll mini = INF;
        for (ll i = 0; i < states.size(); i++)
        {
            if (states[i].s)
            {
                auto ptr = tests[i].s.upper_bound(states[i].f);
                ll next = *tests[i].s.begin() + startsInfo[i].s.s;
                if (ptr != tests[i].s.end()) next = *ptr;
                mini = min(mini, next - states[i].f);
            }
            else
            {
                auto ptr = tests[i].f.upper_bound(states[i].f);
                ll next = *tests[i].s.begin() + startsInfo[i].f.s;
                if (ptr != tests[i].f.end()) next = *ptr;
                mini = min(mini, next - states[i].f);
            }
        }
        moves += mini;
        vector<pair<ll, bool>> newStates;
        for (ll i = 0; i < states.size(); i++)
        {
            pair<ll, bool> newState = states[i];
            newState.f += mini;
            if (!newState.s && newState.f >= startsInfo[i].f.s) {newState.s = true; newState.f -= startsInfo[i].f.s;}
            if (newState.s) newState.f %= startsInfo[i].s.s;
            newStates.pb(newState);
        }
        states = newStates;
    }
    */
    cout << moves << "\n";
    input.close();
    return 0;
}