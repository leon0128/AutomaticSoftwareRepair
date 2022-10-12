#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1

int main(){
  int i,j,H,W;scanf("%d%d",&H,&W);
  char **g=NULL;
  int **vis=NULL;
  g=(char**)malloc(sizeof(char*)*H);
  vis=(int**)malloc(sizeof(int*)*H);
  
  for(i=0;i<H;i++){
    g[i]=(char*)malloc(sizeof(char*)*(W+1));
    vis[i]=(int*)malloc(sizeof(int*)*W);
    for(j=0;j<W;j++){
      scanf(" %c",&g[i][j]);
      vis[i][j]=FALSE;
    }
    g[i][j+1]='\0';
  }

  i=j=0;
  while(1){
    if(vis[i][j]==TRUE){
      printf("-1");
      exit(0);
    }
    vis[i][j]=TRUE;
    if(g[i][j]=='U'&&i!=0){
      --i;
    }else if(g[i][j]=='D'&&i!=H-1){
      ++i;
    }else if(g[i][j]=='L'&&j!=0){
      --j;
    }else if(g[i][j]=='R'&&j!=W-1){
      ++j;
    }else break;
  }

  printf("%d %d",i+1,j+1);

  return 0;
}