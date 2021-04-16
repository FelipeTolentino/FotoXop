#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Imagem.h"
#include "Filtros.h"

float convolucao(Imagem *img, int h, int w, float* pesos, int tam, int cor){
    float novaCor;
    if (tam == 3){
        novaCor = pesos[0] * obtemCor(img, h-1, w-1, cor);
        novaCor += pesos[1] * obtemCor(img, h-1, w, cor);
        novaCor += pesos[2] * obtemCor(img, h-1, w+1, cor);
        novaCor += pesos[3] * obtemCor(img, h, w-1, cor);
        novaCor += pesos[4] * obtemCor(img, h, w, cor);
        novaCor += pesos[5] * obtemCor(img, h, w+1, cor);
        novaCor += pesos[6] * obtemCor(img, h+1, w-1, cor);
        novaCor += pesos[7] * obtemCor(img, h+1, w, cor);
        novaCor += pesos[8] * obtemCor(img, h+1, w-1, cor);

    }
    else{
        novaCor = pesos[0] * obtemCor(img, h-2, w-2, cor);
        novaCor += pesos[1] * obtemCor(img, h-2, w-1, cor);
        novaCor += pesos[2] * obtemCor(img, h-2, w, cor);
        novaCor += pesos[3] * obtemCor(img, h-2, w+1, cor);
        novaCor += pesos[4] * obtemCor(img, h-2, w+2, cor);
        novaCor += pesos[5] * obtemCor(img, h-1, w-2, cor);
        novaCor += pesos[6] * obtemCor(img, h-1, w-1, cor);
        novaCor += pesos[7] * obtemCor(img, h-1, w, cor);
        novaCor += pesos[8] * obtemCor(img, h-1, w+1, cor);
        novaCor += pesos[9] * obtemCor(img, h-1, w+1, cor);
        novaCor += pesos[10] * obtemCor(img, h, w-2, cor);
        novaCor += pesos[11] * obtemCor(img, h, w-1, cor);
        novaCor += pesos[12] * obtemCor(img, h, w, cor);
        novaCor += pesos[13] * obtemCor(img, h, w+1, cor);
        novaCor += pesos[14] * obtemCor(img, h, w+2, cor);
        novaCor += pesos[15] * obtemCor(img, h+1, w-2, cor);
        novaCor += pesos[16] * obtemCor(img, h+1, w-1, cor);
        novaCor += pesos[17] * obtemCor(img, h+1, w, cor);
        novaCor += pesos[18] * obtemCor(img, h+1, w+1, cor);
        novaCor += pesos[19] * obtemCor(img, h+1, w+2, cor);
        novaCor += pesos[20] * obtemCor(img, h+2, w-2, cor);
        novaCor += pesos[21] * obtemCor(img, h+2, w-1, cor);
        novaCor += pesos[22] * obtemCor(img, h+2, w, cor);
        novaCor += pesos[23] * obtemCor(img, h+2, w+1, cor);
        novaCor += pesos[24] * obtemCor(img, h+2, w+2, cor);
    }
    novaCor = (novaCor > 255) ? 255 : novaCor;
    novaCor = (novaCor < 0) ? 0 : novaCor;

    return novaCor;
}

