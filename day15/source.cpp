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
    string withoutNewLine = "";
    while(!input.eof())
    {
        string str;
        getline(input, str);
        withoutNewLine += str;
    }
    withoutNewLine += ",";
    string cur = "";
    vector<vector<pair<string, ll>>> boxes(256);
    for (char x : withoutNewLine)
    {
        if (x == ',')
        {
            string pt1;
            string pt2;
            bool part = false;
            bool add = false;
            for (char x : cur)
            {
                if (x == '-' || x == '=') {part = true; add = (x == '=');}
                else if (part) pt2 += x;
                else pt1 += x;
            }
            ll pt1hash = 0;
            for (char x : pt1) pt1hash = ((pt1hash + x) * 17) % 256;
            if (add)
            {
                ll focal = atoi(pt2.c_str());
                bool done = false;
                for (auto &cur : boxes[pt1hash]) if (cur.f == pt1) {cur.s = focal; done = true;}
                if (!done) {boxes[pt1hash].eb(pt1, focal);}
            }
            else
            {
                ll index = -1;
                for (ll i = 0; i < boxes[pt1hash].size(); i++) if (boxes[pt1hash][i].f == pt1) index = i;
                if (index != -1)
                {
                    boxes[pt1hash].erase(boxes[pt1hash].begin() + index);
                }
            }
            cur = "";
        }
        else cur += x;
    }
    ll sum = 0;
    for (ll box = 0; box < 256; box++)
    {
        for (ll lens= 0; lens < boxes[box].size(); lens++)
        {
            sum += (box + 1) * (lens + 1) * boxes[box][lens].s;
        }
    }
    cout << sum << "\n";
    input.close();
    return 0;
}