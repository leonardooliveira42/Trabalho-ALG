#include <stdio.h>
#include <conio.h>
#include <time.h>

int map[5][10] = {{0,0,0,0,3,3,3,0,0,0},{2,2,2,2,1,0,3,3,0,0},{2,2,2,0,1,0,4,4,4,4},{0,2,1,1,1,1,4,5,5,5},{0,0,2,0,1,4,4,5,5,5}};
//PARA REFERENCIAR A MATRIZ LEMBRAR QUE E [Y][X] NAS POSIÇÕES
struct pos{
	int x;
	int y
};

struct pos posP;
struct pos posT;

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
	}while(!map[y][x] || (posP.x == x && posP.y == y);
	posT.x = x;
	posT.y = y;
}
int randProb(int mod){
	srand(time(NULL));
	return rand()%mod;
}

int main(){
	
}