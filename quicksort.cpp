#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
// Para usar swap
#include <algorithm>
using namespace std;

int particao(int vetor[], int menor, int maior)
{
    // Escolhe o último elemento como pivô
    int pivo = vetor[maior];
    // menor - 1 pois caso entre no primeiro if, ele n troque com o da frente, e sim com ele mesmo
    int i = menor - 1;

    for (int j = menor; j < maior; j++)
    {
        // caso n entre n incrementamos o i, assim na proxima entrada teremos salvo o indice de um numero maior q o pivo
        // para realizar o suap
        if (vetor[j] < pivo)
        {
            i++;
            // puxa todos os numeros menores que o pivo
            // e troca com os numeros maiores que o pivo
            swap(vetor[i], vetor[j]);
        }
    }
    // Coloca o pivô na posição correta
    swap(vetor[i + 1], vetor[maior]);
    // Retorna o índice do pivô
    return (i + 1);
}

void quickSort(int vetor[], int menor, int maior)
{
    // valvula de escape da recursividade
    if (menor < maior)
    {
        // Encontra o índice do pivô
        int pi = particao(vetor, menor, maior);
        // Ordena recursivamente à esquerda do pivô
        // Passa o pivô como maior
        quickSort(vetor, menor, pi - 1);

        // Ordena recursivamente à direita do pivô
        // Passa o pivô como menor
        quickSort(vetor, pi + 1, maior);
    }
}

bool Importar_txt(const string &endereco, vector<int> &numeros)
{
    ifstream arquivo(endereco);
    if (!arquivo)
    {
        cerr << "Erro ao abrir o arquivo " << endereco << endl;
        return false;
    }

    int num;
    while (arquivo >> num)
    {
        numeros.push_back(num);
    }

    arquivo.close();
    return true;
}

bool salvar_txt(const string &endereco, const vector<int> &numeros)
{
    ofstream arquivo(endereco);
    if (!arquivo)
    {
        cerr << "Erro ao abrir o arquivo para escrita: " << endereco << endl;
        return false;
    }

    for (int i = 0; i < numeros.size(); i++)
    {
        arquivo << numeros[i];
        if (i < numeros.size() - 1)
        {
            arquivo << "\n";
        }
    }

    arquivo.close();
    return true;
}

int main()
{
    string endereco = "../50_milhoes.txt";
    vector<int> numeros;

    // pega o tempo inicial do codigo completo
    auto codigo_tempo = chrono::high_resolution_clock::now();

    // Carrega os números do arquivo para o vetor
    if (!Importar_txt(endereco, numeros))
    {
        return 1;
    }

    int tamanho = numeros.size();
    int *vetor = numeros.data();

    // pega o tempo inicial
    auto inicio = chrono::high_resolution_clock::now();

    quickSort(vetor, 0, tamanho - 1);

    // pega o tempo final e subtrai o tempo inicia
    auto resultado = chrono::high_resolution_clock::now() - codigo_tempo;

    long long milissegundos = chrono::duration_cast<chrono::milliseconds>(resultado).count();
    double segundos = chrono::duration<double>(resultado).count();

    // Salva os números ordenados de volta no arquivo
    if (!salvar_txt(endereco, numeros))
    {
        return 1;
    }

    // pega o tempo final do codigo completo
    auto codigo_tempo_resultado = chrono::high_resolution_clock::now() - inicio;
    long long tempo_milissegundos = chrono::duration_cast<chrono::milliseconds>(codigo_tempo_resultado).count();
    double tempo_segundos = chrono::duration<double>(codigo_tempo_resultado).count();

    cout << "\nArquivo atualizado com os numeros ordenados." << endl;

    cout << "\nTempo do Algoritimo por completo:" << endl;
    cout << " Tempo em milisegundos: " << tempo_milissegundos << endl;
    cout << " Tempo em segundos: " << tempo_segundos << endl;

    cout << "\nTempo do QuickSort:" << endl;
    cout << " Tempo em milisegundos: " << milissegundos << endl;
    cout << " Tempo em segundos: " << segundos << endl;
    return 0;
}
