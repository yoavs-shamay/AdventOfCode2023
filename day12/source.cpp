#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> v;
typedef vector<v> vv;

#define pb push_back

int main()
{
    string to;
    ll res = 0;
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    while (getline(input, to))
    {
        string pt1 = "", pt2 = "";
        bool cur = false;
        for (char x : to)
        {
            if (isspace(x))
            {
                cur = true;
                continue;
            }
            if (!cur) pt1 += x;
            else
            {
            	 if (x == ',') pt2 += ' ';
            	 else pt2 += x;
            }
        }
        v numbers;
        stringstream pt2stream;
        pt2stream << pt2;
        while (!pt2stream.eof())
        {
            ll num;
            pt2stream >> num;
        	if (num == 0) break;
        	numbers.push_back(num);
        }
        v newNumbers;
        for (ll t=0;t<5;t++)
        {
        	for (ll x : numbers) newNumbers.pb(x);
        }
        numbers = newNumbers;
        string newPt1 = pt1;
        for (ll t=0;t<4;t++) newPt1 += "?"+pt1;
        pt1 = newPt1;
        vv dp(pt1.size()+2, v(numbers.size()+1,0));
        dp[pt1.size()][0]=1;
        dp[pt1.size()+1][0]=1;
        for (ll i=pt1.size()-1;i>=0;i--)
        {
        	for (ll j=0;j<=numbers.size();j++)
        	{
        		if (pt1[i] != '#') dp[i][j] += dp[i+1][j];
        		if (j>0)
        		{
        			ll amt = numbers[numbers.size()-j];
        			if (i+amt>pt1.size()) continue;
        			bool poss=true;
        			for (ll k=i; k<i+amt; k++)
        				if (pt1[k]=='.') poss = false;
        			if (i+amt<pt1.size()&&pt1[i+amt] == '#') poss = false;
        			if (poss) dp[i][j] += dp[i+amt+1][j-1];
        		}
        	}
        }
        res+=dp[0][numbers.size()];
    }
    cout << res << "\n";
    return 0;
}