#include<stdio.h>

#define max_nodes 5

struct node{
    int distance[max_nodes];
    int next_hop[max_nodes];
};

void main(){
    int n,i,j,k;
    printf("enter the number of nodes:\n");
    scanf("%d",&n);
    struct node nodes[n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i!=j){
                nodes[i].distance[j]=9999;
            }
            else{
                nodes[i].distance[j]=0;
            }
            nodes[i].next_hop[j]=-1;
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(nodes[i].distance[j]==9999 && i<j)
            {
                printf("Enter the direct cost from node %d to node %d (9999 if indirect): ", i, j);
                scanf("%d", &nodes[i].distance[j]);
                nodes[j].distance[i]=nodes[i].distance[j];
                nodes[i].next_hop[j]=j;
                nodes[j].next_hop[i]=i;
            }
            
        }
    }
    int flag;
    do{
        flag=0;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<n;k++){
                    if(nodes[i].distance[j]>nodes[i].distance[k]+nodes[k].distance[j]){
                        nodes[i].distance[j]=nodes[i].distance[k]+nodes[k].distance[j];
                        nodes[i].next_hop[j]=nodes[i].next_hop[k];
                        flag=1;
                    }
                }
            }
        }
    }while(flag);
    for (i = 0; i < n; i++) 
    {
        printf("\nRouting Table for Node %d:\n", i);
        printf("Destination\tCost\tNext Hop\n");
        for (j = 0; j < n; j++) 
        {
            printf("%d\t\t%d\t", j, nodes[i].distance[j]);
            if (nodes[i].next_hop[j] == -1) 
            {
                printf("-\n");
            } else 
            {
                printf("%d\n", nodes[i].next_hop[j]);
            }
        }
    }
    
}