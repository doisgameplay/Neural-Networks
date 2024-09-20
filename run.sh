#!/bin/bash

# Verifica se pelo menos um arquivo foi fornecido como argumento
if [ "$#" -lt 1 ]; then
    echo "Uso: $0 <arquivo1.cpp> [<arquivo2.cpp> ...]"
    exit 1
fi

# Pasta para executáveis
PASTA_EXECUTABLES="executables"

# Cria a pasta executables se não existir
if [ ! -d "$PASTA_EXECUTABLES" ]; then
    echo "Criando a pasta $PASTA_EXECUTABLES..."
    mkdir "$PASTA_EXECUTABLES"
fi

# Array para armazenar arquivos objeto
ARQUIVOS_O=()

# Compila cada arquivo .cpp passado como argumento
for ARQUIVO_CPP in "$@"; do
    if [[ "$ARQUIVO_CPP" == *.cpp ]]; then
        BASE_NAME=$(basename "$ARQUIVO_CPP" .cpp)
        ARQUIVO_O="${BASE_NAME}.o"

        echo "Compilando $ARQUIVO_CPP..."
        g++ -c "$ARQUIVO_CPP" -Isrc/include
        if [ $? -ne 0 ]; then
            echo "Erro na compilação do arquivo $ARQUIVO_CPP"
            exit 1
        fi

        ARQUIVOS_O+=("$ARQUIVO_O")
    else
        echo "Ignorando $ARQUIVO_CPP (não é um arquivo .cpp)"
    fi
done

# Verifica se pelo menos um arquivo objeto foi gerado
if [ "${#ARQUIVOS_O[@]}" -eq 0 ]; then
    echo "Nenhum arquivo .cpp foi compilado com sucesso."
    exit 1
fi

# Cria o executável
ARQUIVO_EXE="${1%.cpp}.exe"
echo "Criando o executável $ARQUIVO_EXE..."
g++ "${ARQUIVOS_O[@]}" -o "$PASTA_EXECUTABLES/$ARQUIVO_EXE" -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
if [ $? -ne 0 ]; then
    echo "Erro na criação do executável $PASTA_EXECUTABLES/$ARQUIVO_EXE"
    exit 1
fi

# Move os arquivos .dll para a pasta executables (ajuste conforme necessário)
echo "Movendo arquivos .dll para a pasta $PASTA_EXECUTABLES..."
for dll in *.dll; do
    if [ -f "$dll" ]; then
        mv "$dll" "$PASTA_EXECUTABLES/"
    fi
done

# Executa o arquivo
echo "Executando $PASTA_EXECUTABLES/$ARQUIVO_EXE..."
"$PASTA_EXECUTABLES/$ARQUIVO_EXE"
if [ $? -ne 0 ]; then
    echo "Erro na execução do arquivo $PASTA_EXECUTABLES/$ARQUIVO_EXE"
    exit 1
fi

# Remove os arquivos objeto
for ARQUIVO_O in "${ARQUIVOS_O[@]}"; do
    echo "Removendo o arquivo objeto $ARQUIVO_O..."
    rm "$ARQUIVO_O"
    if [ $? -ne 0 ]; then
        echo "Erro ao remover o arquivo objeto $ARQUIVO_O"
        exit 1
    fi
done

echo "Tarefa concluída com sucesso!"
