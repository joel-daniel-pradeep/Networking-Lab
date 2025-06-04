#include <stdio.h>
#define inf 9999
 
void main(){
    int cost[20][20],dist[20][20],nexthop[10][20],n,i,j,k;
    printf("enter the no. of routers\n");
    scanf("%d",&n);
    printf("Enter the cost matrix. In case no direct link - enter 9999 as the distance\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&cost[i][j]);
            dist[i][j]=cost[i][j];
            nexthop[i][j]=(cost[i][j]==inf)?-1:j;
        }
    }
    
    printf("Using Bellman fords algorithm to calculate shortest route\n");

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                if (dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nexthop[i][j]=nexthop[i][k];
                }
            }
        }
    }
    for(i=0;i<n;i++){
        printf("Routing table for router %d\n",i);
        printf("node\tdistance\tnextnode\tpath\n");
        for(j=0;j<n;j++){
            printf("%d\t%d\t\t%d\t\t",j,dist[i][j],nexthop[i][j]);
            k=i;
            while(k!=j){
                printf("%d->",k);
                k=nexthop[k][j];
            }
            printf("%d\n",j);
        }
    }
    printf("FInished");
}