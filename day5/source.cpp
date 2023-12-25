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
    vector<pair<pair<string, string>, vtri>> parsed;
    pair<string, string> header;
    vtri cur;
    bool inmid = false;
    string str;
    getline(input, str);
    ll i = 0;
    while (str[i] != ' ') i++;
    i++;
    ll num = 0;
    vp seeds;
    v seq;
    ll digCount = 0;
    for (;i<str.size();i++)
    {
        if (isdigit(str[i]))
        {
            num *= 10;
            num += str[i] - '0';
            digCount++;
        }
        else
        {
            if (digCount > 0) seq.pb(num);
            digCount = 0;
            num = 0;
        }
    }
    if (digCount > 0) seq.pb(num);
    for (ll i = 0; i < seq.size(); i+= 2) seeds.eb(seq[i], seq[i] + seq[i+1] - 1);
    while(!input.eof())
    {
        getline(input, str);
        bool empty = true;
        for (char c : str) if (!isspace(c)) empty = false;
        if (empty)
        {
            inmid = false;
            if (!cur.empty()) parsed.eb(header, cur);
            cur = vtri();
            continue;
        }
        if (!inmid)
        {
            string s1, s2;
            ll i = 0;
            while (str[i] != '-') {s1 += str[i]; i++;}
            i += 4;
            while (str[i] != ' ') {s2 += str[i]; i++;}
            header = pair<string,string>(s1, s2);
            inmid = true;
            continue;
        }
        ll sourceStart = 0, desStart = 0, len = 0;
        sscanf(str.c_str(), "%lld %lld %lld", &desStart, &sourceStart, &len);
        cur.eb(len, p(sourceStart, desStart));
    }
    if (!cur.empty()) parsed.eb(header, cur);
    vp curThings = seeds;
    for (auto parse : parsed)
    {
        vp newThings;
        for (tri rule : parse.s)
        {
            vp newCurThings;
            for (ll i = 0; i < curThings.size(); i++)
            {
                p seed = curThings[i];
                p srcRange = p(rule.s.f, rule.s.f + rule.f - 1);
                bool intersect = max(seed.f, srcRange.f) <= min(seed.s, srcRange.s);
                if (intersect)
                {
                    if (srcRange.f > seed.f) newCurThings.eb(seed.f, srcRange.f - 1);
                    if (seed.s > srcRange.s) newCurThings.eb(srcRange.s + 1, seed.s);
                    p intersection = p(max(seed.f, srcRange.f), min(seed.s, srcRange.s));
                    newThings.eb(intersection.f + rule.s.s - rule.s.f, intersection.s + rule.s.s - rule.s.f);
                }
                else newCurThings.pb(seed);
            }
            curThings = newCurThings;
        }
        for (ll i = 0; i < curThings.size(); i++) newThings.pb(curThings[i]);
        curThings = newThings;
    }
    sort(all(curThings));
    cout << curThings[0].f << "\n";
    input.close();
    return 0;
}