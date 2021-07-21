#include "ligador.h"
#include "leitor_arquivos.h"
#include "util.h"

Ligador::Ligador() {}

void Ligador::adicionarPrograma(std::string arquivo) {
    LeitorArquivos leitor(arquivo);

    tamanhoProgramas.push_back(stoi(leitor.obterProximaLinha()));

    std::vector<std::string> programa = separaPalavras(leitor.obterProximaLinha());
    programas.insert(programas.end(), programa.begin(), programa.end());

    while(!leitor.arquivoLidoAteFim()) {
        std::vector<std::string> entradaTabela = separaPalavras(leitor.obterProximaLinha());
        if(entradaTabela.empty() || entradaTabela[1] == "ext") continue;
        std::string valorSimbolo = std::to_string(stoi(entradaTabela[1])+deslocamentoAtual);
        this->tabela.salvarSimbolo(entradaTabela[0],valorSimbolo);
    }

    deslocamentoAtual += tamanhoProgramas.back();
}

std::string Ligador::gerarCodigoMaquinaFinal() {
    int deslocamento = 0;
    for(unsigned long i=0; i < tamanhoProgramas.size(); i++) {
        for(int j=0; j < tamanhoProgramas[i]; j++) {
            if(programas[deslocamento + j].front() == 'E') {
                int posicao = stoi(programas[deslocamento + j].substr(1, programas[deslocamento + j].size()-1));
                posicao += deslocamento;
                programas[deslocamento + j] = std::to_string(posicao);
            }

            if(this->tabela.simboloEstaRegistrado(programas[deslocamento + j])) {
                int aux = stoi(this->tabela.obterValorSimbolo(programas[deslocamento + j])); 
                aux -= deslocamento + j - 1;
                programas[deslocamento + j] = std::to_string(aux);
            }
        }
        deslocamento += tamanhoProgramas[i];
    }

    // Coloca a primeira linha do programa
    std::string saida = "MV-EXE\n";
    // Coloca a segunda linha do programa
    saida += std::to_string(deslocamento);
    saida += " 0 ";
    saida += std::to_string(deslocamento+1000)  + " "; // Considera uma pilha de tamanho 1000
    saida += this->tabela.obterValorSimbolo("main") + "\n"; // Considera as constantes no ínicio do programa
    // Coloca as strings das operações do programa
    for(std::string valor : programas) {
        saida += valor + " ";
    }
    saida += "\n";
    // Retorna a string corresponde ao programa na linguagem de máquina do emulador
    return saida;
}
