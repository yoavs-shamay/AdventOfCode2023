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
    vector<pair<v, ll>> hands;
    map<char, ll> convert{{'2',1},{'3',2},{'4',3},{'5',4},{'6',5},{'7',6},{'8',7},{'9',8},{'T',9},{'J',0},{'Q',11},{'K',12},{'A',13}};
    while(!input.eof())
    {
        string hand, bid;
        input >> hand >> bid;
        ll bidNum = atoi(bid.c_str());
        v handVec;
        for (char c : hand) handVec.pb(convert[c]);
        hands.eb(handVec, bidNum);
    }
    vector<vector<pair<v,ll>>> byType(7);
    for (auto hand : hands)
    {
        v histogram(14, 0);
        for (ll x : hand.f) histogram[x]++;
        ll jCount = histogram[0];
        histogram[0] = 0;
        v histogramRev(6, 0);
        for (ll x : histogram) histogramRev[x]++;
        ll h = 0;
        for (ll i = 0; i < 6; i++) if (histogramRev[i] > 0) h = i;
        histogramRev[h]--;
        histogramRev[h + jCount]++;
        ll type = 0;
        if (histogramRev[5] > 0) type = 6;
        else if (histogramRev[4] > 0) type = 5;
        else if (histogramRev[3] > 0 && histogramRev[2] > 0) type = 4;
        else if (histogramRev[3] > 0) type = 3;
        else if (histogramRev[2] > 1) type = 2;
        else if (histogramRev[2] > 0) type = 1;
        byType[type].pb(hand);
    }
    ll res = 0;
    for (auto &x : byType) sort(all(x));
    ll rank = 1; //TODO 2 equal?
    for (auto x : byType)
    {
        for (auto y : x)
        {
            res += rank * y.s;
            rank++;
        }
    }
    cout << res << "\n";
    input.close();
    return 0;
}