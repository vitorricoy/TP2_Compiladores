#include "tabela_simbolos.h"

#include <iostream>
#include <map>

TabelaSimbolos::TabelaSimbolos() {
    this->tabela = std::map<std::string, std::string>();
}

std::string TabelaSimbolos::obterValorSimbolo(std::string simbolo) {
    return this->tabela[simbolo];
}

void TabelaSimbolos::salvarSimbolo(std::string simbolo, std::string valor) {
    this->tabela[simbolo] = valor;
}

bool TabelaSimbolos::simboloEstaRegistrado(std::string simbolo) {
    return this->tabela.find(simbolo) != this->tabela.end();
}

std::string TabelaSimbolos::toString() {
    std::string saida = "";
    for(auto parChaveValor : this->tabela) {
        saida += parChaveValor.first + " " + parChaveValor.second + "\n";
    }
    return saida;
}