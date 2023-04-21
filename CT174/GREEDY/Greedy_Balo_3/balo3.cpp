#include <stdio.h>

typedef struct{
	char ten[50];
	float KL, GT, DG;
	int PA;
} DoVat;

void Swap(DoVat *a, DoVat *b){
	DoVat temp = *b;
	*b = *a;
	*a = temp;
}

void Bubble_Sort(DoVat a[], int n){
	for(int i = 0; i < n-1; i++){
		for(int j = n-1; j > i; j--){
			if(a[j].DG > a[j-1].DG) Swap(&a[j], &a[j-1]);
		}
	}
}

void READ_FILE(DoVat dv[], int *n, int *w){
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	
	if(f != NULL){
		fscanf(f, "%d", &*w);
		while(!feof(f)){
			fscanf(f, "%f%f%[^\n]", &dv[i].KL, &dv[i].GT, &dv[i].ten);
			dv[i].DG = dv[i].GT / dv[i].KL;
			dv[i].PA = 0;
			i++;
		}
	} else printf("ERROR READ FILE!");
	*n = i;
	
	fclose(f);
}

void PRINT_RESULT(DoVat dv[], int n, int w){
	printf("W = %d\n", w);
	printf("|---|--------------------|----------|----------|----------|----------|\n");
	printf("|%-3s|%-20s|%-10s|%-10s|%-10s|%-10s|\n", "STT", "TEN DO VAT", "KHOI LUONG", "GIA TRI", "DON GIA", "PHUONG AN");
	printf("|---|--------------------|----------|----------|----------|----------|\n");
	float sumKL = 0, sumGT = 0;
	for(int i = 0; i < n; i++){
		printf("|%-3d|%-20s|%-10.2f|%-10.2f|%-10.2f|%-10d|\n",(i+1), dv[i].ten, dv[i].KL, dv[i].GT, dv[i].DG, dv[i].PA);
		sumKL += dv[i].KL * dv[i].PA;
		sumGT += dv[i].GT * dv[i].PA;
	}\
	printf("|---|--------------------|----------|----------|----------|----------|\n");
	printf("Tong khoi luong: %.2f\n", sumKL);
	printf("Tong gia tri: %.2f", sumGT);
}

void Greedy(DoVat dv[], int n, int w){
	for(int i = 0; i < n; i++){
		dv[i].PA = w / dv[i].KL;
		if (dv[i].PA > 1) dv[i].PA = 1;
		w -= dv[i].KL * dv[i].PA;
	}
}

int main(){
	DoVat dv[50];
	int n, w;
	READ_FILE(dv, &n, &w);
	Bubble_Sort(dv, n);
	Greedy(dv ,n, w);
	PRINT_RESULT(dv, n, w);
	return 0;
}
