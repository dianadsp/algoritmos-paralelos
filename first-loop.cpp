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

int main () {

	int max;
	cout << "Ingresar maximo:"<<endl;
	cin >> max;
	
	int max_rand = 100; 
	
	
	double ** a = init_mat(max, max);
	mat_rnd(a, max, max, max_rand);
	
	double * x = new double [max];
	double * y = new double [max];
	
	for (int i = 0;i < max; i++) {
		x[i] = rand()%max_rand;
		y[i] = 0;
	}
	
	cout << "Ejecutando..." << endl;
	clock_t t_ini, t_fin;
	double secs;
	
	t_ini = clock();
	
	for (int i=0;i<max;i++){
		for (int j=0;j<max;j++){
			y[i] += (a[i][j] * x [j]);
		}
	}		
	
	t_fin = clock();

	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	printf("Tiempo: %.16g milisegundos\n", secs * 1000.0);
	
	cout << "Fin de ejecucion" << endl;

}
