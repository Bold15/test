#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//struct untuk menyimpan data penjualan
struct data
{
    int kupon, harga, total;
    char tanggal[10], nama[20], jam[10], catatan[100];
};

// struct untuk menyimpan data pelanggan
struct name
{
    char nama[20];
    int harga;
};


// fungsi untuk mencetak garis penghias
void line(int n)
{
    for(int i=0; i<n; i++){
        printf("=");
    }
    printf("\n");
}

//fungsi untuk input data pelanggan
void cust(struct name name[1000])
{
    system("cls");
    FILE *cust;
    cust = fopen("nama.txt", "a"); // membuka file "nama.txt" untuk diappend
    printf("========== DATA PELANGGAN ==========\n\n");
    printf("nama : ");
    scanf("%[^\n]", name->nama); getchar(); // input data dari user
    printf("harga : ");
    scanf("%d", &name->harga); getchar();   // input data dari user
    fprintf(cust, "%s;%d\n", name->nama, name->harga); // data disimpan di dalam file txt
    printf("data berhasil ditambahkan\n");

    fclose(cust); // tutup file
}

// fungsi untuk baca data pelanggan
void readcust(struct name name[1000])
{
    system("cls");
    FILE *cust;
    cust = fopen("nama.txt", "r"); // buka file "nama.txt" untuk dibaca
    int nam = 0;
    while(fscanf(cust, "%[^\';'];%d\n", name[nam].nama, &name[nam].harga) != EOF) // mengambil data dari file txt
    {
        nam++; // menghitung jumlah data dalam file
    }
    printf("========== DATA PELANGGAN ==========\n\n");
    printf("nama \t\t harga\n");
    line(25);
    for(int i=0; i<nam; i++){
        printf("%s \t\t %d\n", name[i].nama, name[i].harga); // cetak data yang sudah dibaca dari file
    }
    printf("\n");
    fclose(cust); // tutup file
}

// fungsi untuk menghapus data pelanggan
void delcust(struct name name[1000])
{
    system("cls");
    FILE *cust;
    cust = fopen("nama.txt", "r"); // buka file "nama.txt" untuk dibaca
    int nam = 0;
    while(fscanf(cust, "%[^\';'];%d\n", name[nam].nama, &name[nam].harga) != EOF) //mengambil data dari file txt
    {
        nam++; // menghitung jumlah data dalam file
    }
    fclose(cust); // tutup file
    char namadel[20];
    int key = -1;
    readcust(name); // function untuk menampilkan data nama pelanggan
    printf("masukan nama yang ingin dihapus : ");
    scanf("%[^\n]", namadel); getchar();
    cust = fopen("nama.txt", "w"); // buka file "nama.txt" untuk ditulis
    for(int i=0; i<nam; i++){
        if(strcmpi(name[i].nama, namadel)==0){ // membandingkan data dari file dengan data dari user
            key = i; // variabel untuk menentukan apakah data berhasil dihapus atau tidak
            continue;
        }
        else{
            fprintf(cust, "%s;%d\n", name[i].nama, name[i].harga); // print data pelanggan kecuali data dengan indeks i
        }
    }
    if(key != -1){ // jika nilai variabel key masih sama saat dideclare maka data tidak ditemukan
        printf("Data berhasil dihapus\n");
    }
    else{
        printf("Data tidak ditemukan\n");
    }
    fclose(cust); // tutup file
}

