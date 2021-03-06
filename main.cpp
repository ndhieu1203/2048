#include <iostream>
#include <conio.h>
#include "ColorDisplay.h"
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

	ColorCharacter cc;
	ColorDisplay cd;
    COORD pos;

//Gia tri cua cac o trong bang 4x4
const string diem[14] = {"    ", "  2 ", "  4 ", "  8 ", " 16 ", " 32 ", " 64 ", " 128", "256", " 512", "1024", "2048", "4096", "8192"};

//Ma tran 4x4 luu gia tri cac o trong bang
int Matrix[4][4];

//Ma tran toa do cac ki tu
int ToaDo[21][13];

const int delay = 10;

int score, highScore;

bool themSo;

void XoaManHinh()
{
       HANDLE hOut;
       COORD Position;
       hOut = GetStdHandle(STD_OUTPUT_HANDLE);
       Position.X = 0;
       Position.Y = 0;
       SetConsoleCursorPosition(hOut, Position);
}


void Draw(int cot,int dong, char kitu, int mau, COORD pos, ColorCharacter cc)
{
    cc.character = kitu;
    cc.color = mau;
    pos.X = cot;
    pos.Y = dong;
    cd.setColorCharacterAtPosition(cc, pos);
}

void DrawString(const string &str, int cot, int dong)
{
    int i;
    for(i=0;i<str.length();i++)
    {
       Draw(cot, dong, str[i], 7, pos, cc);
       cot++;
    }
}

string ConvertNumberString( int number)
{
    stringstream ss;
    ss<< number;
    string str;
    ss>> str;
    return str;
}

void TaoKhung()
{
	int temp;
	ifstream in("Khung.txt");
	for (int j=0; j<13; j++){
		for (int i=0; i<21; i++){
			in >> temp;
			ToaDo[i][j] = temp;
		}
	}
}

void VeKhung()
{

	for (int j=0; j<13; j++){
		for (int i=0; i<21; i++){
			cout <<(char)ToaDo[i][j];//Ghi ki tu theo ma ASCII
		}
		cout <<endl;
	}
}

void HuongDan()
{
	cout << "Huong dan:\n\n\t-Su dung cac nut dieu huong de di chuyen:\n" << endl
		 << "\t\t+Len:\t"<< (char)24 << endl << endl
		 << "\t\t+Xuong:\t"<< (char)25 << endl << endl
		 << "\t\t+Phai:\t" << (char)26 << endl << endl
		 << "\t\t+Trai:\t"<< (char)27 << endl << endl
		 << "\t\t--> Nhan ESC de thoat tro choi!\n\n";
	system("pause");
}

void Logo()
{
	char c;
	ifstream in("Logo.txt");
	do{
		in >> c;
		cout << c;
		if (c==')') cout << endl;
		Sleep(2);
	}while(c!=',');
	cout << endl << endl;
	system("pause");
}

int TaoSo()
{
	int a=rand()%20;
	if (!a) return 2;	//dien gia tri 4. Xac suat la 5%
	else return 1;		//Dien gia tri 2. Xac suat la 95%
}

int ThemSo()
{
	int i, j, a;
	//Kiem tra xem con cho trong hay khong
	bool ConCho=false;
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if (!Matrix[i][j]){
				ConCho=true;
				break;
			}
		}
	}
	//Neu con cho thi chon cho trong ngau nhien de khoi tao gia tri
	if (ConCho){
		do{
			i = rand()%4;
			j = rand()%4;
		}while (Matrix[i][j]);
		Matrix[i][j] = TaoSo();
	}
}

void InBang()
{
	int i, j, max = 0;

	VeKhung();//Ve khung truoc roi dien gia tri
	for (i=0; i<4; i++){
		for (int j=0; j<4; j++){
            DrawString(diem[Matrix[i][j]], 1+i*5, 2+j*3);
		}
	}
	//In diem nguoi choi
	string highScorestring = ConvertNumberString(highScore);
	DrawString("BEST: " + highScorestring, 30,1);

	string scorestring = ConvertNumberString(score);
	DrawString("DIEM: " + scorestring, 30,3);

	DrawString("=> Nhan ESC de thoat.", 30,6);
}

bool ConOTrong()
{
	bool kq = false;
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if (!Matrix[i][j]){
				kq = true;
			}
		}
	}
	return kq;
}


bool ThuaCuoc()
{
	bool kq1, kq2;
	if (ConOTrong()) {kq1 = true;} //Con o trong thi true
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			//Con 2 o canh nhau co cung gia tri thi true
			if (Matrix[i][j]==Matrix[i][j+1] || Matrix[i][j]==Matrix[i+1][j]){
				kq2 = true;
			}
		}
	}
	if ((!kq1) && (!kq2)) return true;
	else return false;
}



