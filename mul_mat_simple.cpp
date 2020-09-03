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

void mul_mat(double ** & res, double ** & a, double ** & b, int m, int n) {

	//Existe tres FOR, el primero es para las filas
	for (int i = 0;i < m; i++) {
		//El segundo es para las columnas
		//Con este FOR podemos decir que las direcciones de memoria de a[i][k] y res[i][j] son guardas en cache (Cache Missed) para su futura indexaccion, ya que el for superior recorre todas las filas
		for (int j = 0;j < n;j++) {
			//El el tercero para la sumatoria de las multiplicaciones de cada columna
			//Con este FOR tambien se podria probocar Cache Miss por la indexacion de res[i][j] y b[k][j], Ya que la memoria es limitada y i guardar toda una fila de datos es imposible. 			
			for (int k = 0;k < m;k++) {
				// Se vuelve a provocar Cache Miss para la idexaccion de b[k][j]
				// El resultado se guarda en su respectiva posicion y realiza la multiplicacion de matrices
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}



int main(){

	srand (time(NULL)); 

	cout << "Multiplicacion Matrices Simple"<<endl;
	
	int m;
	int n;
	int max = 1000;
	
	cout << "Ingresar tamano de matriz MxN:\n";
	cout << "Ingresar M:";
	cin >> m; 
	cout << "Ingresar N:";
	cin >> n; 
	
	double ** a = init_mat(m, n);
	double ** b = init_mat(m, n);

	mat_rnd(a, m, n, max);
	mat_rnd(b, m, n, max);

	//print_mat(a, m, n);
	//print_mat(b, m, n);
	cout << "Ejecutando..." << endl;
	clock_t t_ini, t_fin;
	double secs;
	
	t_ini = clock();

	double ** r = init_mat(m, n);
	mat_zeros(r, m, n);
	mul_mat(r, a, b, m, n);
	//print_mat(r, m, n);

	t_fin = clock();

	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	printf("Tiempo: %.16g milisegundos\n", secs * 1000.0);
	
	cout << "Fin de ejecucion" << endl;
	
    return 0;
}
