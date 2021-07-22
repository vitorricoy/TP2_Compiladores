#include "ligador.h"
#include "leitor_arquivos.h"
#include "util.h"

Ligador::Ligador() {}

void Ligador::adicionarPrograma(std::string arquivo) {
    LeitorArquivos leitor(arquivo);
    // Salva o tamanho do programa, na ordem que foi lido
    tamanhoProgramas.push_back(stoi(leitor.obterProximaLinha()));

    // Adiciona as instruções e labels desse programa na lista de instruções e labels geral
    std::vector<std::string> programa = separaPalavras(leitor.obterProximaLinha());
    programas.insert(programas.end(), programa.begin(), programa.end());

    // Enquanto existir entradas da tabela de símbolos
    while(!leitor.arquivoLidoAteFim()) {
        std::vector<std::string> entradaTabela = separaPalavras(leitor.obterProximaLinha());
        // Se a linha não corresponder a uma entrada ou se essa entrada é um símbolo externo
        // Ignora o conteúdo da linha
        if(entradaTabela.empty() || entradaTabela[1] == "ext") continue;
        // Adiciona a posição de memória referenciada por esse símbolo no programa final
        // Para isso, é considerado o deslocamento do programa sendo analisado no momento
        std::string valorSimbolo = std::to_string(stoi(entradaTabela[1])+deslocamentoAtual);
        // Salva o símbolo com sua posição na tabela de símbolos
        this->tabela.salvarSimbolo(entradaTabela[0],valorSimbolo);
    }
    // Calcula o deslocamento do próximo programa lido
    deslocamentoAtual += tamanhoProgramas.back();
}

std::string Ligador::gerarCodigoMaquinaFinal() {
    // Itera pelas operações e símbolos de cada programa lido
    int deslocamento = 0;
    for(unsigned long i=0; i < tamanhoProgramas.size(); i++) {
        for(int j=0; j < tamanhoProgramas[i]; j++) {
            // Se essa entrada do programa é um símbolo previamente desconhecido
            if(this->tabela.simboloEstaRegistrado(programas[deslocamento + j])) {
                // Resolve o símbolo
                int aux = stoi(this->tabela.obterValorSimbolo(programas[deslocamento + j])); 
                // Atualiza a referência do símbolo para considerar o endereçamento relativo ao PC
                aux -= deslocamento + j + 1;
                // Salva o resultado na posição, sobrescrevendo o símbolo desconhecido
                programas[deslocamento + j] = std::to_string(aux);
            }
        }
        // Registra o deslocamento do programa
        deslocamento += tamanhoProgramas[i];
    }

    // Coloca a primeira linha do programa
    std::string saida = "MV-EXE\n";
    // Coloca a segunda linha do programa
    saida += std::to_string(deslocamento); // Vale notar que 'deslocamento' corresponde ao tamanho do programa
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
