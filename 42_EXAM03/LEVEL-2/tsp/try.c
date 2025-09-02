#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct { float x,y; } P;

float d(P a,P b){
    float dx=a.x-b.x,dy=a.y-b.y;
    return sqrtf(dx*dx+dy*dy);
}

void tsp(P*p,int*n,int l,int r,float*best,int N){
    if(l==r){
        float sum=0;
        for(int i=0;i<N-1;i++) {
            sum+=d(p[n[i]],p[n[i+1]]);
        };
        sum+=d(p[n[N-1]],p[n[0]]);
        if(sum<*best)
            *best=sum;
        return;
    }
    for(int i=l;i<=r;i++){
        int t=n[l]; 
        n[l]=n[i];
        n[i]=t;
        tsp(p,n,l+1,r,best,N);
        t=n[l]; 
        n[l]=n[i]; 
        n[i]=t;
    }
}

int main(){
    P p[11]; int N=0;
    while(scanf("%f, %f",&p[N].x,&p[N].y)==2)
        N++;
    int n[11]; 
    for(int i=0;i<N;i++)
        n[i]=i;
    float best=1e30f;
    tsp(p,n,1,N-1,&best,N); 
    printf("%.2f\n",best);
    return 0;
}
