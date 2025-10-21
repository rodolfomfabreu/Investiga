# 🕵️ Investiga - Jogo de Investigação

<p align="center">
  <img src="https://img.shields.io/badge/C-Programming-00599C?style=for-the-badge&logo=c"/>
  <img src="https://img.shields.io/badge/Data%20Structures-Tree%20%7C%20Hash-FF6B6B?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Game-Investigation-4ECDC4?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-9B59B6?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Compilation-GCC%20%7C%20MinGW-FF9500?style=for-the-badge"/>
</p>

<div align="center">
  <b>🇧🇷 Português | <a href="#english-version">🇺🇸 English below</a></b>
</div>

---

## 📑 Sumário | Table of Contents
- [Sobre o Projeto | About](#sobre-o-projeto--about)
- [Funcionalidades | Features](#funcionalidades--features)
- [Tecnologias | Technologies](#tecnologias--technologies)
- [Estrutura | Structure](#estrutura--structure)
- [Instalação e Compilação | Installation & Compilation](#instalação-e-compilação--installation--compilation)
- [Como Usar | How to Use](#como-usar--how-to-use)
- [Autor | Author](#autor--author)

---

## Sobre o Projeto | About

**PT-BR:**
> Um jogo interativo de investigação desenvolvido em C que simula um detetive coletando pistas para resolver um caso. O projeto implementa estruturas de dados avançadas como árvores binárias de busca e tabelas hash para gerenciar mapas de ambientes, pistas e suspeitos. Inclui sistema de ajuda integrado, demo automatizada completa, ambientes expandidos com 16 locais cada, histórias enriquecidas e casos pré-definidos. Ideal para aprendizado de programação em C, estruturas de dados e desenvolvimento de jogos textuais.

**EN:**
> An interactive investigation game developed in C that simulates a detective collecting clues to solve a case. The project implements advanced data structures such as binary search trees and hash tables to manage environment maps, clues, and suspects. Includes integrated help system, complete automatic demo, expanded environments with 16 locations each, enriched stories, and pre-defined cases. Ideal for learning C programming, data structures, and text-based game development.

---

## 🎮 Funcionalidades | Features

**PT-BR:**
- **Sistema de Mapas**: Navegação entre diferentes cômodos usando árvores binárias de busca
- **Coleta de Pistas**: Sistema de descoberta e coleta de evidências com descrições detalhadas
- **Associação Pista-Suspeito**: Tabela hash para conectar pistas aos suspeitos automaticamente
- **Modo Construtor**: Criação de casos personalizados com múltiplos ambientes e suspeitos
- **Presets de Jogo**: Casos pré-definidos (básico e demo) para começar rapidamente
- **Demo Automática**: Demonstração completa com navegação automática e exibição de pistas
- **Sistema de Acusação**: Mecânica de resolução do caso com validação do culpado
- **Interface Interativa**: Menu intuitivo com navegação por comandos de texto
- **Sistema de Ajuda**: Tutoriais integrados para jogo e modo construtor
- **Ambientes Expandidos**: 16 cômodos no preset básico e 16 áreas no preset demo
- **Histórias Enriquecidas**: Narrativas detalhadas e envolventes para cada caso

**EN:**
- **Map System**: Navigation between different rooms using binary search trees
- **Clue Collection**: Discovery and collection system for evidence with detailed descriptions
- **Clue-Suspect Association**: Hash table to automatically connect clues to suspects
- **Builder Mode**: Creation of custom cases with multiple environments and suspects
- **Game Presets**: Pre-defined cases (basic and demo) to start quickly
- **Automatic Demo**: Complete demonstration with automatic navigation and clue display
- **Accusation System**: Case resolution mechanics with suspect validation
- **Interactive Interface**: Intuitive menu with text-based command navigation
- **Help System**: Integrated tutorials for game and builder mode
- **Expanded Environments**: 16 rooms in basic preset and 16 areas in demo preset
- **Enriched Stories**: Detailed and engaging narratives for each case

---

## 🚀 Tecnologias | Technologies

**PT-BR:**
- **C (C99)**: Linguagem de programação principal para desenvolvimento do jogo
- **GCC/MinGW**: Compilador C para Windows e Linux
- **Árvores Binárias de Busca**: Estrutura de dados para gerenciar mapas e pistas
- **Tabelas Hash**: Estrutura de dados para associação rápida pista-suspeito
- **Alocação Dinâmica de Memória**: Gerenciamento de memória com malloc/free
- **Estruturas de Dados Personalizadas**: Implementação de nós, listas e tabelas

**EN:**
- **C (C99)**: Main programming language for game development
- **GCC/MinGW**: C compiler for Windows and Linux
- **Binary Search Trees**: Data structure for managing maps and clues
- **Hash Tables**: Data structure for fast clue-suspect association
- **Dynamic Memory Allocation**: Memory management with malloc/free
- **Custom Data Structures**: Implementation of nodes, lists, and tables

---

## 🗂️ Estrutura | Structure
```
Investiga/
├── main.c              # Arquivo principal com lógica do jogo (705 linhas)
├── structs.h           # Definições de estruturas de dados (63 linhas)
├── arvore_binaria.c    # Implementação de árvores binárias (85 linhas)
├── arvore_busca.c      # Implementação de árvores de busca para pistas (108 linhas)
├── tabela_hash.c       # Implementação de tabelas hash (70 linhas)
├── investiga.exe       # Executável compilado (Windows)
├── *.o                 # Arquivos objeto compilados
└── README.md           # Documentação do projeto (244 linhas)
```

---

## ⚙️ Instalação e Compilação | Installation & Compilation

**PT-BR:**
1. **Pré-requisitos:** 
   - GCC ou MinGW (Windows) / GCC (Linux)
   - Make (opcional, para automação)
2. **Clone ou baixe o projeto**
3. **Compile o projeto:**
   ```bash
   # Windows (MinGW)
   gcc -o investiga.exe main.c arvore_binaria.c arvore_busca.c tabela_hash.c
   
   # Linux
   gcc -o investiga main.c arvore_binaria.c arvore_busca.c tabela_hash.c
   ```
4. **Execute o jogo:**
   ```bash
   # Windows
   ./investiga.exe
   
   # Linux
   ./investiga
   ```

**EN:**
1. **Prerequisites:** 
   - GCC or MinGW (Windows) / GCC (Linux)
   - Make (optional, for automation)
2. **Clone or download the project**
3. **Compile the project:**
   ```bash
   # Windows (MinGW)
   gcc -o investiga.exe main.c arvore_binaria.c arvore_busca.c tabela_hash.c
   
   # Linux
   gcc -o investiga main.c arvore_binaria.c arvore_busca.c tabela_hash.c
   ```
4. **Run the game:**
   ```bash
   # Windows
   ./investiga.exe
   
   # Linux
   ./investiga
   ```

---

## 🎯 Como Usar | How to Use

**PT-BR:**

### Menu Principal
Ao executar o programa, você terá acesso ao menu principal com as seguintes opções:

1. **Novo jogo** - Cria um caso básico pré-definido
2. **Criar jogo personalizado** - Modo construtor para criar casos customizados
3. **Jogar** - Inicia o jogo com o caso atual
4. **Demo automática** - Executa uma demonstração automática do jogo
5. **Como jogar (ajuda)** - Explica detalhadamente como usar o jogo
6. **Como criar um jogo personalizado (ajuda)** - Tutorial completo do modo construtor
0. **Sair** - Encerra o programa

### Modo Jogo
Durante o jogo, você pode:
- **Navegar entre cômodos**: Digite o nome do cômodo para se mover
- **Inspecionar cômodo atual**: Descobrir pistas disponíveis
- **Coletar pistas**: Digite o nome exato da pista para coletá-la
- **Ver pistas coletadas**: Revisar todas as evidências encontradas
- **Acusar suspeito**: Digite o nome do suspeito para resolver o caso

### Modo Construtor
No modo construtor, você pode:
- **Inserir cômodos**: Adicionar novos ambientes ao mapa
- **Inserir pistas**: Adicionar evidências em cômodos específicos
- **Associar pista-suspeito**: Conectar pistas aos suspeitos
- **Definir culpado**: Estabelecer quem é o verdadeiro culpado
- **Criar história**: Personalizar a narrativa inicial do caso

### Demo Automatizada
A demo automatizada oferece uma experiência completa:
- **Navegação automática**: Move entre 10 locais diferentes
- **Exibição de pistas**: Mostra todas as evidências disponíveis em cada cômodo
- **Coleta automática**: Coleta pistas automaticamente sem interação
- **Demonstração educativa**: Explica como o sistema funciona
- **Casos pré-definidos**: Demonstração com história corporativa envolvente

### Sistema de Ajuda Integrado
O jogo inclui sistema de ajuda completo:
- **Tutorial de jogo**: Explica objetivo, navegação e mecânicas
- **Guia do construtor**: Passo a passo para criar casos personalizados
- **Dicas estratégicas**: Orientações para investigações eficientes
- **Exemplos práticos**: Casos de uso e melhores práticas

**EN:**

### Main Menu
When running the program, you'll have access to the main menu with the following options:

1. **New game** - Creates a predefined basic case
2. **Create custom game** - Builder mode to create custom cases
3. **Play** - Starts the game with the current case
4. **Automatic demo** - Runs an automatic game demonstration
5. **How to play (help)** - Detailed explanation of how to use the game
6. **How to create a custom game (help)** - Complete tutorial for builder mode
0. **Exit** - Closes the program

### Game Mode
During gameplay, you can:
- **Navigate between rooms**: Type the room name to move
- **Inspect current room**: Discover available clues
- **Collect clues**: Type the exact clue name to collect it
- **View collected clues**: Review all evidence found
- **Accuse suspect**: Type the suspect's name to solve the case

### Builder Mode
In builder mode, you can:
- **Insert rooms**: Add new environments to the map
- **Insert clues**: Add evidence to specific rooms
- **Associate clue-suspect**: Connect clues to suspects
- **Define culprit**: Establish who the real culprit is
- **Create story**: Customize the initial case narrative

### Automatic Demo
The automatic demo offers a complete experience:
- **Automatic navigation**: Moves between 10 different locations
- **Clue display**: Shows all available evidence in each room
- **Automatic collection**: Collects clues automatically without interaction
- **Educational demonstration**: Explains how the system works
- **Pre-defined cases**: Demonstration with engaging corporate story

### Integrated Help System
The game includes a complete help system:
- **Game tutorial**: Explains objectives, navigation, and mechanics
- **Builder guide**: Step-by-step instructions for creating custom cases
- **Strategic tips**: Guidelines for efficient investigations
- **Practical examples**: Use cases and best practices

---

## 👨‍💻 Autor | Author

**PT-BR:**

<div align="center">

**Rodolfo M. F. Abreu**  
Desenvolvedor de software apaixonado por tecnologia, aprendizado contínuo e boas práticas de programação. Sempre em busca de novos desafios e oportunidades para colaborar em projetos inovadores.

[![GitHub](https://img.shields.io/badge/GitHub-rodolfomfabreu-black?style=for-the-badge&logo=github)](https://github.com/salamandery)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Rodolfo%20Abreu-blue?style=for-the-badge&logo=linkedin)](https://linkedin.com/in/rodolfo-marques-ferreira-de-abreu/)

Sinta-se à vontade para entrar em contato para dúvidas, sugestões ou colaborações!

</div>

**EN:**

<div align="center">

**Rodolfo M. F. Abreu**  
Software developer passionate about technology, continuous learning, and best programming practices. Always looking for new challenges and opportunities to collaborate on innovative projects.

[![GitHub](https://img.shields.io/badge/GitHub-rodolfomfabreu-black?style=for-the-badge&logo=github)](https://github.com/salamandery)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Rodolfo%20Abreu-blue?style=for-the-badge&logo=linkedin)](https://linkedin.com/in/rodolfo-marques-ferreira-de-abreu/)

Feel free to get in touch for questions, suggestions, or collaborations!

</div>

---

<div align="center">
  <b>Feito com 💙 para estudos de programação em C, estruturas de dados e desenvolvimento de jogos.<br/>
  Made with 💙 for C programming, data structures and game development studies.</b>
</div>

---

<div align="center" id="english-version">
  <b>🇺🇸 English version above | <a href="#top">🇧🇷 Versão em português acima</a></b>
</div>