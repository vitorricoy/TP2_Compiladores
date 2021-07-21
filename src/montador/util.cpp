#include "util.h"
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> separaPalavras(std::string linha) {
    std::istringstream streamLinha(linha);
    std::string palavra;
    std::vector<std::string> palavras;

    while (streamLinha >> palavra) {
        palavras.push_back(palavra);
    }

    return palavras;
}

std::string juntaPalavras(std::vector<std::string> linha) {
    std::string join("");

    for (std::string palavra: linha) {
        join = join + palavra + " ";
    }

    return join;
}

std::string removeComentario(std::string linha) {
    return linha.substr(0, linha.find(";"));
}

int tamanhoInstrucao(std::string mnemonico) {
    if(mnemonico == "HALT" || mnemonico == "RET") {
        return 1;
    }
    
    if(mnemonico == "LOAD" || mnemonico == "STORE" || mnemonico == "COPY" || mnemonico == "ADD" ||
       mnemonico == "SUB" || mnemonico == "MUL" || mnemonico == "DIV" || mnemonico == "MOD" ||
       mnemonico == "AND" || mnemonico == "OR") {
        return 3;
    }

    if(mnemonico == "READ" || mnemonico == "WRITE" || mnemonico == "PUSH" || mnemonico == "POP" ||
       mnemonico == "NOT" || mnemonico == "JUMP" || mnemonico == "JZ" || mnemonico == "JN" || 
       mnemonico == "CALL") {
        return 2;
    }

    return 1;
}