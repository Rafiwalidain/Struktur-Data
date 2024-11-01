#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
	struct node *prev;
};

typedef struct node node;

void tambahAwal(node **head);
void tambahData(node **head);
void tranverse(node *head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head, int val);
void hapusAkhir(node **head);
void cariData(node *head, int val);
int hitungJumlahNode(node *head);
int jumlahkanData(node *head);

int main() {
    node *head = NULL;
    char pilih;
    int val;

    do {
        system("cls");
        printf("Masukkan pilihan:\n");
        printf("0. Tambah data di awal\n");
        printf("1. Tambah data di tengah list\n");
        printf("2. Cetak isi list\n");
        printf("3. Tambah data di akhir linked list\n");
        printf("4. Hapus data di awal linked list\n");
        printf("5. Hapus data di tengah linked list\n");
        printf("6. Hapus data di akhir linked list\n");
        printf("7. Pencarian data dalam linked list\n");
        printf("8. Menampilkan informasi jumlah data di linked list\n");
        printf("9. Menampilkan hasil penjumlahan dari semua data di linked list\n"); 
        printf("MASUKKAN PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);
        scanf(" %c", &pilih);

        switch (pilih) {
            case '0':
                tambahAwal(&head);
                break;
            case '1':
                tambahData(&head);
                break;
            case '2':
            	tranverse(head);
                getch();
                break;
            case '3':
            	tambahAkhir(&head);
                break;
            case '4':
            	hapusAwal(&head);
                break;
            case '5':
            	printf("Masukkan nilai yang akan dihapus: ");
                scanf("%d", &val);
                hapusTengah(&head, val);
                break;
            case '6':
            	hapusAkhir(&head);
                break;
            case '7':
            	printf("Masukkan nilai yang ingin dicari: ");
                scanf("%d", &val);
                cariData(head, val);
                getch();
                break;
            case '8':
            	hitungJumlahNode(head);
            	getch();
                break;
            case '9':
            	jumlahkanData(head);
                getch();
                break;
             case 'q':
                break;
            default:
                printf("Pilihan tidak valid!\n");
                getch();
        }
    } while (pilih != 'q');

    return 0;
}

void tambahAwal(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*head == NULL) {
            *head = pNew;
            pNew->next = pNew;
            pNew->prev = pNew;
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pNew->next = *head;
            pNew->prev = pCur;
            pCur->next = pNew;
            (*head)->prev = pNew;
            *head = pNew;
        }
        printf("Node dengan data %d berhasil ditambahkan di awal.\n", bil);
    } else {
        printf("Alokasi memori gagal\n");
        getch();
    }
}


void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nPosisi penyisipan setelah data bernilai: ");
    scanf("%d", &pos);
    printf("\nBilangan: ");
    scanf("%d", &bil);

    pCur = *head;

    do {
        if (pCur->data == pos) break;
        pCur = pCur->next;
    } while (pCur != *head);

    if (pCur == *head && pCur->data != pos) {
        printf("\nNode tidak ditemukan\n");
        getch();
    } else {
        pNew = (node *)malloc(sizeof(node));
        if (pNew == NULL) {
            printf("\nAlokasi memori gagal\n");
            getch();
        } else {
            pNew->data = bil;

            pNew->next = pCur->next;
            pNew->prev = pCur;

            if (pCur->next != *head) {
                pCur->next->prev = pNew;
            } else {
                (*head)->prev = pNew;
            }

            pCur->next = pNew;

            printf("Node dengan data %d berhasil ditambahkan di tengah.\n", bil);
        }
    }
}


void tranverse(node *head) {
    node *pWalker;

    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }

    printf("Traversal Maju (forward):\n");
    pWalker = head;
    do {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    } while (pWalker != head);
    printf("HEAD\n");

    printf("Traversal Mundur (backward):\n");
    pWalker = head->prev; 
    do {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->prev;
    } while (pWalker != head->prev);
    printf("HEAD\n");
}


void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = pNew;
            pNew->prev = pNew;
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *head;
            pNew->prev = pCur;
            (*head)->prev = pNew;
        }
        printf("Node dengan data %d berhasil ditambahkan di akhir.\n", bil);
    } else {
        printf("Alokasi memori gagal\n");
        getch();
    }
}


void hapusAwal(node **head) {
    node *pTemp, *pCur;

    system("cls");
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        pCur = *head;
        while (pCur->next != *head) {
            pCur = pCur->next;
        }
        pTemp = *head;
        *head = (*head)->next;
        (*head)->prev = pCur;
        pCur->next = *head;
        free(pTemp);
    }
    printf("Data di awal berhasil dihapus.\n");
    getch();
}


void hapusTengah(node **head, int val) {
    node *pCur, *pPrev;

    system("cls");

    if (*head == NULL) {
        printf("List kosong, tidak ada data yang bisa dihapus.\n");
        return;
    }

    pCur = *head;

    do {
        if (pCur->data == val) break;
        pCur = pCur->next;
    } while (pCur != *head);

    if (pCur == *head && pCur->data != val) {
        printf("\nNode dengan nilai %d tidak ditemukan.\n", val);
    } else {
        if (pCur == *head) {
            if (pCur->next == *head) {  
                free(pCur);
                *head = NULL;
            } else {
                node *pLast = (*head)->prev;
                *head = pCur->next; 
                (*head)->prev = pLast;
                pLast->next = *head;
                free(pCur);
            }
        } else {
            pCur->prev->next = pCur->next;
            pCur->next->prev = pCur->prev;
            free(pCur);
        }
        printf("\nNode dengan nilai %d berhasil dihapus.\n", val);
    }
    getch();
}


void hapusAkhir(node **head) {
    node *pCur, *pPrev;
    pCur = *head;
    pPrev = NULL;
    system("cls");

    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
    } else if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        while (pCur->next != *head) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *head;
        (*head)->prev = pPrev;
        free(pCur);
    }
    printf("Data di akhir berhasil dihapus.\n");
    getch();
}


void cariData(node *head, int val) {
    node *pCur = head;
    
    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }
    
    system("cls");
    do {
        if (pCur->data == val) {
            printf("Data %d ditemukan dalam linked list.\n", val);
            return;
        }
        pCur = pCur->next;
    } while (pCur != head);
    
    printf("Data %d tidak ditemukan.\n", val);
    getch();
}


int hitungJumlahNode(node *head) {
    int count = 0;
    node *pCur = head;

    if (head == NULL) {
        printf("List kosong.\n");
        return count;
    }

    system("cls");
    do {
        count++;
        pCur = pCur->next;
    } while (pCur != head);

    printf("Jumlah node di linked list: %d\n", count);
    return count;
}


int jumlahkanData(node *head) {
    int sum = 0;
    node *pCur = head;

    if (head == NULL) {
        printf("List kosong.\n");
        return sum;
    }

    system("cls");
    do {
        sum += pCur->data;
        pCur = pCur->next;
    } while (pCur != head);

    printf("Jumlah seluruh data di linked list: %d\n", sum);
    return sum;
}




