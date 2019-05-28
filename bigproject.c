#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

long long int cash=0;
int i, x, totalData;

typedef struct Data{
	int Unit, Hrg;
	char Nama[100];
}smv;

void menu();
void logo();
long long int plusdana(long long int c);
long long int minusdana(long long int c);
int scanDatauang(long long int c);
void writeDatauang(long long int c);
void scanDatabase(smv *inp);
void writeDatabase(smv *inp);
void daftarBarang(smv *inp);
int tambahBarang(smv *inp, long long int c);
int kurangBarang(smv *inp, long long int c);
void help();

void clean(){
	while(getchar() != '\n');		//Hilangkan Buffer Input
}

int main(){
  system("COLOR 70");
	menu();
  return 0;
}

void menu(){
	smv inp[10000];
	int i;
  char in[10];
  do{
    fflush(stdin);
		scanDatabase(inp);
		cash = scanDatauang(cash);
		logo();
    printf("\t\t\t\t\t\t1. Daftar Stok Barang\n");
    printf("\t\t\t\t\t\t2. Barang Masuk\n");
    printf("\t\t\t\t\t\t3. Barang Keluar\n");
    printf("\t\t\t\t\t\t4. Tambah/kurangi Dana\n");
    printf("\t\t\t\t\t\t5. Petunjuk Penggunaan\n");
    printf("\t\t\t\t\t\t6. Keluar\n\n");

    printf("\t\t\t\t\t\tPilihan : ");
    scanf("%s",&in );

    system("cls");
		clean();

	if (in[0]=='1' && in[1]==0){
		daftarBarang(inp);
    }
    else if (in[0]=='2' && in[1]==0){
			cash = tambahBarang(inp, cash);
			writeDatabase(inp);
      system("pause");
    }
    else if (in[0]=='3' && in[1]==0){
      cash = kurangBarang(inp, cash);
			writeDatabase(inp);
      system("pause");
    }
    else if (in[0]=='4' && in[1]==0){
      int y;
      empat:
      system("cls");
      fflush(stdin);
      printf("\t\t\t\t\t\t1. Tambah Dana\n\t\t\t\t\t\t2. Kurang Dana\n\n\t\t\t\t\t\tPilihan : ");
      scanf("%d",&y);
      if (y==1){
        cash = plusdana(cash);
      }
      else if (y==2) {
        cash = minusdana(cash);
      }
      else {
        printf("\n\t\t\t\t\t\tInput tidak sesuai\n" );
        printf("\n\t\t\t\t\t\tKetik apapun untuk kembali\n");
        getch();
        goto empat;
      }
    }
    else if (in[0]=='5' && in[1]==0){
    	help();
			writeDatauang(cash);
    }
    else if (in[0]!='6' || in[1]!=0){
      printf("\nInput tidak sesuai\n\n" );
      printf("Ketik apapun untuk kembali\n");
      getch();
    }
		writeDatauang(cash);
    system("cls");
  }
  while (in[0]!='6' || in[1]!=0);
  printf("Terima kasih telah menggunakan program ini :)\n");
}

void logo(){
 printf(" +================================================================================================================================+   \n");
 printf(" |                                                                                                                                |   \n");
 printf(" |   $$$$$$   $$    $$   $$$$$$$$$    $$$$$$     $$            $$    $$$$$$    $$$$$$$    $$$$$$    $$$$$$$   $$$$$$$   $$$$$$$   |   \n");
 printf(" |  $$    $$  $$    $$   $$     $$   $$    $$    $$$$        $$$$   $$    $$  $$     $$  $$    $$  $$        $$        $$     $$  |   \n");
 printf(" |  $$        $$    $$   $$     $$   $$    $$    $$ $$      $$ $$   $$    $$  $$     $$  $$    $$  $$        $$        $$     $$  |   \n");
 printf(" |   $$$$$$   $$$$$$$$   $$     $$   $$$$$$$     $$  $$    $$  $$   $$$$$$$$  $$     $$  $$$$$$$$  $$  $$$   $$$$$$$$  $$$$$$$$   |   \n");
 printf(" |        $$  $$    $$   $$     $$   $$          $$   $$  $$   $$   $$    $$  $$     $$  $$    $$  $$    $$  $$        $$ $$      |   \n");
 printf(" |  $$    $$  $$    $$   $$     $$   $$          $$    $$$$    $$   $$    $$  $$     $$  $$    $$  $$    $$  $$        $$   $$    |   \n");
 printf(" |   $$$$$$   $$    $$   $$$$$$$$$   $$          $$     $$     $$   $$    $$  $$     $$  $$    $$   $$$$$$    $$$$$$$  $$     $$  |   \n");
 printf(" |                                                                                                                                |   \n");
 printf(" +================================================================================================================================+   \n\n");
 printf("\n\n\t\t\t\t\t\tDana : %lld\n\n", cash);
}


