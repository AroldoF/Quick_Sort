import random

# Parâmetros
num_elements = 100000000  # Número de elementos
output_file = "100_milhões.txt"  # Nome do arquivo de saída

# Gerar uma lista de números
numbers = list(range(1, num_elements + 1))  # Números de 1 a 1 milhão

# Embaralhar os números (opcional)
random.shuffle(numbers)

# Escrever no arquivo
with open(output_file, "w") as file:
    for number in numbers:
        file.write(f"{number}\n")

print(f"Arquivo '{output_file}' criado com sucesso!")