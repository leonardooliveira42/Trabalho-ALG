#include <stdio.h> 					//TITULO PARA O SNAKE E PARA O PONG 
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define TELA_W 80
#define TELA_H 25
int pontos = 0;
int dir = 0;
int tam =3;

struct pos{
	int x;
	int y;
};

struct pos head[500];
struct pos fruta;

int ini [5][23] =  {1,1,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,1,0,1,1,1,1,
					1,0,0,0,1,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,
					1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,0,1,1,0,0,
					0,0,1,0,1,0,0,1,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,
					1,1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,1,1,1};
					
int teclaw[3][5]  ={'|',' ',' ',' ','|',
					'|',' ',' ',' ','|',
					'|',' ',' ','W','|',};
					
int teclas[3][5]  ={'|',' ',' ',' ','|',
					'|',' ',' ',' ','|',
					'|',' ',' ','S','|',};
					
int teclaa[3][5]  ={'|',' ',' ',' ','|',
					'|',' ',' ',' ','|',
					'|',' ',' ','A','|',};
					
int teclad[3][5]  ={'|',' ',' ',' ','|',
					'|',' ',' ',' ','|',
					'|',' ',' ','D','|',};					
										
										

int randDir(){
	srand(time(NULL));
	int a = rand()%4;
	return a;
	//0 = direita (1,0)
	//1 = cima (0,1)
	//2 = esquerda (-1,0)
	//3 = baixo (0,-1)
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
	char vert = (char)184;
	char hori = (char)205;
	int i;
	gotoxy(0,0);
	printf("Pontos: %d", (tam-3)*10);
	char c1 = (char)201;
	gotoxy(1,1); printf("%c",c1);
	char c2 = (char)187; 
	gotoxy(79,1); printf("%c",c2);
	char c3 = (char)200;
	gotoxy(1,23); printf("%c",c3);
	char c4 = (char)188;
	gotoxy(79,23); printf("%c",c4);
	

}
void setFruta(){
	srand(time(NULL));
	fruta.x = 6+rand()%(TELA_W - 12);
	fruta.y = 6+rand()%(TELA_H - 12);
}
void setup(){
	int i,j;
	struct pos s1;
	s1.x = 10;
	struct pos s2;
	s2.x = 9;
	struct pos s3;
	s3.x = 8;
	s1.y = s2.y = s3.y = 6;
	head[0] = s1;
	head[1] = s2;
	head[2] = s3;
	setFruta();
	dir = randDir();
	if(dir==2) dir = 0;
	
	system("cls");
	
}
void updateSnake(){
	int i;
	if(fruta.x == head[0].x && fruta.y == head[0].y){
		tam++;
		setFruta();
	}
	for(i = tam; i>0;i--){
		head[i] = head[i-1];
	}
	if(dir == 0) head[0].x++;
	if(dir == 1) head[0].y--;
	if(dir == 2) head[0].x--;
	if(dir == 3) head[0].y++;
}
void desenharTela(){
	int i, j;
	for(i = 0; i<tam; i++){
		gotoxy(head[i].x,head[i].y);
		if(i)
			printf("#");
		else
			printf("@");
		
	}
	gotoxy(fruta.x,fruta.y);
	printf("O");
}
int testEnd(){
	int i;
	for(i = tam; i>0; i--){
		if((head[0].x == head[i].x) && (head[0].y == head[i].y)){
			return 1;
		}
	}
	if((head[0].x == 1 || head[0].y == 1 || head[0].y == 23 || head[0].x == 79)) //bordas 
		return 1;
	return 0;
}
void checkKeys(char ch){
	if(ch == 'w' && dir != 3){ 
		dir = 1;	
	}else{
		if(ch == 's' && dir != 1){
			dir = 3;
		}else{
			if(ch == 'd' && dir != 2){
				dir = 0;
			}else{
				if(ch == 'a' && dir != 0){
					dir = 2;
				}
			}
		}
	}
}

void inicio(){		//Inicio do jogo
	
	int i, j; 
	
	for	(i = 0; i < 5; i++)
		for(j = 0; j < 23; j++)	
			if(ini[i][j] == 1) {
				gotoxy(j+10,i+2);
				printf("#");}
				
	for(i = 0; i < 3; i++)
		for(j = 0; j < 5; j++){
			gotoxy(j+10,i+9);
			printf("%c",teclaw[i][j]);
		}
	for(i = 0; i < 3; i++)
		for(j = 0; j < 5; j++){
			gotoxy(j+16,i+9);
			printf("%c",teclas[i][j]);
			if(i == 1) printf("\tPressione W e S para subir e descer.");
		}
		
	for(i = 0; i < 3; i++)
		for(j = 0; j < 5; j++){
			gotoxy(j+10,i+14);
			printf("%c",teclaa[i][j]);
		}
	for(i = 0; i < 3; i++)
		for(j = 0; j < 5; j++){
			gotoxy(j+16,i+14);
			printf("%c",teclad[i][j]);
			if(i == 1) printf("\tPressione A e D para ir p/ os lados");
		}
		
	printf("\n\n\tSe a cabeça da cobra bater em alguma parede, ou na propria calda\n\tO jogo acaba!");
	printf("\n\tPegue as comidas que aparecem aleatoriamente\n\tPara aumentar o tamanho da cobra, e os pontos.");
	printf("\n\n\t") ;
	
}

int main(){
	setup();
	char ch;
	//system("chcp 65001");
	inicio(); 	
	system("pause");
	gotoxy(0,0);
	printf("Pontos: 0");
	int end = 0;
	while(1){ //game loop principal
		borda();
		
		inputTeclado(&ch);
		checkKeys(ch);
		updateSnake();
		desenharTela();
		end = testEnd();
		if(end) break;
		delay(160);
		system("cls");
		ch = 0;
	}
	if(end){
		gotoxy(30,10);
		printf("Fim do jogo!");
		gotoxy(80,0);
		getch();
	}
	
	
}

