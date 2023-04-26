#include <stdio.h>

#define size 30

typedef struct{
	float do_dai;
	int dau, cuoi, da_dung;
}canh;

void READ_FILE(char filename[], canh a[][size], int *n){
	FILE *f;
	f = fopen(filename, "r");
	if(f!=NULL){
		fscanf(f, "%d", n);
		for(int i = 0; i < *n; i++)
			for(int j = 0; j < *n; j++){
				fscanf(f, "%f", &a[i][j].do_dai);
				a[i][j].dau = i;
				a[i][j].cuoi = j;
			}	
	} else printf("ERROR READ FILE!\n");
}

void PRINT_MATRIX(canh a[][size], int n){
	for(int i = 0; i < n; i++)
		{
			for(int j = 0; j <= 0; j++)
				printf("%c%c = %5.2f    ", a[i][j].dau + 97, a[i][j].cuoi +97, a[i][j].do_dai);
			printf("\n");
		}
}


int main(){
	canh a[size][size];
	int n;	
	
	READ_FILE("data.txt",a, &n);
	PRINT_MATRIX(a, n); 
	
	return 0;
}