int scanDatauang(long long int c) {
	int l;
	FILE *dataFile;
		dataFile = fopen("Datauang.txt","r+");

	if (dataFile == NULL){
		printf("File Database Tidak Ditemukan!\n");
	}
	else {
		while ((l=getc(dataFile)) != EOF){
			fscanf(dataFile, "%lld\n", &c);
		}
	}
	fclose(dataFile);
	return c;
}

void writeDatauang(long long int c){
	char data[13]= "Datauang.txt";
	FILE *copy;
	copy = fopen("replica.txt", "w");

	fprintf(copy, "0%lld\n", c);
	fclose(copy);

	remove(data);
	rename("replica.txt", data);
}


void scanDatabase(smv *inp){
	int c;
	totalData=0;

	FILE *dataFile;
		dataFile = fopen("Database.txt", "r+");

	if (dataFile == NULL){
		printf("File Database Tidak Ditemukan!\n");
	}
	else {
		x=0;
		while ((c=getc(dataFile)) != EOF){
			if(x%4==1){
				fgets(inp[totalData].Nama, sizeof(inp[totalData].Nama), dataFile);
			}
			else if(x%4==2){
				fscanf(dataFile, "%d\n", &inp[totalData].Unit);
			}
			else if(x%4==3){
				fscanf(dataFile, "%d\n", &inp[totalData].Hrg);
				totalData++;
			}
			x++;
		}
		totalData--;
	}
	fclose(dataFile);
}

void writeDatabase(smv *inp){
	int i;
	char data[13]= "Database.txt";
	FILE *copy;
	copy = fopen("replica.txt", "w");
	for (i=0; i<=totalData; i++){
		fprintf(copy, "0\n");
		fprintf(copy, "%s", inp[i].Nama);
		fprintf(copy, "0%d\n", inp[i].Unit);
		fprintf(copy, "0%d\n", inp[i].Hrg);
	}
	fclose(copy);

	remove(data);
	rename("replica.txt", data);
}

void daftarBarang(smv *inp){
	if (totalData>=0){
		printf("\t\t\t\t\tTotal Data : %d\n", totalData+1);
		for(i=0; i<=totalData; i++){
			printf("\n\n\t\t\t\t\tNama : %s", inp[i].Nama);
			printf("\t\t\t\t\tUnit : %d", inp[i].Unit);
			printf("\n\t\t\t\t\tHarga : Rp%d", inp[i].Hrg);
		}
	}
	else
		printf("\nAnda belum memiliki stok barang apapun\n");

	printf("\n\n");
	system("pause");
}

