#include <iostream>
#include <string>
#include <utility> // Para std::swap
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <sstream> // Agrega esta línea para incluir <sstream>
#include "C:/Program Files/MySQL/MySQL Server 8.0/include/mysql.h"
#include "C:/Program Files/MySQL/MySQL Server 8.0/include/mysqld_error.h"
#include <mysql.h>


using namespace std;
MYSQL* establecerConexion() {
	MYSQL* conexion = mysql_init(NULL);
	if (conexion == NULL) {
        cout << "Error al inicializar la conexión: " << mysql_error(conexion) << endl;
        return NULL;
    }

    if (mysql_real_connect(conexion, "localhost", "root", "080322", "reniec", 3306, NULL, 0) == NULL) {
        cout << "Error al conectar a la base de datos: " << mysql_error(conexion) << endl;
        return NULL;
    }
	return conexion;
}
template <typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
bool ejecutarQuery(MYSQL* conexion, const std::string& query) {
    if (mysql_query(conexion, query.c_str()) != 0) {
        cout << "Error al ejecutar la consulta: " << mysql_error(conexion) << endl;
        return false;
    }
    return true;
}
struct Dni{
	string  primer_Nombre;
	string  segundo_Nombre;
	string  primer_Apellido;
	string  segundo_Apellido;
	int anioNacimiento;
	string  lugar_Nac;
	string  nacionalidad;
	string  direccion;
	string  sexo;
	string  estado; 
	int numeroDNI;
	char numeroSolicitud[3];
	struct Dni *sgte;
};typedef struct Dni *TpLista;


struct Solicitud{
	char codigo[3];
	int nacionalidad;
	/*1.Peruano 2.Extrangero*/
	int estado;
	/*1.En espera
	2.Aceptado
	3.Rechazado*/
	struct Solicitud *sgte;
};typedef struct Solicitud *TpSoli;

//Contar lista
int ContarLista(TpSoli lista){
	int cantidad=0;
	TpSoli p=lista;
	while(p!=NULL){	
		cantidad++;
		p=p->sgte;
	}
	return cantidad;
}
	
//Crear solicitud (crear nodo)
TpSoli crearSolicitud(){
	TpSoli nuevo=NULL;
	nuevo=new(struct Solicitud);
	cout<<"Ingresar codigo --->";cin>>nuevo->codigo;
	cout<<"Ingresar nacionalidad"<<endl;
	cout<<"(1.Peruano 2.Extranjero)-->";
	cin>>nuevo->nacionalidad;
	cout<<"Estado en espera"<<endl;
	/*Posibles estados
	1.En espera
	2.Aceptado
	3.Rechazado*/
	nuevo->estado=1;
	cout<<endl;
	nuevo->sgte=NULL;
	
	std::string codigoStr = to_string(nuevo->codigo);
	std::string nacionalidadStr = to_string(nuevo->nacionalidad);
	std::string estadoStr = to_string(nuevo->estado);
	std::string sgteStr = to_string(reinterpret_cast<long long>(nuevo->sgte));  // Convertir puntero a cadena de texto
	MYSQL* conexion = establecerConexion();
	if (conexion != NULL) {
    std::string query = "INSERT INTO Solicitud (codigo, nacionalidad, estado, Solicitudsgte) VALUES (" + codigoStr + ", " + nacionalidadStr + ", " + estadoStr + ", " + sgteStr + ")";
    cout << "Se ejecuta la conexion" << endl;
    cout << codigoStr << "," << nacionalidadStr << "," << estadoStr << "," << sgteStr << endl;

    int resultado = mysql_query(conexion, query.c_str());
    if (resultado != 0) {
        cout << "Error al ejecutar la consulta: " << mysql_error(conexion) << endl;
    } else {
        cout << "Consulta ejecutada correctamente" << endl;
    }
	}

	return nuevo;
}

//Ver Solicitud
void VerSolicitud(TpSoli solicitud){
	int i=0;
	while(solicitud != NULL){
		cout<< " "<<i+1<<")  "<<solicitud->codigo<<" - ";
		if(solicitud->nacionalidad==1){
			cout<<"Peruano"<<" - ";
		}else{
			cout<<"Extranjero"<<" - ";
		}
		
		switch(solicitud->estado){
			case 1:cout<<"En espera"<<endl;break;
			case 2:cout<<"Aceptado"<<endl;break;
			case 3:cout<<"Rechazado"<<endl;
		}
		solicitud=solicitud->sgte;
		i++;	
	}	
}

