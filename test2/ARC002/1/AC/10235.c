#define C(y)(y%4?0:!(y%400)?1:!(y%100)?0:1)
main(x){scanf("%d",&x);puts(C(x)?"YES":"NO");exit(0);}