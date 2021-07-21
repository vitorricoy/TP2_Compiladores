#ifndef LEITOR_ARQUIVOS_H
#define LEITOR_ARQUIVOS_H

#include <iostream>
#include <fstream>

class LeitorArquivos {
    private:
        std::ifstream arquivo;
    public:
        ~LeitorArquivos();

        LeitorArquivos(std::string nomeArquivo);

        bool arquivoLidoAteFim();

        std::string obterProximaLinha();
};

#endif
