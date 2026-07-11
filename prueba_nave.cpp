#include <stdio.h> 
#include <windows.h>
#include <conio.h> 
#include <stdlib.h>
#include <list>
#include <locale>
using namespace std;

# define ARRIBA 72
# define IZQUIERDA 75
# define DERECHA 77
# define ABAJO 80

// variable gotoxy vacio
void gotoxy(int x, int y) {

	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);

}

//nos permite ocultar el cursor al ejecutarlo en terminal o cmd
void OcultarCursor(){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon,&cci);
	
}

// creación de la clase nave, atributos y funciones (POO)
class NAVE{
    int x, y;
    int corazones;
    int vidas;
public:
	NAVE(int _x, int _y, int _corazones, int _vidas): x(_x), y(_y), corazones(_corazones), vidas(_vidas) {}
	int X () {return x;}
	int Y() {return y;}
	int VID() {return vidas;}
	void COR (){corazones --;}
	void pintar();
	void borrar();
	void mover();
	void pintar_corazones();
	void morir();
};

//funcion de pintar nave
void NAVE::pintar(){
	gotoxy(x, y);     printf("  ^  ");
    gotoxy(x, y + 1); printf(" / \\ ");
    gotoxy(x, y + 2); printf("-----");
}

//funcion de borrar nave
void NAVE::borrar(){
	gotoxy(x,y);   printf("     ");
	gotoxy(x,y+1); printf("     ");
	gotoxy(x,y+2); printf("     ");
}

//NAVE::NAVE(int _x, int _y): x(_x), y(_y)

//funcion de mover nave
void NAVE:: mover(){
	if (kbhit()) {
		char tecla = getch();
	    borrar();
		if (tecla == IZQUIERDA && x > 3) x--;
		if (tecla == DERECHA && x+6 < 77) x++;
		if (tecla == ARRIBA && y > 4) y--;
		if (tecla == ABAJO && y+3 < 23) y++;
		if (tecla == 'e') corazones--;
	    pintar();
	    pintar_corazones();
	}
}

//funcion de pintar los limites de la pantalla

void pintar_limites(){
    // Bordes horizontales
    for (int i = 3; i < 77; i++){
        gotoxy(i, 3);  printf("%c", 205); // Borde superior
        gotoxy(i, 32); printf("%c", 205); // Borde inferior (ajustado a 32)
    }
    // Bordes verticales
    for (int i = 4; i < 32; i++){
        gotoxy(3, i);  printf("%c", 186); // Borde izquierdo
        gotoxy(76, i); printf("%c", 186); // Borde derecho
    }
    // Esquinas
    gotoxy(3, 3);   printf("%c", 201);
    gotoxy(3, 32);  printf("%c", 200);
    gotoxy(76, 3);  printf("%c", 187);
    gotoxy(76, 32); printf("%c", 188);
}

//pintar los corazones del mapa e indicar vidas xd
void NAVE::pintar_corazones(){
    gotoxy(50, 1); printf("VIDAS %d", vidas); // Fila 1 (segura)
    gotoxy(64, 1); printf("Salud: ");         // Fila 1 (segura)
    
    gotoxy(71, 1); printf("      ");          // Limpiar área
    
    for (int i = 0; i < corazones; i++){
        gotoxy(71 + (i * 2), 1); printf("-"); //salud
}
}

//funcion de morir del juego
void NAVE::morir(){
	if (corazones <= 0){
		borrar();
		gotoxy(x,y);   printf("   **   ");
	    gotoxy(x,y+1); printf("  ****  ");
	    gotoxy(x,y+2); printf("   **   ");
	    Sleep(200);
	    
	    borrar();
	    gotoxy(x,y);   printf(" * **  *");
	    gotoxy(x,y+1); printf("  ****  ");
	    gotoxy(x,y+2); printf(" * **  *");
	    Sleep(200);
	    
	    borrar();
	    vidas--;
	    corazones = 3;
	    pintar_corazones();
	    pintar();
	    
	}
}

