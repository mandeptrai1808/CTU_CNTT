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

void Selection_Sort(DoVat a[], int n){
	for(int i = 0; i < n-1; i++){
		float max = a[i].DG;
		int idMax = i;
		for(int j = i+1; j < n; j++){
			if(a[j].DG > max){
				max = a[j].DG;
				idMax = j;
			}
		}
		Swap(&a[i], &a[idMax]);
	}
}

void READ_FILE(DoVat dsdv[], int *n, int *w){
	FILE *f;
	f = fopen("data.txt", "r");
	int i= 0;
	if(f!=NULL){
		fscanf(f, "%d", &*w);
		printf("w = %d\n", *w);
		while(!feof(f)){
			fscanf(f, "%f%f%[^\n]", &dsdv[i].KL, &dsdv[i].GT, &dsdv[i].ten);
			dsdv[i].DG = dsdv[i].GT / dsdv[i].KL;
			dsdv[i].PA = 0;
			i++;
		}
	} else printf("ERROR READ FILE!");
	
	*n = i;
	fclose(f);
}

void PRINT_RESULT(DoVat dv[], int n, int w){
	printf("|---|--------------------|----------|----------|----------|----------|\n");
	printf("|%-3s|%-20s|%-10s|%-10s|%-10s|%-10s|\n", "STT", "Ten Do Vat", "Khoi Luong", "Gia Tri", "Don Gia", "Phuong An");
	printf("|---|--------------------|----------|----------|----------|----------|\n");
	float sumKL = 0, sumGT = 0;
	for(int i = 0; i < n; i++){
		printf("|%-3d|%-20s|%-10.2f|%-10.2f|%-10.2f|%-10d|\n", i+1, dv[i].ten, dv[i].KL, dv[i].GT, dv[i].DG, dv[i].PA);
		sumKL += dv[i].KL*dv[i].PA;
		sumGT += dv[i].GT*dv[i].PA;
	}
	printf("|---|--------------------|----------|----------|----------|----------|\n");
	printf("Tong khoi luong: %.2f\n", sumKL);
	printf("Tong Gia Tri: %.2f\n", sumGT);
	
}

void Greedy(DoVat dv[], int n, int w){
	for(int i = 0; i < n; i++){
		dv[i].PA = w / dv[i].KL;
		w -= dv[i].KL * dv[i].PA;
	}
}

int main(){
	
	DoVat dsdv[50];
	int n, w;
	READ_FILE(dsdv, &n, &w);
	Selection_Sort(dsdv, n);
	Greedy(dsdv, n, w);
	PRINT_RESULT(dsdv, n, w);
	
	return 0;
}
