/*
*   Author: Georgios Romporas
*   Created Nov 17 2023
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
const int N = 5;

int max(int a,int b){
    return (a>b) ? a : b;
}

bool isValid(int i, int j){
    return (i>=0 && i<=(N-1) && j>=0 && j<=(N-1));
}

int main(){
    int mine[5][5] = { 
        {0, 0, 0, 0, 0}, 
        {1, 6, 0, 0, 0}, 
        {3, 5, 1, 0, 0}, 
        {15, 3, 8, 2, 0}, 
        {1, 2, 2, 6, 4}, 
    };
    int dp[5][5] = {0};
    
    dp[1][0]=mine[1][0];
    dp[1][1]=mine[1][1];
    
    int LEN = 3;
    for(int i=2; i<N; i++){
        for(int j=0; j<LEN; j++){
            
            int v1,v2 = 0;
            if(isValid(i-1,j)){
                v1 = dp[i-1][j];
            }
            if(isValid(i-1,j-1)){
                v2 = dp[i-1][j-1];
            }
            
            dp[i][j] = max(v1,v2)+mine[i][j];

        }
        LEN++;
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
    int mx = dp[N-1][0];
    int pos_i=N-1, pos_j = 0;
    for(int j=1; j<N; j++){
        if(dp[N-1][j]> mx){
            mx = dp[N-1][j];
            pos_j = j;
        }
    }
    printf("Max golden rocks: %d\n", mx);
    
    int temp_i=pos_i;
    int temp_j=pos_j;
    /*** PATH SIZE == (N-1) ***/
    int path[4];
    path[3] = mine[pos_i][pos_j];
    int idx = 2;
    for(int t = 0; t<N-2; t++){

        mx = -1;
        
        if(isValid(pos_i-1,pos_j)){
            if(dp[pos_i-1][pos_j]>mx){
                mx = dp[pos_i-1][pos_j];
                temp_i=pos_i-1;
                temp_j=pos_j;
            }
        }
        if(isValid(pos_i-1,pos_j-1)){
            if(dp[pos_i-1][pos_j-1]>mx){
                mx = dp[pos_i-1][pos_j-1];
                temp_i=pos_i-1;
                temp_j=pos_j-1;
            }
        }
        path[idx]=mine[temp_i][temp_j];
        if(idx>=1){
            idx--;
        }
        pos_i = temp_i;
        pos_j = temp_j;
    
    }
    printf("Solution Path: \n");
    for(int i=0; i<3; i++){
        printf("%d -> ", path[i]);
    }
    printf("%d\n", path[3]);
   
}
