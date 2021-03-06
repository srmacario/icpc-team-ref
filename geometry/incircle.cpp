//INCIRCLE

#include <bits/stdc++.h>

using namespace std;

#define st first
#define nd second
#define pb push_back
#define cl(x,v) memset((x), (v), sizeof(x))
#define db(x) cerr << #x << " == " << x << endl
#define dbs(x) cerr << x << endl
#define _ << ", " <<

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<int, pii> piii;
typedef pair<ll,ll> pll;
typedef pair<ll, pll> plll;
typedef vector<int> vi;
typedef vector <vi> vii;

const ld EPS = 1e-9, PI = acos(-1.);
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f, MOD = 1e9+7;
const int N = 1e5+5;

typedef long double type;

bool ge(type x, type y) { return x + EPS > y; }
bool le(type x, type y) { return x - EPS < y; }
bool eq(type x, type y) { return ge(x, y) and le(x, y); }

struct point {
  type x, y;

  point() : x(0), y(0) {}
  point(type x, type y) : x(x), y(y) {}

  point operator -() { return point(-x, -y); }
  point operator +(point p) { return point(x+p.x, y+p.y); }
  point operator -(point p) { return point(x-p.x, y-p.y); }

  point operator *(type k) { return point(k*x, k*y); }
  point operator /(type k) { return point(x/k, y/k); }

  type operator *(point p) { return x*p.x + y*p.y; }
  type operator %(point p) { return x*p.y - y*p.x; }

  // o is the origin, p is another point
  // dir == +1 => p is clockwise from this
  // dir ==  0 => p is colinear with this
  // dir == -1 => p is counterclockwise from this
  int dir(point o, point p) {
    type x = (*this - o) % (p - o);
    return ge(x,0) - le(x,0);
  }

  bool on_seg(point p, point q) {
    if (this->dir(p, q)) return 0;
    return ge(x, min(p.x, q.x)) and le(x, max(p.x, q.x)) and
           ge(y, min(p.y, q.y)) and le(y, max(p.y, q.y));
  }

  ld abs() { return sqrt(x*x + y*y); }
  type abs2() { return x*x + y*y; }
  ld dist(point x) { return (*this - x).abs(); }
  type dist2(point x) { return (*this - x).abs2(); }

  ld arg() { return atan2l(y, x); }

  // Project point on vector y
  point project(point y) { return y * ((*this * y) / (y * y)); }

  // Project point on line generated by points x and y
  point project(point x, point y) { return x + (*this - x).project(y-x); }

  ld dist_line(point x, point y) { return dist(project(x, y)); }

  ld dist_seg(point x, point y) {
    return project(x, y).on_seg(x, y) ? dist_line(x, y) :  min(dist(x), dist(y));
  }

  point rotate(ld sin, ld cos) { return point(cos*x-sin*y, sin*x+cos*y); }
  point rotate(ld a) { return rotate(sin(a), cos(a)); }
  // rotate around the argument of vector p
  point rotate(point p) { return rotate(p.x / p.abs(), p.y / p.abs()); }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    point p[3];
    cout << setprecision(10) << fixed;
    for(int i=0;i<3;i++) cin >> p[i].x >> p[i].y;
    //calculate area and find radius: area = semiperimeter * incircle_radius
    ld area = fabs(((p[2]-p[0])%(p[1]-p[0]))/2);
    ld per = 0;
    for(int i=0;i<3;i++){
        per += p[i].dist(p[(i+1)%3]);
    }
    ld rad = 2*(area/per);
    //find center using a triangle side unitary vector and its perpendicular (pointing to the opposite vertex)
    point base = (p[1] - p[0]) / (p[1] - p[0]).abs();
    point perp = base.rotate(p[1].dir(p[0],p[2]),0);
    //vector sum: p[0] + (center projection on side - p[0]) + radius * unitary in radial direction
    point center = p[0] + perp*rad + base*(per/2 - (p[2] - p[1]).abs());
    cout << center.x << " " << center.y << " " << rad << "\n";
    return 0;
}