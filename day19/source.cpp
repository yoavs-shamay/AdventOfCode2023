#include <bits/stdc++.h>
using namespace std;

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

typedef struct Workflow
{
    vector<pair<string, pair<bool, p>>> rules;
    string otherwise;
} Workflow;

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    unordered_map<string, Workflow> flows;
    vv parts;
    bool isFlow = true;
    map<char,ll> convert{{'x',0},{'m',1},{'a',2},{'s',3}};
    while(!input.eof())
    {
        string str;
        getline(input, str);
        if (str.empty()) {isFlow = false; continue;}
        if (isFlow)
        {
            string name = "";
            ll i = 0;
            while (str[i] != '{') {name += str[i]; i++;}
            i++;
            ll ruleCount = count(all(str),',');
            vector<pair<string, pair<bool, p>>> rules;
            for (ll t = 0; t < ruleCount; t++)
            {
                ll xmas = convert[str[i]];
                i++;
                bool type = str[i] == '>';
                i++;
                char *end;
                auto pos = str.c_str() + i;
                ll number = strtol(pos, &end, 10);
                i = end - str.c_str();
                i++;
                string dest;
                while (str[i] != ',') {dest += str[i]; i++;}
                i++;
                rules.eb(dest, pair<bool,p>{type, p(xmas, number)});
            }
            string otherwise = "";
            while (str[i] != '}') {otherwise += str[i]; i++;}
            flows[name] = Workflow{rules, otherwise};
        }
        else
        {
            string number1;
            string number2;
            string number3;
            string number4;
            ll i = 3;
            while (isdigit(str[i])) {number1 += str[i]; i++;}
            i += 3;
            while (isdigit(str[i])) {number2 += str[i]; i++;}
            i += 3;
            while (isdigit(str[i])) {number3 += str[i]; i++;}
            i += 3;
            while (isdigit(str[i])) {number4 += str[i]; i++;}
            i += 3;
            v cur = {stoi(number1),stoi(number2),stoi(number3),stoi(number4)};
            parts.pb(cur);
        }
    }
    ll sum = 0;
    vv values(4, v{1, 4001});
    for (auto x : flows)
    {
        for (auto rule : x.s.rules)
        {
            values[rule.s.s.f].pb(rule.s.s.s + (rule.s.f? 1 : 0));
        }
    }
    for (auto &x : values)
    {
        sort(all(x));
        x.erase(unique(all(x)),x.end());
    }
    for (ll i = 0; i < values[0].size() - 1; i++)
    {
        for (ll j =0 ; j < values[1].size() - 1; j++)
        {
            for (ll k = 0; k < values[2].size() - 1; k++)
            {
                for (ll l = 0; l < values[3].size() - 1; l++)
                {
                    v part = {values[0][i],values[1][j],values[2][k],values[3][l]};
                    ll cnt = (values[0][i+1] - values[0][i]) * (values[1][j+1] - values[1][j]) * (values[2][k+1] - values[2][k]) * (values[3][l+1] - values[3][l]);
                    string flow = "in";
                    while (flow != "A" && flow != "R")
                    {
                        bool done = false;
                        for (auto rule : flows[flow].rules)
                        {
                            ll val = part[rule.s.s.f];
                            if ((rule.s.f && val > rule.s.s.s) || (!rule.s.f && val < rule.s.s.s))
                            {
                                done = true;
                                flow = rule.f;
                                break;
                            }
                        }
                        if (!done) flow = flows[flow].otherwise;
                    }
                    if (flow == "A") sum += cnt;
                }
            }
        }
        cout << i + 1 << " / " << values[0].size()-1 << endl;
    }
    cout << sum << "\n";
    input.close();
    return 0;
}