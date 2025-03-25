#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>



void crea_matrice(int **mat, int *pInitCond, int init_cond_size, int size){
	
	for(int i=0; i<size; i++){
		std::fill(mat[i], mat[i]+size, 0);
	}
	
	for(int j=0; j<2*init_cond_size; j+=2){
		mat[pInitCond[j]][pInitCond[j+1]]=1;
	}
	
}

void stampa_matrice(int **mat, int size){
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			std::cout<<mat[i][j]<<" ";
		}
		std::cout<<"\n";
	}
	
}

bool qualcuno_vivo(int **mat, int size){
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			if(mat[i][j]==1){
				return true;
			}
		}
	}
	return false;
	
}

void renderizza_matrice(int **mat, int size) {
	
    system("CLS");
    stampa_matrice(mat,size);
    Sleep(300);
    
}

void controlla_vicini(int **mat, int **adj_mat, int size){
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			adj_mat[i][j] = mat[(size+i-1)%size][(size+j-1)%size] + mat[(size+i-1)%size][j] + mat[(size+i-1)%size][(j+1)%size] +
							mat[i][(size+j-1)%size] + mat[i][(j+1)%size] +
							mat[(i+1)%size][(size+j-1)%size] + mat[(i+1)%size][j] + mat[(i+1)%size][(j+1)%size];
		}
	}
	
}

void aggiorna_matrice(int **mat, int **new_mat, int size){
	
	int **adjacency_mat = new int*[size];
	for (int i=0; i<size; i++){
		adjacency_mat[i] = new int[size];
	}
		
	controlla_vicini(mat, adjacency_mat, size);
	
	
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
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
	int size = 10;
	int max_iter = 100;
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
	
	crea_matrice(mat, pInitCond, init_cond_size, size);	
	
	delete[] pInitCond;
	
	stampa_matrice(mat,size);
	
	while(qualcuno_vivo(mat,size)==true && cont<max_iter){
		
		
		aggiorna_matrice(mat, new_mat, size);
		std::cout<<"\n";
		 
		 //stampa_matrice(new_mat, size)
		renderizza_matrice(new_mat,size);
		
		for (int i = 0; i < size; i++) {
			for (int j=0; j<size; j++){
				mat[i][j] = new_mat[i][j];
				
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
