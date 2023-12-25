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
    string times;
    string distances;
    bool mode = false;
    string cur;
    input >> cur;
    while(!input.eof())
    {
        input >> cur;
        if (input.eof()) break;
        if (cur[0] == 'D'){ mode = true; continue;}
        if (mode) distances += cur;
        else times += cur;
    }
    __int128 d = stoll(distances), t = stoll(times);
    __int128 square = t * t;
    __int128 dis = square - 4 * d;
    ll from = floor((t - sqrt(dis)) / 2.0 + 1);
    ll to = ceil((t + sqrt(dis)) / 2.0 - 1);
    cout << to - from + 1 << "\n";
    input.close();
    return 0;
}