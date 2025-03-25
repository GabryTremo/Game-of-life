#include <iostream>
#include <vector>
#include <cmath>


int crea_matrice(int *pInitCond, int init_cond_size){
	
	int mat[100][100];
	
	for(int i=0; i<100; i++){
		std::fill(mat[i], mat[i]+100, 0);
	}
	
	for(int j=0; j<init_cond_size; j++){
		mat[pInitCond[j]][pInitCond[j+1]];
	}
	
	return mat[100][100];
}

void stampa_matrice(int mat[100][100]){
	
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
	int mat[100][100];
	
	
	
	
	std::cout<<"Inserisci il numero di cellule vive iniziali: ";
	std::cin>>init_cond_size;
	pInitCond = new int[2*init_cond_size];
	std::cout<<"Inserisci le coordinate delle cellule vive iniziali:\n";
	for (int i=0; i<init_cond_size; i++){
		//std::cout<<"(";
		std::cin>>pInitCond[i];
		//std::cout<<",";
		std::cin>>pInitCond[i+1];
		//std::cout<<"); ";
	}
	
	mat[100][100] = crea_matrice(pInitCond, init_cond_size);	
	
	delete[] pInitCond;
	
	stampa_matrice(mat);
	
	
	return 0;
}
