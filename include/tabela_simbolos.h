#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <string>
#include <map>

class TabelaSimbolos {
    private:
        std::map<std::string, int> tabela;
    public:
        TabelaSimbolos();

        int obterValorSimbolo(std::string simbolo);

        bool simboloEstaRegistrado(std::string simbolo);

        void salvarSimbolo(std::string simbolo, int valor);
};

#endif
