/********************************************************************************\
 * Programación 1. Examen Practico
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 31 de Enero de 2020
 * Resumen: Fichero "main" de turno1.cpp
\********************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

const int CLAVE_ROT13 = 13;
const int MAX_LONG_LINEA = 100;
const int MAX_LONG_NOMBRE_FICHERO = 200;
const char DIR_DATOS[] = "./datos/";
const char MSJ_FICH_A_LEER []  = "Nombre del fichero a leer: ";
const char MSJ_FICH_A_ESCRIBIR []  = "Nombre del fichero a escribir: ";

/**
 * PRE:  Metodo que pide al usuario que inserte el nombre de dos ficheros: el primero del que se va a leer
 *       y el segundo en el que se va a escribir. Estos ficheros pueden estar en cualquier parte del proyecto,
 *       aunque por ahora se usa la cadeana de caracteres llamada ruta DIR_DATOS[] que situa a los archivos que se leen
 *       en una carpeta "datos" dentro del proyecto.
 * POST: Guardo los nombres de los archivos a leer y a escribir tras realizar el cifrado/descifrado con la clave CLAVE_ROT13
 *       para luego usarlos en los parametros por referencia que se pasan llamados "ficheroLectura" y "ficheroEscritura" 
 */
void pedirNombreFichero(char ficheroLectura [], char ficheroEscritura []){
    cout << MSJ_FICH_A_LEER;
    char ficheroALeer [MAX_LONG_NOMBRE_FICHERO];
    cin >> ficheroALeer;
    
    char ficheroLeerCompleto[MAX_LONG_NOMBRE_FICHERO]; 

    strcpy(ficheroLeerCompleto, DIR_DATOS);
    strcat(ficheroLeerCompleto, ficheroALeer);
    
    strcpy(ficheroLectura, ficheroLeerCompleto);

    
    cout << MSJ_FICH_A_ESCRIBIR;
    char ficheroAEscribir [MAX_LONG_NOMBRE_FICHERO];
    cin >> ficheroAEscribir;
    strcpy(ficheroEscritura, ficheroAEscribir);
    
}

/**
 * PRE:  Existiendo una cadena de caracteres llamada lineaOriginal que se pasa como una constante, una cadena
 *       de caracteres de la misma longitud que la de lineaOriginal, y un entero pasado por referencia 
 *       llamado caracteresTraducidos y que en lineaOriginal haya por lo menos un caracter que se sea ">".
 * POST: Si se cumple la precondicion, todos los caracteres que sigue al caracter ">" seran cifrado con la clave 13, 
 *       llamada tambien CLAVE_ROT13, por lo que si ya estaba cifrada el texto que seguia al caracter ">" el metodo lo descifrara
 *       y sino  estaba cifrado en ninguna clave, lo cifrara a CLAVE_ROT13
 */
void traducirLinea(const char lineaOriginal [], char lineaTraducida [], int& caracteresTraducidos){
    bool traducir = false;
    int algoritmo = 26 - CLAVE_ROT13;

    lineaTraducida[strlen(lineaOriginal)] = '\0';
    
    for (int i=0; lineaOriginal[i] != '\0'; i++){
        char c = lineaOriginal[i];
        if(traducir){
            if('a' <= c && c <= 'z'){
                lineaTraducida[i] = 'a' + ( (c - 'a' + algoritmo) % 26);
                caracteresTraducidos++;
            }else if('A' <= c && c <= 'Z'){
                lineaTraducida[i] = 'A' + ( (c - 'A' + algoritmo) % 26);
                caracteresTraducidos++;
            }else{
                lineaTraducida[i] = c;
            }
        }else{
            lineaTraducida[i] = c;
        }
        
        if(c == '>' ){
            traducir = true;
        }
    }
}

/**
 * PRE:  Existiendo un fichero de texto en el cual aparece en algun momento un caracter ">" seguido de un 
 *       texto cifrado en clave ROT13, o de un texto sin cifrar.
 * POST: Si cumple la precondicion el programa, convierte todos los caracteres que siguen detras del caracter ">" 
 *       a un texto cifrado con la clave ROT13.
 */
int main(){
    
    int letrasDescifradas = 0;
    
    char leer [MAX_LONG_NOMBRE_FICHERO];
    char escribir [MAX_LONG_NOMBRE_FICHERO];
    
    pedirNombreFichero(leer, escribir);
    
    ifstream ficheroLeer (leer);
    
    if(!ficheroLeer.is_open()){
         cerr << "ERROR No se ha podido acceder al fichero " << leer << endl; 
    }else{
        ofstream ficheroEscribir (escribir);
        
        if(!ficheroEscribir.is_open()){
            cerr << "ERROR No se ha podido crear el archivo " << escribir << endl; 
        }else{
            
            char linea [MAX_LONG_LINEA];
            ficheroLeer.getline(linea,MAX_LONG_LINEA);
            
            while(!ficheroLeer.eof()){

                char lineaTraducida [MAX_LONG_LINEA];
                int letrasCambiadas = 0;
                
                traducirLinea(linea, lineaTraducida, letrasCambiadas);
                
                letrasDescifradas+=letrasCambiadas;
                
                ficheroEscribir << lineaTraducida << endl;
                
                ficheroLeer.getline(linea,MAX_LONG_LINEA);
            }
            ficheroEscribir.close();
            
        }
        
    }
    
    ficheroLeer.close();
    
    cout << "Se han cifrado una cantidad de " << letrasDescifradas << " letras" << endl; 
    
    return 0;
}
