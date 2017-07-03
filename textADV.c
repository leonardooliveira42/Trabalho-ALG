#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define bx 14
#define by 4
#define bW 50
#define bH 15
#define ty 6
#define tx 16
int invC = 6;
int map[5][10] = {{0,0,0,0,3,3,3,0,0,0},{2,2,2,2,1,0,3,3,0,0},{2,2,2,0,1,0,4,4,4,4},{0,2,1,1,1,1,4,5,5,5},{0,0,2,0,1,4,4,5,5,5}};
int inv[3] = {1,1,1};
/* 	0 chave
	1 mapa
	2 espada
 */
int procureFlag = 0;


struct pos{
	int x;
	int y;
};

int linesize = (bx+bW-2)-(bx+2);


struct pos posP;
struct pos posT;

void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void respBox(){
	int i;
	char vert = (char)186;
	char hori = (char)205;
	char c1 = (char)201;
	char c2 = (char)187;
	char c3 = (char)200;
	char c4 = (char)188;
	gotoxy(bx+1,by+bH-3); 		printf("%c",c1);
	gotoxy(bx+bW-1,by+bH-3);	printf("%c",c2);
	gotoxy(bx+1,by+bH-1);		printf("%c",c3);
	gotoxy(bx+bW-1,by+bH-1);	printf("%c",c4);
	for(i=bx+2;i<bx+bW-1;i++){
		gotoxy(i,by+bH-3);
		printf("%c",hori);
		gotoxy(i,by+bH-1);
		printf("%c",hori);
	}
	gotoxy(bx+1,by+bH-2); 	printf("%c",vert);
	gotoxy(bx+bW-1,by+bH-2); 	printf("%c",vert);
	gotoxy(bx+2,by+bH-2); //bota o cursor para user input
}
void borda(){
	char vert = (char)186;
	char hori = (char)205;
	int i;
	gotoxy(0,0);
	char c1 = (char)201;
	gotoxy(bx,by); printf("%c",c1);
	char c2 = (char)187; 
	gotoxy(bx+bW,by); printf("%c",c2);
	char c3 = (char)200;
	gotoxy(bx,by+bH); printf("%c",c3);
	char c4 = (char)188;
	gotoxy(bx+bW,by+bH); printf("%c",c4);
	for(i=bx+1;i<bx+bW;i++){
		gotoxy(i,by);
		printf("%c",hori);
		gotoxy(i,by+bH);
		printf("%c",hori);
	}
	for(i=by+1;i<by+bH;i++){
		gotoxy(bx,i);
		printf("%c",vert);
		gotoxy(bx+bW,i);
		printf("%c",vert);
	}
}
void boxWrite(char str[]){
	system("cls");
	gotoxy(0,1);
	printf("col %d,lin %d",posP.x, posP.y);
	gotoxy(0,2);
	printf("col %d,lin %d",posT.x, posT.y);
	borda();
	int i,j;
	int size = (int)strlen(str);
	char t1[linesize];
	int lin = size/linesize;
	int rest = size%linesize;
	for(i = 0; i<lin;i++){
		gotoxy(tx,ty+i);
		for(j = linesize*i;j<(linesize*i)+linesize;j++){
			printf("%c",str[j]);
		}
	}
	gotoxy(tx,ty+i);
	for(i = (linesize*i);i<size;i++){
		printf("%c",str[i]);
	}
	respBox();
}
char getResposta(char str[]){
	if(strstr(str,"Norte") != NULL || strstr(str,"norte")!= NULL)
		return 'N';
	if(strstr(str,"Sul") != NULL || strstr(str,"sul")!= NULL)
		return 'S';
	if(strstr(str,"Leste") != NULL || strstr(str,"leste")!= NULL)
		return 'L';
	if(strstr(str,"Oeste") != NULL || strstr(str,"oeste")!= NULL)
		return 'O';
	if(strstr(str,"Atacar") != NULL || strstr(str,"atacar")!= NULL)
		return 'A';
	if(strstr(str,"Fugir") != NULL || strstr(str,"fugir")!= NULL)
		return 'F';
	if(strstr(str,"Procurar") != NULL || strstr(str,"procurar")!= NULL)
		return 'P';
	if(strstr(str,"Inventario") != NULL || strstr(str,"inventario")!= NULL)
		return 'I';
	if(strstr(str,"Mapa") != NULL || strstr(str,"mapa")!= NULL)
		return 'M';
	
	return ' ';
}
void startRandPos(){
	srand(time(NULL));
	int x,y;
	do{
		y = rand()%5;
		x = rand()%10;
	}while(!map[y][x]);
	posP.x = x;
	posP.y = y;
	do{
		y = rand()%5;
		x = rand()%10;
	}while(!map[y][x] || (posP.x == x && posP.y == y));
	posT.x = x;
	posT.y = y;
}
int randProb(int mod){
	srand(time(NULL));
	return rand()%mod;
}
int moveTo(char r){
	if(r == 'N'){
		if(map[posP.y-1][posP.x])
			posP.y-=1;
		else
			return 0;
	}
	else{
		if(r == 'S'){
			if(map[posP.y+1][posP.x])
				posP.y +=1;
			else
				return 0;
		}
		else{
			if(r == 'L'){
				if(map[posP.y][posP.x+1])
					posP.x +=1;
				else
					return 0;
			}
			else{
				if(map[posP.y][posP.x-1])
					posP.x -=1;
				else
					return 0;
			}	
		}
	}
	return map[posP.y][posP.x];
}
void verInventario(char str[]){
	int i;
	for(i = 0; i<3 ;i++){
		switch(i){
			case 0:
				if(inv[i])
					strcat(str," Chave ");
			break;
			case 1:
				if(inv[i])
					strcat(str," Mapa ");
			break;
			case 2:
				if(inv[i])
					strcat(str," Espada ");
			break;
		}
	}
}
void procurar(){
	int i;
	if(randProb(4) == 1 && !inv[0] && map[posP.y][posP.x] == 3){
		boxWrite("Em uma arvore seca voce encontra um corpo vestido com uma armadura com uma chave pendurada em um cordao... Voce coleta a chave.");
		getch();
		inv[0] = 1;
		return;
	}
	if(randProb(5) == 1 && !inv[1] && map[posP.y][posP.x] == 2){
		boxWrite("Cavando um buraco no chao de areia, foi possivel encontrar uma garrafa com um mapa dentro!");
		getch();
		inv[1] = 1;
		return;
	}
	if(randProb(5) == 1 && !inv[2] && map[posP.y][posP.x] == 4){
		boxWrite("Voce procurou nas redondezas e achou um bau prateado... Ao abri-lo encontrou uma espada reluzente!");
		getch();
		inv[2] = 1;
		return;
	}
	boxWrite("Voce nao encontrou nada na area...");
	getch();
	procureFlag=1;
}
void verMapa(){
	system("cls");
	borda();
	int i,j;
	for(i = 0; i<5;i++){
		gotoxy(24,9+i);
		for(j = 0; j<10;j++){
			if(map[i][j] == 0)
				printf(" @ ");
			else{
				if(j == posP.x && i == posP.y)
					printf("|X|");
				else
					printf("| |");
			}
			
		}
	}
	gotoxy(16,17);
	printf("| | = caminho  X = voce  @ = caminho bloqueado");
	getch();
}
int opcoesPadrao(char r){
	if(r == 'N' || r == 'S' || r == 'L' || r == 'O'){
		if(moveTo(r))
			return 1;
		else{
			boxWrite("Nao e possivel prosseguir nessa direcao...");
			getch();
		}
	}else{
		if(r == 'I'){
			char str[100] = "Inventario: ";
			verInventario(str);
			
			boxWrite(str);
			getch();
		}else{
			if(r == 'P'){
				if(procureFlag){
					boxWrite("Voce ja procurou nessa area...");
					getch();
				}else
					procurar();
			}else{
				if(r == 'M'){
					if(inv[1]){
						verMapa();
					}else{
						boxWrite("Voce nao possui um mapa...");
						getch();
					}
				}
				
			}
		}
		
	}
		
}
int floresta(int var){
	switch(var){
		case 0:
				boxWrite("Voce se encontra em uma clareira de uma floresta densa, a ausencia de som causa desconforto, entretanto, o ambiente nao aparenta ser amedontrador...");
			break;
		case 1:
				boxWrite("A floresta na qual voce se encontra parece se extender por varios kilometros, existem diversos arbustos frondosos a sua volta...");
			break;
		case 2:
				boxWrite("Diversos galhos frondosos obstruem sua visao, enquanto seus pulmoes se enchem com o ar fresco da floresta... Voce pode sentir o vento agitando a copa das arvores acima de voce...");
			break;
		case 3:
				boxWrite("Voce encontra uma pequena clareira na densa floresta, onde voce consegue brevemente descancar...");
			break;
	}
	return 0;
}
int deserto(int var){
	switch(var){
		case 0:
				boxWrite("Voce consegue observar um horizonte interminavel repleto de dunas de areia fina...");
			break;
		case 1:
				boxWrite("Durante sua travessia uma breve tempestade de areia te desorientou e te fez perder o sentido que estava caminhando...");
			break;
		case 2:
				boxWrite("A longa caminhada pelo seco deserto resseca totalmente seu corpo, aumentando cada vez mais sua vontade de beber agua...");
			break;
		case 3:
				return 1;
			break;
	}
	return 0;
}
int pantano(int var){
	switch(var){
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:	
			break;
	}
	return 0;
}
int caverna(int var){
	switch(var){
		case 0:
				
			break;
		case 1:
				
			break;
		case 2:
				
			break;
		case 3:
				
			break;
	}
	return 0;
}
int planice(int var){
	switch(var){
		case 0:
				
			break;
		case 1:
				
			break;
		case 2:
				
			break;
		case 3:
				
			break;
	}
	return 0;
}
int encontro(){
	boxWrite("Voce encontra um monstro... o que deseja fazer?");
	char str[44];
	scanf("%s",str);
	char r = getResposta(str);
	if(r == 'F'){
		boxWrite("Voce conseguiu fugir com sucesso do monstro!");
		getch();
		return 0;
	}else{
		if(r == 'A'){
			if(inv[2]){
				boxWrite("Voce atacou o monstro com a espada e o derrotou!");
				getch();
				if(!inv[0]){
					boxWrite("Preso nos dentes do monstro voce retira uma chave!");
					inv[0] = 1;
				}
				return 0;
			}else{
				boxWrite("Voce tentou atacar o monstro de maos vazias e acabou sendo devorado...");
				getch();
				return 1;
			}
		}else{
			boxWrite("Voce nao conseguiu realizar tal acao e foi devorado pelo monstro...");
			getch();
			return 1;
		}
	}
	return 0;
}
int tileStart(){
	int tileType = map[posP.y][posP.x];
	int randVar = randProb(4);
	int r = 0;
	int v = 0;
	char str[44];
	char resp;
	procureFlag = 0;
	if(randProb(10)==1){
		v = encontro();
	}
	if(!v){
		do{
			switch(tileType){
				case 1:
						r = floresta(randVar);
					break;
				case 2:
						r = deserto(randVar);
					break;
				case 3:
						r = pantano(randVar);
					break;
				case 4:
						r = caverna(randVar);
					break;
				case 5:
						r = planice(randVar);
					break;
			}
			if(!r){
				scanf("%s",str);
				resp = getResposta(str);
				if(opcoesPadrao(resp)==1){
					//moveTo conseguiu retorno
					r = 1;
				}else{
					r = 0;
				}	
			}
		}while(r!=1);
	}else
		return 0;
	return 1;
	
}
int main(){
	system("chcp 65001");
	system("cls");
	startRandPos();
	posP.x = 4;
	posT.x = 4;
	posT.y = 1;
	posP.y = 3;
	boxWrite("    Jogo da Aventura - Encontre o tesouro!        Pressione qualquer tecla para iniciar...");
	getch();
	int v=1;
	while(v){
		if(posP.x == posT.x && posP.y == posT.y){
			if(inv[0]){
				boxWrite("Você encontrou um bau e o abriu com sua chave...");
				getch();
				v = 2;
				break;
			}else{
				boxWrite("Voce observa que o bau necessita de uma chave para abri-lo... Voce decide deixa-lo ali por enquanto..");
				getch();
			}
			
		}
		v = tileStart();
		system("cls");
	}
	if(v){
		boxWrite("Voce encontrou o tesouro!!!");
	}else{
		boxWrite("Voce esta morto...");
	}
	gotoxy(16,17);
	printf("<FIM DE JOGO>");
	getch();
	
}

