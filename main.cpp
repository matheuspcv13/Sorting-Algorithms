#include <iostream>
#include <fstream>
#include <vector> /* biblioteca para auxiliar manipulacao dos vetores */
#include <string>

using namespace std;
int qtd_trocas = 0;
int qtd_comparacoes = 0;

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
void bubbleSort(vector<int>& dados, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - i - 1; ++j) {
            if (dados[j] > dados[j + 1]) {
                swap(dados[j], dados[j + 1]); // troca os valores de posicao
            }
        }
    }
    cout << "Dados ordenados com Bubble Sort.\n";
}

/* funcao de ordenacao quicksort */
void quicksort(vector<int>& dados, int inicio, int fim, int& qtd_trocas, int& qtd_comparacoes) {
    if (inicio < fim) {
        int i = inicio;
        int j = fim - 1;
        int pivo = dados[(inicio + fim) / 2] ;

        while (i <= j) {
            while (dados[i] < pivo) i++; /* se elemento for menor que pivo i anda para direita */ 
            while (dados[j] > pivo) j--; /* se elemento for maior que pivo j anda para esquerda */
            if (i <= j) {
                swap(dados[i], dados[j]); /* troca de elementos no array */
                qtd_trocas++;
            }
                qtd_comparacoes++;
                i++;
                j--;
        }

        if (j > inicio) {
            quicksort(dados, inicio, j + 1, qtd_trocas, qtd_comparacoes);
        }
        if (i < fim) {
            quicksort(dados, i, fim, qtd_trocas, qtd_comparacoes);
        }

    }
}

/* funcao para mesclar dois subvetores ordenados */
void merge(vector<int>& dados, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1; /* tamanho do subvetor esquerdo */
    int n2 = fim - meio; /* tamanho do subvetor direito */

    /* vetores temporarios */
    vector<int> esquerda(n1);
    vector<int> direita(n2);

    /* copiando os dados para os vetores temporarios */
    for (int i = 0; i < n1; i++) {
        esquerda[i] = dados[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        direita[j] = dados[meio + 1 + j];
    }

    /* indices */
    int i = 0, j = 0, k = inicio;

    /* mesclando os dois vetores ordenados */
    while (i < n1 && j < n2) {
        if (esquerda[i] <= direita[j]) {
            dados[k] = esquerda[i];
            i++;
        } else {
            dados[k] = direita[j];
            j++;
        }
        k++;
    }

    /* copiando os elementos restantes (se houver) do vetor esquerdo */
    while (i < n1) {
        dados[k] = esquerda[i];
        i++;
        k++;
    }

    /* copiando os elementos restantes (se houver) do vetor direito */
    while (j < n2) {
        dados[k] = direita[j];
        j++;
        k++;
    }
}

/* funcao principal do merge sort */
void mergeSort(vector<int>& dados, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSort(dados, inicio, meio);
        mergeSort(dados, meio + 1, fim);

        /* funcao principal do merge sort */
        merge(dados, inicio, meio, fim);
    }
}

/* funcao para salvar os dados ordenados em dados_ordenados.txt */
void salvarDados(const string& nomeArquivo, const vector<int>& dados) {
    ofstream arquivo(nomeArquivo); /* abre o arquivo para armaezar os dados ordenados */ 

    if (arquivo.is_open()) {
        for (int numero : dados) {
            arquivo << numero << endl; /* escredo os numeros no arquivo */
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
                    // carregar os dados do arquivo
                    vector<int> dados = carregarDados("dados.txt");
                    int tamanho = dados.size();

                    if (dados.empty()) {
                        cout << "Arquivo vazio!\n";
                    } else {
                        if (algoritmoSelecionado == 1) {
                            // Ordenar os dados com Bubble Sort
                            bubbleSort(dados, tamanho);

                        } else if (algoritmoSelecionado == 2) {
                            // Ordenar os dados com quick Sort
                            quicksort(dados, 0, tamanho, qtd_trocas, qtd_comparacoes);

                        } else if (algoritmoSelecionado == 3) {
                            mergeSort(dados, 0, tamanho - 1);
                        } else {
                            cout << "Escolha primeiro um metodo de ordenacao.\n";
                        }

                        // Salvar os dados ordenados em um novo arquivo
                        salvarDados("dados_ordenados.txt", dados);
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
