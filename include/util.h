#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>

std::vector<std::string> separaPalavras(std::string linha);

std::string juntaPalavras(std::vector<std::string> linha);

std::string removeComentario(std::string linha);

int tamanhoInstrucao(std::string mnemonico);

#endif
