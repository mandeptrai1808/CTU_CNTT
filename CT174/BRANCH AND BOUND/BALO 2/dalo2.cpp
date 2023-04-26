#include <stdio.h>

typedef struct{
	char ten[50];
	int PA, SL;
	float KL, GT, DG;
}DoVat;

void Swap(DoVat *a, DoVat *b){
	DoVat temp = *b;
	*b = *a;
	*a = temp;
}

void Bubble_Sort(DoVat a[], int n){
	for(int i = 0; i < n-1; i++)
		for(int j = n-1; j > i; j--)
			if(a[j].DG > a[j-1].DG) Swap(&a[j], &a[j-1]);
}

void READ_FILE(DoVat a[], int *n, float *w){
	FILE *f;
	f = fopen("data.txt", "r");
	if(f!=NULL){
		int i = 0;
		fscanf(f, "%f", w);
		while(!feof(f)){
			fscanf(f, "%f%f%d%[^\n]", &a[i].KL, &a[i].GT, &a[i].SL, &a[i].ten);
			a[i].DG = a[i].GT / a[i].KL;
			a[i].PA = 0;
			i++;
		}
		*n = i;
		fclose(f);
	}else printf("ERROR READ FILE!");
}

void PRINT_RESULT(DoVat a[], int n, float w){
	float sumKL = 0, sumGT = 0;
	printf("W = %.2f\n", w);
	printf("|===|====================|==========|==========|==========|==========|==========|\n");
	printf("|%-3s|%-20s|%-10s|%-10s|%-10s|%-10s|%-10s|\n", "STT", "Ten", "KL", "GT", "SL", "DG", "PA");
	printf("|===|====================|==========|==========|==========|==========|==========|\n");
	for(int i = 0; i < n; i++){
			printf("|%-3d|%-20s|%-10.2f|%-10.2f|%-10d|%-10.2f|%-10d|\n", (i+1), a[i].ten, a[i].KL, a[i].GT, a[i].SL, a[i].DG, a[i].PA);
			sumKL += a[i].KL * a[i].PA;
			sumGT += a[i].GT * a[i].PA;
	}
	printf("|===|====================|==========|==========|==========|==========|==========|\n");
	printf("Tong khoi luong: %.2f\n", sumKL);
	printf("Tong gia tri: %.2f", sumGT);
}

void node_init(float *TGT, float *CT, float *GLNTT, float DG_MAX, float w, float *v){
	*TGT = 0;
	*v = w;
	*CT = *v * DG_MAX;
	*GLNTT = 0;
}

void update(DoVat a[], int n, int x[], float *GLNTT, float TGT){
	if(*GLNTT < TGT){
		*GLNTT = TGT;
		for(int i = 0; i < n; i++) a[i].PA = x[i];
	}
}

int min(int a, int b){
	return a<b ? a:b;
}

void nhanh_can(DoVat a[], int n, int i, float *TGT, float *CT, float *GLNTT, float *v, int x[]){
	int yk = min(a[i].SL, *v / a[i].KL);
	for(int j = yk; j >= 0; j--){
		*TGT += j*a[i].GT;
		*v -= j*a[i].KL;
		*CT = *TGT + *v * a[i+1].DG;
		 if (*CT > *GLNTT || *v == 0){
		 	x[i] = j;
		 	if (i == n-1) update(a, n, x, GLNTT, *TGT);
		 	else nhanh_can(a, n, i+1, TGT, CT, GLNTT, v, x);
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
	READ_FILE(a, &n, &w);
	Bubble_Sort(a, n);
	float TGT, CT, GLNTT, v;
	int  x[30];
	node_init(&TGT, &CT, &GLNTT, a[0].DG, w, &v);
	nhanh_can(a, n, 0, &TGT, &CT, &GLNTT, &v, x);
	PRINT_RESULT(a, n, w);
	return 0;
}
