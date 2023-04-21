#include <stdio.h>

typedef struct{
	char tenTien[50];
	int MG, PA;
} Tien;

void Swap(Tien *a, Tien *b){
	Tien temp = *b;
	*b = *a;
	*a = temp;
}

void Bubble_Sort(Tien a[], int n){
	for(int i = 0; i < n; i++)
		for(int j = n; j >= i+1; j--){
			if(a[j].MG > a[j-1].MG) Swap(&a[j], &a[j-1]);
		}
}

void READ_FILE(Tien t[], int *n){
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if (f!=NULL){
		while(!feof(f)){
			t[i].MG = -1;
//			char tempTen[50];
				fscanf(f, "%d%[^\n]", &t[i].MG, &t[i].tenTien);
				if(t[i].MG != -1){
					i++;	
				}
				
		}
	} else printf("ERROR READ FILE!");
	
	*n = i;
//	printf("n = %d\n", *n);
}

void PRINT_RESULT(Tien t[], int n){
	printf("|---|-------------------------|----------|----------|------------|\n");
	printf("|%-3s|%-25s|%-10s|%-10s|%-12s|\n", "STT", "Loai Tien", "Don Gia", "So To", "Thanh Tien");
	printf("|---|-------------------------|----------|----------|------------|\n");
	for(int i = 0; i < n; i++){
//		printf("%d %s %d\n", t[i].MG, t[i].tenTien, t[i].PA);
		printf("|%-3d|%-25s|%-10d|%-10d|%-12d|\n", i+1, t[i].tenTien, t[i].MG, t[i].PA, t[i].MG*t[i].PA);
	}	
	printf("|---|-------------------------|----------|----------|------------|\n");
}

void Greedy(Tien t[], int n, int s){
	for(int i = 0; i < n; i++){
		t[i].PA = s / t[i].MG;
		s = s - t[i].MG*t[i].PA;
	}
}

int main(){
	Tien t[50];
	int n, s;
	READ_FILE(t, &n);
	Bubble_Sort(t, n);
	printf("Nhap so tien can doi: ");
	scanf("%d", &s);
	Greedy(t, n, s);
	printf("PHUONG AN TOI UU DE DOI %dVND LA: \n", s);
	PRINT_RESULT(t,n);
	return 0;
}
