#ifndef CONVERSOR_INSTRUCOES_H
#define CONVERSOR_INSTRUCOES_H

#include <iostream>
#include <vector>

#include "tabela_simbolos.h"

namespace Conversor {
    std::string converterOperando(std::string operando, TabelaSimbolos& tabela, int& linhaAtual);
    std::vector<std::string> converterInstrucao(std::vector<std::string> instrucao, TabelaSimbolos& tabela, int& linhaAtual, int& constantesVistas);
}

#endif
