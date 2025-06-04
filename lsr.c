#include <stdio.h>

#define inf 9999
int adj[20][20],n;

void printpath(int j,int parent[]){
    if (parent[j]==-1){
        printf("%d",j);
        return;
    }
    printpath(parent[j],parent);
    printf("->%d",j);
}

int mindist(int dist[],int visited[]){
    int minindex=-1,min=inf,i;
    for(i=0;i<n;i++){
        if(!visited[i] && min>dist[i]){
            min=dist[i];
            minindex=i;
        }
    }
    return minindex;
}

void dijkstras(int k){
    int dist[20],parent[20],visited[20],i,j;
    for(i=0;i<n;i++){
        dist[i]=inf;
        parent[i]=-1;
        visited[i]=0;
    }
    dist[k]=0;

    for(i=0;i<n-1;i++){
        int m=mindist(dist,visited);
        if(m==-1){
            return;
        }
        visited[m]=1;
        for(j=0;j<n;j++){
            if(!visited[j] && dist[m]!=inf && adj[m][j]!=inf && dist[j]>adj[m][j]+dist[m]){
                dist[j]=adj[m][j]+dist[m];
                parent[j]=m;
            }
        }
    }
    printf("Printing routing table for router %d\n",k);
    printf("node\tdistance\tnexthop\tpath\n");
    for(j=0;j<n;j++){
        printf("%d\t%d\t\t",j,dist[j]);
        int nexthop=j;
        while(parent[nexthop]!=-1 && parent[nexthop]!=k ){
            nexthop=parent[nexthop];
        }
        printf("%d",nexthop);
        printpath(j,parent);
        printf("\n");
    }
}
int main(){
    int i,v,j;
    printf("enter the number of routers\n");
    scanf("%d",&n);
    printf("Enter the adjacency matrix\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&adj[i][j]);
        }
    }

    for(v=0;v<n;v++){
        dijkstras(v);
    }
    return 0;
}