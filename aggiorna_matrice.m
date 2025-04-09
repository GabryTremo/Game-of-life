function A_new = aggiorna_matrice(A)
% A_new = aggiorna_matrice(A) restituisce la matrice della generazione
% successiva a quella di A nel gioco della vita di Conway su un toro

n = size(A,1);
A_new = ones(n);
A_adj = zeros(n+2);

% idea: A_adj è una matrice più grande di A, il cui elemento (i,j) è il
% numero di cellule vive adiacenti alla casella (i,j) nella generazione
% attuale (adj sta per adiacenza). Per le caselle nelle righe e colonne al
% bordo di A conto l'adiacenza sulle righe e colonne aggiuntive di A_adj,
% che sarebbero fuori taglia. Poi, in (1) sotto, sommo le componenti fuori
% taglia da un lato con le componenti all'altro bordo, in modo da
% considerare adiacenti anche le caselle a bordi opposti, per identificarli
% come se fossimo su un toro.

A_adj(1:n,1:n) = A_adj(1:n,1:n) + A;
A_adj(1:n,2:n+1) = A_adj(1:n,2:n+1) + A;
A_adj(1:n,3:n+2) = A_adj(1:n,3:n+2) + A;
A_adj(2:n+1,1:n) = A_adj(2:n+1,1:n) + A;
A_adj(2:n+1,3:n+2) = A_adj(2:n+1,3:n+2) + A;
A_adj(3:n+2,1:n) = A_adj(3:n+2,1:n) + A;
A_adj(3:n+2,2:n+1) = A_adj(3:n+2,2:n+1) + A;
A_adj(3:n+2,3:n+2) = A_adj(3:n+2,3:n+2) + A;

% (1), vedi sopra
A_adj(2:n+1,2) = A_adj(2:n+1,2) + A_adj(2:n+1,n+2);
A_adj(2:n+1,n+1) = A_adj(2:n+1,n+1) + A_adj(2:n+1,1);
A_adj(2,2:n+1) = A_adj(2,2:n+1) + A_adj(n+2,2:n+1);
A_adj(n+1,2:n+1) = A_adj(n+1,2:n+1) + A_adj(1,2:n+1);
A_adj(2,2) = A_adj(2,2) + A_adj(n+2,n+2);
A_adj(n+1,n+1) = A_adj(n+1,n+1) + A_adj(1,1);
A_adj(2,n+1) = A_adj(2,n+1) + A_adj(n+2,1);
A_adj(n+1,2) = A_adj(n+1,2) + A_adj(1,n+2);

% ora ho sistemato i bordi e posso quindi eliminare le componenti fuori
% taglia
A_adj = A_adj(2:n+1,2:n+1);

% la nuova matrice ha 1 nella casella (i,j) sse vale una tra le due regole
% sotto, che sono quelle che creano o conservano una cellula viva nel
% classico gioco della vita, e 0 altrimenti
A_new = A_new.*(((A == 1)&((A_adj ==2)|(A_adj == 3)))|((A == 0)&(A_adj ==3)));

