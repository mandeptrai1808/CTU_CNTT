#include <stdio.h>

typedef int typekey;
typedef float typeothefield;


typedef struct{
	typekey key;
	typeothefield otherfields;	
} recordtype;
	
	
void Swap(int *a, int *b){
	int temp  = *b;
	*b = *a;
	*a = temp;
}

void Selection_Sort(recordtype a[], int n){
	for(int i = 0; i < n-1; i++){
		int min = a[i].key;
		int index = i;
		for(int j = i+1; j < n; j++){
			if(a[j].key < min){
				min = a[j].key;
				index = j;
			}	
		}
		Swap(&a[i].key, &a[index].key);
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
	}
	else printf("READ FILE ERROR!");
	*n = i;
}

void PRINT_RESULT(recordtype a[], int n){
	printf("|    Key    |   Other  |\n");
	printf("------------------------\n");
	for(int i = 0; i < n; i++){
		printf("|%10d |%10.2f|\n", a[i].key, a[i].otherfields);
		printf("------------------------\n");
	}
}

int main(){
	recordtype a[100];
	int n;	
	
	READ_FILE(a, &n);
	
	printf("DEFAULT VALUES: \n");
	PRINT_RESULT(a,n);
	Selection_Sort(a, n);
	printf("AFTER SELECTION SORT: \n");
	PRINT_RESULT(a, n);
	
	return 0;
}
