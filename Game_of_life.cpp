#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

void crea_matrice(int **mat, int *pInitCond, int init_cond_size, int size){
	
	//Riempie la matrice mat, passata per riferimento, con le condizioni iniziali
	//date in input in precedenza.
	
	//Inizializza la matrice con tutti zeri
	for(int i=0; i<size; i++){
		std::fill(mat[i], mat[i]+size, 0);
	}
	
	//Inserisce 1 nelle posizioni indicate dall'utente
	for(int j=0; j<2*init_cond_size; j+=2){
		mat[pInitCond[j]][pInitCond[j+1]]=1;
	}
	
}

void stampa_matrice(int **mat, int size){
	
	//Mostra a schermo la matrice mat in modo standard
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			std::cout<<mat[i][j]<<" ";
		}
		std::cout<<"\n";
	}
	
}

bool qualcuno_vivo(int **mat, int size){
	
	//Restituisce true se almeno uno degli elementi di mat è non nullo, false altrimenti
	
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
	
	//Crea un frame della pseudo-animazione che mostra l'evoluzione della matrice mat
	
	std::cout<<"\n";
    system("CLS");					//Ripulisce il terminale
    stampa_matrice(mat,size);		
    Sleep(300);						//Mette in pausa l'esecuzione per 300 ms, in modo da
    								//diminuire i frame per secondo della pseudo-animazione
    
}

void controlla_vicini(int **mat, int **adj_mat, int size){
	
	//Riempie una matrice di adiacenza adj_mat, che contiene in ogni entrata il numero di 
	//cellule vive adiacenti alla corrispondente entrata della matrice mat, identificando
	//i lati opposti sul quadrato di gioco, come fosse un toro
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			adj_mat[i][j] = mat[(size+i-1)%size][(size+j-1)%size] + mat[(size+i-1)%size][j] + mat[(size+i-1)%size][(j+1)%size] +
							mat[i][(size+j-1)%size] + mat[i][(j+1)%size] +
							mat[(i+1)%size][(size+j-1)%size] + mat[(i+1)%size][j] + mat[(i+1)%size][(j+1)%size];
		}
	}
	
}

void aggiorna_matrice(int **mat, int **new_mat, int size){
	
	//Riempie la matrice new_mat, passata per riferimento, con i valori corrispondenti
	//alla generazione successiva rispetto a mat nel gioco della vita
	
	//Alloca memoria per la matrice di adiacenza adjacency_mat, che conterrà in ogni entrata 
	//il numero di cellule vive adiacenti alla corrispondente entrata della matrice mat
	int **adjacency_mat = new int*[size];
	for (int i=0; i<size; i++){
		adjacency_mat[i] = new int[size];
	}
	
	//Riempie la matrice di adiacenza	
	controlla_vicini(mat, adjacency_mat, size);
		
	//Riempie la matrice new_mat seguendo le regole del gioco
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
	
	//Libera la memoria allocata per adjacency_mat, che per adesso non serve
	//più, e verrà reinizializzata alla prossima chiamata di questa funzione
	for (int i = 0; i < size; i++) {
        delete[] adjacency_mat[i];
    }
    delete[] adjacency_mat;
}



int main() {
	
	int *pInitCond = NULL;					//vettore delle posizioni delle cellule iniziali
	int init_cond_size;						//numero di cellule iniziali
	int **mat = NULL, **new_mat = NULL;		//matrici che rappresentano la generazione corrente e la successiva, rispettivamente
	int size = 20;							//dimensione del campo di gioco
	int max_iter = 100;						//massimo numero di generazioni
	int cont = 0;							//contatore per fermare l'esecuzione quando si raggiunge il numero massimo di generazioni
	
	//Alloca memoria per mat 
	mat = new int*[size];
	for (int i=0; i<size; i++){
		mat[i] = new int[size];
	}
	
	//Alloca memoria per new_mat
	new_mat = new int*[size];
	for (int i=0; i<size; i++){
		new_mat[i] = new int[size];
	}
	
	//Chiede in input il numero di cellule iniziali e le loro coordinate,
	//nel formato (i_1,j_1), (i_2,j_2), ...
	std::cout<<"Inserisci il numero di cellule vive iniziali: ";
	std::cin>>init_cond_size;
	pInitCond = new int[2*init_cond_size];
	std::cout<<"Inserisci le coordinate delle cellule vive iniziali:\n";
	for (int i=0; i<2*init_cond_size; i++){
		std::cin>>pInitCond[i];
	}
	
	//Riempie la matrice mat, corrispondente alla prima generazione, a 
	//partire dalle condizioni iniziali fornite sopra
	crea_matrice(mat, pInitCond, init_cond_size, size);	
	
	//Libera la memoria allocata per il vettore delle condizioni iniziali
	delete[] pInitCond;
	
	//Mostra a schermo la prima generazione
	stampa_matrice(mat,size);
	
	//Loop principale del gioco, che si interrompe se tutte le cellule sono
	//morte oppure se si è raggiunto il numero massimo di generazioni
	while(qualcuno_vivo(mat,size)==true && cont<max_iter){
		
		//Riempie la matrice new_mat con la prossima generazione
		aggiorna_matrice(mat, new_mat, size);
		
		//Mostra a schermo un frame della pseudo-animazione
		renderizza_matrice(new_mat,size);
		
		//Rende la matrice corrispondente alla generazione successiva la matrice
		//corrente per il loop successivo
		for (int i = 0; i < size; i++) {
			for (int j=0; j<size; j++){
				mat[i][j] = new_mat[i][j];
				
			}
		}
		cont++;
	}
	
	//Libera la memoria allocata per mat
	for (int i = 0; i < size; i++) {
        delete[] mat[i];
    }
    delete[] mat;
    
    //Libera la memoria allocata per new_mat
    for (int i = 0; i < size; i++) {
        delete[] new_mat[i];
    }
    delete[] new_mat;
	
	
	return 0;
}
