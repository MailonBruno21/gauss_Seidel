#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int criterio_Linhas(float x[100][100], int quant_Element){
    float somatorio = 0;
    //REALIZA O SOMATORIO DAS POSIÇÕES DA MATRIZ COM "i" DE "0" AO FIM DA EQUAÇÃO, COM "i != j"
    for(int i = 0; i < quant_Element; i++){
        for(int j = 0; j < quant_Element; j++){
            if (i != j){
            somatorio = x[i][j] + somatorio;
            }
        }
        //FAZ O MODULO CASO SOMATORIO SEJA NEGATIVO
        if(somatorio < 0){
            somatorio = somatorio * -1;
        }
    }
    if(somatorio < 1){
        return 1;   //CRITÉRIO ATENDIDO RETORNA VALOR 1
    }else{
        return -1;  //CRITÉRIO NÃO ATENDIDO RETORNA VALOR -1
    }
}

int estri_Diag_Domin(float x[100][100], int quant_Element){

    //REALIZA O SOMATORIO DAS POSIÇÕES DA MATRIZ COM "i" DE "0" AO FIM DA EQUAÇÃO, COM "i != j"
    for(int i = 0; i < quant_Element; i++){
        float somatorio = 0;
        for(int j = 0; j < quant_Element; j++){
            if (i != j){
            somatorio = x[i][j] + somatorio;
            }
            if(x[i][i] < 0){
                if(x[i][i]*-1 < somatorio){
                    return -1; //INDICA QUE A MATRIZ NÃO É ESTRITAMENTE DIAGONAL DOMINANTE
                }
            }
        }
    }
    return 1; //INDICA QUE A MATRIZ É ESTRITAMENTE DIAGONAL DOMINANTE
}

int criterio_Sassenfeld(float x[100][100], int quant_Element){

    float b[100];
    int aux = 0;
    //REALIZA O SOMATORIO DAS POSIÇÕES DA MATRIZ COM "i" DE "0" AO FIM DA EQUAÇÃO, COM "i != j"

    float somatorio = 0;

    while(aux < 100){
        b[aux] = 0;
        aux++;
    }

    for(int j = 1; j < quant_Element; j++){
            if(x[0][j] < 0){
                somatorio = (x[0][j]*-1) + somatorio;
            }else{
                somatorio = x[0][j] + somatorio;
            }
    }

    b[0] = somatorio / x[0][0];

    for(int j = 1; j < quant_Element; j++){
        for(int i = 0; i < j; i++){
            if (i != j){
                if(x[j][i] < 0){
                    b[j] = (x[j][i]*-1) * b[j-1] + b[j];
                }else{
                    b[j] = x[j][i]* b[j-1] + b[j];
                }
            }
        }

        b[j] = b[j]/x[j][j];

        if(b[j] > 1){
            return -1; //INDICA QUE A MATRIZ NÃO OBEDECE O CRITERIO DE SASSENFELD
        }
    }

    return b[quant_Element]; //INDICA QUE A MATRIZ OBEDECE O CRITERIO DE SASSENFELD
}

float calc_Erro(float result_Atual, float result_Anterior){
    float erro = (result_Atual-result_Anterior) / result_Atual;
    if(erro < 0){
        erro = erro * -100;
    }else{
        erro = erro *100;
    }
    return erro;
}

int main(){

    setlocale(LC_ALL,"");

    int quant_Element, opc = 1, interacoes = 0;
    float x[100][100], b[100], resultado[100], result_Anterior[100], erro;
    printf("-------- ATENÇÃO --------\n\n");
    printf("A NOTAÇÃO X1, X2 , ...\n");
    printf("REPRESENTA AS VARIAVEIS DO SISTEMA\n\n");
    printf("-------------------------\n\n\n");

    system("pause");
    system("cls");

    printf("IINSIRA A QUANTIDADE DE ELEMENTOS DA EQUAÇÃO (1 ATÉ 100): ");
    scanf("%d", &quant_Element);

    system("cls");
    printf("DÍGITE OS VALORES DO SISTEMA LINEAR\n\n");
    for(int i = 0; i < quant_Element; i++){
        printf("%dº EQUAÇÃO\n\n", i+1);
        for(int j = 0; j < quant_Element; j++){
            printf("X%d = ", j+1);
            scanf("%f", &x[i][j]);
        }

        printf("B%d = ", i+1);
        scanf("%f", &b[i]);

        system("cls");
        for(int k = 0; k <= i; k++){
            for(int q = 0; q < quant_Element; q++){
                printf("%.2fX%d ", x[k][q], q+1);
            }
            printf("= %.2f\n", b[k]);
        }
        printf("\n");
    }
    int p = 0;

    //CHAMA A FUNÇÃO TESTE DO CRITERIO DAS LINHAS
    if(criterio_Linhas(x, quant_Element) == -1){
        printf("MATRIZ NÃO OBEDECE O CRITERIO DAS LINHAS\n");
       }else{
        printf("MATRIZ OBEDECE O CRITERIO DAS LINHAS\n");
       }

    //CHAMA A FUNÇÃO TESTE DA MATRIZ ESTRITAMENTE DIAGONAL DOMINANTE
    if(criterio_Linhas(x, quant_Element) == -1){
        printf("MATRIZ NÃO ESTRITAMENTE DIAGONAL DOMINANTE\n");
       }else{
        printf("MATRIZ ESTRITAMENTE DIAGONAL DOMINANTE\n");
       }

    if(criterio_Sassenfeld(x, quant_Element) == -1){
        printf("MATRIZ NÃO OBEDECE O CRITERIO DE SASSENFELD\n");
       }else{
        printf("MATRIZ OBEDECE O CRITERIO DE SASSENFELD\n");
       }


    system("pause");

    //Interações de convergencia

    //INICIA AS VARIAVEIS COM CHUTE INICIAL = 0
    while(p < quant_Element){
        resultado[p] = 0;
        p++;
    }

    system("cls");
    printf("PARAR QUANDO O ERRO ESTIVEM ABAIXO DE: ");
    scanf("%f", &erro);

    while(opc > erro){

    for(int i = 0; i < quant_Element; i++){
        float somatorio = 0;
        for(int j = 0; j < quant_Element; j++){
            if (i != j){
            somatorio = (-1*x[i][j])* resultado[j] + somatorio;
            }
        }
        resultado[i] = (b[i]+ somatorio) / x[i][i];
    }
    system("cls");
    for(int k = 0; k < quant_Element; k++){
            for(int q = 0; q < quant_Element; q++){
                printf("%.2fX%d ", x[k][q], q+1);
            }
            printf("= %.2f\n", b[k]);
        }
    printf("\n\n");
    for(int t = 0; t < quant_Element; t++){
        if(interacoes != 0){
            printf("X%d = %.5f --> ERRO %.4f%%\n", t+1, resultado[t], calc_Erro(resultado[t], result_Anterior[t]));
            opc = calc_Erro(resultado[t], result_Anterior[t]);
            result_Anterior[t] = resultado[t];
        }else{
            result_Anterior[t] = resultado[t];
            printf("X%d = %.5f\n", t+1, resultado[t]);
        }
    }
    interacoes++;
    printf("\n\n NÚMERO DE INTERAÇÕES: %d\n\n", interacoes);
    }
    return 0;
}
