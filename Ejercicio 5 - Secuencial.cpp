#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;
class Pila{
	private:
		int *items;
		int indexTop;
		int maxSize;
	public:
		Pila(int maxSize = 10); //si no se pasa como parámetro la cantidad maxima de elementos, por defecto son 10
		int size() const;	    //devuelve la cantidad actual de elementos
		bool empty() const;     //devuelve True si la pila está vacia
		int top() const;	    //devuelve el valor del ultimo elemento agregado
		void push(int dat);     //agrega un elemento a la pila
		void pop();			    //elimina el elemento que está en la posición top de nuestra pila
		void recorrer();		//recorre la pila
		~Pila();			    //es el destructor
};

Pila::Pila(int max){
	indexTop = -1;
	maxSize = max;
	items = new int[max];
	
}

int Pila::size() const{
	return indexTop + 1;
}

bool Pila::empty() const{
	return (indexTop == -1);
}

int Pila::top() const{
	return items[indexTop];
}

void Pila::push(int dat){
	if(indexTop + 1 < maxSize)
		items[++indexTop] = dat;
}

void Pila::pop(){
	if(!empty())
		indexTop--;
}
void Pila::recorrer(){
	int i;
	if (!empty()){
		for (i=indexTop; i>=0; i--){
			cout<<items[i]<<endl;
		}
	}
}
Pila::~Pila(){
	delete[]items;
}

void limpiarPantalla(void){
	system("CLS");
}

void mostrarTitulo(void){
	printf("-------- El juego de los discos: La Torre de Hanoi --------\n\n");
}

void mostrarInstrucciones(void){
	puts("Tienes que mover los discos de la TORRE 1 a la TORRE 3");
	puts("Para mover los discos debes ingresar el valor correspondiente a su tamanio");
	puts("Nunca se puede colocar un disco grande sobre uno mas pequenio");
}

//  INICIO SUBPROGRAMAS INHERENTES AL JUEGO EN SI

int ingresarNumDiscos(void){
	int n;
	
	printf("Ingrese numero de discos: ");
	scanf("%d", &n);
	limpiarPantalla();
	mostrarTitulo();
	return (n);
}

int calcularMovimientosMinimos(int numDiscos){
	int movimientosMinimos;
	
	movimientosMinimos = pow(2, numDiscos) - 1;
	limpiarPantalla();
	mostrarTitulo();
	return (movimientosMinimos);
}

void mostrarMovimientosMinimos(int &movimientosMinimos){
	printf("Minimo de movimientos: %d\n", movimientosMinimos); fflush(stdin);
	
}

void mostrarMovimientosActuales(int &movimientosActuales){
	printf("Tu numero de movimientos: %d\n\n", movimientosActuales);
}

void cargarP1(Pila &p1, int numDiscos){
	int i;
	
	for (i=numDiscos; i>=1; i--){
		p1.push(numDiscos);
		numDiscos = numDiscos - 1;
	}
	limpiarPantalla();
	mostrarTitulo();
}

void mostrarTorre(Pila &p, int num){
	printf("Torre %d\n", num);
	puts("--------");
	p.recorrer();
	puts("--------\n");
}

void realizarMovimiento(Pila &psalida, Pila &pdestino, int &movimientosActuales){
	int aux;
	if (pdestino.empty() == 1 || psalida.top() < pdestino.top()){
		pdestino.push(psalida.top());
		psalida.pop();
		movimientosActuales = movimientosActuales + 1;
	}
}

void interactuar(Pila &p1, Pila &p2, Pila &p3, int &movimientosActuales){
	int inicio = -1, destino = -1;
	bool vacia=1;
	
	while (vacia){
		
		printf("Movimiento de la Torre: ");
		scanf("%d", &inicio);
		
		
		switch (inicio){
		case 1: vacia=p1.empty(); break;
		
		case 2: vacia=p2.empty(); break;
		
		case 3: vacia=p3.empty(); break;
		}
	}
	
	
	while (destino < 1 || destino > 3){
		printf("Hacia la Torre: ");
		scanf("%d", &destino);
	}
	
	switch (inicio){
		case 1: switch (destino){
					case 2: realizarMovimiento(p1, p2, movimientosActuales); break;
					case 3: realizarMovimiento(p1, p3, movimientosActuales); break; 
				}
				break;
		case 2: switch (destino){
					case 1: realizarMovimiento(p2, p1, movimientosActuales); break;
					case 3: realizarMovimiento(p2, p3, movimientosActuales); break;
				}
				break;
		case 3: switch (destino){
					case 1: realizarMovimiento(p3, p1, movimientosActuales); break;
					case 2: realizarMovimiento(p3, p2, movimientosActuales); break;
				}
				break;
	}	
}

void jugar(void){
	int numDiscos, movimientosMinimos, movimientosActuales=0;
	bool band=1;
	Pila p1, p2, p3;
	
	numDiscos = ingresarNumDiscos();
	movimientosMinimos = calcularMovimientosMinimos(numDiscos);
	cargarP1(p1, numDiscos);
	
	
	while (band){
		mostrarMovimientosMinimos(movimientosMinimos); fflush(stdin);
		mostrarMovimientosActuales(movimientosActuales);
		mostrarTorre(p1, 1);
		mostrarTorre(p2, 2);
		mostrarTorre(p3, 3);
		interactuar(p1, p2, p3, movimientosActuales);
		
		
		if (p3.size() == numDiscos){
			limpiarPantalla();
			mostrarTitulo();
			puts("FELICITACIONES! LO LOGRASTE");
			mostrarMovimientosMinimos(movimientosMinimos); fflush(stdin);
			printf("Movimientos realizados: %d\n", movimientosActuales);
			system("PAUSE()");
			band = 0;
		} 
		limpiarPantalla();
		mostrarTitulo();
	}
	
	
}

//  INICIO SUBPROGRAMAS INHERENTES AL JUEGO EN SI

int main(){
	int flag=-1;
	
	system("color F1");
	
	mostrarTitulo();
	
	while (flag != 3){
		puts("\n----------MENU----------");
		puts("1. Jugar");
		puts("2. Instrucciones");
		puts("3. Salir");
		scanf("%d", &flag); fflush(stdin);
		switch (flag){
			case 1: limpiarPantalla();
					mostrarTitulo();
					jugar();
					break;
			
			case 2: limpiarPantalla();
					mostrarTitulo();
					mostrarInstrucciones(); 
					break;
					
			case 3: limpiarPantalla();
					mostrarTitulo();
					puts("Adios.."); break;
			
			default: 	limpiarPantalla();
						mostrarTitulo();
						puts("Opcion incorrecta");
		}
	}
	
}
