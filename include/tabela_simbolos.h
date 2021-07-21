#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <string>
#include <map>

class TabelaSimbolos {
    private:
        std::map<std::string, std::string> tabela;
    public:
        TabelaSimbolos();

        std::string obterValorSimbolo(std::string simbolo);

        bool simboloEstaRegistrado(std::string simbolo);

        void salvarSimbolo(std::string simbolo, std::string valor);

        std::string toString();
};

#endif
