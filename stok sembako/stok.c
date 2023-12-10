#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
   char nama[20];
   int id_sembako;
   int stok;
   struct node *next;
   struct node *prev;
};

typedef struct node *mynode;

mynode create_node(int stok, char nama[20], int id_sembako){
   mynode new_node;
   new_node=(mynode)malloc(sizeof(struct node));
   new_node->id_sembako=id_sembako;
   new_node->stok=stok;
   strcpy(new_node->nama,nama);
   new_node->next=NULL;
   new_node->prev=NULL;
   return(new_node);
}

mynode insert_node(mynode head, int stok, char nama[20], int id_sembako){
   mynode new_node=create_node(stok,nama,id_sembako);
   // head masih null
   if(head==NULL){
      head=new_node;
      return(head);
   }

   // nyari posisi
   mynode cursor=head;
   mynode precursor;

   // tambah head
   if (cursor->id_sembako<=id_sembako){
      new_node->next=head;
      head->prev=new_node;
      head=new_node;
   } else {
      while(cursor->next!=NULL){
         if (cursor->id_sembako>id_sembako){
            precursor=cursor;
            cursor=cursor->next;
         } else break;
      }
      if (cursor->id_sembako>id_sembako){
         // tambah tail
         cursor->next=new_node;
         new_node->prev=cursor;
      } else if (cursor->id_sembako<=id_sembako){
         precursor->next=new_node;
         new_node->next=cursor;
         cursor->prev=new_node;
         new_node->prev=precursor;
      }
   }
   return(head);
}

mynode remove_node (mynode head, int id_sembako){
   mynode cursor = head;

   if (cursor->id_sembako == NULL){
      printf ("List masih kosong\n");
      return (head);
   }
   else if (cursor->id_sembako == id_sembako){
      if (head->next == NULL){
         head = NULL;
         return(head);
      }
      head = head->next;
      cursor->next = NULL;
      head->prev = NULL;
      free(cursor);
   }
   else {
      while (cursor->id_sembako == id_sembako){
         if (cursor->next != NULL){
            cursor = cursor->next;
         }
         else break;
      }
      if (cursor->id_sembako == id_sembako){
         // node yang dihapus adalah tail
         if (cursor->next == NULL){
            mynode tail = cursor->prev;
            tail->next = NULL;
            cursor->prev = NULL;
            free(cursor);
         }
         else {
            cursor->prev->next = cursor->next;
            cursor->next->prev = cursor->prev;
            cursor->prev = NULL;
            cursor->next = NULL;
            free (cursor);
         }
      }
   }
   return (head);
}

void tampil_node(mynode head){
   mynode n=head;
   printf("---------------------------------------------------------\n");
   printf("| Nama\t\t     | ID Sembako\t  | Stok\t|\n");
   printf("---------------------------------------------------------\n");
   while (n!=NULL){
      printf("| %-18s | %-18d | %-11d | \n", n->nama, n->id_sembako, n->stok);
      printf("---------------------------------------------------------\n");
      n=n->next;
   }  
}

void menu(){
   printf("\n Silahkan dipilih menunya!\n");
   printf("1. Tambah Data Sembako\n");
   printf("2. Hapus Data Sembako\n");
   printf("3. Tampilkan Data Sembako\n");
   printf("4. Keluar\n");
}

int main(){
   int pilih, stok, id_sembako;
   char nama[20];
   mynode head=NULL;
   do {
      menu();
      do{
         printf("Pilihan anda \t: ");
         scanf("%d", &pilih);
      } while((pilih<1) || (pilih>4));

      switch (pilih){
      case 1:
         printf("Nama Sembako\t: ");
         scanf("%s", nama);
         printf("ID Sembako\t: ");
         scanf("%d", &id_sembako);
         printf("Stok Barang\t: ");
         scanf("%d", &stok);
         head=insert_node(head,stok,nama,id_sembako);
         break;
      case 2:
         printf("ID Sembako yang ingin dihapus :");
         scanf("%d", &id_sembako);
         head = remove_node(head,id_sembako);
         break;
      case 3:
         tampil_node(head);
      }
   }while (pilih!=4);      
}
