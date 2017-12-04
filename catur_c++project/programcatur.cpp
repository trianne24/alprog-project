/*
	
	// TUGAS AKHIR PRAKTIKUM ALPROG SEMESTER 1 //

	Nama	: Vega Savera Yuana | Patricia Joanne
	NPM		: 140810160053		| 140810160065
	Program	: Catur

	// PEMBAGIAN KERJA //
	
	Vega:
	- Membuat papan catur dasar
	- Membuat kondisi game over ketika raja sudah dimakan
	- Membuat tidak ganti giliran bila notasi yang dimasukan salah
	- Menambah estetika (warna, desain opening dan papan)

	Patricia:
	- Merapikan agar output program rapi (atur jarak, tambah kata-kata)
	- Membuat perpindahan bidak dengan notasi string
	- Menjadikan codingan dalam bentuk fungsi semua
	- Membuat perintah untuk memulai permainan baru
	
*/

#include<iostream>
#include<iomanip>
#include<windows.h>
using namespace std;

char b=219;
char p=223;
typedef char papan[8][8];

void welcome(){
	system("color 3F");
	cout<<"\n\n\n\n\n"<<setw(17);	
	
	for(int i=0;i<49;i++){
		cout<<b;
	}
	cout<<endl;
	cout<<setw(17)<<b<<setw(48)<<b<<endl;
	cout<<setw(17)<<b<<"\tProgram Sederhana Permainan Catur\t"<<b<<endl;
	cout<<setw(17)<<b<<setw(48)<<b<<endl;
	cout<<setw(17)<<b<<"   Vega Savera Yuana\t\t140810160053\t"<<b<<endl;
	cout<<setw(17)<<b<<"   Patricia Joanne\t\t140810160065\t"<<b<<endl;
	cout<<setw(17)<<b<<setw(48)<<b<<endl;
	cout<<setw(17);
	for(int i=0;i<49;i++){
		cout<<b;
	}
	
	cout<<"\n\n\n\n\n";
		system("pause");
		system("CLS");
}
void ketentuan(){
	system("color F3");
	
	cout<<"\n\n\n\n";
	cout<<setw(10);
	for(int i=0;i<60;i++){
		cout<<b;
	}
	cout<<endl<<setw(10)<<b<<setw(59)<<b;
	cout<<endl<<setw(10)<<b<<"\t\t\tPermainan Catur!"<<setw(21)<<b;
	cout<<endl<<setw(10)<<b<<setw(59)<<b;
	cout<<endl<<setw(10)<<b<<"\t\tCara Bermain: "<<setw(31)<<b;
	cout<<endl<<setw(10)<<b<<setw(59)<<b;
	cout<<endl<<setw(10)<<b<<"  P=Pion\t1. Bagian atas hitam dan bagian bawah putih"<<setw(2)<<b;
	cout<<endl<<setw(10)<<b<<"  B=Benteng\t2. Kolom catur a-h dan baris catur 1-8"<<setw(7)<<b;
	cout<<endl<<setw(10)<<b<<"  K=Kuda\t3. Masukkan notasi bidak yang dijalankan"<<setw(5)<<b;
	cout<<endl<<setw(10)<<b<<"  G=Gajah\t4. Pemain putih memulai dahulu"<<setw(15)<<b;
	cout<<endl<<setw(10)<<b<<"  M=Menteri\t5. Setiap pemain harus melindungi rajanya"<<setw(4)<<b;
	cout<<endl<<setw(10)<<b<<"  R=Raja\t6. Pemain yang mendapat raja lawan menang"<<setw(4)<<b;
	cout<<endl<<setw(10)<<b<<setw(59)<<b;
	cout<<endl<<setw(10)<<b<<"\t\t\tSelamat Bermain!"<<setw(21)<<b;
	cout<<endl<<setw(10)<<b<<setw(59)<<b;
	cout<<endl<<setw(10);
	for(int i=0; i<60; i++){
		cout<<b;
	}
	cout<<"\n\n\n\n\n";
	
		system("pause");
		system("CLS");
}
void start(int i,int j,papan catur){
	//papan atas
	cout<<setw(43)<<"_____Hitam_____"<<endl;
	cout<<setw(43)<<"a b c d e f g h"<<endl;
	cout<<setw(27)<<b;
	for(i=0;i<17;i++){ 
		cout<<p;
	}
	cout<<b<<endl;

	//isi papan
	for(i=7;i>-1;i--){ 
		cout<<"\t\t\t"<<i+1<<" "<<b<<" ";
		for (j=0;j<8;j++){
			cout<<catur[i][j]<<" ";
		}
		cout<<b<<endl;
	}
		
	//papan bawah
	cout<<setw(27)<<b<<setw(18)<<b;
	cout<<endl<<setw(27);
	for(i=0;i<19;i++){
		cout<<p;
	}
	cout<<endl;
	cout<<setw(43)<<"a b c d e f g h"<<endl;
	cout<<setw(43)<<"_____Putih_____"<<endl;
}
int permainan(int i,int j,int giliran,papan catur){
	// GILIRAN //
	giliran=0;
	system("CLS");
	for(i=0;i>-1;i++){
		giliran++;
		
			if (giliran%2==0){
				system("color F0");
				cout<<endl<<endl<<setw(42)<<"Giliran Hitam"<<endl<<endl;
			}
			else if (giliran%2==1){
				system("color F");
				cout<<endl<<endl<<setw(42)<<"Giliran Putih"<<endl<<endl;
			}
	
	// PAPAN CATUR //
	start(i,j,catur);

	// NOTASI //
	back:
	string notasi;
	int k,l,m,n;
	cout<<endl<<"Contoh notasi yang benar: e2-e4";
	cout<<endl<<"Jika ingin keluar, ketik: exit";
	cout<<endl<<endl<<"Masukkan notasi bidak yang dijalankan: ";
	cin>>notasi;
		if (notasi.substr(0,4)=="exit"){
			break;
		}
		if((notasi.substr(0,1)>="a"&&notasi.substr(0,1)<="h")&&(notasi.substr(1,1)>="1"&&notasi.substr(1,1)<="8")&&(notasi.substr(3,1)>="a"&&notasi.substr(3,1)<="h")&&(notasi.substr(4,1)>="1"&&notasi.substr(4,1)<="8")){
			k =  notasi[0] - 'a';
			l =  notasi[1] - '1';
			m =  notasi[3] - 'a';
			n =  notasi[4] - '1';
			
			if (catur[n][m]=='r'){
				system("CLS");
				system("color F");
				cout<<"\n\n\n\n\n"<<setw(17);	

				for(int i=0;i<49;i++){
					cout<<b;
				}

				cout<<endl;
				cout<<setw(17)<<b<<setw(48)<<b<<endl;
				cout<<setw(17)<<b<<setw(37)<<"G A M E  O V E R ! ! !\t\t"<<b<<endl;
				cout<<setw(17)<<b<<setw(48)<<b<<endl;
				cout<<setw(17)<<b<<setw(37)<<"Selamat! Putih menang!\t\t"<<b<<endl;
				cout<<setw(17)<<b<<setw(48)<<b<<endl;
				cout<<setw(17);
				for(int i=0;i<49;i++){
					cout<<b;
				}
				return 0;
			}
			if (catur[n][m]=='R'){
				system("CLS");
				system("color F0");
				cout<<"\n\n\n\n\n"<<setw(17);	

				for(int i=0;i<49;i++){
					cout<<b;
				}

				cout<<endl;
				cout<<setw(17)<<b<<setw(48)<<b<<endl;
				cout<<setw(17)<<b<<setw(37)<<"G A M E  O V E R ! ! !\t\t"<<b<<endl;
				cout<<setw(17)<<b<<setw(48)<<b<<endl;
				cout<<setw(17)<<b<<setw(37)<<"Selamat! Hitam menang!\t\t"<<b<<endl;
				cout<<setw(17)<<b<<setw(48)<<b<<endl;
				cout<<setw(17);
				for(int i=0;i<49;i++){
					cout<<b;
				}
				return 0;
			}
			catur[n][m]=catur[l][k];
			catur[l][k]='-';
		}

		else {
			cout<<"Notasi salah! Silakan input ulang"<<endl;
			goto back;
		}
	system("CLS");
	}
}

