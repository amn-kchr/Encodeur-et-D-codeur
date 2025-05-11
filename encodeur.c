#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour convertir un caractère en binaire
char* char_to_binary(char c) {
    char* binary = (char*)malloc(8 * sizeof(char));

    for (int i = 0; i < 8; i++) {
        binary[i] = (c >> 7 - i) & 1;
    }

    return binary;
}

// Fonction pour convertir un nombre binaire en nombre décimal: Elle prends en paramèttre un un pointeur "char *" et rentourne un entier
int binary_to_decimal(char* binary) {
    int decimal_value = 0;
    int base = 1;

    for (int i = 7; i >= 0; i--) {
        decimal_value += (binary[i] - '0') * base;
        base *= 2;
    }

    return decimal_value;
}

// La fonction "convert_to_binary" prend un tableau de caractères, convertit chaque caractère en binaire à l'aide de la fonction précédente (char_to_binary), et stocke le résultat dans chaque ligne d'une matrice.
void convert_to_binary(char* buffer, int n, char** binary) {
    *binary = (char*)malloc(8 * n * sizeof(char));
    int index = 0;

    for (int i = 0; i < n; i++) {
        char* binary_char = char_to_binary(buffer[i]);

        for (int j = 0; j < 8; j++) {
            (*binary)[index] = binary_char[j] + '0';
            index++;
        }

        free(binary_char);
    }
}

