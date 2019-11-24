#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int criterio_Linhas(double x[100][100], int quant_Element){
    double somatorio = 0;
    //REALIZA O SOMATORIO DAS POSIÇÕES DA MATRIZ COM "i" DE "0" AO FIM DA EQUAÇÃO, COM "i != j"
    for(int i = 0; i < quant_Element; i++){
        for(int j = 0; j < quant_Element; j++){
            if (i != j){
                if( x[i][j] < 0){
                    somatorio = (x[i][j] * -1) + somatorio;
                }else{
                    somatorio = x[i][j] + somatorio;
                }
            }
        }
        //FAZ O MODULO CASO SOMATORIO SEJA NEGATIVO

        if((somatorio/x[i][i]) >= 1){
            return -1;   //CRITÉRIO NÃO ATENDIDO RETORNA VALOR 1
        }

    }
    return 1;  //CRITÉRIO ATENDIDO RETORNA VALOR -1
}

int estri_Diag_Domin(double x[100][100], int quant_Element){
    //REALIZA O SOMATORIO DAS POSIÇÕES DA MATRIZ COM "i" DE "0" AO FIM DA EQUAÇÃO, COM "i != j"
    for(int i = 0; i < quant_Element; i++){
        double somatorio = 0;
        for(int j = 0; j < quant_Element; j++){
            if (i != j){
                if(x[i][j] < 0){
                    somatorio = (x[i][j]*-1) + somatorio;
                }else{
                    somatorio = x[i][j] + somatorio;
                }
            }
        }
        if(x[i][i] < 0){
            if((x[i][i]* -1) > somatorio){
                 //INDICA QUE A MATRIZ É ESTRITAMENTE DIAGONAL DOMINANTE
            }else{
                return -1;
            }
        }else{
            if(x[i][i] > somatorio){
                 //INDICA QUE A MATRIZ É ESTRITAMENTE DIAGONAL DOMINANTE
            }else{
                return -1;
            }
        }
    }
    return 1;
}

int criterio_Sassenfeld(double x[100][100], int quant_Element){
    double b[quant_Element];

    for(int t = 0; t < quant_Element; t++){
        b[t] = 0;
        if(t == 0){
            for(int i = 1; i < quant_Element; i++){
                b[t]=x[0][i] + b[t];
            }
            b[t] = b[t]/x[0][0];
        }else{
            for(int i = 0; i < quant_Element; i++){
                if(i!= t){
                    if(i < t){
                        b[t]= b[i] * x[t][i];
                    }else{
                        b[t]= b[i] + x[t][i];
                    }

                    b[t]=b[t]/x[t][t];
                }
            }
        }
    }

    double max=0;

    for(int i = 0; i < quant_Element; i++){
        if(b[i] > b[i+1]){
            max = b[i];
        }
    }
    if(max < 1){
        return 1;
    }
        return -1;
}

double calc_Erro(double result_Atual, double result_Anterior){
    double erro = (result_Atual-result_Anterior) / result_Atual;
    if(erro < 0){
        erro = erro * -100;
    }else{
        erro = erro *100;
    }
    return erro;
}

int main(){

    setlocale(LC_ALL,"");

    int quant_Element,interacoes = 0;
    double x[100][100], b[100], resultado[100], result_Anterior[100], erro,  opc = 1;
    printf("-------- ATENÇÃO --------\n\n");
    printf("A NOTAÇÃO X1, X2 , ...\n");
    printf("REPRESENTA AS VARIAVEIS DO SISTEMA\n\n");
    printf("-------------------------\n\n\n");

    system("pause");
    system("cls");

    printf("INSIRA A QUANTIDADE DE ELEMENTOS DA EQUAÇÃO (1 ATÉ 100): ");
    scanf("%d", &quant_Element);

    system("cls");
    printf("DÍGITE OS VALORES DO SISTEMA LINEAR\n\n");
    //LÊ A EQUAÇÃO
    for(int i = 0; i < quant_Element; i++){
        printf("%dº EQUAÇÃO\n\n", i+1);
        for(int j = 0; j < quant_Element; j++){
            printf("X%d = ", j+1);
            scanf("%lf", &x[i][j]);

            if(i == j){
                if(x[i][j] == 0){
                    printf("FUNÇÃO CONTÉM UM ELEMENTO DA DIAGONAL = 0\nIMPOSSIVÉL ISOLAR X%d",j);
                    return -1;
                }
            }
        }

        printf("B%d = ", i+1);
        scanf("%lf", &b[i]);

        system("cls");
        //IMPRIME A EQUAÇÃO NA TELA
        for(int k = 0; k <= i; k++){
            for(int q = 0; q < quant_Element; q++){
                printf("%.2lfX%d ", x[k][q], q+1);
            }
            printf("= %.2lf\n", b[k]);
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
    if( estri_Diag_Domin(x, quant_Element) == -1){
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
    scanf("%lf", &erro);

    while(opc > erro){

    for(int i = 0; i < quant_Element; i++){
        long double somatorio = 0;
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
                printf("%.2lfX%d ", x[k][q], q+1);
            }
            printf("= %.2lf\n", b[k]);
        }
    printf("\n\n");
    for(int t = 0; t < quant_Element; t++){
        if(interacoes != 0){
            printf("X%d = %.5lf --> ERRO %.4lf%%\n", t+1, resultado[t], calc_Erro(resultado[t], result_Anterior[t]));
            opc = calc_Erro(resultado[t], result_Anterior[t]);
            result_Anterior[t] = resultado[t];
        }else{
            result_Anterior[t] = resultado[t];
            printf("X%d = %.5lf\n", t+1, resultado[t]);
        }
    }
    interacoes++;
    printf("\n\n NÚMERO DE INTERAÇÕES: %d\n\n", interacoes);
    }
    return 0;
}
