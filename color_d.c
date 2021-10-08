#include <stdio.h>
#include <stdlib.h>

void mediaGrau (int mat[7][7], int table[7][3]);
void tableImp (int table[7][3]);
int grauMaxColor (int table[7][3]);

void tableImp (int table[7][3]) {
    int grau[4] = {0,0,0,0};
    int soma = 0;
    printf("Colorações esperadas representadas por numeros \n");
    printf(" ______________  \n");
    printf("| 1 - Vermelha | \n");
    printf("| 2 - Verde    | \n");
    printf("| 3 - Azul     | \n");
    printf("| 4 - Amarelo  | \n");
    printf("|______________|");
    printf("\n");
    printf("\n Representacao de cores resultantes e vertices:\n\n");

    printf("     ______________\n");
    printf("    |Vertice| Cores|\n");
    for (int i = 0; i < 7; i++){
        if (table[i][1] == 1){
            printf("    | %d\t    |\t 1 |", table[i][0]);
            if (grau[0] == 0){
                soma++;
                grau[0] = 1;
            }
        }

        if (table[i][1] == 2) {
            printf("    | %d\t    |\t 2 |", table[i][0]);
            if (grau[1] == 0){
                soma++;
                grau[1] = 1;
            }
        }

        if (table[i][1] == 3) {
            printf("    | %d\t    |\t 3 |", table[i][0]);
            if (grau[2] == 0){
                soma++;
                grau[2] = 1;
            }
        }

        if (table[i][1] == 4) {
            printf("    | %d\t    |\t 4 |", table[i][0]);
            if (grau[3] == 0){
                soma++;
                grau[3] = 1;
            }
        }

        printf("\n");
    }
        printf("     ______________\n");
        printf("Quantidade de cores Utilizadas: %d\n", soma);
}

void coloreGrafo (int mat[7][7], int table[7][3]) {

    mediaGrau(mat, table);
    for (int i; i < 7; i++){
        i = grauMaxColor(table);
        table[i][1] = 1;
        for (int j = 0; j < 7; j++){
            if (mat[i][j] != 0) {
                if (table[j][1] == table[i][1]){
                    table[i][1]++;
                    j = 0;
                }
            }
        }
    }
    tableImp(table);
}

int grauMaxColor (int table[7][3]){
    int maiorGrau = 0;
    int posicao;
    for(int i = 0; i < 7; i++){
        if (maiorGrau < table[i][2] && table[i][1] == 0){
            maiorGrau = table[i][2];
            posicao = i;
        }
    }
    return posicao;
}

void mediaGrau (int mat[7][7], int table[7][3]){
    int grau;
    for (int i = 0; i < 7; i++){
        grau = 0;
        for (int j = 0; j < 7; j++){
            if (mat[i][j] != 0){
                grau++;
            }
        }
        table[i][2] = grau;
    }
}

int main() {

     int tableColoracao[7][3] = {
        {0,0,0},
        {1,0,0},
        {2,0,0},
        {3,0,0},
        {4,0,0},
        {5,0,0},
        {6,0,0}
    };

    int matriz[7][7] = {{0, 8, 0, 6, 0, 0, 0},
           {8, 0, 9, 10, 8, 0, 0},
           {0, 9, 0, 0, 6, 0, 0},
           {6, 10, 0, 0,16, 7, 0},
           {0, 8, 6,16, 0, 9, 10},        
           {0, 0, 0, 7, 9, 0,12},        
           {0, 0, 0, 0, 10,12, 0}        
    };                                                         

    coloreGrafo(matriz, tableColoracao);
}