// fungsi untuk input data penjualan
void write(struct data data[1000], struct name name[1000])
{
    system("cls");
    int jlh = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE *fp;
    fp = fopen("kantin.txt", "a"); // buka file "kantin.txt" untuk diappend
    FILE *cust;
    cust = fopen("nama.txt", "r"); // buka file "nama.txt" untuk dibaca
    while(fscanf(cust, "%[^\';'];%d\n", name[jlh].nama, &name[jlh].harga) != EOF) //mengambil data dari file txt
    {
        jlh++; // menghitung jumlah data dalam file
    }
    int key = -1;
    readcust(name);
    printf("========== DATA PENJUALAN ==========\n\n");
    printf("masukan nama : ");
    scanf("%[^\n]", data->nama); getchar(); // nama untuk menentukan apakah lanjut input data atau tidak
    for(int i=0; i<jlh; i++){
        if(strcmpi(name[i].nama, data->nama)==0){ // membandingkan nama dari user dengan nama di file
            key = i;
            printf("masukan jam makan : ");
            scanf("%[^\n]", data->jam); getchar();
            printf("masukan jumlah orang/kupon : ");
            scanf("%d", &data->kupon); getchar(); // input data dari user
            printf("masukan catatan : ");
            scanf("%[^\n]", data->catatan); getchar(); 
            data->total = data->kupon * name[i].harga;
            fprintf(fp, "%d-%d-%d;%s;%s;%d;%s;%d;%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, data->nama, data->jam, data->kupon, data->catatan, name[i].harga, data->total); // cetak data dari user ke file
        }
    }
    if(key != -1){
        printf("Data berhasil ditambahkan!\n"); // jika key bukan -1 data berhasil ditambahkan
    }
    else{
        printf("Nama tidak ditemukan, silahkan input data terlebih dahulu atau masukan ulang nama\n"); // jika nama tidak ditemukan di dalam file
    }
    fclose(fp); // tutup file
    fclose(cust); // tutup file
}

// fungsi untuk baca data penjualan
void read(struct data data[1000])
{
    system("cls");
    int jlhdata = 0;
    FILE *fp;

    fp = fopen("kantin.txt", "r"); // buka file "kantin.txt" untuk dibaca
    while(fscanf(fp, "%[^\';'];%[^\';'];%[^\';'];%d;%[^\';'];%d;%d\n", data[jlhdata].tanggal, data[jlhdata].nama, data[jlhdata].jam, &data[jlhdata].kupon, data[jlhdata].catatan, &data[jlhdata].harga, &data[jlhdata].total) != EOF) //mengambil data dari file txt
    {
        jlhdata++; // menghitung jumlah data dalam file
    }
    printf("========== DATA PENJUALAN ==========\n\n");
    printf("tanggal \t nama \t\t jam makan \t kupon \t\t catatan \t\t\t\t harga \t\t total harga\n");
    line(140);
    for(int i=0; i<jlhdata; i++){
        printf("%-10s \t %-10s \t %-5s \t\t %-5d \t\t %-25s \t\t %-5d \t\t %d\n", data[i].tanggal, data[i].nama, data[i].jam, data[i].kupon, data[i].catatan, data[i].harga, data[i].total); // cetak data yang sudah dibaca dari file
    }
    printf("\n");
    fclose(fp); // tutup file
}

// fungsi untuk hapus data penjualan
void hapus(struct data data[1000])
{
    system("cls");
    FILE *fp;
    int jlh = 0;

    fp = fopen("kantin.txt", "r"); // buka file "kantin.txt" untuk dibaca
    while(fscanf(fp, "%[^\';'];%[^\';'];%[^\';'];%d;%[^\';'];%d;%d\n", data[jlh].tanggal, data[jlh].nama, data[jlh].jam, &data[jlh].kupon, data[jlh].catatan, &data[jlh].harga, &data[jlh].total) != EOF) //mengambil data dari file txt
    {
        jlh++; // menghitung jumlah data dalam file
    }
    fclose(fp); // tutup file
    char tgldel[10], namadel[20], jamdel[10];
    read(data); // function untuk menampilkan data kantin
    printf("masukan tanggal yang ingin dihapus (dd-mm-yyyy) : ");
    scanf("%[^\n]", tgldel); getchar();
    printf("masukan nama yang ingin dihapus : ");
    scanf("%[^\n]", namadel); getchar();
    printf("masukan jam yang ingin dihapus : ");
    scanf("%[^\n]", jamdel); getchar();
    int key = -1;
    fp = fopen("kantin.txt", "w"); // buka file "kantin.txt" untuk ditulis
    for(int i=0; i<jlh; i++){
        if(strcmpi(data[i].tanggal, tgldel)==0 && strcmpi(data[i].nama, namadel)==0 && strcmpi(data[i].jam, jamdel)==0){ // membandingkan data dari user dengan data di file
            key = i;
            continue;
        }
        else{
            fprintf(fp, "%s;%s;%s;%d;%s;%d;%d\n", data[i].tanggal, data[i].nama, data[i].jam, data[i].kupon, data[i].catatan, data[i].harga, data[i].total); // print data pelanggan kecuali data dengan indeks i
        }
    }
    if(key != -1){ // jika nilai variabel key masih sama saat dideclare maka data tidak ditemukan
        printf("Data berhasil dihapus\n");
    }
    else{
        printf("Data tidak ditemukan\n");
    }
    fclose(fp); // tutup file
}

// fungsi untuk edit atau ubah data penjualan
void edit(struct data data[1000], struct name name[1000])
{
    system("cls");

    int jlh=0;
    int nam=0;

    FILE *cust;
    cust = fopen("nama.txt", "r"); // buka file "nama.txt" untuk dibaca
    while(fscanf(cust, "%[^\';'];%d\n", name[nam].nama, &name[nam].harga) != EOF)
    {
        nam++; // menghitung jumlah data dalam file
    }

    FILE *fp;
    fp = fopen("kantin.txt", "r"); // buka file "kantin.txt" untuk dibaca
    while(fscanf(fp, "%[^\';'];%[^\';'];%[^\';'];%d;%[^\';'];%d;%d\n", data[jlh].tanggal, data[jlh].nama, data[jlh].jam, &data[jlh].kupon, data[jlh].catatan, &data[jlh].harga, &data[jlh].total) != EOF) //mengambil data dari file txt
    {
        jlh++; // menghitung jumlah data dalam file
    }
    fclose(fp); // tutup file

    char tgledit[10], namaedit[20], jamedit[10];
    read(data); // function untuk menampilkan data kantin
    printf("masukan tanggal yang ingin diedit (dd-mm-yyyy) : ");
    scanf("%[^\n]", tgledit); getchar();
    printf("masukan nama yang ingin diedit : ");
    scanf("%[^\n]", namaedit); getchar();               // user menginput data
    printf("masukan jam makan yang ingin diedit : ");
    scanf("%[^\n]", jamedit); getchar();
    
    int idx = -1, key = -1;
    fp = fopen("kantin.txt", "w"); // buka file "kantin.txt" untuk ditulis
    
    for(int i = 0; i<jlh; i++){
        if(strcmpi(data[i].tanggal, tgledit)==0 && strcmpi(data[i].nama, namaedit)==0 && strcmpi(data[i].jam, jamedit)==0){ // membandingkan data dari user dengan data di file
            idx = i;
            printf("masukan nama baru : ");
            scanf("%[^\n]", data->nama); getchar(); // input nama untuk dibandingkan
            for(int j=0; j<nam; j++){
                if(strcmpi(name[j].nama, data->nama)==0){ // membandingkan nama dari user dengan nama di file
                    key = j;
                    printf("masukan jam makan baru : "); // jika nama ditemukan maka program akan dilanjutkan
                    scanf("%[^\n]", data[key].jam); getchar();
                    printf("masukan jumlah orang/kupon baru : ");
                    scanf("%d", &data[key].kupon); getchar();
                    printf("masukan catatan baru : ");
                    scanf("%[^\n]", data[key].catatan); getchar();
                    data[i].total = data[key].kupon * name[j].harga;
                    fprintf(fp, "%s;%s;%s;%d;%s;%d;%d\n", tgledit, data[j].nama, data[j].jam, data[j].kupon, data[j].catatan, name[j].harga, data[i].total); 
                }
                }
                if(key != -1){ // jika nilai variabel key masih sama saat dideclare maka data tidak ditemukan
            printf("data berhasil ditambahkan!\n");
        }
        else{
            printf("nama tidak ditemukan, silahkan input data terlebih dahulu atau masukan ulang nama\n");
        }
            }
            else{
                    fprintf(fp, "%s;%s;%s;%d;%s;%d;%d\n", data[i].tanggal, data[i].nama, data[i].jam, data[i].kupon, data[i].catatan, data[i].harga, data[i].total); // print data pelanggan kecuali data dengan indeks i
        }
    }
    if(idx == -1){
        printf("Data tidak ditemukan\n"); // jika nilai variabel key masih sama saat dideclare maka data tidak ditemukan
    }
    fclose(fp); // tutup file
    fclose(cust); // tutup file
}

// fungsi untuk mengurutkan data penjualan berdasarkan nama pelanggan
void sortbyname(struct data data[1000])
{
    system("cls");
    struct data temp;
    FILE *fp;
    fp = fopen("kantin.txt", "r"); // buka file "kantin.txt" untuk dibaca
    int jlh = 0;
    while(fscanf(fp, "%[^\';'];%[^\';'];%[^\';'];%d;%[^\';'];%d;%d\n", data[jlh].tanggal, data[jlh].nama, data[jlh].jam, &data[jlh].kupon, data[jlh].catatan, &data[jlh].harga, &data[jlh].total) != EOF) //mengambil data dari file txt
    {
        jlh++; // menghitung jumlah data dalam file
    }
    for(int i=0; i<jlh; i++){
        for(int j=i+1; j<jlh; j++){
            if(strcmp(data[i].nama, data[j].nama)>0){
                temp=data[i];
                data[i]=data[j]; // sort data menggunakan bubble sort
                data[j]=temp;
            }
        }
    }
    printf("tanggal \t nama \t\t jam makan \t kupon \t\t catatan \t\t\t\t harga \t\t total harga\n");
    line(140);
    for(int i=0; i<jlh; i++){
        printf("%-10s \t %-10s \t %-5s \t\t %-5d \t\t %-25s \t\t %-5d \t\t %d\n", data[i].tanggal, data[i].nama, data[i].jam, data[i].kupon, data[i].catatan, data[i].harga, data[i].total); // cetak data yang sudah diurutkan
    }
    printf("\n");
    fclose(fp); // tutup file
}

// fungsi untuk mencari data penjualan berdasarkan tanggal
void searchbydate(struct data data[1000])
{
    system("cls");
    FILE *fp;
    fp = fopen("kantin.txt", "r"); // buka file "kantin.txt" untuk dibaca
    int jlh = 0;
    while(fscanf(fp, "%[^\';'];%[^\';'];%[^\';'];%d;%[^\';'];%d;%d\n", data[jlh].tanggal, data[jlh].nama, data[jlh].jam, &data[jlh].kupon, data[jlh].catatan, &data[jlh].harga, &data[jlh].total) != EOF) //mengambil data dari file txt
    {
        jlh++; // menghitung jumlah data dalam file
    }
    char search[10];
    int idx = -1;
    printf("========== DATA PENJUALAN ==========\n\n");
    printf("masukan tanggal yang dicari : ");
    scanf("%[^\n]", search); getchar(); 
    printf("tanggal \t nama \t\t jam makan \t kupon \t\t catatan \t\t\t\t harga \t\t total harga\n");
    line(140);
    for(int i=0; i<jlh; i++){
        if(strcmpi(data[i].tanggal, search)==0){ // membandingkan tanggal dari user dengan tanggal di file
            idx = i;
            printf("%-10s \t %-10s \t %-5s \t\t %-5d \t\t %-25s \t\t %-5d \t\t %d\n", data[i].tanggal, data[i].nama, data[i].jam, data[i].kupon, data[i].catatan, data[i].harga, data[i].total); // print data dengan index i
        }
    }
    if(idx == -1){
        printf("Data tidak ditemukan\n");
    }
    printf("\n");
    fclose(fp);// tutup file
}

// fungsi untuk mencari data penjualan berdasarkan nama pelanggan
void searchbyname(struct data data[1000])
{
    system("cls");
    FILE *fp;
    fp = fopen("kantin.txt", "r"); // buka file "kantin.txt" untuk dibaca
    int jlh = 0;
    int tagihan;
    while(fscanf(fp, "%[^\';'];%[^\';'];%[^\';'];%d;%[^\';'];%d;%d\n", data[jlh].tanggal, data[jlh].nama, data[jlh].jam, &data[jlh].kupon, data[jlh].catatan, &data[jlh].harga, &data[jlh].total) != EOF) //mengambil data dari file txt
    {
        jlh++; // menghitung jumlah data dalam file
    }
    char search[10];
    int idx = -1;
    printf("========== DATA PENJUALAN ==========\n\n");
    printf("masukan nama yang dicari : ");
    scanf("%[^\n]", search); getchar();
    printf("tanggal \t nama \t\t jam makan \t kupon \t\t catatan \t\t\t\t harga \t\t total harga\n");
    line(140);
    for(int i=0; i<jlh; i++){
        if(strcmpi(data[i].nama, search)==0){ // membandingkan nama dari user dengan nama di file
            idx = i;
            printf("%-10s \t %-10s \t %-5s \t\t %-5d \t\t %-25s \t\t %-5d \t\t %d\n", data[i].tanggal, data[i].nama, data[i].jam, data[i].kupon, data[i].catatan, data[i].harga, data[i].total); // print data dengan index i
        }
    }
    if(idx == -1){
        printf("Data tidak ditemukan\n");
    }
    printf("\n");
    fclose(fp); // tutup file
}

int main()
{
    struct data data[1000];
    struct name name[1000];
    int pil;
        do{
            system("cls");
            printf("========== MAIN MENU ==========\n");
            printf("1. Input data penjualan\n");
            printf("2. Read data penjualan\n");
            printf("3. Delete data penjualan\n");
            printf("4. Edit data penjualan\n");
            printf("5. Urutkan berdasarkan nama\n");
            printf("6. Cari berdasarkan tanggal\n");
            printf("7. Cari berdasarkan nama\n");
            printf("8. Input data pelanggan\n");
            printf("9. Read data pelanggan\n");
            printf("10. Delete data pelanggan\n");
            printf("11. Exit\n");
            printf("===============================\n");
            printf("masukan pilihan : ");
            scanf("%d", &pil); getchar();
            switch(pil)
            {
                case 1:
                    write(data, name);
                    system("pause");
                    break;
                case 2:
                    read(data);
                    system("pause");
                    break;
                case 3:
                    hapus(data);
                    system("pause");
                    break;
                case 4:
                    edit(data, name);
                    system("pause");
                    break;
                case 5:
                    sortbyname(data);
                    system("pause");
                    break;
                case 6:
                    searchbydate(data);
                    system("pause");
                    break;
                case 7:
                    searchbyname(data);
                    system("pause");
                    break;
                case 8:
                    cust(name);
                    system("pause");
                    break;
                case 9:
                    readcust(name);
                    system("pause");
                    break;
                case 10:
                    delcust(name);
                    system("pause");
                    break;
                default:
                    break;
                }
            }while(pil >= 1 && pil <= 10);
    getchar();
    return 0;
}