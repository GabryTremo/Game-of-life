#include <iostream>
#include <vector>
#include <cmath>


void crea_matrice(int **mat, int *pInitCond, int init_cond_size){
	
	for(int i=0; i<100; i++){
		std::fill(mat[i], mat[i]+100, 0);
	}
	
	for(int j=0; j<2*init_cond_size; j+=2){
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

bool qualcuno_vivo(int **mat){
	
	for (int i=0; i<100; i++){
		for (int j=0; j<100; j++){
			if(mat[i][j]==1){
				return true;
			}
		}
	}
	return false;
	
}

void controlla_vicini(int **mat, int **adj_mat, int size){
	
	/*
	for (int i=1; i<size-2; i++){
		for (int j=1; j<size-1; j++){
			adj_mat[i][j] = mat[i-1][j-1] + mat[i-1][j] + mat[i-1][j+1] +
							mat[i][j-1] + mat[i][j+1] +
							mat[i+1][j-1] + mat[i+1][j] + mat[i+1][j+1];
		}
	}
	
	for (int i=1; i<size-2; i++){
		
			adj_mat[i][0] = mat[i-1][size-1] + mat[i-1][0] + mat[i-1][1] +
							mat[i][size-1] + mat[i][1] +
							mat[i+1][size-1] + mat[i+1][0] + mat[i+1][1];
		
	}
	
	for (int i=1; i<size-2; i++){
		
			adj_mat[i][size-1] = mat[i-1][size-2] + mat[i-1][size-1] + mat[i-1][0] +
							mat[i][size-2] + mat[i][0] +
							mat[i+1][size-2] + mat[i+1][size-1] + mat[i+1][0];
		
	}
	
	for (int j=1; j<size-2; j++){
		
			adj_mat[0][j] = mat[size-1][j-1] + mat[size-1][j] + mat[size-1][j+1] +
							mat[0][j-1] + mat[0][j+1] +
							mat[1][j-1] + mat[1][j] + mat[1][j+1];
		
	}
	
	for (int j=1; j<size-2; j++){
		
			adj_mat[size-1][j] = mat[size-2][j-1] + mat[size-2][j] + mat[size-2][j+1] +
							mat[size-1][j-1] + mat[size-1][j+1] +
							mat[0][j-1] + mat[0][j] + mat[0][j+1];
		
	}
	*/
	
	for (int i=0; i<size-1; i++){
		for (int j=0; j<size-1; j++){
			adj_mat[i][j] = mat[(100+i-1)%100][(100+j-1)%100] + mat[(100+i-1)%100][j] + mat[(100+i-1)%100][(j+1)%100] +
							mat[i][(100+j-1)%100] + mat[i][(j+1)%100] +
							mat[(i+1)%100][(100+j-1)%100] + mat[(i+1)%100][j] + mat[(i+1)%100][(j+1)%100];
		}
	}
	
	
}

void aggiorna_matrice(int **mat, int **new_mat, int size){
	
	int **adjacency_mat = new int*[size];
	for (int i=0; i<size; i++){
		adjacency_mat[i] = new int[size];
	}
	
	controlla_vicini(mat, adjacency_mat, size);
	
	for (int i=0; i<100; i++){
		for (int j=0; j<100; j++){
			if(mat[i][j]==1){
				if (adjacency_mat[i][j]<2 || adjacency_mat[i][j]>3){
					new_mat[i][j] = 0;
				}
				else{
					new_mat[i][j] = 1;
				}
			}
			else if(mat[i][j]==0 && adjacency_mat[i][j]==3){
				new_mat[i][j] = 1;
			}
			else{
				new_mat[i][j] = 0;
			}
		}
	}
	
	for (int i = 0; i < size; i++) {
        delete[] adjacency_mat[i];
    }
    delete[] adjacency_mat;
}


int main() {
	
	int *pInitCond = NULL;
	int init_cond_size;
	int **mat = NULL, **new_mat = NULL;
	int size = 100;
	int max_iter = 10;
	int cont = 0;
	
	
	mat = new int*[size];
	for (int i=0; i<size; i++){
		mat[i] = new int[size];
	}
	
	new_mat = new int*[size];
	for (int i=0; i<size; i++){
		new_mat[i] = new int[size];
	}
	
	
	std::cout<<"Inserisci il numero di cellule vive iniziali: ";
	std::cin>>init_cond_size;
	pInitCond = new int[2*init_cond_size];
	std::cout<<"Inserisci le coordinate delle cellule vive iniziali:\n";
	for (int i=0; i<2*init_cond_size; i++){
		std::cin>>pInitCond[i];
	}
	
	crea_matrice(mat, pInitCond, init_cond_size);	
	
	delete[] pInitCond;
	
	stampa_matrice(mat);
	
	while(qualcuno_vivo(mat)==true && cont<max_iter){
		aggiorna_matrice(mat, new_mat, size);
		std::cout<<"\n";
		//stampa_matrice(new_mat); 
		for (int i = 0; i < size; i++) {
			for (int j=0; j<size; j++){
				new_mat[i][j] = mat[i][j];
			}
		}
		cont++;
	}
	
	
	for (int i = 0; i < size; i++) {
        delete[] mat[i];
    }
    delete[] mat;
    
    for (int i = 0; i < size; i++) {
        delete[] new_mat[i];
    }
    delete[] new_mat;
	
	
	return 0;
}
