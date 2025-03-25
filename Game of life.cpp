#include <iostream>
#include <vector>
#include <cmath>


void crea_matrice(int **mat, int *pInitCond, int init_cond_size){
	
	for(int i=0; i<100; i++){
		std::fill(mat[i], mat[i]+100, 0);
	}
	
	for(int j=0; j<init_cond_size; j++){
		mat[pInitCond[j]][pInitCond[j+1]]=1;
	}
	
}

void stampa_matrice(int **mat){
	
	for (int i=0; i<100; i++){
		for (int j=0; j<100; j++){
			std::cout<<mat[i][j]<<" ";
		}
		std::cout<<"\n";
	}
	
}


int main() {
	
	int *pInitCond = NULL;
	int init_cond_size;
	int **mat = NULL;
	int size = 100;
	
	mat = new int*[size];
	for (int i=0; i<size; i++){
		mat[i] = new int[size];
	}
	
	
	std::cout<<"Inserisci il numero di cellule vive iniziali: ";
	std::cin>>init_cond_size;
	pInitCond = new int[2*init_cond_size];
	std::cout<<"Inserisci le coordinate delle cellule vive iniziali:\n";
	for (int i=0; i<init_cond_size; i++){
		std::cin>>pInitCond[i];
		std::cin>>pInitCond[i+1];
	}
	
	crea_matrice(mat, pInitCond, init_cond_size);	
	
	delete[] pInitCond;
	
	stampa_matrice(mat);
	
	
	
	
	for (int i = 0; i < size; i++) {
        delete[] mat[i];
    }
    delete[] mat;
	
	
	return 0;
}
