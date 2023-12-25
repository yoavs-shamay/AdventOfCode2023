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
const double EPS = 1e-5;

#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define loop(a) for (ll i = 0; i < a; i++)
#define setmin(a, b) a = min(a, b)
#define setmax(a, b) a = max(a, b)
#define all(v) v.begin(), v.end()

#define double long double

typedef struct Point
{
    double x, y, z;
    Point()
    {
        x = 0; y = 0; z = 0;
    }
    Point(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point operator+(Point other)
    {
        return Point(x+other.x,y+other.y,z+other.z);
    }
    Point operator-(Point other)
    {
        return Point(x-other.x,y-other.y,z-other.z);
    }
    Point operator*(double mul)
    {
        return Point(x*mul,y*mul,z*mul);
    }
    Point operator/(double mul)
    {
        return Point(x/mul,y/mul,z/mul);
    }
    void operator+=(Point other)
    {
        x += other.x; y += other.y; z += other.z;
    }
    void operator-=(Point other)
    {
        x -= other.x; y -= other.y; z -= other.z;
    }
    void operator*=(double mul)
    {
        x *= mul; y *= mul; z *= mul;
    }
    void operator/=(double mul)
    {
        x /= mul; y /= mul; z /= mul;
    }
} Point;

typedef struct Equation
{
    double a, b, c;
    Equation()
    {
        a = 0; b = 0; c = 0;
    }
    Equation(Point start, Point velocity)
    {
        if (velocity.x == 0)
        {
            a = 1;
            b = 0;
            c = -start.x;
        }
        else
        {
            a = velocity.y / velocity.x;
            b = -1;
            c = start.y - start.x * a;
        }
    }
} Equation;

typedef struct Hailstone
{
    Point start;
    Point velocity;
    Equation eq;
    Hailstone(Point start, Point velocity)
    {
        this->start = start;
        this->velocity = velocity;
        this->eq = Equation(start, velocity);
    }
    Hailstone(ll sx,ll sy,ll sz,ll vx,ll vy,ll vz) : Hailstone(Point(sx,sy,sz), Point(vx,vy,vz)) {}
} Hailstone;

bool onSegment(Point p, Point q, Point r)
{
    return q.x <= (max(p.x, r.x) + EPS) && q.x >= (min(p.x, r.x) - EPS) && q.y <= (max(p.y, r.y) + EPS) && q.y >= (min(p.y, r.y) - EPS);
}
ll orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    if (abs(val) < EPS) return 0;
    return (val > 0)? 1: 2;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    ll o1 = orientation(p1, q1, p2); 
    ll o2 = orientation(p1, q1, q2); 
    ll o3 = orientation(p2, q2, p1); 
    ll o4 = orientation(p2, q2, q1); 
    if (o1 != o2 && o3 != o4) 
        return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
    return false;
} 

typedef struct Segment
{
    Point start;
    Point end;
    Equation eq;
    Segment(Point start, Point end)
    {
        this->start = start;
        this->end = end;
        eq = Equation(start, end - start);
    }
} Segment;

const ll from = 2e14;
const ll to = 4e14;

int main()
{
    ifstream input("C:\\Projects\\AdventOfCode\\2023\\in.txt");
    vector<Hailstone> hails;
    while(!input.eof())
    {
        string str;
        getline(input, str);
        ll sx = 0, sy = 0, sz = 0, vx = 0, vy = 0, vz = 0;
        sscanf(str.c_str(),"%lld,%lld,%lld@%lld,%lld,%lld", &sx,&sy,&sz,&vx,&vy,&vz);
        hails.eb(sx,sy,sz,vx,vy,vz);
    }
    vector<Segment> segments;
    for (auto hail : hails)
    {
        if (hail.velocity.x == 0)
        {
            if (hail.start.x >= from && hail.start.y <= to) {segments.eb(Point(hail.start.x,from,0), Point(hail.start.x,to,0));}
        }
        else if (hail.velocity.x > 0 && hail.start.x <= to)
        {
            double curFrom = max((double)from, hail.start.x);
            double y1 = curFrom * hail.eq.a + hail.eq.c;
            double y2 = to * hail.eq.a + hail.eq.c;
            segments.eb(Point(curFrom, y1, 0), Point(to, y2, 0));
        }
        else if (hail.velocity.x < 0 && hail.start.x >= from)
        {
            double curTo = min((double)to, hail.start.x);
            double y1 = from * hail.eq.a + hail.eq.c;
            double y2 = curTo * hail.eq.a + hail.eq.c;
            segments.eb(Point(from, y1, 0), Point(curTo, y2, 0));
        }
    }
    ll cnt = 0;
    for (ll i = 0; i < segments.size(); i++)
    {
        for (ll j = i + 1; j < segments.size(); j++)
        {
            if (doIntersect(segments[i].start, segments[i].end, segments[j].start, segments[j].end))
            {
                Equation eq1 = segments[i].eq, eq2 = segments[j].eq;
                if (eq1.b * eq2.a == eq1.a * eq2.b)
                {
                    double fromY = max(segments[i].start.y, segments[j].start.y);
                    double toY = min(segments[i].end.y, segments[j].end.y);
                    if (fromY > toY) swap(fromY, toY);
                    if (fromY <= to && toY >= from) cnt++;
                }
                else
                {
                    Point intersection((eq1.c * eq2.b - eq1.b * eq2.c) / (eq1.b * eq2.a - eq1.a * eq2.b), (eq1.a * eq2.c - eq1.c * eq2.a) / (eq1.b * eq2.a - eq1.a * eq2.b), 0);      
                    if (intersection.y >= from - EPS && intersection.y <= to + EPS) cnt++; 
                }
            }
        }
    }
    cout << cnt << "\n";
    input.close();
    return 0;
}