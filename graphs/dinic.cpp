#include <bits/stdc++.h>
using namespace std;

#define pb push_back

struct edge{int v , c , f;};
const int N = 1e3+5 , INF = 1e9;

vector<int> g[N] , q;
vector<edge> edgs;
int snk , src , vis[N] , ptr[N] , h[N];
bool ok;

void add_edge(int u , int v , int c){
  int k = edgs.size();
  edgs.pb({v,c,0}) , edgs.pb({u,c,0});// {u,0,0} graph directed {u,c,0} bidirected:x
  g[u].pb(k) , g[v].pb(k+1);
}

bool bfs(int u){
  queue<int> fila;
  memset(h,0,sizeof(h)) , fila.push(u) , h[u] = 1;
  while(!fila.empty()){
    u = fila.front() , fila.pop();
    for(int i = 0 ; i < g[u].size() ; i++){
      if(edgs[g[u][i]].c - edgs[g[u][i]].f == 0 || h[edgs[g[u][i]].v] != 0) continue;
      h[edgs[g[u][i]].v] = h[u] + 1 , fila.push(edgs[g[u][i]].v);
    }
  }
  return h[snk];;
}

void find_path(int u , int k){
  if(vis[u] == k) return;
  vis[u] = k;
  if(u == snk){ok = true; return;}
  for(int &i = ptr[u] ; i < g[u].size() ; i++){
    edge dir = edgs[g[u][i]];
    if(dir.c - dir.f == 0 || h[dir.v] != h[u] + 1) continue;
    find_path(edgs[g[u][i]].v,k);
    if(ok){q.pb(g[u][i]); return;}
  }
}

int Dinic(){
  int resp = 0 , cnt = 1;
  while(bfs(src)){
    int flow = INF;
    cnt++ , ok = false , q.clear() , memset(ptr,0,sizeof(ptr));
    find_path(src,cnt);
    while(!q.empty()){
      for(int i = 0 ; i < q.size() ; i++) flow = min(flow,edgs[q[i]].c-edgs[q[i]].f);
      for(int i = 0 ; i < q.size() ; i++) edgs[q[i]].f += flow , edgs[q[i]^1].f -= flow;
      resp += flow , q.clear() , ok = false , flow = INF , cnt++ , find_path(src,cnt);
    }
 }
    return resp;
}

int n , m;

int main(){

  cin >> n >> m;
  src = 1 , snk = n;

  for(int i = 0 ; i < m ; i++){
    int x , y , z;
    cin >> x >> y >> z;
    add_edge(x , y , z);
  }

  cout << Dinic() << "\n";

  for(int i = 0 ; i < edgs.size() ; i+= 2)
    cout << edgs[i].f << "\n";
}

