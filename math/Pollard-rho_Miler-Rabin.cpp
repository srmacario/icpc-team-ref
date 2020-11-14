#include<bits/stdc++.h>
using namespace std;

// Esse código calcula quantos divisores um número muito grande tem

long long gcd(long long x, long long y){
	long long h;
	if(x<y) swap(x,y);
	while(x%y){
		h=x%y;
		x=y;
		y=h;
	}
	return y;
}

long long mul(long long x, long long y, long long n){
	long long r=0;
	while(y){
		if(y&1) r=(r+x)%n;
		y/=2;
		x=(x+x)%n;
	}
	return r;
}

long long pow(long long x, long long y, long long n){
	long long r=1;
	while(y){
		if(y&1) r=mul(r,x,n);
		y/=2;
		x=mul(x,x,n);
	}
	return r;
}

// Retorna um fator de N que não é 1 nem N
// Probabilisticamente O(sqrt(sqrt(N)))
long long pollard_rho(long long n) {
    long long x,y,d,c=1;
    if(!(n%2)) return 2;
    while(1) {
        y=x=2;
        while(1) {
            x=mul(x,x,n); x=(x+c)%n;
            y=mul(y,y,n); y=(y+c)%n;
            y=mul(y,y,n); y=(y+c)%n; 
            d=gcd(abs(y-x),n);
            if(d==n) break ; 
            else if(d>1) return d; 
        }
        c++;
    }
}

// Calcula se N é primo em O(k*log³N), sendo k quantos candidatos tem na sua base
bool miller_rabin(long long a , long long n) {
    if(a>=n) return true;
    long long r=0,s=n-1,j;
    while(!(s & 1)) s>>=1,r++;
    long long x=pow(a,s,n);
    if(x==1) return true;
    for(j=0;j<r;j++,x=mul(x,x,n)) if (x==n-1) return true ;
    return false ;
}
 
bool isprime (long long n) {
    long long base[]={2,3,5,7,11,13,17,19,23,29};
    for(int i=0;i<10;i++) if(!miller_rabin(base[i],n)) return false;
    return true ;
}

int main(){
	long long n,h,p,r=1;
	scanf("%lld", &n);
	for(long long i=2;i<=1e6;i++){
		h=1;
		while(n%i==0){
			n/=i;
			h++;
		}
		r*=h;
	}
	if(n==1) printf("%lld\n", r);
	else{
		if(isprime(n)) printf("%lld\n", 2*r);
		else if(pollard_rho(n)*pollard_rho(n)==n) printf("%lld\n", 3*r);
		else printf("%lld\n", 4*r);
	}
	return 0;
}
