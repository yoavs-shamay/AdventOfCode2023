#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> v;
typedef vector<v> vv;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;

#define pb push_back

int main()
{
    string to;
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vvvb parsed;
    vvb cur;
    while (getline(input, to))
    {
        if (to.size() == 0)
        {
        	parsed.pb(cur);
        	cur = vvb();
        	continue;
        }
        vb cur2;
        for (char c : to) cur2.pb(c=='#');
        cur.pb(cur2);
    }
    if (cur.size()>0) parsed.pb(cur);
    ll res = 0;
    for (auto grid : parsed)
    {
    	for (ll col = 0; col<grid[0].size()-1;col++)
    	{
    		ll valid = 1;
    		for (ll cur = 0; col-cur>=0&&(cur+col+1)<grid[0].size();cur++)
    		{
    			for (ll i=0;i<grid.size();i++)
    				if (grid[i][col-cur]!=grid[i][col+cur+1]) valid--;
    		}
    		if (valid==0) res += col+1;
    	}
    	for (ll row = 0; row<grid.size()-1;row++)
    	{
    		ll valid = 1;
    		for (ll cur = 0; row-cur>=0&&(cur+row+1)<grid.size();cur++)
    		{
    			for (ll i=0;i<grid[0].size();i++)
    				if (grid[row-cur][i]!=grid[row+cur+1][i]) valid--;
    		}
    		if (valid==0) res += 100*(row+1);
    	}
    }
    cout << res << "\n";
    return 0;
}