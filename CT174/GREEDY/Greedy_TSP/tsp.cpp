#include <stdio.h>

typedef struct{
	int dau, cuoi;
	float dodai;
} Canh;

void Swap(Canh *a, Canh *b){
	Canh temp = *b;
	*b = *a;
	*a = temp;
}

void Bubble_Sort(Canh a[], int n){
	for(int i = 0 ; i < n-1; i++)
		for(int j = n-1; j > i; j--){
			if(a[j].dodai < a[j-1].dodai) Swap(&a[j], &a[j-1]);
 		}
}

void READ_FILE(Canh a[], int *n){
	FILE *f;
	f = fopen("data.txt", "r");
	if(f != NULL){
		fscanf(f, "%d", n);
		float temp;
		int k = 0;
		for(int i = 0; i < *n; i++)
			for(int j = i; j < *n; j++){
				if(j==i) for(int t = 0; t <= j; t++) fscanf(f, "%f", &temp);
				else{
					fscanf(f, "%f", &a[k].dodai);
					a[k].dau = i;
					a[k].cuoi = j;
					k++;
				}
			}
	} else{
		printf("ERROR READ FILE!");
		return;
	}
	fclose(f);
}

float PRINT_RESULT(Canh a[], int n){
	float sum = 0;
	printf("|---|---------|----------|\n");
	printf("|%-3s|%-9s|%-10s|\n", "STT", "CANH", "DO DAI");
	printf("|---|---------|----------|\n");
	for(int i = 0; i < n; i++){
		printf("|%3d|%c%c%8c %9.2f|\n", (i+1), a[i].dau+97, a[i].cuoi+97,'|', a[i].dodai);
		sum += a[i].dodai;
	}
	printf("|---|---------|----------|\n");
	return sum;
}

void init_parent(int p[], int n){
	for(int i = 0; i < n; i++)
		p[i] = i;
}

int find_parent(int p[], int u){
	while(u != p[u]) u = p[u];
	return u;
}

void update_parent (int p[], int r1, int r2){
	p[r2] = r1;
}

int checkCanh3Dinh(Canh PA[], int k, Canh moi){
	int dem = 1;
	for(int i = 0; i < k; i++)
		if(moi.dau == PA[i].dau || moi.dau == PA[i].cuoi) dem++;
	if (dem == 3) return 1;
	
	dem = 1;
	for(int i = 0; i < k; i++)
		if(moi.cuoi == PA[i].dau || moi.cuoi == PA[i].cuoi) dem++;
	return (dem == 3);
}

int checkChuTrinh(int r1, int r2){
	return r1 == r2;
}

void Greedy(Canh a[], Canh PA[], int n){
	int i, j = 0, r_dau, r_cuoi;
	int parent[n];
	init_parent(parent, n);
	for(i = 0; i < n*(n-1)/2 && j < n-1; i++){
		r_dau = find_parent(parent, a[i].dau);
		r_cuoi = find_parent(parent, a[i].cuoi);
		if(!checkCanh3Dinh(PA, j, a[i]) && !checkChuTrinh(r_dau, r_cuoi)){
			PA[j] = a[i];
			j++;
			update_parent(parent, r_dau, r_cuoi);
		}
	}	
	
	for(; i < n*(n-1)/2; i++){
		if(!checkCanh3Dinh(PA, j, a[i])){
			PA[j] = a[i];
			break;
		}
	}
}

int main(){
	Canh a[50];
	int n;	
	
	READ_FILE(a, &n);
	Bubble_Sort(a, (n*(n-1)/2));
	
	Canh PA[n];
	Greedy(a,PA, n);
	printf("Danh sach cach canh da sap xep: \n");
	PRINT_RESULT(a, (n*(n-1)/2));
	
	printf("\nPHUONG AN: \n");
	float sum = PRINT_RESULT(PA, n);
	printf("Tong do dai: %.2f", sum);
	return 0;
}
