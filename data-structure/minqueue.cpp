struct minQueue{
    deque<pll> dq;
    ll ini, fim;
    minQueue(){
        ini = 1, fim = 0;
    }
    void push(ll x){
        while(!dq.empty() and dq.back().st >= x) dq.pop_back();
        dq.pb({x,++fim});
    }
    void pop(){
        if(!dq.empty() and (dq.front().nd == ini++)) dq.pop_front();
    }
    ll query(){
        return dq.front().st;
    }
};

struct maxQueue{
    deque<pll> dq;
    ll ini, fim;
    maxQueue(){
        ini = 1, fim = 0;
    }
    void push(ll x){
        while(!dq.empty() and dq.back().st <= x) dq.pop_back();
        dq.pb({x,++fim});
    }
    void pop(){
        if(!dq.empty() and (dq.front().nd == ini++)) dq.pop_front();
    }
    ll query(){
        return dq.front().st;
    }
};