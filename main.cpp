#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/* funcao para carregar dados do arquivo dados.txt */
vector<int> carregarDados(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    vector<int> dados;
    int numero;

    if (arquivo.is_open()) {
        while (arquivo >> numero) { // operador para ler somente numeros
            dados.push_back(numero); // adiciona o numero no vetor e aumenta o tamanho do vetor 
        }
        arquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo '" << nomeArquivo << "'. Verifique se o arquivo existe.\n";
    }

    return dados;
}

/* funcao bubble Sort */
void bubbleSort(vector<int>& dados) {
    for (size_t i = 0; i < dados.size(); i++) {
        for (size_t j = 0; j < dados.size() - i - 1; ++j) {
            if (dados[j] > dados[j + 1]) {
                swap(dados[j], dados[j + 1]); // troca os valores de posicao
            }
        }
    }
    cout << "Dados ordenados com Bubble Sort.\n";
}

/* funcao para salvar os dados ordenados em dados_ordenados.txt */
void salvarDados(const string& nomeArquivo, const vector<int>& dados) {
    ofstream arquivo(nomeArquivo); // abre o arquivo para armaezar os dados ordenados

    if (arquivo.is_open()) {
        for (int numero : dados) {
            arquivo << numero << endl; // escreve os dados no arquivo
        }
        arquivo.close();
        cout << "Dados salvos em '" << nomeArquivo << "'.\n";
    } else {
        cerr << "Erro ao salvar os dados no arquivo '" << nomeArquivo << "'.\n";
    }
}

/* caso o usuario digite 1, venha para qual algoritmo ele deseja usar */
void escolherAlgoritmo(int& algoritmoSelecionado) {
    cout << "Escolha o algoritmo de ordenacao:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Quick Sort\n";
    cout << "3. Merge Sort\n";
    cout << "Opcao: ";
    cin >> algoritmoSelecionado;

    if (algoritmoSelecionado < 1 || algoritmoSelecionado > 3) {
        cout << "Opcao invalida, escolha novamente.\n";
        escolherAlgoritmo(algoritmoSelecionado);
    } else {
        cout << "Algoritmo " << algoritmoSelecionado << " selecionado.\n";
    }
}

/* funcao principal */
int main() {
    int option = 0;
    int algoritmoSelecionado = 0;

    while (option != 4) {
        cout << "===============================\n";
        cout << "     SISTEMA DE ORDENACAO      \n";
        cout << "===============================\n";
        cout << "1. Escolher algoritmo de ordenacao\n";
        cout << "2. Ordenar dados (Crescente)\n";
        cout << "3. Gerar relatorio de desempenho\n";
        cout << "4. Sair\n";
        cout << "===============================\n";

        cout << "Escolha uma opcaoo: ";
        cin >> option;

        switch (option) {
            case 1:
                escolherAlgoritmo(algoritmoSelecionado);
                break;
            case 2: {
                if (algoritmoSelecionado == 1) {
                    // Carregar os dados do arquivo
                    vector<int> dados = carregarDados("dados.txt");

                    if (!dados.empty()) {
                        cout << "Dados carregados com sucesso. Ordenando...\n";

                        // Ordenar os dados com Bubble Sort
                        bubbleSort(dados);

                        // Salvar os dados ordenados em um novo arquivo
                        salvarDados("dados_ordenados.txt", dados);
                    }
                } else {
                    cout << "Funcionalidade para outros algoritmos ainda nao implementada.\n";
                }
                break;
            }
            case 3:
                cout << "Funcionalidade de relatório sera implementada aqui.\n";
                break;
            case 4:
                cout << "Saindo do sistema.\n";
                break;
            default:
                cout << "Opcao invalida, tente novamente.\n";
        }
    }

    return 0;
}
