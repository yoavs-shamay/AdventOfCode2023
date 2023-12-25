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
    vvb grid;
    ll startX, startY;
    ll x = 0;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        vb cur;
        ll y = 0;
        for (auto c : str)
        {
            cur.pb(c == '#');
            if (c == 'S')
            {
                startX = x; startY = y;
            }
            y++;
        }
        x++;
        grid.pb(cur);
    }
    ll N = grid.size(), M = grid[0].size();
    v possX = {0, startX, N - 1}, possY = {0, startY, M - 1};
    ll maxi = -INF;
    for (auto x : possX)
    {
        for (auto y : possY)
        {
            vvv distance(N, vv(M, v(2, -1)));
            queue<pair<p, ll>> dfs;
            dfs.emplace(p(x, y), 0);
            while (!dfs.empty())
            {
                auto top = dfs.front();
                dfs.pop();
                if (top.f.f < 0 || top.f.s < 0 || top.f.f >= N || top.f.s >= M) continue;
                if (grid[top.f.f][top.f.s]) continue;
                if (distance[top.f.f][top.f.s][top.s % 2] != -1) continue;
                distance[top.f.f][top.f.s][top.s % 2] = top.s;
                dfs.emplace(p(top.f.f + 1, top.f.s), top.s + 1);
                dfs.emplace(p(top.f.f - 1, top.f.s), top.s + 1);
                dfs.emplace(p(top.f.f, top.f.s + 1), top.s + 1);
                dfs.emplace(p(top.f.f, top.f.s - 1), top.s + 1);
            }
            for (ll i = 0; i < N; i++) for (ll j = 0; j < M; j++) for (ll k = 0 ; k < 2 ;k++) if (distance[i][j][k] != -1) setmax(maxi, distance[i][j][k]);
        }
    }
    ll actMaxi = ceil((double) maxi / N) * N;
    maxi = actMaxi;
    vvv reachableSquares(3, vv(3, v(maxi + 2, 0)));
    for (ll i=  0; i < 3; i++)
    {
        for (ll j = 0; j < 3; j++)
        {
            for (ll k = 0; k < maxi + 2; k++)
            {
                ll x = i * startX, y = j * startY;
                vvb visited(N, vb(M, false));
                queue<tri> bfs;
                bfs.emplace(0, p(x, y));
                while (!bfs.empty())
                {
                    auto top = bfs.front();
                    bfs.pop();
                    if (top.s.f < 0 || top.s.s < 0 || top.s.f >= N || top.s.s >= M) continue;
                    if (visited[top.s.f][top.s.s]) continue;
                    if (grid[top.s.f][top.s.s]) continue;
                    if (top.f > k) continue;
                    visited[top.s.f][top.s.s] = true;
                    if (top.f % 2 == k % 2) reachableSquares[i][j][k]++;
                    bfs.emplace(top.f+1,p(top.s.f+1,top.s.s));
                    bfs.emplace(top.f+1,p(top.s.f-1,top.s.s));
                    bfs.emplace(top.f+1,p(top.s.f,top.s.s+1));
                    bfs.emplace(top.f+1,p(top.s.f,top.s.s-1));
                }
            }
        }
    }
    //TODO - once - single discount, twice - double discount
    const ll maxSteps = 26501365;
    ll totalSteps = maxSteps - startX - 1;
    ll totalStepsDiag = maxSteps - 2 * startX - 2;
    ll maxStepStraight = (totalSteps - actMaxi) / N + 1;
    ll maxStepsDiag = (totalStepsDiag - actMaxi) / N + 2;
    ll amt = reachableSquares[1][1][maxi + ((maxSteps - maxi) % 2)];
    for (ll i = 1; i <= maxStepStraight; i++)
        amt += (reachableSquares[2][1][maxi + ((totalSteps - N * (i - 1) - maxi) % 2)] + reachableSquares[0][1][maxi + ((totalSteps - N * (i - 1) - maxi) % 2)] + reachableSquares[1][0][maxi + ((totalSteps - N * (i - 1) - maxi) % 2)] + reachableSquares[1][2][maxi + ((totalSteps - N * (i - 1) - maxi) % 2)]);
    //Amount of ways to write a + b <= atLeast where both are at least 1
    for (ll i = 2; i <= maxStepsDiag; i++)
        amt += ((i - 1) * (reachableSquares[0][0][maxi + ((totalStepsDiag - N * (i - 2) - maxi) % 2)] + reachableSquares[0][2][maxi + ((totalStepsDiag - N * (i - 2) - maxi) % 2)] + reachableSquares[2][0][maxi + ((totalStepsDiag - N * (i - 2) - maxi) % 2)] + reachableSquares[2][2][maxi + ((totalStepsDiag - N * (i - 2) - maxi) % 2)]));
    //Now actually 131 remaining
    ll straightRemaining = totalSteps - (maxStepStraight) * N;
    for(;straightRemaining >= 0; straightRemaining-=N)
    {
        amt += reachableSquares[1][0][straightRemaining] + reachableSquares[1][2][straightRemaining] + reachableSquares[0][1][straightRemaining] + reachableSquares[2][1][straightRemaining];
    }
    ll diagRemaining = totalStepsDiag - (maxStepsDiag - 1) * N;
    for(;diagRemaining >= 0; diagRemaining-=N)
    {
        amt += (maxStepsDiag) * (reachableSquares[0][0][diagRemaining] + reachableSquares[0][2][diagRemaining] + reachableSquares[2][0][diagRemaining] + reachableSquares[2][2][diagRemaining]);
        maxStepsDiag++;
    }
    cout << amt << "\n";
    input.close();
    return 0;
}