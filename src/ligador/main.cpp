#include <iostream>

#include "ligador.h"

int main(int argc, char *argv[]) {
    Ligador ligador;
    for(int i = 1; i < argc; i++){
        ligador.adicionarPrograma(argv[i]);
    }
    std::cout << ligador.gerarCodigoMaquinaFinal(); // Gera o código que pode ser executado pelo emulador
}
