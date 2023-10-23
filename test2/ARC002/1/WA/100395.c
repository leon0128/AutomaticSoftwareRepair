#include <stdio.h>

int main (void)
{
	int i,j;
	int daymin,monmin;
	int uruu,flg;
	int waridata,waridata1;
	int year,mon,day;
	int mondata[12] = {31,29,31,30,31,30,31,31,30,31,30,31},mondata1[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	float wari,wari1;
	
	scanf ("%d/%d/%d",&year,&mon,&day);
	
	uruu=0;
	if (year%4 == 0 && year%100 != 0 || year%400 == 0) 
		uruu=1;
		
	wari=(float)year/mon/day;
	waridata=wari;
	wari=wari-waridata;
	
//	printf ("%f\n",wari);	
	
	if (wari == 0) {
		printf ("%04d/%02d/%02d\n",year,mon,day);
	}
	else {
		if (uruu) {
			monmin=13;
			daymin=32;
			flg=0;
			for (i=day+1; i<=mondata[mon-1]; i++) {
				wari1=(float)year/mon/i;
				waridata1=wari1;
				wari1=wari1-waridata1;
				if (wari1 == 0 && i < daymin) 
					daymin=i;
			}
			
			if (daymin != 32) 
				printf ("%04d/%02d/%02d\n",year,mon,daymin);
			
			else {
				for (i=mon+1; i<=12; i++) {
					for (j=1; j<=mondata[i-1]; j++) {
						wari1=(float)year/i/j;
						waridata1=wari1;
						wari1=wari1-waridata1;
						if (wari1 == 0 && i < monmin && j < daymin) {
							monmin=i;
							daymin=j;
						}
					}
				}
				if (monmin != 13 && daymin != 32) 
					printf ("%04d/%02d/%02d\n",year,monmin,daymin);
				
				else  		printf ("%d/01/01\n",year+1);
			}
		}
		else {
			monmin=13;
			daymin=32;
			flg=0;
			for (i=day+1; i<=mondata1[mon-1]; i++) {
				wari1=(float)year/mon/i;
				waridata1=wari1;
				wari1=wari1-waridata1;
				if (wari1 == 0 && i < daymin) 
					daymin=i;
			}
			
			if (daymin != 32) 
				printf ("%04d/%02d/%02d\n",year,mon,daymin);
			
			else {
				for (i=mon+1; i<=12; i++) {
					for (j=1; j<=mondata1[i-1]; j++) {
						wari1=(float)year/i/j;
						waridata1=wari1;
						wari1=wari1-waridata1;
						if (wari1 == 0 && i < monmin && j < daymin) {
							monmin=i;
							daymin=j;
						}
					}
				}
				if (monmin != 13 && daymin != 32) 
					printf ("%04d/%02d/%02d\n",year,monmin,daymin);
				
				else  		printf ("%d/01/01\n",year+1);
			}
		}
	}
	
	return 0;
}
