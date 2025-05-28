# 🐍 POS Kernel - Patos Operating System 

Bem-vindo ao repositório do **POS Kernel (Patos Operating System)**, um kernel educacional desenvolvido durante a disciplina de **Sistemas Operacionais II** do curso de **Ciência da Computação - UFMT**.

Este repositório contém **15 aulas práticas** focadas no desenvolvimento do kernel, desde o boot até a implementação de entrada e saída com UART, tratamento de interrupções, gerenciamento básico de memória e execução de aplicações no modo supervisor.

---

## 📂 Estrutura do Repositório

```
├── aula01/                # Introdução ao bootloader e primeiros binários
├── aula02/                # Setup de registradores de controle
├── aula03/                # UART - Comunicação serial
├── aula04/                # printf e strings
├── aula05/                # Entrada de dados com uartgetc
├── aula06/                # Gerenciamento simples de memória
├── aula07/                # Exceções e interrupções
├── aula08/                # Temporizadores com CLINT
├── aula09/                # Introdução a traps
├── aula10/                # Entrada no modo supervisor
├── aula11/                # syscall e tratamento de software traps
├── aula12/                # Organização da estrutura do kernel
├── aula13/                # Criação de interfaces de usuário simples
├── aula14/                # Organização de arquivos do sistema
├── aula15/                # Integração geral e refatoração
└── snake/                 # Implementação do jogo da cobrinha (Snake)
```

---

## 🧠 Conteúdo abordado nas aulas

- Boot em Assembly e salto para o kernel em C
- Escrita direta em UART para saída serial
- Impressão formatada com `printf`
- Leitura de caracteres via interrupção
- Organização de memória com heap simples
- Tratamento de exceções e interrupções
- Utilização de `mtime` e `mtimecmp` (CLINT) para temporização
- Modos de execução (M-mode e S-mode)
- Implementação de chamadas de sistema (syscalls)
- Criação de um mini-jogo funcional no modo texto

---

## 🎮 Snake no Kernel

O jogo da cobrinha (Snake) foi implementado como uma aplicação que roda **dentro do kernel**. Ele utiliza:

- **UART** para receber comandos do usuário
- **Escape codes ANSI** para desenhar a tela no terminal
- **Contador de tempo** (em segundos)
- **Gerador de maçãs aleatórias**
- **Interface interativa** com seleção de dificuldade (lento, normal, rápido)
- **Tratamento de colisões e pontuação**

---

## ▶️ Como executar

Este kernel foi desenvolvido para rodar em **RISC-V (RV64)** e pode ser testado em um emulador como o [QEMU](https://www.qemu.org/):

```bash
qemu-system-riscv64 -machine virt -nographic -kernel kernel
```

Requisitos:
- `riscv64-linux-gnu-gcc`
- `riscv64-linux-gnu-ld`
- `qemu-system-riscv64`

---

## ✏️ Créditos

Desenvolvido por: Lucas Lucena na Matéria de **Sistemas Operacionais II**  
**Universidade Federal de Mato Grosso (UFMT)**  
Orientado pelo Prof. Maxweel Silva Carmo 
Ano: 2025

---

## 📜 Licença

Este projeto é de uso **educacional** e pode ser livremente adaptado para fins acadêmicos.

---
