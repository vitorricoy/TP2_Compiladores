#ifndef CONVERSOR_INSTRUCOES_H
#define CONVERSOR_INSTRUCOES_H

#include <iostream>
#include <vector>

#include "tabela_simbolos.h"

namespace Conversor {
    int converterOperando(std::string operando, TabelaSimbolos& tabela, int& linhaAtual);
    std::vector<int> converterInstrucao(std::vector<std::string> instrucao, TabelaSimbolos& tabela, int& linhaAtual, int& constantesVistas);
}

#endif
