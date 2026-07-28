#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <locale>

struct Habitacion {
    std::string descripcion;
    std::string pista;
    std::map<std::string, std::string> salidas; // "norte", "sur", etc.
    bool explorada = false;
    
    Habitacion(std::string d = "", std::string p = "", std::map<std::string, std::string> s = {})
        : descripcion(d), pista(p), salidas(s), explorada(false) {}
};

class MisteryMansion {
private:
    std::map<std::string, Habitacion> mansion;
    std::string habitacionActual;
    std::vector<std::string> inventarioPistas;
    bool juegoTerminado;

public:
    MisteryMansion() {
        juegoTerminado = false;
        habitacionActual = "Recibidor";

       
        mansion["Recibidor"] = {
            "Te encuentras en la entrada principal. Un candelabro parpadea en el techo.",
            "Hay un diario viejo que menciona la biblioteca.",
            {{"norte", "Biblioteca"}, {"este", "Cocina"}}
        };

        mansion["Biblioteca"] = {
            "Filas de libros cubiertos de polvo. Hay un pasadizo secreto detrás de un estante.",
            "Un libro de C++ tiene una llave dorada oculta entre sus páginas.",
            {{"sur", "Recibidor"}, {"secreto", "Sotano"}}
        };

        mansion["Cocina"] = {
            "Platos rotos y olor a medicina rancia.",
            "Una nota rápida dice: 'La llave abre la puerta del sótano'.",
            {{"oeste", "Recibidor"}}
        };

        mansion["Sotano"] = {
            "¡El laboratorio secreto! Has encontrado el misterio de la mansión.",
            "¡FELICIDADES! Resolviste el misterio.",
            {}
        };
    }

    void iniciar() {
        std::cout << "=== MISTERY MANSION: DS EDITION ===" << std::endl;
        std::cout << "Explora la mansión, junta pistas y descubre el secreto.\n" << std::endl;

        while (!juegoTerminado) {
            Habitacion& actual = mansion[habitacionActual];
            std::cout << "\n[ Ubicación: " << habitacionActual << " ]" << std::endl;
            std::cout << actual.descripcion << std::endl;

            std::cout << "\n¿Qué deseas hacer? (escribir 'buscar', 'ir [direccion]', 'pistas', 'salir'): ";
            std::string accion;
            std::cin >> accion;

            if (accion == "buscar") {
                if (!actual.explorada) {
                    actual.explorada = true;
                    inventarioPistas.push_back(actual.pista);
                    std::cout << "?? Encontraste: " << actual.pista << std::endl;
                    if (habitacionActual == "Sotano") juegoTerminado = true;
                } else {
                    std::cout << "Ya examinaste bien esta habitación." << std::endl;
                }
            } 
            else if (accion == "ir") {
                std::string dir;
                std::cin >> dir;
                if (actual.salidas.find(dir) != actual.salidas.end()) {
                    habitacionActual = actual.salidas[dir];
                } else {
                    std::cout << "? No puedes ir en esa dirección." << std::endl;
                }
            } 
            else if (accion == "pistas") {
                std::cout << "?? Pistas recolectadas:" << std::endl;
                for (const auto& p : inventarioPistas) std::cout << "- " << p << std::endl;
            } 
            else if (accion == "salir") {
                juegoTerminado = true;
            }
        }
    }
};

int main() {
	setlocale(LC_ALL, "");
    MisteryMansion juego;
    juego.iniciar();
    return 0;
}
