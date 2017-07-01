#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


#define TELA_W 50
#define TELA_H 25
int tela[TELA_W][TELA_H];
int pontos = 0;
struct pos{
	int x;
	int y;
	int s;
};

struct ball{
	int x;
	int y;
	int dirx;
	int diry;
};

struct pos pos1;
struct pos pos2;
struct ball bola;

int randDir(){
	srand(time(NULL));
	int a = rand()%2;
	if(a) return 1;
	else return -1;
}
	
void delay(int ms)
{
    long pause;
    clock_t now,then;

    pause = ms*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
char inputTeclado(char *ch){
	DWORD start_time, check_time;
	
	start_time=GetTickCount();
	check_time=start_time+1;
	char c;
	*ch = 0;

	while (check_time>GetTickCount()) {
		if (kbhit()) {
			*ch = getch();
			//while ((c = getch()) != '\n' && c != EOF) { }
			break;
		}
		else{
			*ch = 0;
		}
	}
}
void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void borda(){
	int i;
	gotoxy(0,0);
	char c1 = (char)201;
	gotoxy(1,1); printf("%c",c1);
	char c2 = (char)187; 
	gotoxy(79,1); printf("%c",c2);
	char c3 = (char)200;
	gotoxy(1,23); printf("%c",c3);
	char c4 = (char)188;
	gotoxy(79,23); printf("%c",c4);
	

}
void setup(){
	pos1.x = 10;
	pos1.y = 10;
	pos1.s = 4;
	
	pos2.x = 70;
	pos2.y = 10;
	pos2.s = 4;
	
	bola.x = 40;
	bola.y = 12;
	bola.dirx = randDir();
	bola.diry = randDir();
	system("cls");
	int i,j;
	for(i = 0; i<TELA_W; i++){
		for(j = 0; j<TELA_H; j++){
			tela[i][j] = 0;
		}
	}
	for(i = pos1.y; i<pos1.y+pos1.s; i++){
		tela[pos1.x][i] = 1;
	}
	tela[(int)bola.x][(int)bola.y] = 2;
	/*for(i = pos2.y; i<pos2.y+pos2.s; i++){
		tela[pos2.x][i] = 1;
	}*/
}
void updateBola(){
	int x = bola.x;
	int y = bola.y;
	//Colisão com as bordas da tela
	if(bola.y >= TELA_H-3 || bola.y <= 2){
		bola.diry=-bola.diry;
	}
	if(bola.x >= TELA_W-3 || bola.x <= 2){
		bola.dirx=-bola.dirx;
	}
	//Colisão com o jogador
	if((bola.y>=pos1.y && bola.y<=pos1.y+pos1.s && bola.x <= pos1.x+1)){
		bola.dirx=-bola.dirx;
		pontos+=10;
	}
	
	bola.x+=bola.dirx;
	bola.y+=bola.diry;
	tela[bola.x][bola.y] = 2;
	tela[x][y]=0;
	gotoxy(0,0);
	printf("Pontos: %d", pontos);
}
void desenharTela(){
	int i, j;
	for(i = 0; i<TELA_W; i++){
		for(j = 0; j<TELA_H; j++){
			if(tela[i][j]){
				gotoxy(i,j);
				printf("%c",219);
			}
			if(tela[i][j] == 2){
				gotoxy(i,j);
				printf("O");
			}
		}
	}
	for(i = pos1.y; i<pos1.y+pos1.s; i++){
		tela[pos1.x][i] = 1;
	}
	tela[(int)bola.x][(int)bola.y] = 2;
	
	/*for(i = pos2.y; i<pos2.y+pos2.s; i++){
		tela[pos2.x][i] = 1;
	}*/
}
int testEnd(){
	if(bola.x<pos1.x-1) return 1;
	return 0;
}
int main(){
	setup();
	char ch1,ch2;
	system("chcp 65001");
	system("pause");
	gotoxy(0,0);
	printf("Pontos: 0");
	int end = 0;
	while(1){ //game loop principal
		borda();
		inputTeclado(&ch1);
		//inputTeclado(&ch2);
		if(ch1 == 'w' && pos1.y>=3){ 
			pos1.y-=1;
			tela[pos1.x][pos1.y+pos1.s]=0;
			
		}
		if(ch1 == 's' && pos1.y<=TELA_H-7){
			pos1.y+=1;
			tela[pos1.x][pos1.y-1]=0;
		}
		/*
		if(ch2 == 'i'){ 
			pos2.y-=1;
			tela[pos2.x][pos2.y+pos2.s]=0;
			
		}
		if(ch2 == 'k'){
			pos2.y+=1;
			tela[pos2.x][pos2.y-1]=0;
		}*/
		updateBola();
		desenharTela();
		end = testEnd();
		if(end)break;
		delay(80);
		system("cls");
		ch1 = 0;
		ch2 = 0;
	}
	if(end){
		gotoxy(30,10);
		printf("Fim do jogo!");
		gotoxy(80,0);
		getch();
	}
	
}

