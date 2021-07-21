#ifndef LIGADOR_H
#define LIGADOR_H

#include "tabela_simbolos.h"
#include <iostream>
#include <vector>

class Ligador {
    private:
        std::vector<std::string> programas;
        std::vector<int> tamanhoProgramas;
        TabelaSimbolos tabela;
        int deslocamentoAtual = 0;

    public:
        Ligador();

        void adicionarPrograma(std::string arquivo);

        std::string gerarCodigoMaquinaFinal();
};

#endif
