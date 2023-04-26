#include <stdio.h>

typedef struct{
	char ten[50];
	float KL, GT, DG;
	int PA;
}DoVat;

void Swap(DoVat *a, DoVat *b){
	DoVat temp = *b;
	*b = *a;
	*a = temp;
}

void Bubble_Sort(DoVat a[], int n){
	for(int i = 0; i < n -1; i++)
		for(int j = n-1; j > i; j--){
			if(a[j].DG > a[j-1].DG) Swap(&a[j], &a[j-1]);
		}
}

void READ_FILE(char filename[], DoVat a[], int *n, float *w) {
	FILE *f;
	f = fopen(filename, "r");
	if(f!=NULL){
		int i = 0;
		fscanf(f, "%f", w);
		while(!feof(f)){
			fscanf(f, "%f%f%[^\n]", &a[i].KL, &a[i].GT, &a[i].ten);
			a[i].DG = a[i].GT / a[i].KL;
			a[i].PA = 0;
			i++;
		}
		*n = i;
		fclose(f);
	}	else printf("ERROR READ FILE!");
	
}

void PRINT_RESULT(DoVat a[], int n, float w){
	float sumKL = 0, sumGT = 0;
	
	printf("W = %.2f\n", w);
	printf("|===|====================|==========|==========|==========|==========|\n");
	printf("|%-3s|%-20s|%-10s|%-10s|%-10s|%-10s|\n", "STT", "Ten do vat", "Khoi luong", "Gia tri", "Don gia", "Phuong an");
	printf("|===|====================|==========|==========|==========|==========|\n");
	for(int i = 0; i < n; i++){
		printf("|%-3d|%-20s|%-10.2f|%-10.2f|%-10.2f|%-10d|\n", (i+1), a[i].ten, a[i].KL, a[i].GT, a[i].DG, a[i].PA);
		sumKL += a[i].KL * a[i].PA;
		sumGT += a[i].GT * a[i].PA;
	}
	printf("|===|====================|==========|==========|==========|==========|\n");
	printf("Tong khoi luong: %.2f\n", sumKL);
	printf("Tong gia tri: %.2f", sumGT);
}


void tao_nut_goc(float w, float *v, float *CT, float *GLNTT, float *TGT, float DG_Max){
	*TGT = 0;
	*v = w;
	*CT = *v * DG_Max;
	*GLNTT = 0;
}

void update(float TGT, float *GLNTT, int x[], DoVat a[], int n){
	if(*GLNTT < TGT){
		*GLNTT = TGT;
		for(int i = 0; i < n; i++)	a[i].PA = x[i];
	}
}

int min(int a, int b){
	return a<b ? a:b;
}

void nhanh_can(DoVat a[], int n, int i,float *TGT, float *CT, float *v, float *GLNTT, int x[]){
	int yk = *v / a[i].KL;
	for(int j = yk; j >= 0; j--){
		*TGT += j*a[i].GT;
		*v -= j*a[i].KL;
		*CT = *TGT + *v * a[i+1].DG;
		
		if (*CT > *GLNTT){
			x[i] = j;
			if (i == n-1 || &v == 0) update(*TGT, GLNTT, x, a, n);
			else nhanh_can(a, n, i+1, TGT, CT, v, GLNTT, x);
		}
		x[i] = 0;
		*TGT -= j*a[i].GT;
		*v += j*a[i].KL;
	}
}

int main(){
	DoVat a[30];
	int n;
	float w;
	READ_FILE("data.txt", a, &n, &w);
	Bubble_Sort(a, n);
	
	float v, TGT, GLNTT, CT;
	int x[30];
	
	tao_nut_goc(w, &v, &CT, &GLNTT, &TGT, a[0].DG);
	nhanh_can(a, n, 0, &TGT, &CT, &v, &GLNTT, x);
	
	PRINT_RESULT(a, n, w);
	return 0;
}