void Down()
{
	int i, j, vt1, vt2, temp;
	for (i=0; i<4; i++){
		//Gop het nhung o trong ben duoi
		for (j=3; j>0; j--){
			if (!Matrix[i][j]){
				vt1=vt2=j;
				do{ vt2--;if (vt2==0) break;} while (!Matrix[i][vt2]);
				if (vt2 || (!vt2 && Matrix[i][vt2])){

						DrawString("    ",i*5+1,vt2*3+2);	//Ghi chen so bi di chuyen nam trong ma tran khi InBang
						DrawString(diem[Matrix[i][vt2]],i*5+1,vt1*3+2);

						Sleep(delay);

					//Doi cho o trong voi o co gia tri trong ma tran
					temp = Matrix[i][vt1];
					Matrix[i][vt1] = Matrix[i][vt2];
					Matrix[i][vt2]= temp;
					themSo = true;
				}
			}
		}
		//Cong 2 o co cung gia tri
		for (j=3; j>0; j--){
			if (Matrix[i][j]!=0 && Matrix[i][j]==Matrix[i][j-1]){
				Matrix[i][j]++;
				score+=pow(2,Matrix[i][j]);
				Matrix[i][j-1] = 0;
				themSo = true;
			}
		}
		//Gop het nhung o trong ben duoi
		for (j=3; j>0; j--){
			if (!Matrix[i][j]){
				vt1=vt2=j;
				do{ vt2--;if (vt2==0) break;} while (!Matrix[i][vt2]);
				if (vt2 || (!vt2 && Matrix[i][vt2])){

						DrawString("    ",i*5+1,vt2*3+2);	//Ghi chen so bi di chuyen nam trong ma tran khi InBang
						DrawString(diem[Matrix[i][vt2]],i*5+1,vt1*3+2);

						Sleep(delay);

					//Doi cho o trong voi o co gia tri trong ma tran
					temp = Matrix[i][vt1];
					Matrix[i][vt1] = Matrix[i][vt2];
					Matrix[i][vt2]= temp;
					themSo = true;
				}
			}
		}
	}
}

void Up()
{
	int i, j, vt1, vt2, temp;
	for (i=0; i<4; i++){
		//Gop het nhung o trong ben tren
		for (j=0; j<3; j++){
			if (!Matrix[i][j]){
				vt1=vt2=j;
				do{ vt2++;if (vt2==3) break;} while (!Matrix[i][vt2]);
				if (vt2!=3 || (vt2==3 && Matrix[i][vt2])){

						DrawString("    ",i*5+1,vt2*3+2);	//Ghi chen so bi di chuyen nam trong ma tran khi InBang
						DrawString(diem[Matrix[i][vt2]],i*5+1,vt1*3+2);

						Sleep(delay);

					//Doi cho o trong voi o co gia tri trong ma tran
					temp = Matrix[i][vt1];
					Matrix[i][vt1] = Matrix[i][vt2];
					Matrix[i][vt2]= temp;
					themSo = true;
				}
			}
		}
		//Cong 2 o co cung gia tri
		for (j=0; j<3; j++){
			if (Matrix[i][j]!=0 && Matrix[i][j]==Matrix[i][j+1]){
				Matrix[i][j]++;
				score+=pow(2,Matrix[i][j]);
				Matrix[i][j+1] = 0;
				themSo = true;
			}
		}
        //Gop het nhung o trong ben tren
		for (j=0; j<3; j++){
			if (!Matrix[i][j]){
				vt1=vt2=j;
				do{ vt2++;if (vt2==3) break;} while (!Matrix[i][vt2]);
				if (vt2!=3 || (vt2==3 && Matrix[i][vt2])){

						DrawString("    ",i*5+1,vt2*3+2);	//Ghi chen so bi di chuyen nam trong ma tran khi InBang
						DrawString(diem[Matrix[i][vt2]],i*5+1,vt1*3+2);

						Sleep(delay);

					//Doi cho o trong voi o co gia tri trong ma tran
					temp = Matrix[i][vt1];
					Matrix[i][vt1] = Matrix[i][vt2];
					Matrix[i][vt2]= temp;
					themSo = true;
				}
			}
		}
	}
}

