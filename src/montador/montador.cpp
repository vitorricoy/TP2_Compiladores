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
            tabelaSimbolos.salvarSimbolo(palavras[0].substr(0, palavras[0].size()-1), numeroLinha);
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

std::vector<int> Montador::executarPassoDois(std::vector<std::vector<std::string> > tokens) {
    // Declara o vetor dos inteiros que compõe o programa final
    std::vector<int> resultadoFinal;
    // Inicializa a linha correspondente à instrução atual no programa final
    int linhaAtual = 0;
    // Inicializa as variáveis responsáveis por identificar quantas constantes 
    // existem no inicio do programa
    int constantesInicioAux = 0;
    bool encontrouConstantesInicio = false;
    // Itera pelas linhas
    for(std::vector<std::string> linha : tokens) {
        // Salva o valor antigo de constantes no inicio do programa
        int constantesInicioAntiga = constantesInicioAux;
        // Converte a instrução dessa linha para o código de máquina do emulador
        std::vector<int> codigoMaquina = Conversor::converterInstrucao(linha, this->tabelaSimbolos, linhaAtual, constantesInicioAux);
        // Se na conversão não foi encontrada constante, já encontrou todas as constantes
        // no início do programa
        // Também verifica se já não foram encontradas as constantes do ínicio
        if(!encontrouConstantesInicio && constantesInicioAntiga == constantesInicioAux) {
            // Salva o numero de constantes no inicio do programa
            this->constantesInicio = constantesInicioAntiga;
            // Determina que já encontrou todas as constantes no inicio do programa
            encontrouConstantesInicio = true;
        }
        // Insere os inteiros encontrados no programa final
        resultadoFinal.insert(resultadoFinal.end(), codigoMaquina.begin(), codigoMaquina.end());
    }
    // Retorna os inteiros do programa final
    return resultadoFinal;
}

std::string Montador::gerarPrograma(std::vector<int> instrucoes) {
    // Coloca a primeira linha do programa
    std::string saida = "MV-EXE\n";
    // Coloca a segunda linha do programa
    saida+=std::to_string(instrucoes.size());
    saida+=" 0 ";
    saida+=std::to_string(instrucoes.size()+1000)  + " "; // Considera uma pilha de tamanho 1000
    saida+=std::to_string(this->constantesInicio) + "\n"; // Considera as constantes no ínicio do programa
    // Coloca os inteiros das operações do programa
    for(int inteiro : instrucoes) {
        saida+=std::to_string(inteiro) + " ";
    }
    saida+= "\n";
    // Retorna a string corresponde ao programa na linguagem de máquina do emulador
    return saida;
}
