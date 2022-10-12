#include <stdio.h>
#include<string.h>
int main(void){
      int h,w;
      scanf("%d%d",&h,&w);
      char g[h+2][w+2];
      int x,t;
      for(x=1;x<=h;x++){
            scanf("%s",g[x]+1);
      }
      int ver[10000000],bes[10000000];
      int stop=0,i=1,j=1,cou=0,stopstop=0;
      while(stop<=0&&stopstop<=0&&cou<1000){
            ver[cou]=i;
            bes[cou]=j;
            if(g[i][j]=='U'&&i!=1){
                  i=i-1;
            }else if(g[i][j]=='D'&&i!=h){
                  i=i+1;
            }else if(g[i][j]=='L'&&j!=1){
                  j=j-1;
            }else if(g[i][j]=='R'&&j!=w){
                  j=j+1;
            }else{
                  stop++;
            }
            if(cou>=3){
            
            cou++;
      }
      for(x=1;x<=cou-1;x++){
                  if(stop>0){}else if(stopstop>0){}else{
                  if(ver[x]==i&&bes[x]==j){
                        if(ver[x-1]==ver[cou]&&bes[x-1]==ver[cou]){
                              stopstop++;
                        }
                  }
                  
            }}}
      if(stopstop>0){
            printf("-1");
      }else{
            printf("%d %d\n",i,j);
      }
      return 0;
}