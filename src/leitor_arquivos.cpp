#include <iostream>

#include "leitor_arquivos.h"

LeitorArquivos::LeitorArquivos(std::string nomeArquivo) {
    this->arquivo.open(nomeArquivo);
}

bool LeitorArquivos::arquivoLidoAteFim() {
    return this->arquivo.eof();
}

std::string LeitorArquivos::obterProximaLinha() {
    std::string linha;
    std::getline(this->arquivo, linha);
    return linha;
}

LeitorArquivos::~LeitorArquivos() {
    this->arquivo.close();
}
