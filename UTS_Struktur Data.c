#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char nama [50];
	char gender;
	struct Node* next;
} Node;

Node* buatNode (char* nama, char gender) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy (newNode -> nama, nama);
	newNode -> gender = gender;
	newNode -> next = NULL;
	return newNode;
}

int maksimal_lingkaran (Node* head) {
    if (head == NULL) return 0;

    int count = 0;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);

    return count;
}

int kasus_cindy (Node* head){
	if (head == NULL) return 1;
	Node* temp = head;
	do {
		if (temp -> gender == 'L'){
			return 0;
		}
		temp = temp -> next;
	}while (temp != head);
	return 1;
}

void inputan (Node** head, char* nama, char gender){
    if (maksimal_lingkaran(*head) >= 20) {
        printf("Lingkaran Sudah Penuh. Tidak Dapat Menambahkan %s.\n", nama);
        return;
    }

    if (strcmp(nama, "cindy") == 0 && gender == 'P') {
        if (!kasus_cindy(*head)) {
            printf("Cindy Tidak Dapat Masuk Karena Ada Mahasiswa Laki-Laki Di Lingkaran.\n");
            return;
        }
    }
    
    if ((strcmp(nama, "irsyad") == 0 || strcmp(nama, "arsyad") == 0) && gender == 'L') {
        Node* newNodeIrsyad = buatNode("irsyad", 'L');
        Node* newNodeArsyad = buatNode("arsyad", 'L');
        if (*head == NULL) {
            *head = newNodeIrsyad;
            newNodeIrsyad->next = newNodeArsyad;
            newNodeArsyad->next = *head;
        } else {
            Node* temp = *head;
            while (temp->next != *head) {
                temp = temp->next;
            }
            temp->next = newNodeIrsyad;
            newNodeIrsyad->next = newNodeArsyad;
            newNodeArsyad->next = *head;
        }
        printf("Irsyad dan Arsyad berhasil ditambahkan bersama ke lingkaran.\n");
        return;
    }

    Node* newNode = buatNode(nama, gender);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
    printf("%s berhasil ditambahkan ke lingkaran.\n", nama);
}


void hapus_mahasiswa (Node** head, char* nama){
	if (*head == NULL){
		printf ("Lingkaran Belum Terisi Mahasiswa.\n");
		return;
	}
	Node *temp = *head, *prev = NULL;
	do {
		if (strcmp (temp -> nama, nama) == 0){
			if (prev == NULL){
				Node* last = *head;
				while (last -> next != *head)
				last = last -> next;
				if (last == *head){
					free (*head);
					*head = NULL;
				}else {
					last -> next = (*head) -> next;
					free (*head);
					*head = last -> next;
				}
			}else{
				prev -> next = temp -> next;
				free(temp);
			}
			printf ("%s telah keluar dari lingkaran mahasiswa.\n", nama);
			return;
		}
		prev = temp;
		temp = temp -> next;
	}while (temp != *head);
	printf ("%s tidak ada pada lingkaran mahasiswa.\n", nama);
}

void tampilkan_lingkaran(Node* head) {
    if (head == NULL) {
        printf("Lingkaran Belum Terisi.\n");
        return;
    }
    Node* temp = head;
    do {
        printf ("%s (%c) -> ", temp -> nama, temp -> gender);
        temp = temp -> next;
    } while (temp != head);
    printf("(kembali ke %s)\n", head -> nama);
}

void pisah_lingkaran (Node* head, Node** lingkaran_mahasiswa, Node** lingkaran_mahasiswi){
	if (head == NULL){
		printf ("Lingkaran Belum Di Isi, Tidak Dapat Di Pisah.\n");
		return;
	}
	Node* temp = head;
	do{
		if (temp -> gender == 'L'){
			inputan (lingkaran_mahasiswa, temp -> nama, temp -> gender);
		}else if(temp -> gender == 'P'){
			inputan (lingkaran_mahasiswi, temp -> nama, temp -> gender);
		}
		temp = temp -> next;
	}while (temp != head);
}

int main () {
	Node* lingkaran = NULL;
	Node* lingkaran_mahasiswa = NULL;
	Node* lingkaran_mahasiswi = NULL;
	
	int pilihan;
	char nama [50];
	char gender;
	
	do{
		printf ("pilih : \n");
		printf ("1. Tambah Mahasiswa\n");
		printf ("2. Hapus Mahasiswa\n");
		printf ("3. Pisah Menjadi 2 Lingkaran Sesuai Gender\n");
		printf ("4. Keluar\n");
		printf ("Pilih Opsi : ");
		scanf ("%d", &pilihan);
		
		switch (pilihan){
			case 1:
                printf("Masukkan Nama: ");
                scanf("%s", nama);
                printf("Masukkan Jenis Kelamin / Gender (L/P): ");
                scanf(" %c", &gender);
                inputan(&lingkaran, nama, gender);
                break;
                
            case 2:
                printf("Masukkan Nama Mahasiswa Yang Ingin Keluar Dari Lingkaran : ");
                scanf("%s", nama);
                hapus_mahasiswa(&lingkaran, nama);
                break;
                
            case 3:
                printf("Memisahkan Lingkaran...\n");
                pisah_lingkaran(lingkaran, &lingkaran_mahasiswi, &lingkaran_mahasiswa);
                
                printf("Lingkaran Mahasiswa:\n");
                tampilkan_lingkaran(lingkaran_mahasiswa);
                
                printf("Lingkaran Mahasiswi:\n");
                tampilkan_lingkaran(lingkaran_mahasiswi);
                break;
                
            case 4:
                printf("Keluar Dari Program.\n");
                break;
                
            default:
                printf("Opsi tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 4);
    
    return 0;
}