void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   - v) >= 0 ? (pixel.cor[RED]   - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? (pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  - v) >= 0 ? (pixel.cor[BLUE]  - v) : 0);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void clarearImagem(Imagem *img){
    int v;
    printf("Digite o fator de clareamento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++){
        for (int w = 0; w < obtemLargura(img); w++){
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED] = (((int)pixel.cor[RED] + v) <= 255 ? (pixel.cor[RED] + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? (pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE] = (((int)pixel.cor[BLUE] + v) <= 255 ? (pixel.cor[BLUE] + v) : 255);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void escalaDeCinzaImagem(Imagem *img){
    int novaCor, escolha;
    printf("\n======== ESCALA DE CINZA ========\n");
    printf(" '0' Media de cores\n"
           " '1' Pesos da cores\n"
           "Escolha um dos metodos: ");
    scanf("%d", &escolha);

    for (int h = 0; h < obtemAltura(img); h++){
        for (int w = 0; w < obtemLargura(img); w++){
            Pixel pixel = obtemPixel(img, h, w);
            if (escolha){
                novaCor = ((int)pixel.cor[RED] +
                (int)pixel.cor[GREEN] +
                (int)pixel.cor[BLUE])/3;
            }
            else{
                novaCor = (((int)pixel.cor[RED] * 0.3) +
                ((int)pixel.cor[GREEN] * 0.59) +
                ((int)pixel.cor[BLUE] * 0.11));
            }
            pixel.cor[RED] = (Byte)novaCor;
            pixel.cor[GREEN] = (Byte)novaCor;
            pixel.cor[BLUE] = (Byte)novaCor;
            recolorePixel(img, h, w, pixel);
        }
    }
}

void filtroSobel(Imagem *img){
    /* Dicas:
     * 1) Se quiser, pode ignorar as bordas das imagens
     * 2) Para o pixel na posição (h, w), obtenha os outros 8 pixels vizinhos e aplique a matriz gx e gy
     *    em cada banda de cor do pixel. Combine o valor obtido por gx e gy e modifique o pixel de img.
     *    Lembre-se que a obtenção dos pixels deve ser a partir de uma cópia da imagem.
     * 3) Verifique se o novo valor obtido para a banda de cor é um valor válido (entre 0 e 255).
    */

    Imagem *copia = copiaImagem(img);
    Pixel pixel;
    int yCor = 0, xCor = 0, media;

    for (int h = 1; h < obtemAltura(copia) - 1; h++){
        for (int w = 1; w < obtemLargura(copia) - 1; w++){
            for (int cor = 0; cor < 3; cor++){
                yCor = obtemCor(copia, h-1, w-1, cor);
                yCor += 2 * obtemCor(copia, h-1, w, cor);
                yCor += obtemCor(copia, h-1, w+1, cor);
                yCor += -1 * obtemCor(copia, h+1, w-1, cor);
                yCor += -2 * obtemCor(copia, h+1, w, cor);
                yCor += -1 * obtemCor(copia, h+1, w+1, cor);

                xCor = obtemCor(copia, h-1, w-1, cor);
                xCor += -1 * obtemCor(copia, h-1, w+1, cor);
                xCor += 2 * obtemCor(copia, h, w-1, cor);
                xCor += -2 * obtemCor(copia, h, w+1, cor);
                xCor += obtemCor(copia, h+1, w-1, cor);
                xCor += -1 * obtemCor(copia, h+1, w+1, cor);

                //xCor = (xCor > 255) ? 255 : xCor;
                //xCor = (xCor < 0) ? 0 : xCor;
                //yCor = (yCor > 255) ? 255 : yCor;
                //yCor = (yCor < 0) ? 0 : yCor;

                media = sqrt(pow(xCor, 2) + pow(yCor, 2));

                media = (media > 255) ? 255 : media;
                media = (media < 0) ? 0 : media;
                pixel.cor[cor] = (Byte)media;

            }
            recolorePixel(img, h, w, pixel);
        }
    }

    liberaImagem(copia);
}

void deteccaoBordasLaplace(Imagem *img) {
    Imagem *copia = copiaImagem(img);
    Pixel pixel;
    float kernel[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    int novaCor;

    for (int h = 1; h < obtemAltura(copia) - 1; h++){
        for (int w = 1; w < obtemLargura(copia) - 1; w++){
            for (int cor = 0; cor < 3; cor++){

                novaCor = convolucao(copia, h, w, kernel, 3, cor);
                pixel.cor[cor] = (Byte)novaCor;

            }
            recolorePixel(img, h, w, pixel);
        }
    }
    liberaImagem(copia);
}

void desfocarImagem(Imagem *img){
    Imagem *copia = copiaImagem(img);
    Pixel pixel;
    int novaCor;

    float kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 9; i++){
        kernel[i] *= 0.11;
    }

    for (int h = 1; h < obtemAltura(copia) - 1; h++){
        for (int w = 1; w < obtemLargura(copia) - 1; w++){
            for (int cor = 0; cor < 3; cor++){
                novaCor = convolucao(copia, h, w, kernel, 3, cor);
                pixel.cor[cor] = (Byte)novaCor;

            }
            recolorePixel(img, h, w, pixel);
        }
    }
    liberaImagem(copia);
}

void destacarRelevo(Imagem *img){
    Imagem *copia = copiaImagem(img);
    Pixel pixel;
    int novaCor;

    float kernel[] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};

    for (int h = 1; h < obtemAltura(copia) - 1; h++){
        for (int w = 1; w < obtemLargura(copia) - 1; w++){
            for (int cor = 0; cor < 3; cor++){
                novaCor = convolucao(copia, h, w, kernel, 3, cor);
                pixel.cor[cor] = (Byte)novaCor;

            }
            recolorePixel(img, h, w, pixel);
        }
    }
    liberaImagem(copia);
}

void trocaCor(Imagem *img){
    int corAntiga, corNova;
    printf("\n========== TROCAR COR ==========\n");
    printf(" '0' Vermelho\n"
           " '1' Verde\n"
           " '2' Azul\n");
    printf("Qual cor deseja substituir? ");
    scanf("%d", &corAntiga);
    printf("Por qual cor? ");
    scanf("%d", &corNova);
    Pixel pixel;
    Byte corAux;
    for (int h = 0; h < obtemAltura(img); h++){
        for (int w = 0; w < obtemLargura(img); w++){
            pixel = obtemPixel(img, h, w);

            if (!corAntiga){
                if (pixel.cor[RED] > pixel.cor[GREEN] &&
                    pixel.cor[RED] > pixel.cor[BLUE]){
                        corAux = pixel.cor[RED];
                        pixel.cor[RED] = pixel.cor[corNova];
                        pixel.cor[corNova] = corAux;
                    }
            }
            else if (corAntiga == 1){
                if (pixel.cor[GREEN] > pixel.cor[RED] &&
                    pixel.cor[GREEN] > pixel.cor[BLUE]){
                        corAux = pixel.cor[GREEN];
                        pixel.cor[GREEN] = pixel.cor[corNova];
                        pixel.cor[corNova] = corAux;
                    }
            }
            else{
                if (pixel.cor[BLUE] > pixel.cor[RED] &&
                    pixel.cor[BLUE] > pixel.cor[GREEN]){
                        corAux = pixel.cor[BLUE];
                        pixel.cor[BLUE] = pixel.cor[corNova];
                        pixel.cor[corNova] = corAux;
                    }
            }

            recolorePixel(img, h, w, pixel);
        }
    }
}

void espelhar(Imagem *img){
    int eixo;
    printf("\n========= ESPELHAR =========\n");
    printf(" '0' Eixo Y\n"
           " '1' Eixo X\n");
    printf("Em qual eixo deseja espelhar? ");
    scanf("%d", &eixo);
    Pixel pixel;
    int altura = obtemAltura(img);
    int largura = obtemLargura(img);
    int larAux, altAux;
    if (!eixo){
        for (int h = 0; h < altura; h++){
            larAux = largura/2;
            for (int w = largura/2; w < largura; w++){
                pixel = obtemPixel(img, h, larAux);
                recolorePixel(img, h, w, pixel);
                larAux--;
            }
        }
    }
    else{
        altAux = 0;
        for (int h = altura - 1; h >= altura/2; h--){
            larAux = 0;
            for (int w = 0; w < largura; w++){
                pixel = obtemPixel(img, altAux, larAux);
                recolorePixel(img, h, w, pixel);
                larAux++;
            }
            altAux++;
        }
    }
}

void negativarImagem(Imagem *img){
    Pixel pixel;
    Byte novaCor;
    for (int h = 0; h < obtemAltura(img); h++){
        for (int w = 0; w < obtemLargura(img); w++){
            pixel = obtemPixel(img, h, w);
            for(int cor = 0; cor < 3; cor++){
                novaCor = (Byte)(255 - (int)pixel.cor[cor]);
                pixel.cor[cor] = novaCor;
            }

            recolorePixel(img, h, w, pixel);
        }
    }
}

void filtroListras(Imagem* img){
    int espaco, escolha, h, w, red, green, blue;
    int* orientacao;
    printf(" '0' horizontal\n"
           " '1' vertical\n");
    printf("Qual a orientação das litras? ");
    scanf("%d", &escolha);
    printf("Espacamento das listras em pixels\n"
           "(Valores entre 3-5 dão bons resultados): ");
    scanf("%d", &espaco);
    printf("Informe a cor das listras (valores para R, G e B)\n");
    printf("R: ");
    scanf("%d", &red);
    red = (red > 255) ? 255 : red;
    red = (red < 0) ? 0 : red;
    printf("G: ");
    scanf("%d", &green);
    green = (green > 255) ? 255 : green;
    green = (green < 0) ? 0 : green;
    printf("B: ");
    scanf("%d", &blue);
    blue = (blue > 255) ? 255 : blue;
    blue = (blue < 0) ? 0 : blue;
    if (!escolha)
        orientacao = &h;
    else
        orientacao = &w;
    Pixel pixel;
    for (h = 0; h < obtemAltura(img); h++){
        for (w = 0; w < obtemLargura(img); w++){
            if (*orientacao % espaco == 0){
                pixel = obtemPixel(img, h, w);
                pixel.cor[RED] = (Byte)red;
                pixel.cor[GREEN] = (Byte)green;
                pixel.cor[BLUE] = (Byte)blue;
                recolorePixel(img, h, w, pixel);
            }
        }
    }
}

void cinzaSemEscolha(Imagem *img){
    int novaCor;

    for (int h = 0; h < obtemAltura(img); h++){
        for (int w = 0; w < obtemLargura(img); w++){
            Pixel pixel = obtemPixel(img, h, w);
            novaCor = (((int)pixel.cor[RED] * 0.3) +
                        ((int)pixel.cor[GREEN] * 0.59) +
                        ((int)pixel.cor[BLUE] * 0.11));
            pixel.cor[RED] = (Byte)novaCor;
            pixel.cor[GREEN] = (Byte)novaCor;
            pixel.cor[BLUE] = (Byte)novaCor;
            recolorePixel(img, h, w, pixel);
        }
    }
}

int geraRandom(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void filtroGlitch(Imagem* img){
    int desloc;
    printf("Informe o deslocamento em pixels. \n"
           "(Valores entre 10-20 dão bons resultados): ");
    scanf("%d", &desloc);

    cinzaSemEscolha(img);
    Imagem* semRed = copiaImagem(img);

    Pixel pixel, pixelCinza, pixelGlitch;
    for (int h = 0; h < obtemAltura(img); h++){
        for (int w = 0; w < obtemLargura(img); w++){
                pixel = obtemPixel(semRed, h, w);
                pixel.cor[RED] = 0;
                recolorePixel(semRed, h, w, pixel);
        }
    }

    for (int h = 0; h < obtemAltura(img); h++){
        for (int w = desloc; w < obtemLargura(img); w++){
                pixelCinza = obtemPixel(img, h, w);
                pixelGlitch = obtemPixel(semRed, h, w - desloc);
                pixelCinza.cor[GREEN] = pixelGlitch.cor[GREEN];
                pixelCinza.cor[BLUE] = pixelGlitch.cor[GREEN];

                recolorePixel(img, h, w, pixelCinza);
        }
    }
    liberaImagem(semRed);
}

void opcoesMeuFiltro(){
    printf("\n"
           "\n*********** OPCOES DE FILTROS ***********\n"
           " '0' para manter a imagem original\n"
           " '1' para escurecer a imagem\n"
           " '2' para clarear a imagem\n"
           " '3' para deixar a imagem em escala de cinza\n"
           " '4' para aplicar o filtro de Sobel\n"
           " '5' para aplicar a detecção de bordas de Laplace\n"
           " '6' para aplicar desfoque\n"
           " '7' para aplicar destaque de relevo\n"
           " '8' para aplicar a troca de cores\n"
           " '9' para aplicar a espelhagem\n"
           " '10' para aplicar o negativo\n"
           " '11' para aplicar listras\n"
           " '12' para aplicar efeito glitch\n");
}

void geraVetorFiltros(Imagem* img, Imagem** efeitos, int* escolha, int qnt){
    for(int i = 0; i < qnt; i++){
        if (escolha[i] == 1){
            efeitos[i] = copiaImagem(img);
            escurecerImagem(efeitos[i]);
        }
        else if (escolha[i] == 2){
            efeitos[i] = copiaImagem(img);
            clarearImagem(efeitos[i]);
        }
        else if (escolha[i] == 3){
            efeitos[i] = copiaImagem(img);
            escalaDeCinzaImagem(efeitos[i]);
        }
        else if (escolha[i] == 4){
            efeitos[i] = copiaImagem(img);
            filtroSobel(efeitos[i]);
        }
        else if (escolha[i] == 5){
            efeitos[i] = copiaImagem(img);
            deteccaoBordasLaplace(efeitos[i]);
        }
        else if (escolha[i] == 6){
            efeitos[i] = copiaImagem(img);
            desfocarImagem(efeitos[i]);
        }
        else if (escolha[i] == 7){
            efeitos[i] = copiaImagem(img);
            destacarRelevo(efeitos[i]);
        }
        else if (escolha[i] == 8){
            efeitos[i] = copiaImagem(img);
            trocaCor(efeitos[i]);
        }
        else if (escolha[i] == 9){
            efeitos[i] = copiaImagem(img);
            espelhar(efeitos[i]);
        }
        else if (escolha[i] == 10){
            efeitos[i] = copiaImagem(img);
            negativarImagem(efeitos[i]);
        }
        else if (escolha[i] == 11){
            efeitos[i] = copiaImagem(img);
            filtroListras(efeitos[i]);
        }
        else if (escolha[i] == 12){
            efeitos[i] = copiaImagem(img);
            filtroGlitch(efeitos[i]);
        }
        else{
            efeitos[i] = copiaImagem(img);
        }

    }
}

void meuFiltro(Imagem *img){

    int grid;
    printf("\n========== MODO DO GRID ==========\n"
           " '0' Grid 2x2\n"
           " '1' Dividir Horizontalmente\n"
           " '2' Dividir Verticalmente\n"
           " '3' Dividir na diagonal\n");
    printf("Escolha o formato do grid: ");
    scanf("%d", &grid);

    int altura = obtemAltura(img);
    int largura = obtemLargura(img);
    Pixel pixel;

    int escolha[4];
    Imagem* efeitos[4];

    switch(grid){
    case 0:
        opcoesMeuFiltro();
        printf("Qual efeito filtro no 1 quadrante: ");
        scanf("%d", &escolha[0]);
        printf("Qual efeito filtro no 2 quadrante: ");
        scanf("%d", &escolha[1]);
        printf("Qual efeito filtro no 3 quadrante: ");
        scanf("%d", &escolha[2]);
        printf("Qual efeito filtro no 4 quadrante: ");
        scanf("%d", &escolha[3]);

        geraVetorFiltros(img, efeitos, escolha, 4);

        for(int h = 0; h < altura; h++){
            for (int w = 0; w < largura; w++){

                if (h < altura/2 && w < largura/2){
                    pixel = obtemPixel(efeitos[0], h, w);
                    recolorePixel(img, h, w, pixel);
                }
                else if (h < altura/2 && w >= largura/2){
                    pixel = obtemPixel(efeitos[1], h, w);
                    recolorePixel(img, h, w, pixel);
                }
                else if (h >= altura/2 && w < largura/2){
                    pixel = obtemPixel(efeitos[2], h, w);
                    recolorePixel(img, h, w, pixel);
                }
                else{
                    pixel = obtemPixel(efeitos[3], h, w);
                    recolorePixel(img, h, w, pixel);
                }
            }
        }

        for (int k = 0; k < 4; k++){
            if (efeitos[k] == img) continue;
            liberaImagem(efeitos[k]);
        }
        break;

    case 1:
        opcoesMeuFiltro();
        printf("Qual efeito filtro no 1 quadrante: ");
        scanf("%d", &escolha[0]);
        printf("Qual efeito filtro no 2 quadrante: ");
        scanf("%d", &escolha[1]);

        geraVetorFiltros(img, efeitos, escolha, 2);

        for(int h = 0; h < altura; h++){
            for (int w = 0; w < largura; w++){

                if (h < altura/2){
                    pixel = obtemPixel(efeitos[0], h, w);
                    recolorePixel(img, h, w, pixel);
                }
                else{
                    pixel = obtemPixel(efeitos[1], h, w);
                    recolorePixel(img, h, w, pixel);
                }
            }
        }

        for (int k = 0; k < 2; k++){
            liberaImagem(efeitos[k]);
        }
        break;
    case 2:
        opcoesMeuFiltro();
        printf("Qual efeito filtro no 1 quadrante: ");
        scanf("%d", &escolha[0]);
        printf("Qual efeito filtro no 2 quadrante: ");
        scanf("%d", &escolha[1]);

        geraVetorFiltros(img, efeitos, escolha, 2);

        for(int h = 0; h < altura; h++){
            for (int w = 0; w < largura; w++){

                if (w < largura/2){
                    pixel = obtemPixel(efeitos[0], h, w);
                    recolorePixel(img, h, w, pixel);
                }
                else{
                    pixel = obtemPixel(efeitos[1], h, w);
                    recolorePixel(img, h, w, pixel);
                }
            }
        }

        for (int k = 0; k < 2; k++){
            liberaImagem(efeitos[k]);
        }
        break;
    case 3:
        opcoesMeuFiltro();
        printf("Qual efeito filtro no 1 quadrante: ");
        scanf("%d", &escolha[0]);
        printf("Qual efeito filtro no 2 quadrante: ");
        scanf("%d", &escolha[1]);

        geraVetorFiltros(img, efeitos, escolha, 2);

        for(int h = 0; h < altura; h++){
            for (int w = 0; w < largura; w++){

                if (h < w){
                    pixel = obtemPixel(efeitos[0], h, w);
                    recolorePixel(img, h, w, pixel);
                }
                else{
                    pixel = obtemPixel(efeitos[1], h, w);
                    recolorePixel(img, h, w, pixel);
                }
            }
        }

        for (int k = 0; k < 2; k++){
            liberaImagem(efeitos[k]);
        }
    }

}
