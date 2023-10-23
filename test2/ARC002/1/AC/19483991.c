main(N){
  scanf("%d",&N);
  puts(N%4?"NO":N%100?"YES":N%400?"NO":"YES");
}