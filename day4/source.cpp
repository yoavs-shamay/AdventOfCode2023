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
    vector<ll> wins;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        ll i = 0;
        while (str[i] != ':') i++;
        i += 2;
        v winning;
        ll cur = 0;
        ll digCount = 0;
        while (str[i] != '|')
        {
            if (isdigit(str[i]))
            {
                cur *= 10;
                cur += str[i] - '0';
                digCount++;
            }
            else if (digCount != 0)
            {
                winning.pb(cur);
                cur = 0;
                digCount = 0;
            }
            i++;
        } 
        if (digCount != 0)
        {
            winning.pb(cur);
        }
        i += 2;
        v numbers;
        cur = 0;
        digCount = 0;
        while (i < str.size())
        {
            if (isdigit(str[i]))
            {
                cur *= 10;
                cur += str[i] - '0';
                digCount++;
            }
            else if (digCount != 0)
            {
                numbers.pb(cur);
                cur = 0;
                digCount = 0;
            }
            i++;
        }
        if (digCount != 0)
        {
            numbers.pb(cur);
        }
        sort(all(numbers));
        sort(all(winning));
        v intersection;
        set_intersection(all(numbers), all(winning), back_inserter(intersection));
        ll amt = intersection.size();
        wins.pb(amt);
    }
    v res(wins.size(), 1);
    for (ll i = wins.size() - 1; i >= 0; i--)
    {
        for (ll j = 1;j <= wins[i]; j++) res[i] += res[i + j];
    }
    ll sum = 0;
    for (ll x : res) sum += x;
    cout << sum << "\n";
    input.close();
    return 0;
}