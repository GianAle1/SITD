#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Dni{
	string  primer_Nombre;
	string  segundo_Nombre;
	string  primer_Apellido;
	string  segundo_Apellido;
	string  lugar_Nac;
	string  nacionalidad;
	string  direccion;
	string  sexo;
	string  estado; 
	int numeroDNI;
	struct Dni *sgte;
};typedef struct Dni *TpLista;

TpLista Registrar(){
TpLista nuevo=NULL;
nuevo=new(struct Dni);
		srand(time(0));
		int numero = rand() % 9000000 + 1000000;
		int numeroAleatorio = rand() % 4 + 1;
    	nuevo->numeroDNI = numeroAleatorio + numero;
		cout<<"\n\t Ingrese los datos solicitados\n\n";
		cout<<"DNI: "<<nuevo->numeroDNI<<endl;
		cout<<"1. Primer nombre: "; 
		cin>>nuevo->primer_Nombre;
		cout<<"2. Segundo nombre: "; 
		cin>>nuevo->segundo_Nombre;
		cout<<"3. Primer apellido: "; 
		cin>>nuevo->primer_Apellido;
		cout<<"4. Segundo apellido: "; 
		cin>>nuevo->segundo_Apellido;
		cout<<"5. Lugar nacimiento: "; 
		cin>>nuevo->lugar_Nac;
		cout<<"6. Nacionalidad: "; 
		cin>>nuevo->nacionalidad;
		cout<<"7. Direccion de su vivienda: "; 
		cin>>nuevo->direccion;
		cout<<"8. Indique su sexo: "; 
		cin>>nuevo->sexo;
		cout<<"9. Indique su estado civil: "; 
		cin>>nuevo->estado;
		cout<<endl;
		nuevo->sgte=NULL;
return nuevo;
}

void InsertarDNI(TpLista &lista){
	TpLista n=NULL;
	n = Registrar();
	if(lista != NULL){
		n->sgte = lista;
	}
	lista=n;

}
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
void Mostrar(TpLista lista){
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
bool busquedaDNI(TpLista lista, int b){
TpLista p=lista;
bool flag=false;
while(p != NULL){
	if(p->numeroDNI == b){
		flag=true;
	}
	p=p->sgte;
	}
	if(flag==false){
		cout<<"Valor buscado "<<b<<" no existe en la lista"<<endl;
		system("pause");
	}
	return flag;
}

void Actualizar(TpLista lista, int b, string primer_N, string  segundo_N, string primer_A, string segundo_A, string lugar_Na, string nacion, string  direc, string  sex, string  estad){
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
void menu(){
	system("cls");
	cout<<"\n\t LISTA CIRCULAR SIMPLE\n\n";
	cout<<"1.- Registrar DNI"<<endl;
	cout<<"2.- Mostrar"<<endl;
	cout<<"3.- Modificar"<<endl;
	cout<<"4.- Busqueda por DNI"<<endl;
	cout<<"0.- Salir"<<endl;
	cout<<"Ingrese Opcion---> ";
}

int main(){
	TpLista lista=NULL;
	int opc, busca;
	string  reempNP, reempSN, reempPA, reempSA, reempLN, reempN, reempD, reempS, reempE;
	do{ 
		menu();
		cin>>opc;
		switch(opc){
			case 1:{
				InsertarDNI(lista);
				system("pause");
				break;
			}
			case 2:{
				Mostrar(lista);
				system("pause");
				break;
			}
			case 3:{
					if(lista == NULL){
					cout<<"\nERROR.. La lista esta vacia.. no permite esta opcion "<<endl;
					system("pause");
				}
				else{
				  cout<<"\nIngresar el DNI: ";cin>>busca;
				if(busquedaDNI(lista, busca)==true){
				cout<<"1. Primer nombre: "; 
				cin>>reempNP;
				cout<<"2. Segundo nombre: "; 
				cin>>reempSN;
				cout<<"3. Primer apellido: "; 
				cin>>reempPA;
				cout<<"4. Segundo apellido: "; 
				cin>>reempSA;
				cout<<"5. Lugar nacimiento: "; 
				cin>>reempLN;
				cout<<"6. Nacionalidad: "; 
				cin>>reempN;
				cout<<"7. Direccion de su vivienda: "; 
				cin>>reempD;
				cout<<"8. Sexo: "; 
				cin>>reempS;
				cout<<"9. Estado civil: "; 
				cin>> reempE;
				Actualizar(lista, busca, reempNP, reempSN, reempPA, reempSA, reempLN, reempN, reempD, reempS, reempE);
				 }
				  else{
				  	cout<<"\nERROR: No esta permitido ese valor"<<endl;
				  	system("pause");
				  }		
				}
				system("pause");
				break;
			}
			case 4:{
				if (lista == NULL) {
        		cout << "\nERROR: La lista está vacía. No permite esta opción." << endl;
    			} else {
        		cout << "\nIngresar el DNI: ";
        		cin >> busca;
        		ImprimirDNI(lista, busca);
    			}
    		system("pause");
    		break;
		}//switch
		}
		}while(opc != 0);	
	return 0;
}


