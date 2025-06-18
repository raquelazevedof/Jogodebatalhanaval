# Projeto Batalha Naval com Áreas de Efeito de Habilidades

## Descrição

Este projeto em C implementa um tabuleiro de Batalha Naval 10x10, onde navios são posicionados e habilidades especiais aplicam áreas de efeito sobre o tabuleiro. O objetivo é visualizar as regiões impactadas pelas habilidades sem executar lógica de dano, apenas mostrando graficamente os efeitos.

As habilidades especiais são representadas por matrizes de efeito com formato de:

- **Cone**: Área triangular que se expande para baixo a partir do ponto de origem.
- **Cruz**: Área em forma de cruz com origem no centro.
- **Octaedro**: Área em forma de losango (vista frontal do octaedro) com origem no centro.

O tabuleiro utiliza os seguintes valores:

- `0` — Água
- `3` — Navio
- `5` — Área afetada pela habilidade

## Funcionalidades

- Inicialização do tabuleiro 10x10 com água.
- Posicionamento de navios ortogonais (horizontal e vertical) e diagonais (↘ e ↙).
- Construção dinâmica das matrizes de área de efeito para as habilidades Cone, Cruz e Octaedro, utilizando loops e condicionais.
- Sobreposição das áreas de efeito no tabuleiro centrando na posição de origem definida.
- Impressão formatada do tabuleiro mostrando navios, água e áreas de efeito.

## Estrutura do Código

- Funções para inicializar e posicionar navios  
- Funções para construir as matrizes de habilidades com área de efeito  
- Função para aplicar a matriz da habilidade no tabuleiro, respeitando limites  
- Função para exibir o tabuleiro no console com legenda clara  
