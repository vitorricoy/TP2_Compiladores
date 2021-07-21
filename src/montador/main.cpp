#include <iostream>

#include "montador.h"

int main(int argc, char *argv[]) {
    std::string arquivo = argv[1];
    Montador montador(arquivo);
    auto tokens = montador.executarPassoUm();
    auto resultado = montador.executarPassoDois(tokens);
    std::string programa = montador.gerarPrograma(resultado);
    std::cout << programa; // Exibe o programa gerado pelo montador
    return 0;
}
