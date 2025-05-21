// hackearcontraseña.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

int main()
{

    cout << R"(
    __               __                      __               
   / /_  ____ ______/ /__   _______  _______/ /____  ____ ___ 
  / __ \/ __ `/ ___/ //_/  / ___/ / / / ___/ __/ _ \/ __ `__ \
 / / / / /_/ / /__/ ,<    (__  ) /_/ (__  ) /_/  __/ / / / / /
/_/ /_/\__,_/\___/_/|_|  /____/\__, /____/\__/\___/_/ /_/ /_/ 
                              /____/                          
                             
)" << endl;

    string nombre, apellido;
    int anioNacimiento;

    // Solicitar datos al usuario
    cout << "Ingrese el nombre: ";
    cin >> nombre;
    cout << "Ingrese el apellido: ";
    cin >> apellido;
    cout << "Ingrese el año de nacimiento: ";
    cin >> anioNacimiento;

    // Variantes de nombre y apellido
    string nombreMin = nombre, apellidoMin = apellido;
    string nombreMay = nombre, apellidoMay = apellido;
    string nombreCap = nombre, apellidoCap = apellido;
    if (!nombreCap.empty()) nombreCap[0] = toupper(nombreCap[0]);
    if (!apellidoCap.empty()) apellidoCap[0] = toupper(apellidoCap[0]);
    transform(nombreMin.begin(), nombreMin.end(), nombreMin.begin(), ::tolower);
    transform(apellidoMin.begin(), apellidoMin.end(), apellidoMin.begin(), ::tolower);
    transform(nombreMay.begin(), nombreMay.end(), nombreMay.begin(), ::toupper);
    transform(apellidoMay.begin(), apellidoMay.end(), apellidoMay.begin(), ::toupper);

    string anioStr = to_string(anioNacimiento);
    string anio2 = anioStr.substr(2, 2);

    vector<string> patrones = {
        "{NOMBRE}{APELLIDO}{AÑO}",
        "{APELLIDO}{NOMBRE}{AÑO}",
        "{NOMBRE}{AÑO}{APELLIDO}",
        "{APELLIDO}{AÑO}{NOMBRE}",
        "{NOMBRE}_{APELLIDO}{AÑO}",
        "{APELLIDO}_{NOMBRE}{AÑO}",
        "{NOMBRE}{APELLIDO}",
        "{APELLIDO}{NOMBRE}",
        "{NOMBRE}{AÑO}",
        "{APELLIDO}{AÑO}",
        "{NOMBRE}{AÑO2}",
        "{APELLIDO}{AÑO2}",
        "{NOMBRE}123",
        "{APELLIDO}123",
        "{NOMBRE}{APELLIDO}123",
        "{APELLIDO}{NOMBRE}123",
        "{NOMBRE}!{AÑO}",
        "{APELLIDO}!{AÑO}",
        "{NOMBRE}{APELLIDO}!{AÑO2}",
        "{APELLIDO}{NOMBRE}!{AÑO2}",
        "{NOMBRE}.{APELLIDO}",
        "{APELLIDO}.{NOMBRE}",
        "{NOMBRE}-{APELLIDO}{AÑO2}",
        "{APELLIDO}-{NOMBRE}{AÑO2}",
        "{NOMBRE}*{APELLIDO}{AÑO}",
        "{APELLIDO}*{NOMBRE}{AÑO}",
        "{NOMBRE}#{AÑO}",
        "{APELLIDO}#{AÑO}",
        "{NOMBRE}{APELLIDO}!",
        "{APELLIDO}{NOMBRE}!",
        "{NOMBRE}qwerty",
        "{APELLIDO}asdf",
        "{NOMBRE}password",
        "{APELLIDO}pass",
        "{NOMBRE}2024",
        "{APELLIDO}2024",
        "{NOMBRE}2025",
        "{APELLIDO}2025",
        "{NOMBRE}{APELLIDO}2025",
        "{APELLIDO}{NOMBRE}2025",
        "{NOMBRE}{APELLIDO}2024",
        "{APELLIDO}{NOMBRE}2024"
    };

    vector<string> nombres = { nombre, nombreMin, nombreMay, nombreCap };
    vector<string> apellidos = { apellido, apellidoMin, apellidoMay, apellidoCap };
    vector<string> anios = { anioStr, anio2, "2024", "2025" };
    vector<string> simbolos = { "", "!", "#", "*", ".", "-", "_", "@" };

    set<string> posiblesContrasenas;

    // Generar combinaciones usando patrones y variantes
    for (const auto& n : nombres) {
        for (const auto& a : apellidos) {
            for (const auto& y : anios) {
                for (const auto& s : simbolos) {
                    for (const auto& patron : patrones) {
                        string pass = patron;
                        // Reemplazar los marcadores por los valores actuales
                        size_t pos;
                        while ((pos = pass.find("{NOMBRE}")) != string::npos)
                            pass.replace(pos, 8, n);
                        while ((pos = pass.find("{APELLIDO}")) != string::npos)
                            pass.replace(pos, 10, a);
                        while ((pos = pass.find("{AÑO}")) != string::npos)
                            pass.replace(pos, 5, y);
                        while ((pos = pass.find("{AÑO2}")) != string::npos)
                            pass.replace(pos, 6, anio2);
                        // Insertar símbolo en diferentes posiciones
                        posiblesContrasenas.insert(pass + s);
                        posiblesContrasenas.insert(s + pass);
                        if (posiblesContrasenas.size() >= 1000) break;
                    }
                    if (posiblesContrasenas.size() >= 1000) break;
                }
                if (posiblesContrasenas.size() >= 1000) break;
            }
            if (posiblesContrasenas.size() >= 1000) break;
        }
        if (posiblesContrasenas.size() >= 1000) break;
    }

    // Si aún no hay 1000, rellenar con combinaciones simples
    int contador = 0;
    while (posiblesContrasenas.size() < 1000) {
        posiblesContrasenas.insert(nombre + to_string(contador) + apellido + to_string(anioNacimiento + contador % 100));
        contador++;
    }

    // Guardar en archivo
    ofstream archivo("contraseña.txt");
    if (archivo.is_open()) {
        int i = 0;
        for (const auto& pass : posiblesContrasenas) {
            if (i++ >= 1000) break;
            archivo << pass << endl;
        }
        archivo.close();
        cout << "\nLas posibles contraseñas se han guardado en 'contraseña.txt'.\n";
    }
    else {
        cout << "No se pudo abrir el archivo para escribir.\n";
    }

    // Mostrar las primeras 30 posibles contraseñas en consola
    cout << "\nPrimeras 30 posibles contraseñas generadas:\n";
    int i = 0;
    for (const auto& pass : posiblesContrasenas) {
        if (i++ >= 30) break;
        cout << pass << endl;
    }

	cout << "\nTotal de contraseñas generadas: " << posiblesContrasenas.size() << endl;
    return 0;
}