//Recibir Solicitud
//Insertar al Inicio (PUSH de pila)
void pushSolicitud(TpSoli &pila){
	TpSoli n=NULL;
	int cantidad=ContarLista(pila);
	if(cantidad>=8){
		cout<<"Solo se permiten hasta 8 solictudes"<<endl;
		return;
	}
	n = crearSolicitud();
	if(pila != NULL)
		n->sgte=pila;
	pila = n;
}


//Extraer Pila
TpSoli popSolicitud(TpSoli &pila){
	TpSoli temporal=pila;
	pila=pila->sgte;
	cout<<"\nSolicitud extraido es el del codigo:"<<temporal->codigo<<endl;
	temporal->sgte=NULL;
	return temporal;
}


//Trasladar a la cola
void TrasladarCola(TpSoli &cola, TpSoli q){
	TpSoli p = cola;	
	if(cola == NULL)
		cola=q;
	else{
		while(p->sgte != NULL){
			p=p->sgte;
		}
		p->sgte=q;
	}
}


//Extraer sobre de la cola
TpSoli ExtraerCola(TpSoli &cola){
	TpSoli t=cola;
	cola=cola->sgte;
	/*cout<<"\nNodo estraido es el del codigo:"<<t->codigo<<endl;*/
	t->sgte=NULL;
	return t;
}


//Eliminar sobre de la cola
void Desencolar(TpSoli &cola){
	TpSoli t=cola;
	cola=cola->sgte;
	cout<<"Eliminando) "<<t->codigo<<" - "<<"Extranjero"<<" - "<<"Rechazada";
	t->sgte=NULL;
	//Solicitud rechazada
	t->estado=3;
}


int GenerarDNI(int anioNacimiento){
    // Semilla para generar números aleatorios
    srand(time(0));
    int numeroAleatorio;
    
    //Condicionales para crear el primer
    if(anioNacimiento < 1978){
        // Personas con mayoria de edad antes de 1996
        //naci + 18 < 1996  -> naci <1978
        //1,2
        numeroAleatorio = rand() % 2 + 1;
    } else if(anioNacimiento >= 1978 && anioNacimiento < 2006 ){
        //personas que cumplian 18 a partir de 1996
        //1996 - naci <=18  -> naci >= 1978
        //4
        numeroAleatorio = 4;
    } else {
        //nacidos apartir de 2006
        //naci >= 2006
        //6, 7
        numeroAleatorio = rand() % 2 + 6;
    }

    // Generar número aleatorio de 7 cifras
    int numero = rand() % 9000000 + 1000000;


    int numeroDNI = numero + numeroAleatorio*10000000;

    return numeroDNI;
}


TpLista Registrar(TpSoli temporal){
	TpLista nuevo=NULL;
	nuevo=new(struct Dni);
	temporal->estado=3;
	/*nuevo->numeroSolicitud=temporal->codigo;*/		
	cout<<"\nIngrese los datos solicitados\n";
	
	cout<<"1. Primer nombre: "; 
	cin>>nuevo->primer_Nombre;
	cout<<"2. Segundo nombre: "; 
	cin>>nuevo->segundo_Nombre;
	cout<<"3. Primer apellido: "; 
	cin>>nuevo->primer_Apellido;
	cout<<"4. Segundo apellido: "; 
	cin>>nuevo->segundo_Apellido;
	cout<<"5. Anio de nacimiento: "; 
	cin>>nuevo->anioNacimiento;
	cout<<"6. Lugar nacimiento: ";
	cin>>nuevo->lugar_Nac;
	cout<<"7. Nacionalidad: ";
	
	if(temporal->nacionalidad==1){
		cout<<"Peruano"<<endl;
		nuevo->nacionalidad="Peruano";
	}else{
		cout<<"Extranjero"<<endl;
		nuevo->nacionalidad="Extranjero";
	}
	
	cout<<"8. Direccion de su vivienda: "; 
	cin>>nuevo->direccion;
	cout<<"9. Indique su sexo: "; 
	cin>>nuevo->sexo;
	cout<<"10. Indique su estado civil: "; 
	cin>>nuevo->estado;
	nuevo->numeroDNI=GenerarDNI(nuevo->anioNacimiento);
	cout<<"11. DNI: "<<nuevo->numeroDNI<<endl;
	cout<<endl;
	nuevo->sgte=NULL;
	return nuevo;
}

