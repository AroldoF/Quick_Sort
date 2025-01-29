#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std;

int medianaDeTres(int vetor[], int menor, int maior) {
    int meio = menor + (maior - menor) / 2;

    if (vetor[menor] > vetor[meio])
        swap(vetor[menor], vetor[meio]);
    if (vetor[menor] > vetor[maior])
        swap(vetor[menor], vetor[maior]);
    if (vetor[meio] > vetor[maior])
        swap(vetor[meio], vetor[maior]);

    return meio;
}

int particao(int vetor[], int menor, int maior) {
    int pivoIndex = medianaDeTres(vetor, menor, maior);
    swap(vetor[pivoIndex], vetor[maior]);
    int pivo = vetor[maior];
    int i = menor - 1;

    for (int j = menor; j < maior; j++) {
        if (vetor[j] < pivo) {
            i++;
            swap(vetor[i], vetor[j]);
        }
    }
    swap(vetor[i + 1], vetor[maior]);
    return i + 1;
}

void quickSort(int vetor[], int menor, int maior) {
    while (menor < maior) {
        int pi = particao(vetor, menor, maior);

        if (pi - menor < maior - pi) {
            quickSort(vetor, menor, pi - 1);
            menor = pi + 1;
        } else {
            quickSort(vetor, pi + 1, maior);
            maior = pi - 1;
        }
    }
}

void quickSortParalelo(int vetor[], int menor, int maior, int profundidade = 0) {
    if (menor < maior) {
        int pi = particao(vetor, menor, maior);

        if (profundidade < 4) {
            thread esquerda(quickSortParalelo, vetor, menor, pi - 1, profundidade + 1);
            quickSortParalelo(vetor, pi + 1, maior, profundidade + 1);
            esquerda.join();
        } else {
            quickSort(vetor, menor, pi - 1);
            quickSort(vetor, pi + 1, maior);
        }
    }
}

bool Importar_txt(const string &endereco, vector<int> &numeros) {
    ifstream arquivo(endereco);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo " << endereco << endl;
        return false;
    }

    int num;
    while (arquivo >> num) {
        numeros.push_back(num);
    }
    arquivo.close();
    return true;
}

bool salvar_txt(const string &endereco, const vector<int> &numeros) {
    ofstream arquivo(endereco);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para escrita: " << endereco << endl;
        return false;
    }

    for (size_t i = 0; i < numeros.size(); i++) {
        arquivo << numeros[i] << (i < numeros.size() - 1 ? "\n" : "");
    }
    arquivo.close();
    return true;
}

int main() {
    string endereco = "../50_milhoes.txt";
    vector<int> numeros;

    auto codigo_tempo = chrono::high_resolution_clock::now();

    if (!Importar_txt(endereco, numeros)) {
        return 1;
    }

    int tamanho = numeros.size();
    int *vetor = numeros.data();

    auto inicio = chrono::high_resolution_clock::now();

    quickSortParalelo(vetor, 0, tamanho - 1);

    auto resultado = chrono::high_resolution_clock::now() - codigo_tempo;
    long long milissegundos = chrono::duration_cast<chrono::milliseconds>(resultado).count();
    double segundos = chrono::duration<double>(resultado).count();

    if (!salvar_txt(endereco, numeros)) {
        return 1;
    }

    auto codigo_tempo_resultado = chrono::high_resolution_clock::now() - inicio;
    long long tempo_milissegundos = chrono::duration_cast<chrono::milliseconds>(codigo_tempo_resultado).count();
    double tempo_segundos = chrono::duration<double>(codigo_tempo_resultado).count();

    cout << "\nArquivo atualizado com os números ordenados." << endl;
    cout << "\nTempo do Algoritmo por completo:" << endl;
    cout << " Tempo em milissegundos: " << tempo_milissegundos << endl;
    cout << " Tempo em segundos: " << tempo_segundos << endl;

    cout << "\nTempo do QuickSort:" << endl;
    cout << " Tempo em milissegundos: " << milissegundos << endl;
    cout << " Tempo em segundos: " << segundos << endl;
    return 0;
}