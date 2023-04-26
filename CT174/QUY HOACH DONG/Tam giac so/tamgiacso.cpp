#include <stdio.h>
#define size 50

void READ_FILE(int a[][size], int *n){
	FILE *f;
	f = fopen("data.txt", "r");
	if(f != NULL){
		int i = 0;
		while(!feof(f)){
			for(int j = 0; j <= i; j++){
				fscanf(f, "%d", &a[i][j]);
			}
			i++;
		}
		*n = i;
		fclose(f);
	} else printf("ERROR READ FILE!");
}

int CS_Min(int F[][size], int i, int j){
	if(j == 0) return F[i-1][0] > F[i-1][1] ? 0:1;
	if (j==i) return i-1;
	if (j==i-1) return F[i-1][j-1] > F[i-1][j] ? j-1 : j;
	if (F[i-1][j-1] > F[i-1][j] && F[i-1][j-1] > F[i-1][j+1]) return j-1;
	if (F[i-1][j] > F[i-1][j-1] && F[i-1][j] > F[i-1][j+1]) return j;
	if (F[i-1][j+1] > F[i-1][j-1] && F[i-1][j+1] > F[i-1][j]) return j+1;
}

void tao_bang(int a[][size], int F[][size], int n){
	F[0][0] = a[0][0];
	F[1][0] = a[1][0] + F[0][0];
	F[1][1] = a[1][1] + F[0][0];
	
	for(int i = 2; i < n; i++)
		for(int j = 0; j <= i; j++){
			int k = CS_Min(F, i, j);
			F[i][j] = F[i-1][k] + a[i][j];
		}
	
}

int find_max_last_col(int F[], int n){
	int min = F[0];
	int idmin = 0;
	for(int i = 0; i < n; i++){
		if(F[i] > min){
			min = F[i];
			idmin = i;
		}
	}
	return idmin;
	
}

void tra_bang(int a[][size], int F[][size], int PA[], int n){
	int j = find_max_last_col(F[n-1], n);
	PA[n-1] = a[n-1][j];
	for(int i = n-1; i >= 1; i--){
		j = CS_Min(F, i, j);
		PA[i-1] = a[i-1][j];
	}
}

void in_kq(int PA[], int n){
	for(int i = 0; i < n - 1; i++){
		printf("%d -> ", PA[i]);
	}
	printf("%d \n", PA[n-1]);
}

void PRINT_TRIANGLE(int a[][size], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}
int main(){
	int a[size][size], n, F[size][size], PA[size];
	READ_FILE(a, &n);
	printf("Tam giac so: \n");
	PRINT_TRIANGLE(a, n);
	tao_bang(a, F, n);
	printf("\nBang F: \n");
	PRINT_TRIANGLE(F, n);
	tra_bang(a, F, PA, n);
	in_kq(PA, n);
	return 0;
}