//Insertar el temporal en la lista, y se crea el nodo
void InsertarInicio(TpLista &lista, TpSoli temporal){
 	TpLista q=NULL;
 	//Crea el nodo q
	q = Registrar(temporal);
	//Lo uno al inicio
	if(lista!=NULL)
		q->sgte = lista;
	lista=q;
}

//En un futuro: Aplicar la función Quicksort para el ordenamiento

//RF4-Consulta de información (GF)
//Se aplico busqueda secuencial
//Se necesita aplicar busqueda binaria

void ImprimirDNI(TpLista lista, int dni) {
    TpLista p = lista;
    bool encontrado = false;
    while (p != NULL) {
        if (p->numeroDNI == dni) {
            cout << "DNI: " << p->numeroDNI << endl;
            cout << "Primer nombre: " << p->primer_Nombre << endl;
            cout << "Segundo nombre: " << p->segundo_Nombre << endl;
            cout << "Primer apellido: " << p->primer_Apellido << endl;
            cout << "Segundo apellido: " << p->segundo_Apellido << endl;
            cout << "Lugar nacimiento: " << p->lugar_Nac << endl;
            cout << "Nacionalidad: " << p->nacionalidad << endl;
            cout << "Direccion de su vivienda: " << p->direccion << endl;
            cout << "Indique su sexo: " << p->sexo << endl;
            cout << "Indique su estado civil: " << p->estado << endl;
            encontrado = true;
            break;
        }
        p = p->sgte;
    }
    if (!encontrado) {
        cout << "El DNI ingresado no se encontró en la lista." << endl;
    }
}

//RF4-Consulta de información (GF)
//muestra todos los dni
void MostrarDNI(TpLista lista){
	cout<<"DNI REGISTRADOS "<<endl<<endl;
	while( lista != NULL){
		cout<<"DNI: "<<lista->numeroDNI<<endl;
		cout<<"Primer nombre: "; 
		cout<<lista->primer_Nombre;
		cout<<endl;
		cout<<"Segundo nombre: "; 
		cout<<lista->segundo_Nombre;
		cout<<endl;
		cout<<"Primer apellido: "; 
		cout<<lista->primer_Apellido;
		cout<<endl;
		cout<<"Segundo apellido: "; 
		cout<<lista->segundo_Apellido;
		cout<<endl;
		cout<<"Lugar nacimiento: "; 
		cout<<lista->lugar_Nac;
		cout<<endl;
		cout<<"Nacionalidad: "; 
		cout<<lista->nacionalidad;
		cout<<endl;
		cout<<"Direccion de su vivienda: "; 
		cout<<lista->direccion;
		cout<<endl;
		cout<<"Indique su sexo: "; 
		cout<<lista->sexo;
		cout<<endl;
		cout<<"Indique su estado civil: "; 
		cout<<lista->estado;
		cout<<"--------------------------";
		cout<<endl;
		lista=lista->sgte;
	}
}

void MostrarDNI_Resumido(TpLista lista){
	int i=0;
	while(lista != NULL){
		cout<< " "<<i+1<<")  "<<lista->numeroDNI<<" - "<<lista->primer_Nombre;
		cout<<" - "<<lista->primer_Apellido<<endl;
		lista=lista->sgte;
		i++;	
	}	
}

//RF3-Actualización de Información (Jhair)
//No se debe actualizar todo (leer regla de negocio)
void Actualizar(TpLista lista, int b, string primer_N, string  segundo_N, 
string primer_A, string segundo_A, string lugar_Na, string nacion, 
string  direc, string  sex, string  estad){
	TpLista p=lista;
	while(p != NULL){
		if(p->numeroDNI == b){
			p->primer_Nombre=primer_N;
			p->segundo_Nombre=segundo_N;
			p->primer_Apellido=primer_A;
			p->segundo_Apellido=segundo_A;
			p->lugar_Nac=lugar_Na;
			p->nacionalidad=nacion;
			p->direccion=direc;
			p->sexo=sex;
			p->estado=estad;
		}
		p=p->sgte;
	}
}

//Quicksort

//Conseguir el último nodo de la lista
TpLista getLastNode(TpLista head) {
    if (head == NULL)
        return NULL;
    
    TpLista node = head;
    while (node->sgte != NULL) {
        node = node->sgte;
    }
    
    return node;
}