int main(){
	// DEKLARASI //
	int i,j,giliran;
	char jawab;
	
	// OPENING //
	welcome();
	ketentuan();
	
	// PERMAINAN //
	do{
		papan catur={'B','K','G','M','R','G','K','B','P','P','P','P','P','P','P','P',
				'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
				'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
				'p','p','p','p','p','p','p','p','b','k','g','m','r','g','k','b'};
		
		permainan(i,j,giliran,catur);
		cout<<endl<<endl<<"Mau coba lagi (y/t)? ";
		cin>>jawab; 
	}
	while (jawab=='y' || jawab=='Y');
	cout<<"Selesai. Terima kasih telah bermain!"<<endl<<endl;
}

/*

	// BELOM BISA DIJALANKAN //

	//=== l a n g k a h ===

		//pion (dua langkah pertama mulai dari baris 2/7, lalu selangkah seterusnya)
		//benteng (baris sama/kolomnya sama)
		//kuda (kalo baris+2/baris-2, kolom+1/kolom-1 atau baris+1/baris-1, kolom+2/kolom-2)
		//gajah (baris dan kolom sama" tambah/kurangnya misalnya b2-d4)
		//menteri (gabungan gajah sm benteng)
		//raja (bisa baris+1/kolom=1/baris-1/kolom-1)

*/

