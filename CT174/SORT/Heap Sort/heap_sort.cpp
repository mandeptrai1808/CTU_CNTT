#include <stdio.h>

typedef int keytype;
typedef float othertype;

typedef struct{
	keytype key;
	othertype otherfields;
	
} recordtype;

void READ_FILE(recordtype a[], int *n){
	FILE *f;
	int i = 0;
	f = fopen("data.txt", "r");
	while(!feof(f)){
		fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
		i++;
	}
	*n = i;
}

void PRINT_RESULT(recordtype a[], int n){
	for(int i = 0; i < n; i++){
		printf("%10d%10.2f\n", a[i].key, a[i].otherfields);
	}
}

void Swap(recordtype *a, recordtype *b){
	recordtype temp = *b;
	*b = *a;
	*a = temp;
}

void Push_Down(recordtype a[], int first, int last){
	int r = first;
	while(r <= (last-1)/2){
		if(last == (2*r+1)){
			if(a[r].key > a[last].key)  Swap(&a[r], &a[last]);
			r = last;
		}
		else
		if (a[r].key > a[r*2+1].key && a[r*2+1].key <= a[r*2+2].key){
			Swap(&a[r], &a[r*2+1]);
			r = r*2+1;
		}
		else
		if (a[r].key > a[r*2+2].key && a[r*2+1].key > a[r*2+2].key){
			Swap(&a[r], &a[r*2+2]);
			r = r*2+2;
		}
		else r = last;
	}
}

void Heap_Sort(recordtype a[], int n){
	for(int i = (n-2)/2; i >= 0; i--){
		Push_Down(a, i, n-1);
	}
	for(int i = n-1; i >= 2; i--){
		Swap(&a[0], &a[i]);
		Push_Down(a, 0, i-1);
	}
}

int main(){
	recordtype a[100];
	int n;
		
	READ_FILE(a, &n);
	Heap_Sort(a, n);
	PRINT_RESULT(a, n);
	
	return 0;
}

