#include <locale.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77
#define ESC 27

int cuerpo[200][2];
int n = 1;
int tam = 5; 
int x = 10, y = 12;
int dir = 3;
int xc = 30, yc = 15;
char tecla;
int velocidad = 100, h = 1;
int score = 0;

void gotoxy(int x, int y){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

// Oculta el cursor de la consola para evitar el parpadeo molesto
void ocultarCursor(){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

void pintar(){
    for (int i = 2; i < 78; i++){
        gotoxy(i,3); printf("%c", 205);
        gotoxy(i,23); printf("%c", 205);
    }
    for (int i = 4; i < 23; i++){
        gotoxy(2,i); printf("%c", 186);
        gotoxy(77,i); printf("%c", 186);
    }
    
    gotoxy(2,3); printf("%c", 201);
    gotoxy(2,23); printf("%c", 200);
    gotoxy(77,3); printf("%c", 187);
    gotoxy(77,23); printf("%c", 188);
}

void guardar_posicion(){
    cuerpo[n][0] = x;
    cuerpo[n][1] = y;
    n++;
    if(n == tam) n = 1;
}

void borrar_cuerpo(){
    gotoxy(cuerpo[n][0], cuerpo[n][1]); printf(" ");
}

void pintar_cuerpo(){
    for (int i = 1; i < tam; i++){
        gotoxy(cuerpo[i][0], cuerpo[i][1]); 
        if (i == n - 1 || (n == 1 && i == tam - 1)) {
            printf("O"); // cabeza
        } else {
            printf("*"); // cuerpo
        }
    }
}

void teclear(){
    if(kbhit()){
        tecla = getch();
        // evita que la tecla especial arroje valores dobles de las flechas
        if (tecla == -32 || tecla == 0) tecla = getch(); 

        switch(tecla){
            case ARRIBA:
                if (dir != 2) dir = 1;
                break;
            case ABAJO:
                if (dir != 1) dir = 2;
                break;
            case DERECHA:
                if (dir != 4) dir = 3;
                break;
            case IZQUIERDA:
                if (dir != 3) dir = 4;
                break;
        }
    }
}

void cambiar_velocidad(){
    if(score == h * 20){
        if (velocidad > 20) velocidad -= 15; // protegemos que la velocidad no sea <= 0
        h++;
    }
}

void comida(){
    if(x == xc && y == yc){   
        gotoxy(xc, yc); printf(" ");

        bool enCuerpo;
        do {
            enCuerpo = false;
            xc = (rand() % 73) + 3; // coordenada X entre 3 y 75 (dentro del borde)
            yc = (rand() % 18) + 4; // coordenada Y entre 4 y 21 (dentro del borde)
            
            for(int i = 0; i < tam; i++){
                if(cuerpo[i][0] == xc && cuerpo[i][1] == yc){
                    enCuerpo = true;
                    break;
                }
            }
        } while(enCuerpo);
        
      
        if (tam < 199) tam++;
        score += 10;
       
        gotoxy(xc, yc); printf("%c", 254);
        
        cambiar_velocidad();
    }
}

bool game_over(){
    // choque con los bordes
    if (y <= 3 || y >= 23 || x <= 2 || x >= 77) return false;
    
    // choque con el propio cuerpo (omitimos la posición actual)
    for (int j = 1; j < tam; j++){
        if (j != n && cuerpo[j][0] == x && cuerpo[j][1] == y){
            return false;
        }
    }
    return true;
}

void puntos(){
    gotoxy(3,1); printf("SCORE: %d | VELOCIDAD: %d ms   ", score, velocidad);
}

int main(){
    setlocale(LC_ALL, "");
    srand(time(NULL)); 
    ocultarCursor();
    
    pintar();
    gotoxy(xc, yc); printf("%c", 4);
    
    // Inicializar el cuerpo detrás de la cabeza
    for(int i = 0; i < tam; i++) {
        cuerpo[i][0] = x - i;
        cuerpo[i][1] = y;
    }

    while(tecla != ESC && game_over()){
        borrar_cuerpo();
        guardar_posicion();
        pintar_cuerpo();
        
        comida();
        puntos();
        teclear();
    
        if(dir == 1) y--;
        if(dir == 2) y++;
        if(dir == 3) x++;
        if(dir == 4) x--;
        
        Sleep(velocidad);
    }
    
    system("title: Snake Game");
    system("cls");
    gotoxy(34, 12); printf("GAME OVER");
    gotoxy(31, 15); printf("Score final: %d", score);
    gotoxy(25, 18); printf("Thx for playin', this was developed by j4zyln2: ");
    cout << "see ya" << endl;
    system("pause");
    return 0;
}
