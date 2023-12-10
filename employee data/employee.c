#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
   int employee_id;
   char nama_lengkap[30];
   char tempat_lahir[30];
   int tanggal_lahir;
   char jabatan[50];
   struct node *next;
   struct node *prev;
};

typedef struct node *mynode;

mynode create_node(char nama_lengkap[30], int employee_id, char tempat_lahir[30], int tanggal_lahir, char jabatan[50]){
   mynode new_node;
   new_node=(mynode)malloc(sizeof(struct node));
   new_node->employee_id=employee_id;
   new_node->tanggal_lahir=tanggal_lahir;
   strcpy(new_node->nama_lengkap,nama_lengkap);
   strcpy(new_node->tempat_lahir,tempat_lahir);
   strcpy(new_node->jabatan,jabatan);
   new_node->next=NULL;
   new_node->prev=NULL;
   return(new_node);
}

mynode insert_node(mynode head, char nama_lengkap[30], int employee_id, char tempat_lahir[30], int tanggal_lahir, char jabatan[50]){
   mynode new_node=create_node(nama_lengkap,employee_id,tempat_lahir,tanggal_lahir,jabatan);
   // head masih null
   if(head==NULL){
      head=new_node;
      return(head);
   }

   // nyari posisi
   mynode cursor=head;
   mynode precursor;

   // tambah head
   if (cursor->employee_id<=employee_id){
      new_node->next=head;
      head->prev=new_node;
      head=new_node;
   } else {
      while(cursor->next!=NULL){
         if (cursor->employee_id>employee_id){
            precursor=cursor;
            cursor=cursor->next;
         } else break;
      }
      if (cursor->employee_id>employee_id){
         // tambah tail
         cursor->next=new_node;
         new_node->prev=cursor;
      } else if (cursor->employee_id<=employee_id){
         precursor->next=new_node;
         new_node->next=cursor;
         cursor->prev=new_node;
         new_node->prev=precursor;
      }
   }
   return(head);
}

mynode remove_node (mynode head, int employee_id){
   mynode cursor = head;

   if (cursor->employee_id == NULL){
      printf ("List masih kosong\n");
      return (head);
   }
   else if (cursor->employee_id == employee_id){
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
      while (cursor->employee_id == employee_id){
         if (cursor->next != NULL){
            cursor = cursor->next;
         }
         else break;
      }
      if (cursor->employee_id == employee_id){
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
   printf("-------------------------------------------------------------------------------------------------------------------------\n");
   printf("| Nama Lengkap\t\t| Employee ID\t\t| Tempat Lahir\t\t| Tanggal Lahir\t\t| Jabatan\t\t|\n");
   printf("-------------------------------------------------------------------------------------------------------------------------\n");
   while (n!=NULL){
      printf("| %-18s | %-18d | %-18s | %-18d | %-18s |\n", n->nama_lengkap, n->employee_id, n->tempat_lahir, n->tanggal_lahir, n->jabatan);
      printf("-------------------------------------------------------------------------------------------------------------------------\n");
      n=n->next;
   }  
}

void menu(){
   printf("\n Pilih Menu!\n");
   printf("1. Tambah Data Karyawan\n");
   printf("2. Hapus Data Karyawan\n");
   printf("3. Tampilkan Data Karyawan\n");
   printf("4. Keluar\n");
}

int main(){
   int pilih, employee_id, tanggal_lahir;
   char nama_lengkap[30], tempat_lahir[30], jabatan[50];
   mynode head=NULL;
   do {
      menu();
      do{
         printf("Pilihan anda \t: ");
         scanf("%d", &pilih);
      } while((pilih<1) || (pilih>4));

      switch (pilih){
      case 1:
         printf("Nama Karyawan\t: ");
         scanf("%s", nama_lengkap);
         printf("Employee ID\t: ");
         scanf("%d", &employee_id);
         printf("Tempat Lahir\t: ");
         scanf("%s", tempat_lahir);
         printf("Tanggal Lahir\t: ");
         scanf("%d", &tanggal_lahir);
         printf("Jabatan\t: ");
         scanf("%s", jabatan);
         head=insert_node(head,nama_lengkap,employee_id,tempat_lahir,tanggal_lahir,jabatan);
         break;
      case 2:
         printf("Employee ID yang ingin dihapus :");
         scanf("%d", &employee_id);
         head = remove_node(head,employee_id);
         break;
      case 3:
         tampil_node(head);
      }
   }while (pilih!=4);      
}