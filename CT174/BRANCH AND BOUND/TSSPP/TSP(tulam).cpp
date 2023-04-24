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

void PRINT_MATRIX(canh  a[][size], int n){
	for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				printf("%c%c = %5.2f     ", a[i][j].dau + 97, a[i][j].cuoi+ + 97, a[i][j].do_dai);
			printf("\n");
		}
}
int check_chu_trinh(canh x[], int k, int  ke_tiep){
	int i = 0, co_ct = 0;
	while(i < k && !co_ct){
		if(x[i].dau == ke_tiep) co_ct = 1;
		else i++;
	}
	return co_ct;
}

float canh_nn(canh a[][size], int n){
	float Cmin = 10000000;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		if(i!=j && !a[i][j].da_dung && a[i][j].do_dai < Cmin) Cmin = a[i][j].do_dai;
	return Cmin;
}

float can_duoi(canh a[][size], int n, int i, float TGT){
	return TGT + (n-i)*canh_nn(a, n);
}

void update_pa(canh a[][size], int n, float TGT, float *GNNTT, canh x[], canh PA[]){
	x[n-1] = a[x[n-2].cuoi][x[0].dau];
	TGT += x[n-1].do_dai;
	if (*GNNTT > TGT){
		*GNNTT = TGT;
		for(int i = 0; i < n; i++) PA[i] = x[i];
	}
}

void nhanh_can(canh a[][size], int n, int i, int dau, float *TGT, float *CD, float *GNNTT, canh x[], canh PA[]){
	for(int j = 0; j < n; j++)
		if(j!=dau && !a[dau][j].da_dung && !check_chu_trinh(x, i, j)){
			*TGT += a[dau][j].do_dai;
			*CD = can_duoi(a, n, i+1, *TGT);
			
			if (*CD < *GNNTT){
				x[i] = a[dau][j];
				a[dau][j].da_dung = 1;
				a[j][dau].da_dung = 1;
				
				if (i == n-2) update_pa(a, n, *TGT, GNNTT, x, PA);
				else nhanh_can(a, n, i+1, j, TGT, CD, GNNTT, x ,PA);
			}
			*TGT -= a[dau][j].do_dai;
			a[dau][j].da_dung = 0;
			a[j][dau].da_dung = 0;
		}
		
}

void in_PA(canh PA[], int n){
	float sum = 0;
	printf("PHUONG AN TIM DUOC: \n");
	for(int i = 0; i < n; i++){
		printf("%c%c = %5.2f\n", PA[i].dau + 97, PA[i].cuoi + 97, PA[i].do_dai);
		sum +=  PA[i].do_dai;
	}
	
	printf("Chu trinh: ");
	for(int i = 0; i < n - 1; i++){
		printf("%c -> ", PA[i].dau + 97);
	}
	printf("%c\n", PA[0].dau + 97);
	printf("Tong do dai: %.2f\n", sum);
	
}

int main(){
	canh a[size][size];
	int n;
	
	READ_FILE("data.txt", a, &n);
	float TGT = 0, CD = 0, GNNTT = 10000000;
	canh x[size], PA[size];
	
	nhanh_can(a, n, 0, 0, &TGT, &CD, &GNNTT, x, PA);
	in_PA(PA,n);
	printf("\n");
	PRINT_MATRIX(a, n);
	
	return 0;
}
