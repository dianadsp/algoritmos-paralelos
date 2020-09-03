#include "iostream"
#include "string"
#include <time.h> 
#include <stdio.h> 
#include <stdlib.h> 
using namespace std;



double ** & init_mat(int m, int n) {
	static double ** matriz;
	matriz = new double * [m];
	for (int i = 0;i < m;i++) {
		matriz[i] = new double[n];
	}
	return matriz;
}

void print_mat(double ** & mat, int m, int n) {
	cout << "Matrix:\n";
	for (int i = 0;i < m; i++) {
		for (int j = 0;j < n;j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

void mat_zeros(double ** & mat, int m, int n) {
	for (int i = 0;i < m; i++) {
		for (int j = 0;j < n;j++) {
			mat[i][j] = 0;
		}
	}
}

void mat_rnd(double ** & mat, int m, int n, int max) {
	for (int i = 0;i < m; i++) {
		for (int j = 0;j < n;j++) {
			mat[i][j] = rand()%max;
		}
	}
}



void mul_block_m(double ** & c, double ** & a, double ** & b, int n, int block)
{
	int bi=0;
	int bj=0;
	int bk=0;
	int i=0;
	int j=0;
	int k=0;
	//Se inicializa todos los parametros en cero ya que son contadores
	int blockSize=block; 
    
    	//Estos tres primeros FOR de anidacion separan de forma homogenia la matriz segun la cantidad de bloques
    	//Esto hace la diferencia, ya que al momento de la indexacion solo guarda una submatriz, haciendo que la se guarde solamente las filas y columnas de esa submatriz, provocando menos Cache Miss
	for(bi=0; bi<n; bi+=blockSize)
		for(bj=0; bj<n; bj+=blockSize)
			for(bk=0; bk<n; bk+=blockSize)
				// Las Siguientes tres matrices hacen la multiplicaciòn de matrices clasica, pero iteran dentro del rango de un solo bloque
				// El comportamiento de la memoria es exaxtamente similar la supeior ya descrita, la principal diferencia es que en este caso espefico los Cache Miss se reducen significativamente porque no fuardas toda una fila o columna, sino solo una fraccion de ella, es ideal escoger la cantidad bloques dependiendo del tamaño de la matriz, asi podemos hacer mas eficiente la funcion
				for(i=0; i<blockSize; i++)
					for(j=0; j<blockSize; j++)
						for(k=0; k<blockSize; k++){
							// Los tres FOR realizan la operaciòn clasica, pero el desplazamiento depende de la pisicion asignada segun su bloque.
							c[bi+i][bj+j] += a[bi+i][bk+k]*b[bk+k][bj+j];
						}
}



int main(){

	srand (time(NULL)); 

	cout << "Multiplicacion Matrices por bloques"<<endl;
	
	int n;
	int blocks;
	int max = 1000;
	
	cout << "Ingresar tamano de matriz NxN:\n";
	cout << "Ingresar N:";
	cin >> n; 
	cout << "Ingresar Bloques:";
	cin >> blocks; 
	
	double ** a = init_mat(n, n);
	double ** b = init_mat(n, n);

	mat_rnd(a, n, n, max);
	mat_rnd(b, n, n, max);

	//print_mat(a, n, n);
	//print_mat(b, n, n);
	cout << "Ejecutando..." << endl;
	clock_t t_ini, t_fin;

	double secs;
	
	t_ini = clock();

	double ** r = init_mat(n, n);

	mat_zeros(r, n, n);

	mul_block_m(r, a, b, n, blocks);
	
	//print_mat(r, n, n);
	
	t_fin = clock();

	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	printf("Tiempo: %.16g milisegundos\n", secs * 1000.0);
	
	cout << "Fin de ejecucion" << endl;
	
    return 0;
}


