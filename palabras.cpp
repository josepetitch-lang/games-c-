#include <iostream>
#include <fstream>

using namespace std;

int main(){
	//crea y abre un archivo
	ofstream archivo("palabras.txt");
	
	if(archivo.is_open()){
		archivo << "bateria\n";
		archivo << "computadora\n";
		archivo << "pantalla\n";
		archivo << "cargador\n";
		archivo << "puerta\n";
		archivo << "luz\n";		
		archivo.close(); //cerramos el archivo
	    cout << "archivo.txt creado" << endl;
	} else {
		cout << "Error al intentaer crear el archivo.txt" << endl;
	}
	return 0;
}
