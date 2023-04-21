#include <stdio.h>
#include <math.h>
typedef struct{
	char ten[50];
	float KL, GT, DG;
	int SL, PA;
} DoVat;

void Swap(DoVat *a, DoVat *b){
	DoVat temp = *b;
	*b = *a;
	*a = temp;
}
void Insertion_Sort(DoVat dv[], int n){
	for(int i = 1 ; i < n; i++){
		for(int j = i; j > 0; j--){
			if(dv[j].DG > dv[j-1].DG) Swap(&dv[j], &dv[j-1]);
			else break;
		}
	}
}

void READ_FILE(DoVat dv[], int *n, int *w){
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if(f!=NULL){
		fscanf(f, "%d", &*w);
		while(!feof(f)){
			fscanf(f, "%f%f%d%[^\n]", &dv[i].KL, &dv[i].GT, &dv[i].SL, &dv[i].ten);
			dv[i].DG = dv[i].GT / dv[i].KL;
			dv[i].PA = 0;
			i++;
		}
	} else printf("ERROR READ FILE!");
	*n = i;
	
	fclose(f);
}

void PRINT_RESULT(DoVat dv[], int n, int w){
	printf("w = %d\n", w);
	printf("|---|--------------------|----------|----------|----------|----------|----------|\n");
	printf("|%-3s|%-20s|%-10s|%-10s|%-10s|%-10s|%-10s|\n", "STT", "TEN DO VAT", "KHOI LUONG", "GIA TRI", "SO LUONG", "DON GIA", "PHUONG AN");
	printf("|---|--------------------|----------|----------|----------|----------|----------|\n");
	float sumKL = 0, sumGT = 0;
	for(int i = 0; i < n; i++){
		printf("|%-3d|%-20s|%-10.2f|%-10.2f|%-10d|%-10.2f|%-10d|\n",(i+1), dv[i].ten ,dv[i].KL, dv[i].GT, dv[i].SL, dv[i].DG, dv[i].PA);
		sumKL += dv[i].KL * dv[i].PA;
		sumGT += dv[i].GT * dv[i].PA;
	}
	printf("|---|--------------------|----------|----------|----------|----------|----------|\n");
	printf("Tong khoi luong: %.2f\n", sumKL);
	printf("Tong gia tri: %.2f\n", sumGT);
}

void Greedy(DoVat dv[], int n, int w){
	for(int i = 0; i < n; i++){
		dv[i].PA = w / dv[i].KL;
		if (dv[i].PA > dv[i].SL) dv[i].PA = dv[i].SL;
		w -= dv[i].KL*dv[i].PA;
	}
}

int main(){
	DoVat dv[50];
	int n, w;
	READ_FILE(dv, &n, &w);	
	Insertion_Sort(dv, n);
	Greedy(dv, n, w);
	PRINT_RESULT(dv, n ,w);
	return 0;
}
