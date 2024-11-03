#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK 10

typedef struct node {
	char data [50];
	struct node* next;
}node;

typedef struct stack{
	int count;
	node* top;
}stack;

void buat_stack(stack* stack){
	stack -> count = 0;
	stack -> top = NULL;
}

int empty(stack* stack){
	return stack -> top == NULL;
}

int full(stack* stack){
	return stack -> count >= MAX_STACK;
}

int push(stack* stack, char* data){
	if (full(stack)){
		printf ("stack penuh, tidak dapat menambah. maksimal %d data.\n", MAX_STACK);
		return 0;
	}else {
		node* newPtr = (node*) malloc (sizeof (node));
		strcpy (newPtr -> data, data);
		newPtr -> next = stack -> top;
		stack -> top = newPtr;
		stack -> count++;
		printf ("data %s berhasil ditambahkan ke stack.\n", data);
		return 1;
	}
}

int pop (stack* stack, char* data_keluar){
	if (empty(stack)){
		printf ("stack kosong, tidak ada data yang dihapus.\n");
		return 0;
	}else {
		node* dltPtr = stack -> top;
		strcpy (data_keluar, dltPtr -> data);
		stack -> top = stack -> top -> next;
		stack -> count--;
		free (dltPtr);
		printf ("data %s dihapus dari stack.\n", data_keluar);
		return 1;
	}
}

int top (stack* stack, char* data_keluar){
	if (empty(stack)){
		printf ("stack kosong, tidak ada data.\n");
		return 0;
	}else {
		strcpy (data_keluar, stack -> top -> data); 
		printf ("data teratas adalah %s\n", data_keluar);
		return 1;
	}
}

void destroy (stack* stack){
	while (!empty(stack)){
		node* temp = stack -> top;
		stack -> top = stack -> top -> next;
		free (temp);
	}
	stack -> count = 0;
	printf ("stack telah dikosongkan.\n");
}

int main(){
	stack stack;
	int pilihan;
	char isi [50];
	
	buat_stack (&stack);
	
	do {
		printf ("Menu Operasi Stack:\n");
        printf ("1. Push (Tambah kata)\n");
        printf ("2. Pop (Hapus kata atas)\n");
        printf ("3. Top (Lihat kata teratas)\n");
        printf ("4. Cek Apakah Stack Kosong\n");
        printf ("5. Destroy Stack\n");
        printf ("6. Keluar\n");
        printf ("Pilih operasi: ");
        scanf ("%d", &pilihan);
        getchar();
        
        switch (pilihan){
        	case 1:
        		printf ("masukan kata yang akan ditambahkan : ");
        		fgets (isi, sizeof (isi), stdin);
        		isi [strcspn (isi, "\n")] = '\0';
        		push (&stack, isi);
        		system("pause");
        		system("cls");
        		break;
        		
        	case 2:
        		pop(&stack, isi);
        		system("pause");
				break;
				
			case 3:
				top (&stack, isi);
				system("pause");
				system("cls");
				break;
				
			case 4:
				if (empty (&stack)){
					printf ("stack kosong.\n");
				}else {
					printf ("stack tidak kosong.\n");
				}
				system("pause");
				system("cls");
				break;
			
			case 5:
				destroy (&stack);
				system("pause");
				system("cls");
				break;
				
			case 6:
				printf ("keluar dari program.\n");
				system("pause");
				system("cls");
				break;
				
			default:
				printf ("pilihan tidak valid.\n");
				system("pause");
				system("cls");
		}
	} while (pilihan != 6);
	
	return 0;
}






