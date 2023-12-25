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

bool isSymbol(vector<string> &arr, ll i, ll j)
{
    if (i < 0 || i >= arr.size() || j < 0 || j >= arr[i].size()) return false;
    char cur = arr[i][j];
    return !isdigit(cur) && cur != '.';
}

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vector<string> schem;
    while(!input.eof())
    {
        string str;
        input >> str;
        schem.pb(str);
    }
    map<p, p> numbers;
    ll index = 0;
    for (ll i =0 ; i < schem.size(); i++)
    {
        ll number = 0;
        ll cnt = 0;
        for (ll j =0; j < schem[i].size(); j++)
        {
            if (!isdigit(schem[i][j])) continue;
            number *= 10;
            number += schem[i][j] - '0';
            cnt++;
            if (j < schem[i].size() - 1 && isdigit(schem[i][j+1])) continue;
            bool adj = false;
            for (ll pos = j - cnt + 1; pos <= j; pos++)
            {
                for (ll add = -1; add <= 1; add++)
                {
                    for (ll add2 = -1; add2 <= 1; add2++)
                    {
                        if(isSymbol(schem, i + add, pos + add2)) adj = true;
                    }
                }
            }
            if (adj)
            {
                for (ll pos = j - cnt + 1; pos <= j; pos++)
                {
                    numbers[p(i, pos)] = p(index, number);
                }
                index++;
            }
            number = 0;
            cnt = 0;
        }
    }
    ll sum = 0;
    for (ll i = 0; i < schem.size(); i++)
    {
        for (ll j=  0; j < schem[i].size(); j++)
        {
            if (schem[i][j] != '*') continue;
            set<p> used;
            for (ll add = -1; add <= 1; add++)
            {
                for (ll add2 = -1; add2 <= 1; add2++)
                {
                    if (numbers.count(p(i + add, j + add2)) > 0) used.insert(numbers[p(i + add, j + add2)]);
                }
            }
            if (used.size() == 2)
            {
                ll mul = 1;
                for (p x : used) mul *= x.s;
                sum += mul;
            }
        }
    }
    cout << sum << "\n";
    input.close();
    return 0;
}