//////////////////////////////////////////////////////////////////////////////////////// PRINCIPALE ///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    // Vérification des arguments en ligne de commande
    if (argc != 3) {
        printf("La commande %s est de type <prog> <fichier_entree> <fichier_sortie>\n", argv[0]);
        exit(1);
    }

    // Ouverture du fichier d'entrée en lecture binaire
    FILE* fichier = fopen(argv[1], "rb");
    if (fichier == NULL) {
        printf("Le fichier d'entrée n'existe pas !!\n");
        exit(1);
    }

    // Ouverture du fichier de sortie en écriture binaire
    FILE* fichierout = fopen(argv[2], "wb");
    if (fichierout == NULL) {
        printf("Erreur lors de la création du fichier de sortie !!\n");
        fclose(fichier);
        exit(1);
    }

    // tableau des caractères imprimables
    char printable_chars[] = "abcdefghijklmnopqrstuvwxyz012345";

    // Matrice de caractères
    char** mat = NULL;
    //Taille de la matrice des caractères
    int TailleMat = 0;
    //Le caracère
    char cara;
    //un pointeur "char *" (tableau) pour récuperer les bits de chaques caractère
    char* binary_char;
    //compteur de caractères initialisé à 0
    int cmpCara = 0;

    // Lecture des caractères depuis le fichier d'entrée
    while ((fread(&cara, sizeof(char), 1, fichier))) {

        // Allocation dynamique de mémoire pour matrice
        mat = (char**)realloc(mat, (TailleMat + 1) * sizeof(char*)); // reallouer dynamiquement une ligne pour chaque caractère
        mat[TailleMat] = (char*)malloc(8 * sizeof(char)); // allouer les colonnes (une ligne) pour chaques caractères
        binary_char = char_to_binary(cara); // récupération des bits du caractère

        // boucle pour compter le nombre de bits du caractère
        for (int i = 0; i < 8; i++) { 
          cmpCara++; 
        }

        convert_to_binary(&cara, 1, &mat[TailleMat]); // convertir chaque caractère en binaire et le stocker dans chaque ligne de la matrice 

        TailleMat++; // incrémenter la taille de la matrice de caractère
    }

    //compteur des octects
    int CompteurOctet = 1;
    // compteur des bits du bourrages
    int cmpBourrage = 0;

    // Ajout de remplissage si nécessaire en cas où la matrice n'est pas un block de 40 bits
    while (TailleMat % 5 != 0) { 
        mat = (char**)realloc(mat, (TailleMat + 1) * sizeof(char*));
        mat[TailleMat] = (char*)malloc(sizeof(char));

        if (CompteurOctet == 1) {
            *mat[TailleMat] = 128;  // Remplissage avec (10000000) pour la première ligne du bourrage
        } else {
            *mat[TailleMat] = 0;  // Remplissage avec zéro (00000000) pour le reste des lignes du bourrage
        }

        binary_char = char_to_binary(*mat[TailleMat]); // récupération des bits du bourrage

        // boucle pour compter le nombre de bits du bourrage
        for (int i = 0; i < 8; i++) {
               cmpBourrage++;// récupération des bits du bourrage 
        }

        convert_to_binary(mat[TailleMat], 1, &mat[TailleMat]); // convertir chaque octect  du bourrage en binaire et le stocker dans chaque ligne de la matrice pour completer

        TailleMat++; // incrémenter la taille de la matrice de caractère
        CompteurOctet++;/// incrémenter le compteur qui calcules les octects du bourrage
    }
   

    // Séparation des binaires pairs et impairs: Les bits de chaque octet (caractère binaire) sont séparés en bits pairs et impairs, puis stockés dans deux tableaux distincts (binary_pairs et binary_impairs).
    char* binary_pairs = (char*)malloc(TailleMat * 4 * sizeof(char)); // allocation de mémoire dynamique du tableau (binary_pairs).
    char* binary_impairs = (char*)malloc(TailleMat * 4 * sizeof(char)); // allocation de mémoire dynamique du tableau (binary_impairs).

    // boucle pour séparés en bits pairs et impairs, puis stockés dans deux tableaux distincts (binary_pairs et binary_impairs).
    for (int i = 0; i < TailleMat; i++) {
        for (int j = 0; j < 4; j++) {
            binary_pairs[4 * i + j] = mat[i] [2 * j];
            binary_impairs[4 * i + j] = mat[i] [2 * j + 1];
        }
    }

    // Libération de la mémoire de la matrice de caractères
    for (int i = 0; i < TailleMat; i++) {
        free(mat[i]);
    }
    free(mat);

    // Calcul du nombre de lignes (octect) existant dans le fichier d'entrée
    int cmpTotalLignes = (cmpCara + cmpBourrage) / 5;

    // Allocation mémoire pour le tableau final
    char** tableau = (char**)malloc(cmpTotalLignes * sizeof(char*));
    for (int i = 0; i < cmpTotalLignes; i++) {
        tableau[i] = (char*)malloc(8 * sizeof(char));
    }

    int pair = 0, impair = 0;

    // Initialisation du tableau 
    //boucle pour remplir chaque ligne de tableau final avec trois zéros et les bits pairs et impairs des caractères
    for (int i = 0; i < cmpTotalLignes; i++) {
        for (int j = 0; j < 8; j++) {
            if (j < 3) {
                tableau[i][j] = '0';
            } else {
                if (i % 2 == 0) {
                    tableau[i][j] = binary_pairs[pair];
                    pair++;
                } else {
                    tableau[i][j] = binary_impairs[impair];
                    impair++;
                }
            }
        }
    }

    // Libération de la mémoire des tableaux
    free(binary_char);
    free(binary_pairs);
    free(binary_impairs);

    // Écriture dans le fichier de sortie
    int decimal_value;
    char Impcara; // caracteres imprimables
    
     // Écriture dans le fichier de sortie
    for (int i = 0; i < cmpTotalLignes; i++) {
        decimal_value = binary_to_decimal(tableau[i]); // convertir chaque octect en decimal
        Impcara = printable_chars[decimal_value]; // chercher la caractère dans le tableau des caractères imprimables qui se situe dans la case du nombre decimal de l'octect
        fprintf(fichierout, "%c", Impcara);
    }

    // Fermeture du fichier de sortie
    fclose(fichierout);

    // Libération de la mémoire du tableau
    for (int i = 0; i < cmpTotalLignes; i++) {
        free(tableau[i]);
    }
    free(tableau);

    // fermeture de fichier d'entrée
    fclose(fichier);

    return 0;
}

/* Ce programme prend un fichier binaire en entrée, effectue des opérations de manipulation de bits, 
organise ces bits dans une structure spécifique, convertit le résultat en caractères imprimables,
 puis écrit ces caractères dans un fichier de sortie binaire. Ce programme finalement encode un fichier binaire en entrée et 
 le resultat est envoyer dans un fichier de sortie binaire
*/