TpLista partition(TpLista start, TpLista end, TpLista* newStart, TpLista* newEnd) {
    TpLista pivot = end;
    TpLista prev = NULL;
    TpLista curr = start;
    TpLista tail = pivot;
    
    while (curr != pivot) {
        if (curr->numeroDNI < pivot->numeroDNI) {
            if (*newStart == NULL)
                *newStart = curr;
            
            prev = curr;
            curr = curr->sgte;
        }
        else {
            if (prev != NULL)
                prev->sgte = curr->sgte;
            
            TpLista temp = curr->sgte;
            curr->sgte = NULL;
            tail->sgte = curr;
            tail = curr;
            curr = temp;
        }
    }
    
    if (*newStart == NULL)
        *newStart = pivot;
    
    *newEnd = tail;
    
    return pivot;
}

TpLista quicksort(TpLista start, TpLista end) {
	//Caso Base
    if (start == NULL || start == end)
        return start;
    
    TpLista newStart = NULL;
    TpLista newEnd = NULL;
    
    TpLista pivot = partition(start, end, &newStart, &newEnd);
    
    if (newStart != pivot) {
        TpLista temp = newStart;
        while (temp->sgte != pivot) {
            temp = temp->sgte;
        }
        temp->sgte = NULL;
        
        newStart = quicksort(newStart, temp);
        
        temp = getLastNode(newStart);
        temp->sgte = pivot;
    }
    
    pivot->sgte = quicksort(pivot->sgte, newEnd);
    
    return newStart;
}

//----------------------------------------------------

void menu(){
	system("cls");
	cout<<"\n\t SISTEMA DE REGISTRO DE DNI\n\n";
	cout<<"1.- Realizar Solicitud"<<endl;
	cout<<"2.- Extraer Solicitud"<<endl;
	cout<<"3.- Verficar solicitud (extranjeros)"<<endl;
	cout<<"4.- Ordenar DNI"<<endl;
	cout<<"0.- Salir"<<endl;
	cout<<"Ingrese Opcion---> ";
}


int main(){
	
	
	string nac;
	int anios;
	TpLista lista=NULL;
	TpSoli pila=NULL, temporal=NULL, cola=NULL;
	int opc, busca;
	//No todas las variables se deben reemplazar
	string  reempNP, reempSN, reempPA, reempSA, reempLN, reempN, reempD, reempS, reempE;
	do{ 
		menu();
		cin>>opc;
		switch(opc){
			case 1:{
				pushSolicitud(pila);
				cout<<"Mostrando pila"<<endl;
				VerSolicitud(pila);
				system("pause");
				break;
			}
			case 2:{
				temporal=popSolicitud(pila);
				VerSolicitud(pila);
				if(temporal->nacionalidad==1){
					cout<<"Peruano(a) pasando automáticamente a lista"<<endl;
					temporal->estado=2;
					InsertarInicio(lista,temporal);
					cout<<"Mostrando DNI's"<<endl;
					MostrarDNI_Resumido(lista);
				}else{
					cout<<"Extranjero(a) pasando a cola para revision"<<endl;
					TrasladarCola(cola,temporal);
					cout<<"\nCola de solicitudes"<<endl;
					VerSolicitud(cola);
				}
				system("pause");
				break;
			}
			case 3:{
				cout<<"Numero de solicitud: "<<cola->codigo;
				cout<<" Extranjero"<<endl;
				cout<<"Verficando anios de residencia"<<endl;
				cout<<"Cuales son los anios de residencia del solicitante"<<endl;
				cin>>anios;
				if(anios>=2){
					//Ver el primero de la cola
					cout<<"Aceptado para obtener su DNI"<<endl;
					//Extraer el temporal de la cola para pasarlo a la lista
					temporal=ExtraerCola(cola);
					InsertarInicio(lista,temporal);
					cout<<"\nMostrando DNI's"<<endl;
					MostrarDNI_Resumido(lista);
				}else{
					cout<<"Rechazando solicitud"<<endl;
					Desencolar(cola);
					cout<<"\nCola de solicitudes"<<endl;
					VerSolicitud(cola);	
				}
				system("pause");
				break;	
			}
			case 4:{
				//No funciona
				cout<<"Lista sin ordenar"<<endl;
				MostrarDNI_Resumido(lista);	
				cout<<"Ordenando lista"<<endl;
				lista=quicksort(lista,getLastNode(lista));
				cout<<"Lista ordenada"<<endl;
				MostrarDNI_Resumido(lista);	
    			system("pause");
    			break;
		}//switch
		}
		}while(opc != 0);	
	return 0;
}



