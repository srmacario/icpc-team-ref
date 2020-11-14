#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back

typedef pair<int,int> pii;
typedef pair<int,pii> piii;

const int N = 1e5+5;

vector<int> adj[N] , adjr[N];
vector<int> order, component;
int n , m , vis[N];

void dfs1(int u){
  vis[u] = 1;
  for(size_t i = 0 ; i < adj[u].size() ; ++i)
    if(!vis[adj[u][i]]) dfs1(adj[u][i]);
  order.push_back(u);
}

void dfs2(int u){
  vis[u] = 1 , component.push_back(u);
  for(size_t i = 0 ; i < adjr[u].size() ; ++i)
    if(!vis[adjr[u][i]]) dfs2(adjr[u][i]);
}

void kosaraju(){
  
  order.clear();

  memset(vis,0,sizeof(vis));
  for(int i = 1 ; i <= n ; i++)
    if(!vis[i]) dfs1(i);

  memset(vis,0,sizeof(vis));
  for(int i = order.size()-1 ; i >= 0 ; i--)
    if(!vis[order[i]]){
      component.clear() , dfs2(order[i]);
      for(int j = 0 ; j < component.size() ; j++) cout << component[j] << " ";
      cout << "\n";
    }

}

int main(){

  cin >> n >> m;

  for(int i = 0 ; i < m ; i++){
    int x , y;
    cin >> x >> y;
    adj[x].pb(y) , adjr[y].pb(x);
  }

  kosaraju();

}

