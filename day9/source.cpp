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
    vector<deque<ll>> sequences;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        str += ' ';
        deque<ll> sequence;
        ll cur = 0;
        ll neg = 1;
        for (char x : str)
        {
            if (isspace(x))
            {
                sequence.pb(neg * cur);
                cur = 0;
                neg = 1;
            }
            else
            {
                if (x == '-') neg = -1;
                else
                {
                    cur *= 10;
                    cur += x - '0';
                }
            }
        }
        sequences.pb(sequence);
    }
    ll sum = 0;
    for (auto seq : sequences)
    {
        vector<deque<ll>> arrays(1, seq);
        while (true)
        {
            bool stop = true;
            for (ll x : arrays.back()) if (x != 0) stop = false;
            if (stop) break;
            deque<ll> newArr;
            for (ll i = 0; i < arrays.back().size() - 1; i++)
            {
                newArr.pb(arrays.back()[i + 1] - arrays.back()[i]);
            }
            arrays.pb(newArr);
        }
        arrays.back().push_front(0);
        for (ll i = arrays.size() - 2; i >= 0; i--)
        {
            arrays[i].push_front(arrays[i].front() - arrays[i+1].front());
        }
        sum += arrays[0].front();
    }
    cout << sum << "\n";
    input.close();
    return 0;
}