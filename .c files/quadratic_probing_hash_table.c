#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <math.h>

/*
Quadratic probing h(k,i) = (h’(k) + c1i + c2i^2) mod m
                  prob_index = (prob_index + c1 * i + (c2 * pow(i, 2))) % m
*/

int i = 1, n = 0;

void insert(int list[], int m, int size, int c1, int c2);
void del(int list[], int m, int size, int c1, int c2);
void search(int list[], int m, int size, int c1, int c2);

int main(){

    setlocale(LC_ALL, "");

	int size = 0, m = 0, c1 = 0, c2 = 0, i = 0, choice = 0;

	printf("\nInsert hash table size:\n");
	scanf("%d", &size);

	int list[size];

	printf("\nInsert c1 and c2\n");
	printf("c1: ");
	scanf("%d", &c1);
	printf("c2: ");
	scanf("%d", &c2);

	printf("\nInsert function hash mod\n");
	printf("m: ");
	scanf("%d", &m);
	printf("\n");

	for(i = 0; i < size; i++){
        list[i] = INT_MIN; //Assigning INT_MIN indicates that cell is empty
	}

	do{
		printf("Choose an option\n");
		printf(" 1-> Insert value\n 2-> Delete value\n 3-> Search value\n 4-> Print hash table\n 0-> Exit\n");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				insert(list, m, size, c1, c2);

				system("pause");
				system("cls");
				break;

			case 2:
				del(list, m, size, c1, c2);

				system("pause");
				system("cls");
				break;

			case 3:
                search(list, m, size, c1, c2);

				system("pause");
				system("cls");
				break;

			case 4:
				printf("Index\tValue\n");

                for(i = 0; i < size; i++){
                    printf("%d\t%d\n", i, list[i]);
                }

				system("pause");
				system("cls");
				break;

            case 0:
                printf("\nExiting system!\n");
                exit(1);

			default:
				printf("Invalid choice!\n");
				system("pause");
				system("cls");
				break;
		}
	} while(choice);

	return 0;
}

void insert(int list[], int m, int size, int c1, int c2){
    int element = 0, prob_index = 0, sizeSup = 0;
    float loadFactor = 0;

	printf("Key value that will be inserted\n");
	scanf("%d", &element);

	prob_index = element % m;

	while(list[prob_index] != INT_MIN){
		if(list[prob_index] == INT_MAX){
            break;
		}
		prob_index = (int) (prob_index + c1 * i + (c2 * pow(i, 2))) % (int) m;

		sizeSup++;
		if(sizeSup == size){
            break;
		}
	}

	if(sizeSup == size){
        printf("Full hash table\n\n");
        n--;
	}
	else{
        list[prob_index] = element;
    }

    n++;

    loadFactor = (float) n / size;

    printf("Loading factor: %.3f\n\n", loadFactor);
}

void del(int list[], int m, int size, int c1, int c2){

	int element = 0, n = 0, prob_index = 0;

	printf("Key value that will be deleted\n");
	scanf("%d", &element);

	prob_index = element % m;

	while(n++ != size){
		if(list[prob_index]==INT_MIN){
			printf("Value not found in hash table\n");
			break;
		}
		else if(list[prob_index] == element){
			list[prob_index] = INT_MAX;
			printf("Value deleted\n\n");
			break;
		}
		else{
			prob_index = (int) (prob_index + c1 * i + (c2 * pow(i, 2))) % (int) m;
		}
	}
	if(n - 1 == size){
        printf("Value not found in hash table\\n");
	}
}

void search(int list[], int m, int size, int c1, int c2){
	int element = 0, prob_index = 0, n = 0;

	printf("Key value that will be searched\n");
	scanf("%d", &element);

	prob_index = element % m;

	while(n++ != size){
		if(list[prob_index]==element){
			printf("Value found at index: %d\n",prob_index);
			break;
		}
		else{
            if(list[prob_index]==INT_MAX ||list[prob_index]!=INT_MIN){
                prob_index = (int) (prob_index + c1 * i + (c2 * pow(i, 2))) % (int) m;
            }
		}
	}
	if(--n == size)
        printf("Value not found in hash table\n");
}
