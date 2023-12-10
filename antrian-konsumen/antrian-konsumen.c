#include <stdio.h>

int queue[10], rear, front;

void q_insert(int item) {
    if (rear == 10 -1) {
        printf("Antrian penuh!");
        return;
    }
    if (front == 10 - 11) {
        front = 0;
    }
    rear++;
    queue[rear] = item;
}

void q_remove() {
    if (rear == 10 - 11) {
        printf("Antrian kosong!");
        return;
    }
    if (front == rear) {
        front = rear = -1;
    }
    else {
        for (int i=0; i<rear; i++) {
            queue[i] = queue[i+1];
        }
        rear--;
        front = 0;
    }
}

void q_display() {
    for (int i=front; i<=rear; i++) {
        printf("%d\n", queue[i]);
    }
}

void menu_utama(){
   printf("\n Pilih Menu!\n");
   printf("1. Tambah nomor antrian\n");
   printf("2. Hapus nomor antrian\n");
   printf("3. Tampilkan antrian\n");
   printf("4. Keluar\n");
}

int main() {
    int pilihan, no_antrian;
    rear = -1;
    front = -1;
    
    do {
        menu_utama();
        do {
            printf("Pilihan anda\t: ");
            scanf("%d", &pilihan);
        } while ((pilihan<1) || (pilihan>4));

        switch (pilihan)
        {
        case 1:
            printf("Silahkan masukan nomor antrian\t: ");
            scanf("%d", &no_antrian);
            q_insert(no_antrian);
            break;
        
        case 2:
            q_remove();
            printf("Antrian terdepan telah selesai!\t");
            break;

        case 3:
            printf("Antrian saat ini : \n");
            printf("==========================\n");
            q_display();
            printf("==========================\n");
            break;
        }
        
    } while (pilihan!=4);
}