void Right()
{
	int i, j, vt1, vt2, temp;
	for (j=0; j<4; j++){
		//Gop het nhung o trong ben phai
		for (i=3; i>0; i--){
			if (!Matrix[i][j]){
				vt1=vt2=i;
				do{ vt2--;if (vt2==0) break;} while (!Matrix[vt2][j]);
				if (vt2 || (!vt2 && Matrix[vt2][j])){

						DrawString("    ",vt2*5+1,j*3+2);	//Ghi chen so bi di chuyen nam trong ma tran khi InBang
						DrawString(diem[Matrix[vt2][j]],vt1*5+1,j*3+2);

						Sleep(delay);

					//Doi cho o trong voi o co gia tri trong ma tran
					temp = Matrix[vt1][j];
					Matrix[vt1][j] = Matrix[vt2][j];
					Matrix[vt2][j]= temp;
					themSo = true;
				}
			}
		}
		//Cong 2 o co cung gia tri
		for (i=3; i>0; i--){
			if (Matrix[i][j]!=0 && Matrix[i][j]==Matrix[i-1][j]){
				Matrix[i][j]++;
				score+=pow(2,Matrix[i][j]);
				Matrix[i-1][j] = 0;
				themSo = true;
			}
		}
        //Gop het nhung o trong ben phai
		for (i=3; i>0; i--){
			if (!Matrix[i][j]){
				vt1=vt2=i;
				do{ vt2--;if (vt2==0) break;} while (!Matrix[vt2][j]);
				if (vt2 || (!vt2 && Matrix[vt2][j])){

						DrawString("    ",vt2*5+1,j*3+2);	//Ghi chen so bi di chuyen nam trong ma tran khi InBang
						DrawString(diem[Matrix[vt2][j]],vt1*5+1,j*3+2);

						Sleep(delay);

					//Doi cho o trong voi o co gia tri trong ma tran
					temp = Matrix[vt1][j];
					Matrix[vt1][j] = Matrix[vt2][j];
					Matrix[vt2][j]= temp;
					themSo = true;
				}
			}
		}
	}
}

void Left()
{
	int i, j, vt1, vt2, temp;
	for (j=0; j<4; j++){
		//Gop het nhung o trong ben trai
		for (i=0; i<3; i++){
			if (!Matrix[i][j]){
				vt1=vt2=i;
				do{ vt2++;if (vt2==3) break;} while (!Matrix[vt2][j]);
				if (vt2!=3 || (vt2==3 && Matrix[vt2][j])){

						DrawString("    ",vt2*5+1,j*3+2);	//Ghi chen so bi di chuyen nam trong ma tran khi InBang
						DrawString(diem[Matrix[vt2][j]],vt1*5+1,j*3+2);

						Sleep(delay);

					//Doi cho o trong voi o co gia tri trong ma tran
					temp = Matrix[vt1][j];
					Matrix[vt1][j] = Matrix[vt2][j];
					Matrix[vt2][j]= temp;
					themSo = true;
				}
			}
		}
		//Cong 2 o co cung gia tri
		for (i=0; i<3; i++){
			if (Matrix[i][j]!=0 && Matrix[i][j]==Matrix[i+1][j]){
				Matrix[i][j]++;
				score+=pow(2,Matrix[i][j]);
				Matrix[i+1][j] = 0;
				themSo = true;
			}
		}
        		//Gop het nhung o trong ben trai
		for (i=0; i<3; i++){
			if (!Matrix[i][j]){
				vt1=vt2=i;
				do{ vt2++;if (vt2==3) break;} while (!Matrix[vt2][j]);
				if (vt2!=3 || (vt2==3 && Matrix[vt2][j])){

						DrawString("    ",vt2*5+1,j*3+2);	//Ghi chen so bi di chuyen nam trong ma tran khi InBang
						DrawString(diem[Matrix[vt2][j]],vt1*5+1,j*3+2);

						Sleep(delay);

					//Doi cho o trong voi o co gia tri trong ma tran
					temp = Matrix[vt1][j];
					Matrix[vt1][j] = Matrix[vt2][j];
					Matrix[vt2][j]= temp;
					themSo = true;
				}
			}
		}
	}
}

void Choi()
{
	int i, j;
	ifstream inScore("Score.txt");
	inScore >> highScore;
	inScore.close();
	
	char move;
	//Khoi tao gia tri ban dau bang 0
	for (i=0; i<4; i++){
		for (j=0; j<4; j++){
			Matrix[i][j]=0;
		}
	}
	ThemSo();
	do{
		XoaManHinh();
		InBang();
		move=getch();//Doc 1 ki tu tu ban phim
		int x=(int)move;
		themSo = false;
		switch(x){
			case 80:Down();		break;
			case 72:Up();		break;
			case 77:Right();	break;
			case 75:Left();		break;

		}
		if (themSo) ThemSo();
		if (x==27) break;

	}while (!ThuaCuoc());
	XoaManHinh();
	InBang();
	if (score>highScore){
		ofstream outScore("Score.in");
		outScore << score;
		outScore.close();
		cout << "   --->> Ki luc moi!!!";
	}
	DrawString("THUA CUOC !!!!!!!!!!!!!!!!",30,6);

}



int main()
{

    cc.character = ' ' ;
    srand(time(0));
	char chon='c';

	Logo();
	system("cls");

	HuongDan();
	system("cls");

	while (chon=='c'){
		cout << "BAT DAU!!!";
		score =0;
		Sleep(1000);
		system("cls");
		TaoKhung();
		Choi();
		do {
			DrawString("Ban co muon choi tiep?",30,8);

			DrawString("Co/Khong (c/k): ",30,9);

			chon = getch();
		}while(!(chon=='c' || chon=='k'));
	}
	system("cls");
	cout << "\n\n\n\t\tKET THUC TRO CHOI!!!!!!!!!!!\n\n\n\n\n";
	system("pause");
	return 0;
}
