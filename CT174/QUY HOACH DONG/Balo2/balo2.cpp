#include <stdio.h>

typedef int bang[50][30];

typedef struct{
	char ten[50];
	int TL, GT,  SL, PA;
} DoVat;

void READ_FILE(DoVat a[], int *n, int *w){
	FILE *f;
	f = fopen("data.txt", "r");
	if(f != NULL){
		int i = 0;
		fscanf(f, "%d", w);
		while(!feof(f)){
			fscanf(f, "%d%d%d%[^\n]", &a[i].TL, &a[i].GT, &a[i].SL, &a[i].ten);
			a[i].PA = 0;
			i++;
		}
		*n = i;
		fclose(f);
	} else printf("ERROR READ FILE!");
}

void PRINT_TABLE(DoVat a[], int n, int w){
	int sumTL = 0, sumGT = 0;
	printf("|===|====================|==========|==========|==========|==========|\n");
	printf("|%-3s|%-20s|%-10s|%-10s|%-10s|%-10s|\n", "STT", "Ten", "TL", "GT", "SL", "PA");
	printf("|===|====================|==========|==========|==========|==========|\n");
	for(int i = 0; i < n; i++){
		printf("|%-3d|%-20s|%-10d|%-10d|%-10d|%-10d|\n", (i+1), a[i].ten, a[i].TL, a[i].GT, a[i].SL, a[i].PA);
		sumTL += a[i].PA * a[i].TL;
		sumGT += a[i].PA * a[i].GT;
	}
	printf("|===|====================|==========|==========|==========|==========|\n");
	printf("Khoi luong balo ban dau: %d\n", w);
	printf("Tong khoi luong: %d\n", sumTL);
	printf("Tong gia tri: %d\n", sumGT);
}

int min(int a, int b){
	return a < b ? a:b;
}

void tao_bang(DoVat a[], bang X, bang F, int n, int w){
	for(int v = 0; v <= w; v++){
		X[0][v] = min(a[0].SL, v / a[0].TL);
		F[0][v] = X[0][v] * a[0].GT;
	}
	
	for(int k = 1; k < n; k++)
		for(int v = 0; v <= w; v++){
			int Fmax = F[k-1][v];
			int Xmax = 0;
			int yk = min(a[k].SL, v / a[k].TL);
			for(int xk = 1; xk <= yk; xk++)
				if(F[k-1][v - xk*a[k].TL] + xk*a[k].GT > Fmax){
					Fmax = F[k-1][v - xk*a[k].TL] + xk*a[k].GT;
					Xmax = xk;
				}
			F[k][v] = Fmax;
			X[k][v] = Xmax;
			
		}
}

void in_bang(bang X, bang F, int n, int w){
	for(int i = 0; i < n; i++){
		for(int j = 0 ; j <= w; j++){
			printf("%3d%3d|", F[i][j], X[i][j]);
		}
		printf("\n");
	}
}

void tra_bang(DoVat a[], bang X, int n, int w){
	int v = w;
	for(int i = n-1; i >= 0; i--){
		a[i].PA = X[i][v];
		v -= X[i][v]*a[i].TL;
	}
}

int main(){
	DoVat a[50];
	int n, w;
	bang X, F;
	
	READ_FILE(a, &n, &w);
	
	tao_bang(a, X, F, n, w);
	in_bang(X, F, n, w);
	tra_bang(a, X, n, w);
	PRINT_TABLE(a, n ,w);
	return 0;
}
