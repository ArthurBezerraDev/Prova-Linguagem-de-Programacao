# Sistema de Controle de Estoque 📦

Implementação de um sistema de gerenciamento de estoque em **C** utilizando **Listas Encadeadas Dinâmicas** com nó cabeça, desenvolvido para uma avaliação de Linguagem de Programação I (LP1).

## 🚀 Funcionalidades
* **Cadastro de Produtos:** Insere novos produtos ou incrementa a quantidade caso o item já exista no estoque.
* **Realização de Vendas:** Baixa o estoque do produto e remove o nó da memória caso a quantidade chegue a zero.
* **Consulta:** Exibe todos os produtos cadastrados e suas respectivas quantidades.
* **Gerenciamento de Memória:** Liberação completa de nós e ponteiros ao encerrar o programa para evitar vazamentos (*memory leaks*).
