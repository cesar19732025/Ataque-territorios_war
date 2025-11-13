# Ataque-territorios_war
No desenvolvimento do War estruturado foram desenvolvidas funcionalidades de ataque entre territórios, permitindo ao usuário do jogo selecionar um território atacante e outro que será atacado. Foram utilizados ponteiros para manipular os dados dos territórios e alocação dinâmica de memória para armazenar os territórios cadastrados.
O código está estruturado com o uso de alocação dinâmica, estruturas, ponteiros e funções em C.

Simulação de Ataques entre Territórios (C)

Descrição do Projeto

Este projeto implementa uma simulação de ataques entre territórios, inspirada em jogos de estratégia como War ou Risk, utilizando linguagem C.

O programa permite:

1. Cadastro dinâmico de territórios (nome, cor e número de tropas);
2. Simulação de ataques entre territórios via rolagem de dados aleatória (rand()), com regras simples de vitória e derrota;
3. Manipulação por ponteiros, uso de calloc() e free() para alocação e liberação de memória;
4. Validação de entradas e menu interativo para navegação do jogador.


O objetivo é demonstrar conceitos fundamentais de estruturação modular, uso de structs, passagem de parâmetros por referência e controle de memória dinâmica em C.


-Estrutura do Código

O programa é composto pelas seguintes funções principais:

Função	Descrição

alocarTerritorios(int n)	Aloca dinamicamente um vetor de estruturas Territorio com calloc.
cadastrarTerritorios()	Lê os dados (nome, cor e tropas) de cada território via teclado.
exibirTerritorios()	Exibe todos os territórios cadastrados, com índice, cor e tropas.
atacar()	Simula um ataque entre dois territórios, usando dados (1–6) com rand().
liberarMemoria()	Libera o vetor alocado dinamicamente.
lerInteiro()	Lê e valida entradas numéricas com intervalo definido.

Regras de Ataque

1. O jogador escolhe um território atacante e um território defensor (não podem ser o mesmo nem da mesma cor).
2. Cada um rola um dado (1–6).
3. Se o atacante vencer:

O defensor muda de cor (assume a cor do atacante);

Recebe metade das tropas do atacante;

O atacante perde essa metade.

4. Se o atacante perder ou empatar:

O atacante perde 1 tropa.

5. O jogo continua até o jogador optar por sair do menu.

Como Compilar e Executar (usando GCC)

No terminal do VS Code, MSYS2, MinGW ou Linux, execute os comandos abaixo:

# Compilação com alertas e suporte a C11
gcc -std=c11 -Wall -Wextra -Wpedantic -o ataque_territorios "ataque territorios_war.c"

# Execução
./ataque_territorios

Exemplo de Execução

=== SISTEMA DE TERRITORIOS (SIMULACAO DE ATAQUES) ===
Informe o numero total de territorios: 3

Cadastro do 1o territorio:
Nome: Brasil
Cor do exercito: Azul
Tropas: 10

Cadastro do 2o territorio:
Nome: Argentina
Cor do exercito: Vermelho
Tropas: 8

Cadastro do 3o territorio:
Nome: Chile
Cor do exercito: Verde
Tropas: 5

Menu:
 1 - Exibir territorios
 2 - Realizar ataque
 3 - Sair
Escolha uma opcao: 2

Indice do territorio atacante (1..n): 1
Indice do territorio defensor (1..n): 2

Rolagem: Atacante 'Brasil' (cor Azul) -> Dado: 5  
         Defensor 'Argentina' (cor Vermelho) -> Dado: 3  
Resultado: Atacante venceu! Territorio 'Argentina' agora pertence a 'Azul' e recebeu 5 tropas.

Conceitos Didáticos Aplicados

1. Estruturas (struct)

2. Alocação dinâmica (calloc, free)

3. Ponteiros e acesso via aritmética de ponteiros

4. Passagem de parâmetros por referência

5. Funções modulares

6. Controle de fluxo (do...while, if, for)

7. Geração de números aleatórios com rand() e srand()

8. Manipulação segura de strings (strncpy, strcmp)


Requisitos

1. Compilador compatível com C11 (GCC recomendado)

2. Sistema operacional: Windows, Linux ou macOS

3. Terminal configurado para UTF-8

Autor
Cesar Ramos de Andrade 
Projeto desenvolvido como exercício prático de programação em linguagem C.
