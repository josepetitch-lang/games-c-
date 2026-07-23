#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

string palabra_original;
string palabra_mostrar;
int vidas;
int n;

void mostrar();
void ingresar(char x);
void iniciar();
string obtener_palabra_aleatoria();
vector<string> obtener_coleccion_de_palabras();
int obtener_numero_aleatorio_menor(int b);

void mostrar(){
    cout << "Vidas: " << vidas << endl; 
    cout << palabra_mostrar << endl;
}

void iniciar(){
    vidas = 6;
    palabra_original = obtener_palabra_aleatoria();

   
    for(int i = 0; i < palabra_original.length(); i++){
        if(palabra_original[i] >= 'A' && palabra_original[i] <= 'Z'){
            palabra_original[i] += 32; 
        }
    }


    for(int i = 0; i < palabra_original.length(); i++){
        if(palabra_original[i] >= 'a' && palabra_original[i] <= 'z'){
            palabra_mostrar += '-';
        } else {
            palabra_mostrar += palabra_original[i];
        }
    }
}

void ingresar(char x){
    bool perdiVidas = true;

    for(int i = 0; i < palabra_original.length(); i++){
        if(x == palabra_original[i]){
            perdiVidas = false;
            palabra_mostrar[i] = x;
        }
    }

    if(perdiVidas) vidas--;
       
    n = vidas + 1;
       
    switch(n){
        case 6:               
            printf("\n %c%c%c%c%c  ",194,196,196,196,191);
            printf("\n |   O  ");
            printf("\n |      ");
            printf("\n %c      ",193); 
            break;
      
        case 5:               
            printf("\n %c%c%c%c%c  ",194,196,196,196,191);
            printf("\n |   O  ");
            printf("\n |   |  ");
            printf("\n %c      ",193); 
            break;
        
        case 4:               
            printf("\n %c%c%c%c%c  ",194,196,196,196,191);
            printf("\n |   O  ");
            printf("\n |  /|  ");
            printf("\n %c      ",193);
            break;
       
        case 3:               
            printf("\n %c%c%c%c%c  ",194,196,196,196,191);
            printf("\n |   O  ");
            printf("\n |  /|%c ",92);
            printf("\n %c      ",193); 
            break;
        
        case 2:               
            printf("\n %c%c%c%c%c  ",194,196,196,196,191);
            printf("\n |   O   ");                    
            printf("\n |  /|%c ",92); 
            printf("\n %c  /   ",193);
            break;
       
        case 1:               
            printf("\n %c%c%c%c%c  ",194,196,196,196,191);
            printf("\n |   O  ");
            printf("\n |  /|%c ",92);
            printf("\n %c  / %c ",193,92); 
            break;
            
        default: 
            break;
    }
}

vector<string> obtener_coleccion_de_palabras(){
    vector<string> palabras;
    ifstream file_input_stream("palabras.txt");
    
    
    if (!file_input_stream.is_open()) {
        cout << "Error: No se pudo abrir el archivo 'palabras.txt'." << endl;
        cout << "Asegurate de crearlo en la misma carpeta." << endl;
        exit(1); // Cierra el programa si falta el archivo
    }
    
    string palabra;
    while(file_input_stream >> palabra)
        palabras.push_back(palabra);
    
    file_input_stream.close();
    
    
    if (palabras.empty()) {
        cout << "Error: El archivo 'palabras.txt' esta vacio." << endl;
        exit(1);
    }
    
    return palabras;
}

int obtener_numero_aleatorio_menor(int b){
    int numero_aleatorio = rand(); 
    return numero_aleatorio % b;
}

string obtener_palabra_aleatoria(){
    vector<string> palabras = obtener_coleccion_de_palabras();
    int numero_aleatorio = obtener_numero_aleatorio_menor(palabras.size());
    return palabras[numero_aleatorio];
}

int main(){
   
    srand(time(0)); 

    iniciar();
    
    system("title Ahorcado C++");
    system("cls");
    
    // Mostrar estado inicial del monigote con 6 vidas
    switch(vidas + 1){
    case 6:               
            printf("\n %c%c%c%c%c  ",194,196,196,196,191);
            printf("\n |   O  ");
            printf("\n |      ");
            printf("\n %c      ",193); 
            break;
    }
    cout << endl;
    mostrar();

    while(vidas > 0 && palabra_mostrar != palabra_original){
        char x; 
        cin >> x;
        system("title Ahorcado C++");
        system("cls");
        ingresar(x);
        mostrar();
    }

    if(vidas > 0)  
        cout << "Ganaste" << endl;
    else 
        cout << "Perdiste, la palabra era: " << palabra_original << endl;

    return 0;
}
