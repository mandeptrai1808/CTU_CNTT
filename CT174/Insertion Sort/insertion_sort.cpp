#include <stdio.h>

typedef int keytype;
typedef float othertype;

typedef struct{
	keytype key;
	othertype otherfields;
} recordtype;


void Swap(int *a, int *b){
	int temp = *b;
	*b = *a;
	*a = temp;
}

void Insertion_Sort(recordtype a[], int n){
	for(int i = 0; i < n-1; i++){
		for(int j = i+1; j > 0; j--){
			if(a[j].key < a[j-1].key) Swap(&a[j].key, &a[j-1].key);
		}
	}
}

void READ_FILE(recordtype a[], int *n){
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
		}
	}else printf("READ FILE ERROR!");
	*n = i;
}

void PRINT_RESULT(recordtype a[], int n){
	for(int i = 0; i < n; i++){
		printf("%10d%10.2f\n", a[i].key, a[i].otherfields);
	}
}


int main(){
	recordtype a[100];
	int n;
	READ_FILE(a, &n);
	printf("DEFAULT DATA: \n");
	PRINT_RESULT(a,n);
	Insertion_Sort(a,n);
	printf("----------------------\n");
	printf("AFTER INSERTION SORT: \n");
	PRINT_RESULT(a, n);
	return 0;
}