//clase asteroide 
class AST{
     int x, y;
public:
	AST (int _x, int _y): x(_x), y(_y) {}
	int X() {return x;}
	int Y() {return y;}
	void pintar();
	void mover();
	void borrar();
	void choque(class NAVE &N);
};
	
// funcion pintar asteroide

void AST::pintar(){
	gotoxy(x,y); printf("%c", 184);
}

// funcion mover asteroide

void AST::mover(){
	gotoxy(x,y); printf(" ");
	y++;
	if (y > 32){
		gotoxy(x, y-1); printf(" ");
		x = rand()%71 + 4;
		y = 4;
	}
	pintar();
} 

void AST::borrar(){
    gotoxy(x, y); printf(" ");
}

// funcion de choque de asteroide con la NAVE

void AST::choque(class NAVE &N){
	if (x >= N.X() && x < N.X()+6 && y >= N.Y() && y <= N.Y()+2){
		N.COR();
		N.pintar();
		N.pintar_corazones();
		x = rand()%71 + 4;
		y = 4;
	}
}

// clase bala para el disparo de la nave
class BALA{
	int x, y;
public:
	BALA(int _x, int _y): x(_x), y(_y) {}
	int X() {return x;}
	int Y() {return y;}
	void mover();
	bool fuera();
};

bool BALA::fuera(){
	if (y == 4) return true;
	return false;
}

void BALA::mover(){
	gotoxy(x,y); printf(" ");
	y--;
	gotoxy(x,y); printf("*");
}
//funcion principal
int main () {
	setlocale(LC_ALL, "");
	system("chcp 437 > nul");
    system("mode con: cols=80 lines=35");  //tamaño de la vetana
    
    // título a identificar la ventana
    system("title Juego de Naves");
    OcultarCursor();
    pintar_limites();
    NAVE N(7,7,3,3);
    N.pintar();
    N.pintar_corazones();
    
    list <AST*> A;
    list <AST*>::iterator itA;
    for(int i = 0; i < 5; i++){
        A.push_back(new AST(rand()%75 + 3, rand()%5 + 4));
    }
    
    list <BALA*> B;
    list <BALA*>::iterator it;
    
    bool game_over = false;
    int puntos = 0;
    
    while(!game_over) {
        gotoxy(4,2); printf("Puntos %d", puntos);
        
       
        if (kbhit()){
            char tecla = getch();
            if (tecla == 'a'){
                B.push_back(new BALA(N.X() + 2 ,N.Y() - 1 ));
            }
        }
        
        // balas 
        for (it = B.begin(); it != B.end(); ){
			(*it)->mover();	
			if((*it)-> fuera()){
				gotoxy((*it)->X(), (*it)->Y()); printf(" ");
				delete(*it);
				it = B.erase(it);
			} else {
				it++;
			}
		}
        
        // asteroides, movimiento y choque
        for (itA = A.begin(); itA != A.end(); itA++){
            (*itA)->mover();
            (*itA)->choque(N);      
        }
        
      
        for (itA = A.begin(); itA != A.end(); ){
            bool colisiono = false;
            for (it = B.begin(); it != B.end(); ){
                if((*itA)->X() == (*it)->X() && ((*itA)->Y() == (*it)->Y() || (*itA)->Y()+1 == (*it)->Y() )) {
                    
                    // Limpieza forzada del área del asteroide
                    gotoxy((*itA)->X(), (*itA)->Y()); printf(" ");
                    gotoxy((*it)->X(), (*it)->Y());   printf(" ");
                    
                    delete(*it);
                    it = B.erase(it);
                    
                    delete(*itA);
                    itA = A.erase(itA);
                    
                    A.push_back(new AST(rand()%72 + 4, 4)); 
                    puntos += 5;
                    
                    colisiono = true;
                    break;
                } else {
                    it++;
                }
            }
            if(!colisiono) itA++;
        }
        
        if (N.VID() == 0) game_over = true;
        N.morir();
        N.mover();
        Sleep(30);
    }
    
    system("cls"); // Limpiamos pantalla final
    printf("GAME OVER ");
	printf(":(");
    printf(" :Gracias por jugar: Developed by j4zyln2");
    return 0;
}
