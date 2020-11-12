#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int K = 26;
const int S = 5; // num de strings

struct node{

  int next[K] , sl = 0 , p , letter , cnt = 0 , leaf = -1;

  bitset<S> elem;

  node(){memset(next,-1,sizeof(next)) , elem.reset();}

};

vector<node> trie;

void add_string(string s , int num){
  int u = 0;
  for(int i = 0 ; i < s.size() ; i++){
    int ch = s[i] - 'a';
    if(trie[u].next[ch] == -1)
      trie[u].next[ch] = trie.size() , trie.push_back(node());
    int v = trie[u].next[ch];
    trie[v].p = u , trie[v].letter = ch , u = v;
  }
  trie[u].leaf = num , trie[u].cnt++ , trie[u].elem.set(num,1);
}

void get_link(){
  queue<int> fila;
  int u = 0;
  fila.push(u);
  while(!fila.empty()){
    u = fila.front() , fila.pop();
    int inter = trie[u].p, l = trie[u].letter;
    if(u != 0){
      inter = trie[inter].sl;
      while(trie[inter].next[l] == -1 and inter != 0)
        inter = trie[inter].sl;
      if( inter == 0 && (trie[inter].next[l] == -1 || trie[inter].next[l] == u) )
        trie[u].sl = 0;
      else{
        trie[u].sl = trie[inter].next[l] , trie[u].cnt += trie[trie[u].sl].cnt;
        trie[u].elem |= trie[trie[u].sl].elem;
      }
    }
    for(int i = 0 ; i < K ; i++)
      if(trie[u].next[i] != -1) fila.push(trie[u].next[i]);
  }
}

int match(string s){

  bitset<S> bitresp;
  int resp = 0 , u = 0;
  bitresp.reset();
  for(int i = 0 ; i < s.size() ; i++){
    int ch = s[i] - 'a';
    while(trie[u].next[ch] == -1){
      if(trie[u].next[ch] == -1 && u == 0) break;
      u = trie[u].sl;
    }
    if(trie[u].next[ch] != -1){
      u = trie[u].next[ch] , resp += trie[u].cnt , bitresp |= trie[u].elem;
    }
  }
  return resp;
}

int n;
string str[S];

int main(){

  trie.pb(node());

  cin >> n;

  for(int i = 0 ; i < n ; i++){
    cin >> str[i];
    add_string(str[i],i);
  }

  get_link();

  string st;
  cin >> st;

  cout << match(st) << "\n";

}
