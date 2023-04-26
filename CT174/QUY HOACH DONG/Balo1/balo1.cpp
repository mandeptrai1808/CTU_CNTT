#include <stdio.h>
#define size 30

typedef struct{
	char ten[50];
	int TL, GT, PA;
} DoVat;

void READ_FILE(DoVat a[], int *n, int *w){
	FILE *f;
	f = fopen("data.txt", "r");
	if(f!= NULL){
		int i = 0;
		fscanf(f, "%d", w);
		while(!feof(f)){
			fscanf(f, "%d%d%[^\n]", &a[i].TL, &a[i].GT, &a[i].ten);
			a[i].PA = 0;
			i++;
		}
		*n = i;
		
	} else printf("ERROR READ FILE!\n");
}


void PRINT_TABLE(DoVat a[], int n, int w){
	printf("|===|====================|==========|==========|==========|\n");
	printf("|%-3s|%-20s|%-10s|%-10s|%-10s|\n", "STT", "Ten", "KL", "GT", "PA");
	printf("|===|====================|==========|==========|==========|\n");
	for(int i = 0 ; i < n ;i ++){
		printf("|%-3d|%-20s|%-10d|%-10d|%-10d|\n", (i+1), a[i].ten, a[i].TL, a[i].GT, a[i].PA);
	}
	printf("|===|====================|==========|==========|==========|\n");
}


void tao_bang(DoVat a[], int X[][size], int F[][size], int n, int w){
	for(int v = 0; v <= w; v++){
		X[0][v] = v / a[0].TL;
		F[0][v] = X[0][v] * a[0].GT; 
	}
	
	
	
	for(int k = 1; k < n; k++){
		for(int v = 0; v <= w; v++){
			int Fmax = F[k-1][v];
			int Xmax = 0;
			int yk = v / a[k].TL;
			for(int xk = 1; xk <= yk; xk++){
				if(F[k-1][v - xk*a[k].TL] + xk*a[k].GT > Fmax){
					Fmax = F[k-1][v - xk*a[k].TL] + xk*a[k].GT;
					Xmax = xk;
				}
			}
			F[k][v] = Fmax;
			X[k][v] = Xmax;
		}
	}
}

void tra_bang(DoVat a[], int X[][size], int n, int w){
	int v = w;
	for(int i = n-1; i >= 0; i--){
		a[i].PA = X[i][v];
		v -= X[i][v] * a[i].TL;
	}
}

void in_bang(int X[][size], int F[][size], int n, int w){
	for(int i = 0; i < n; i++){
		for(int j= 0 ; j <= w; j++) printf("%3d%3d|", F[i][j], X[i][j]);
		printf("\n");
	}	
}
int main(){
	DoVat a[30];
	int n, w;
	READ_FILE(a, &n, &w);
	
	int X[size][size], F[size][size];
	tao_bang(a, X, F, n ,w);
	in_bang(X, F, n, w);
	tra_bang(a, X, n, w);
	PRINT_TABLE(a, n, w);
	return 0;
}
