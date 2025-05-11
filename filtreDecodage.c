#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour convertir une chaîne binaire en décimal
int binary_to_decimal(char* binary) {
    int decimal_value = 0;
    int base = 1;
    for (int i = 7; i >= 0; i--) {
        decimal_value += binary[i] * base;
        base *= 2;
    }
    return decimal_value;
}

// Fonction pour trouver la position d'un caractère dans la chaîne printable_chars
int char_position(char ch) {
    char printable_chars[] = "abcdefghijklmnopqrstuvwxyz012345";
    for (int i = 0; i < strlen(printable_chars); i++) {
        if (printable_chars[i] == ch) {
            return i;
        }
    }
    return -1;
}

// Fonction pour convertir un nombre décimal en binaire sur 5 bits
char* decimalToBinaryFiveBits(int decimal) {
    char* binary_result = (char*)malloc(5 * sizeof(char));

    if (binary_result == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }

    for (int i = 4; i >= 0; i--) {
        binary_result[i] = decimal % 2;
        decimal /= 2;
    }

    return binary_result;
}

int main(int argc, char* argv[]) {
 FILE* fichier;
FILE* fichierout;

   // Vérification des arguments en ligne de commande (s'il n'y pas assez de paramettres ou beaucoup d'arguments)
   if ( argc > 3) 
    {
        printf("La commande %s est de type <prog> <fichier_entree> <fichier_sortie> ou entree standard\n", argv[0]);
        exit(1);
    }
    else if (argc == 1) 
    {
    // Rediriger l'entrée standard (stdin) à partir d'un fichier
     fichier = stdin;
    if (fichier == NULL) {
        printf("Le fichier d'entrée n'existe pas !!\n");
        exit(1);
    }

    // Rediriger la sortie standard (stdout) vers un fichierout
     fichierout = stdout;
    if (fichierout == NULL) {
        printf("Erreur lors de la création du fichier de sortie !!\n");
        fclose(fichier);
        exit(1);
    }
  }
  else if(argc == 3) // Sinon vérification des arguments en ligne de commande (s'il assez de paramettres)
  {
      
    // Ouverture du fichier d'entrée en lecture binaire
    fichier = fopen(argv[1], "rb");
    if (fichier == NULL) {
        printf("Le fichier d'entrée n'existe pas !!\n");
        exit(1);
    }

    // Ouverture du fichier de sortie en écriture binaire
     fichierout = fopen(argv[2], "wb");
    if (fichierout == NULL) {
        printf("Erreur lors de la création du fichier de sortie !!\n");
        fclose(fichier);
        exit(1);
    }
  }else if(argc == 2){
      // Ouverture du fichier d'entrée en lecture binaire
    fichier = fopen(argv[1], "rb");
    if (fichier == NULL) {
        printf("Le fichier d'entrée n'existe pas !!\n");
        exit(1);
    }

    // Rediriger la sortie standard (stdout) vers un fichierout
     fichierout = stdout;
    if (fichierout == NULL) {
        printf("Erreur lors de la création du fichier de sortie !!\n");
        fclose(fichier);
        exit(1);
    }

  }

    char** matDecod = NULL;
    //Taille de la matrice des caractères
    int TailleMatDecod = 0;
    // le caractère
    char cara;
    //position du caractère
    int poscara;
    //un pointeur "char *" (tableau) pour récuperer les bits de chaques caractère
    char* binary;

    // Lecture du fichier d'entrée et traitement des caractères
    while ((fread(&cara, sizeof(char), 1, fichier))) {
        if (cara != '\n'){
        // Allocation dynamique de mémoire pour matrice de décodage
        matDecod = (char**)realloc(matDecod, (TailleMatDecod + 1) * sizeof(char*)); // reallouer dynamiquement une ligne pour chaque caractère
        matDecod[TailleMatDecod] = (char*)malloc(5 * sizeof(char)); // allouer les colonnes (une ligne) pour chaques caractères

        // Recherche de la position du caractère et conversion en binaire sur 5 bits

        poscara = char_position(cara); // la position du caractère dans la chaîne printable_chars
        binary = decimalToBinaryFiveBits(poscara); // conversion en binaire sur 5 bits

        //boucle pour stocker chaque bits du caractère dans une ligne de la matrice
        for (int i = 0; i < 5; i++) {
            matDecod[TailleMatDecod][i] = binary[i];
        }
        // Libération de la mémoire allouée pour le binaire
        free(binary);
        TailleMatDecod++; // incrémenter la taille de la matrice de caractère
        }
    }

    // Traitement des bits pairs et impairs
    int taille = TailleMatDecod / 2; // devision de la taille de la matrice sur 2 pour allouer deux tableaux binary_pairs et binary_impairs avec cette taille
    //
    char* binary_pairs = (char*)malloc(taille * 5 * sizeof(char));
    char* binary_impairs = (char*)malloc(taille * 5 * sizeof(char));
    int index = 0;
    //boucle pour récuperer les bits pairs dans le tableau binary_pairs et les impairs dans binary_impairs
    for (int i = 0; i < TailleMatDecod; i += 2) {
        for (int j = 0; j < 5; j++) {
            binary_pairs[index] = matDecod[i][j];
            binary_impairs[index] = matDecod[i + 1][j];
            index++;
        }
    }

    // Libération de la mémoire allouée pour matDecod
    for (int i = 0; i < TailleMatDecod; i++) {
        free(matDecod[i]);
    }
    free(matDecod);

    // Calcul de la taille du tableau et allocation de mémoire
    int tailletableau = (TailleMatDecod * 5) / 8;

    // Allocation dynamique du tableau 
    char** tableauDecod = (char**)malloc(tailletableau * sizeof(char*));
    for (int i = 0; i < tailletableau; i++) {
        tableauDecod[i] = (char*)malloc(8 * sizeof(char));
    }

    // Remplissage du tableau avec les bits pairs et impairs
    int pair = 0, impair = 0;
    for (int i = 0; i < tailletableau; i++) {
        for (int j = 0; j < 8; j++) {
            if (j % 2 == 0) {
                tableauDecod[i][j] = binary_pairs[pair];
                pair++;
            } else {
                tableauDecod[i][j] = binary_impairs[impair];
                impair++;
            }
        }
    }

    // Libération de la mémoire allouée pour les bits pairs et impairs
    free(binary_impairs);
    free(binary_pairs);

    // Suppression des zéros de bourrage en fin de tableau

    int decimal; 
    int cmpbourrage = 0; // compteur de ligne de bourrage 

    //boucle pour supprimer le bourrage 
    for (int i = tailletableau - 1; i >= 0; i--) {
        decimal = binary_to_decimal(tableauDecod[i]);
        if (decimal == 0 || decimal == 128) {
            cmpbourrage++;
            free(tableauDecod[i]); // libération des lignes (octect) du bourrage
        } else {
            break;
        }
    }
    
    int TailleSansBourrage = tailletableau - cmpbourrage; // la taille du tableau final sans le bourrage

    // Conversion en décimal et écriture dans le fichier de sortie
    for (int i = 0; i < TailleSansBourrage; i++) 
    {
        fprintf(fichierout, "%c", binary_to_decimal(tableauDecod[i]));
    }

    // Libération de la mémoire allouée pour le tableau final
    for (int i = 0; i < TailleSansBourrage; i++) {
        free(tableauDecod[i]);
    }
    free(tableauDecod);

    // Fermeture des fichiers
    fclose(fichier);
    fclose(fichierout);
    return 0;
}

/* Ce programme est un filtre qui a des options prend un fichier binaire ou une entrée standard en entrée, effectue des opérations de manipulation de bits, 
organise ces bits dans une structure spécifique, convertit le résultat en caractères imprimables,
 puis écrit ces caractères dans un fichier de sortie binaire. Ce programme finalement décode un fichier binaire en entrée et 
 le resultat est envoyer dans un fichier de sortie binaire.
*/