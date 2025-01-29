from random import shuffle

tamanho = 50000000  
nome_arquivo = "50_milhoes.txt"  

numeros = list(range(1, tamanho + 1))  

shuffle(numeros)

with open(nome_arquivo, "w") as file:
    for num in numeros:
        file.write(f"{num}\n")

print(f"Arquivo '{nome_arquivo}' criado com sucesso!")