#include<bits/stdc++.h>
using namespace std;

// dado n, qual os menores g0 e g1 (desempate em g1) que formam uma sequencia de fibonacci
// começando por eles e possui n

long long n,fib[50],a,b,ant,bnt,ma,mb,k;

long long mdc(long long x, long long y){
	if(x%y) return mdc(y,x%y);
	return y;
}

// ax+by=n com n multiplo de mdc(x,y)
// diof(x,y) vai achar a,b para ax+by=mdc(x,y), depois basta multiplicar a e b por n/mdc(x,y)
// inicia com a,bnt=1 e ant,b=0
void diof(long long x, long long y){
	if(x%y){
		a=ant-a*(x/y);
		ant=(ant-a)/(x/y);
		b=bnt-b*(x/y);
		bnt=(bnt-b)/(x/y);
		diof(y,x%y);
	}
}

// recorrencia estilo fibonacci começando por g0 e g1 temos [f(k+1) f(k)]=[g1 g0]*(A^k)
// A=|1 1|
//   |1 0|
// A^k=|fib(k+1) fib(k)|   fib(1)=1, fib(0)=0
//    |fib(k) fib(k-1)|

int main(){
	fib[1]=1;
	for(int i=2;i<50;i++) fib[i]=fib[i-1]+fib[i-2];
	scanf("%lld", &n);
	ma=1;
	mb=n-1;
	for(int i=3;fib[i]<=n;i++){
		long long m=mdc(fib[i-1],fib[i-2]);
		if(n%m) continue;
		b=0;
		bnt=1;
		a=1;
		ant=0;
		diof(fib[i-1],fib[i-2]);
		a*=n/m;
		b*=n/m;
		// voltando para o menor b tal que a,b positivos. 
		// em diofantina, as soluções de a anda em multiplos de y/mdc(x,y) e b em multiplos
		// de x/mdc(x,y)
		if(a>b){
			k=(a-b)*m/(fib[i-1]+fib[i-2])+1;
			a-=k*fib[i-1]/m;
			b+=k*fib[i-2]/m;
		}
		k=(b-a)*m/(fib[i-1]+fib[i-2]);
		a+=k*fib[i-1]/m;
		b-=k*fib[i-2]/m;
		if(a>0 && b>0){
			if(b<mb){
				ma=a;
				mb=b;
			}
			if(mb==b && m<ma){
				ma=a;
				mb=b;
			}
		}
	}
	printf("%lld %lld\n", ma, mb);
	return 0;
}
