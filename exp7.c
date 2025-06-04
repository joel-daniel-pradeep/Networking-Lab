#include<stdio.h>
#define bucket_size 5
#define out_rate 3

void main(){
    int n;
    printf("enter the no of timeslots");
    scanf("%d",&n);
    int packets[n];
    printf("enter the packet sizes for each slot:\n");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &packets[i]);
    }
    int rem_water=0;
    for( int i=0;i<n;i++){
        printf("time slot :%d\n",i+1);
        printf("incoming packet size : %d\n",packets[i]);
        if(rem_water+packets[i]>bucket_size){
            printf("bucket overflow: packet of size %d is discarded\n",(rem_water+packets[i])-bucket_size);
            rem_water=bucket_size;
        }
        else{
            rem_water+=packets[i];
        }
        printf("current water amount in bucket : %d\n",rem_water);

        if(rem_water<=out_rate){
            rem_water=0;
        }
        else{
            rem_water-=out_rate;
        }
        printf("after leakage bucket size : %d\n",rem_water);
    }
}