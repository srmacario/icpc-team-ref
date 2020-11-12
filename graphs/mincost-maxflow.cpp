#include <bits/stdc++.h>
using namespace std;

#define pb push_back

struct edge{int v , c , f , w;};

const int N = 1e3 , inf = 1e9;

vector<edge> edgs;
vector<int> g[N];
int p[N], n , m , snk , src;
bool in[N];

void add_edge(int u , int v , int c , int w){
  int k = edgs.size();
  edgs.pb({v,c,0,w}) , edgs.pb({u,0,0,-w});
  g[u].pb(k) , g[v].pb(k+1);
}

int shortest_path(int u){
  queue<int> fila;
  int dist[N];
  for(int i = 0 ; i < N; i++) dist[i] = inf;
  fila.push(u) , dist[u] = 0 , in[u] = true;
  while(!fila.empty()){
    u = fila.front() , fila.pop() , in[u] = false;
    for(int i = 0 ; i < g[u].size() ; i++){
      edge dir = edgs[g[u][i]];
      if(dist[dir.v] > dist[u] + dir.w && dir.c - dir.f > 0){
        dist[dir.v] = dist[u] + dir.w , p[dir.v] = g[u][i];
        if(!in[dir.v]){
          fila.push(dir.v) , in[dir.v] = true;
        }
      }
    }
  }
  return dist[snk];
}

int min_cost_flow(int flow){
  memset(in,0,sizeof(in));
  int resp = 0 , cost = 0 , d = shortest_path(src);
  while(resp != flow && d != inf){
    int f = flow - resp;
    for(int u = snk ; u != src ; ) f = min(f,edgs[p[u]].c - edgs[p[u]].f) , u = edgs[p[u]^1].v;
    for(int u = snk ; u != src ; ) edgs[p[u]].f += f , edgs[p[u]^1].f -= f , u = edgs[p[u]^1].v;
    resp += f , cost += d*f , d = shortest_path(src);
  }
  return cost;
}

int main(){

  cin >> n >> m;

  src = 1 , snk = n;

  for(int i = 0 ; i < m ; i++){
    int x , y , z , k;
    cin >> x >> y >> z >> k;
    add_edge(x,y,z,k);
  }

  cout << min_cost_flow(inf) << "\n";

}
