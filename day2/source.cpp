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
    ll id = 1;
    ll res = 0;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        ll index = 0;
        while (str[index] != ':') index++;
        index += 2;
        ll maxRed = 0, maxBlue = 0, maxGreen = 0;
        while (index < str.size())
        {
            ll number = 0;
            auto ptr = str.c_str() + index;
            sscanf(ptr,"%d", &number);
            ll digitCount = log10(number) + 1;
            index += digitCount + 1;
            if (str[index] == 'r')
            {
                maxRed = max(maxRed, number);
                index += 5;
            }
            else if (str[index] == 'g')
            {
                maxGreen = max(maxGreen, number);
                index += 7;
            }
            else
            {
                maxBlue = max(maxBlue, number);
                index += 6;
            }
        }
        res += maxRed * maxGreen * maxBlue;
        id++;
    }
    cout << res << "\n";
    input.close();
    return 0;
}