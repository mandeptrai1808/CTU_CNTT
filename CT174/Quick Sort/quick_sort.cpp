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

int FindPivotIndex(recordtype a[], int l, int r){
	for(int i = l; i < r; i++){
		if(a[i].key > a[i+1].key) return i;
		if(a[i].key < a[i+1].key) return i+1;
	}
	return -1;
}


int Partion(recordtype a[], int l, int r, int pivot){
	int right = r;
	while(true){
		while(l <= r && a[l].key < pivot) l++;
		while(r >= l && a[r].key > pivot) r--;
		if (l >= r) break;
		Swap(&a[l].key, &a[r].key);
		l++;
		r--;
	
	}	
	Swap(&a[l].key, &a[right].key);
	return l;
}

void Quick_Sort(recordtype a[], int l, int r){
	keytype pivot = a[FindPivotIndex(a, l, r)].key;
	
	if(l<r){
		int pos = Partion(a, l, r, pivot);
//		printf("pos: %d\n", pos);
		Quick_Sort(a, l, pos-1);
		Quick_Sort(a, pos+1, r);
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
	} else printf("READ FILE ERROR!");
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
	PRINT_RESULT(a, n);
	printf("----------------\n");
	Quick_Sort(a, 0, n-1);
	PRINT_RESULT(a, n);
	
	printf("Pivot: %d", FindPivotIndex(a, 0, n));
	return 0;
}
