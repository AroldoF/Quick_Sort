#include <iostream>
#include <fstream>  // Necessário para manipulação de arquivos
#include <vector>   // Usado para lidar com tamanhos dinâmicos de arrays
#include <algorithm> // Para usar swap
using namespace std;

// Função para particionar o array
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Escolhe o último elemento como pivô
    int i = low - 1;  // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {  // Se o elemento atual for menor que o pivô
            i++;  // Incrementa o índice do menor elemento
            swap(arr[i], arr[j]);  // Troca os elementos
        }
    }
    swap(arr[i + 1], arr[high]);  // Coloca o pivô na posição correta
    return (i + 1);  // Retorna o índice do pivô
}

// Função recursiva do Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Encontra o índice do pivô

        quickSort(arr, low, pi - 1);  // Ordena recursivamente à esquerda do pivô
        quickSort(arr, pi + 1, high);  // Ordena recursivamente à direita do pivô
    }
}

// Função para carregar números de um arquivo
bool loadArrayFromFile(const string& filename, vector<int>& numbers) {
    ifstream file(filename);
    if (!file) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        return false;
    }

    int num;
    while (file >> num) {  // Lê números do arquivo
        numbers.push_back(num);
    }

    file.close();
    return true;
}

// Função para salvar os números ordenados no arquivo
bool saveArrayToFile(const string& filename, const vector<int>& numbers) {
    ofstream file(filename);
    if (!file) {
        cerr << "Erro ao abrir o arquivo para escrita: " << filename << endl;
        return false;
    }

    for (size_t i = 0; i < numbers.size(); i++) {
        file << numbers[i];
        if (i < numbers.size() - 1) {
            file << "\n";  
        }
    }

    file.close();
    return true;
}

int main() {
    string filename = "../100mihoes.txt";
    vector<int> numbers;

    // Carrega os números do arquivo para o vetor
    if (!loadArrayFromFile(filename, numbers)) {
        return 1;  // Sai do programa caso haja erro na leitura
    }

    int n = numbers.size();
    int* arr = numbers.data();  // Converte o vetor para array

    quickSort(arr, 0, n - 1);  // Ordena o array usando Quick Sort

    // Salva os números ordenados de volta no arquivo
    if (!saveArrayToFile(filename, numbers)) {
        return 1;  // Sai do programa caso haja erro na escrita
    }

    cout << "Arquivo atualizado com os números ordenados." << endl;

    return 0;
}
