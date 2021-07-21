#include "tabela_simbolos.h"

#include <iostream>
#include <map>

TabelaSimbolos::TabelaSimbolos() {
    this->tabela = std::map<std::string, int>();
}

int TabelaSimbolos::obterValorSimbolo(std::string simbolo) {
    return this->tabela[simbolo];
}

void TabelaSimbolos::salvarSimbolo(std::string simbolo, int valor) {
    this->tabela[simbolo] = valor;
}

bool TabelaSimbolos::simboloEstaRegistrado(std::string simbolo) {
    return this->tabela.find(simbolo) != this->tabela.end();
}