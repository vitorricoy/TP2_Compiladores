#ifndef MONTADOR_H
#define MONTADOR_H

#include <iostream>
#include <vector>
#include <utility>

#include "leitor_arquivos.h"
#include "tabela_simbolos.h"

class Montador {
    private:
        LeitorArquivos leitorArquivos;
        TabelaSimbolos tabelaSimbolos;
        std::vector<std::pair<std::string, int> > constantes;
    public:
        Montador(std::string arquivoPrograma);
        std::vector<std::vector<std::string>> executarPassoUm();
        std::vector<std::string> executarPassoDois(std::vector<std::vector<std::string>> tokens);
        std::string gerarPrograma(std::vector<std::string> instrucoes);

};

#endif