int tambahBarang(smv *inp, long long int c){
	totalData++;
	char a;
	a='\n';
	printf("Nama Barang yang akan ditambahkan : ");
	//scanf("%s", &inp[totalData].Nama);
	fgets(inp[totalData].Nama, 100, stdin);
	x--;
	back1:
	printf("Jumlah unit : ");
	scanf("%d%c", &inp[totalData].Unit, &a );
		if((a != '\n')	|| (inp[totalData].Unit < 1)){
			printf("input salah\n");
			goto back1;
		}
		else{
			x--;
		}
		back2:
		printf("Harga jual per satuan : Rp");
		scanf("%d%c", &inp[totalData].Hrg, &a );
			if((a != '\n')	|| (inp[totalData].Hrg < 1)){
				printf("input salah\n");
				goto back2;
			}
			else{
				printf("\nData berhasil diinput\n\n");
			}
		c = c-(inp[totalData].Hrg*inp[totalData].Unit);
		return c;
}
int kurangBarang(smv *inp, long long int c){
	int q,w;
	long long int r;
	do {
		printf("\nDaftar Barang : \n\n");
		for (i=0; i<=totalData ; i++){
			printf("%d.", i+1);
			printf("Nama : %s", inp[i].Nama);
			printf("Unit : %d", inp[i].Unit);
			printf("\nHarga : Rp%d\n\n", inp[i].Hrg);
		}

		printf("\nBarang yang terjual (angka) : ");
		scanf("%d", &q);
		if (q<=0){
			system("cls");
			printf("\n\n\n\n\t\t\tPilihan anda tidak terdapat di daftar.\n\n");
			system ("pause");
			system ("cls");
		}
		else if (q>i){
			system("cls");
			printf("\n\n\n\n\t\t\tPilihan anda tidak terdapat di daftar.\n\n");
			system ("pause");
			system ("cls");
		}
	}
	while (q>i || q<=0);

	terjual:

	printf("\n\n\t\t\tJumlah %s\t\t\tyang terjual : ", inp[q-1].Nama );
	scanf("%d",&w );

	if (w<=inp[q-1].Unit){
		inp[q-1].Unit-=w;
		printf("\nHarga jual per satuan : Rp");
		scanf("%lld", &r );
		cash+=(w*r);
	}
	else {
		system ("cls");
		printf("\n\t\t\tInput unit yang terjual melebihi stok barang sekarang\n\n" );
		system("pause");
		goto terjual;
	}
}

long long int plusdana(long long int c){
  long long int plus=0;
  do {
    printf("\n\t\t\t\tMasukkan nominal dana yang akan ditambahkan : Rp");
    scanf("%lld", &plus );
    if (plus<0){
      printf("\t\t\t\t\t\tNominal tidak boleh negatif\n");
      Sleep(1250);
      system("cls");
    }
  }
  while (plus<0);
  c+=plus;
  return c;
}

long long int minusdana(long long int c){
  long long int minus=0;
  do {
    printf("\n\t\t\t\tMasukkan nominal dana yang akan dikurang : Rp");
    scanf("%lld", &minus );
    if (minus<0){
      printf("\t\t\t\t\t\tNominal tidak boleh negatif\n");
      Sleep(1250);
      system("cls");
    }
  }
  while (minus<0);
  c-=minus;
  return c;
}

void help(){
printf("=================== Petunjuk Penggunaan ======================");
printf("\n\n1.Menu 1 digunakan untuk melihat daftar stok barang");
printf("\n2.Menu 2 digunakan untuk memasukkan barang");
printf("\n3.Akan diminta input berupa nama barang, jumlah barang, dan harga satuan");
printf("\n4.Menu 3 digunakan untuk mengeluarkan barang");
//printf("\n\t5.User memilih barang yang terjual/keluar, user diminta input jumlah barang yang terjual, dan harga jualnya\n");
printf("\n6.Menu 4 digunakan untuk menambahkan atau mengurangi dana");
printf("\n\n7.Akan ada dua menu yaitu 1.menambah dana dan 2.mengurangi dana");
printf("\n\n8.Jika salah satu menu dipilih maka akan diminta memberi input berapa besar perubahan dana");
printf("\n\n9.Pilihan no.5 digunakan untuk melihat bantuan pengunaan aplikasi");
printf("\n\n10.Pilihan no.6 digunakan untuk keluar dari aplikasi");
printf("\n=============================================================\n");
printf("\n\n\n Tekan apa saja untuk kembali\n\n\n");
getch();
system("cls");
}
