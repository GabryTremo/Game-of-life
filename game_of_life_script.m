% Versione MATLAB del gioco della vita di Conway sul toro.

% parametri modificabili
dim = 100;
max_iter = 1000;

% inizializzazioni
cont = 0;
A = zeros(dim);

% interfaccia utente
fprintf("Insert the initial condition coordinates in pairs, and press -1 when you want to start the game:\n");

while true
    
    x_1 = input("Insert the first coordinate: ");
        if x_1 == -1
            break
        end
    x_2 = input("Insert the second coordinate: ");
        if x_2 == -1
            break
        else
            A(x_1,x_2) = 1;
        end

end

close all;

% imshow mostra un'immagine con i pixel della matrice in entrata che sono
% bianchi se l'entrata corrispondente della matrice vale 1 e neri se vale 0
im0 = imshow(logical(A));

% loop continua finchè tutte le cellule sono morte, oppure se si supera il
% numero massimo di generazioni fissato
while any(A, "all") & cont<max_iter     

    title("Conway's game of life, generation " + num2str(cont));
    
    % aggiorna la matrice alla generazione successiva secondo le regole del
    % gioco
    A = aggiorna_matrice(A);

    % anzichè richiamare imshow ad ogni iterazione, che ricreerebbe la
    % figura, cambio l'immagine nella figura senza ricrearla
    set(im0, "Cdata", logical(A));
    
    cont = cont + 1;

    pause(0.1);

end


