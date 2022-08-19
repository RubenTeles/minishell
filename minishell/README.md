Shell:
    Um shell é uma interface de usuário para acessar os serviços de um sistema operacional. Em geral, os shells dos sistemas operacionais usam uma interface de linha de comando (CLI) ou uma interface gráfica de usuário (GUI).

Exemplos de tipos de Shell:
    CLI: Comand Line Interface
    GUI: Grafic User Interface

Visão Geral:
    Em Unix, o termo Shell é mais utilizado para se referir aos programas de sistemas como meio de interação entre interface de usuário para o acesso a serviços do kernel no sistema operacional. 
    Este é um programa que recebe, interpreta e executa os comandos de usuário, aparecendo na tela como uma linha de comandos, representada por um interpretador de comandos, que aguarda na tela os comandos do usuário. 
    CLIs podem ser melhores para os servidores que são gerenciados por administradores.
    GUIs oferecem simplicidade e facilidade de uso.

Exemplos de Shell GUI:
    Windows Shell:
        Barra de Tarefas, Menu iniciar, Gestor de Tarefas, windows explorer.

Exemplos de Shell CLI:
    Bash:
        É o Shell CLI mais utilizado em sistemas operacionais,
    ZSH;
    FISH;

Shell Script: #!/bin/MiniShell42
    É um arquivo de texto.sh que contem comandos para que o Shell execute. Para isso o Shell terá que reconhecer os comandos guardados no arquivo.

Resumo:
    Existem tipos diferentes de Shell, cada Shell pode ter o seu própio conjunto de ferramentas, e reconhecer certos comandos e funções. Shell então é um programa utilizado para intrepetar comandos.

Funcionamento de um Shell CLI:

Shell Init:
    É apresentado  um prompt;
            ->  

    O usuário escreve um comando e aperta enter;
            ->

    O Shell interpreta o comando e tenta tomar as ações;
            ->

    Um novo prompt é apresentado ao usuário;
            ->
                (REPL)  ->  Read--Evaluate--Print--Loop

Referencia esquema de funcionamento de um Shell:
https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J
