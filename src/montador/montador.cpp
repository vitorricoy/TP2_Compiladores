#include <iostream>
#include <vector>
#include <utility>

#include "util.h"
#include "montador.h"
#include "leitor_arquivos.h"
#include "tabela_simbolos.h"
#include "conversor_instrucoes.h"

Montador::Montador(std::string arquivoPrograma): leitorArquivos(arquivoPrograma){

}

std::vector<std::vector<std::string>> Montador::executarPassoUm() {

    // Declara o vetor que guarda o conjunto de tokens de cada linha
    std::vector<std::vector<std::string>> resultado;

    // Declara o vetor que guarda o conjunto de tokens da linha atual
    std::vector<std::string> palavras;

    // Inicializa o número da linha correspondente à instrução atual
    // no programa final
    int numeroLinha = 0;

    // Enquanto existir linhas no arquivo
    while(!leitorArquivos.arquivoLidoAteFim()) {
        std::string linha = this->leitorArquivos.obterProximaLinha();

        linha = removeComentario(linha);

        palavras = separaPalavras(linha);

        // A linha é formada por espaços vazios, comentários e espaços apenas
        if(palavras.empty()) {
            continue;
        }

        // Se a palavra é um token
        if(palavras[0].back() == ':') {
            tabelaSimbolos.salvarSimbolo(palavras[0].substr(0, palavras[0].size()-1), std::to_string(numeroLinha));
            palavras.erase(palavras.begin());
        }

        // Se a palavra é a pseudoinstrução WORD
        if(palavras[0] == "WORD") {
            palavras.erase(palavras.begin());
        }
        
        // Se a palavra é a pseudoinstrução END
        if(palavras[0] == "END") {
            break;
        }

        // Atualiza o número da linha correspondente à instrução atual
        // no programa final
        numeroLinha += tamanhoInstrucao(palavras[0]);

        // Se a linha agora está vazia, continua para a próxima linha
        if(palavras[0] == "") {
            continue;
        }

        // Adiciona os tokens gerados nessa linha na lista de tokens
        resultado.push_back(palavras);
    }

    // Retorna a lista de tokens
    return resultado;
}

std::vector<std::string> Montador::executarPassoDois(std::vector<std::vector<std::string> > tokens) {
    // Declara o vetor das strings que compõe o programa final
    std::vector<std::string> resultadoFinal;
    // Inicializa a linha correspondente à instrução atual no programa final
    int linhaAtual = 0;
    // Itera pelas linhas
    for(std::vector<std::string> linha : tokens) {
        // Converte a instrução dessa linha para o código de máquina do emulador
        std::vector<std::string> codigoMaquina = Conversor::converterInstrucao(linha, this->tabelaSimbolos, linhaAtual);
        // Insere os valores encontrados no programa final
        resultadoFinal.insert(resultadoFinal.end(), codigoMaquina.begin(), codigoMaquina.end());
    }
    // Retorna os valores do programa final
    return resultadoFinal;
}

std::string Montador::gerarPrograma(std::vector<std::string> instrucoes) {
    // Coloca a primeira linha da saída
    std::string saida = std::to_string(instrucoes.size()) + "\n";
    // Coloca os valores das operações e símbolos na saída
    for(std::string valor : instrucoes) {
        saida+= valor + " ";
    }
    saida+= "\n";
    // Coloca a tabela de símbolos na saída
    saida+= this->tabelaSimbolos.toString();
    // Retorna a string corresponde à saída para o ligador
    return saida;
}
