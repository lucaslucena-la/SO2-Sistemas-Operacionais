// Define um comando ANSI para limpar a tela do terminal
#define CLS "\x1b[2J"

// Define um comando ANSI para mover o cursor para o canto superior esquerdo da tela
#define TOP_LEFT "\x1B[H"

// Define um comando ANSI para definir a cor do texto como laranja (RGB: 255, 165, 0)
#define ORANGE "\x1B[38;2;255;165;0m"

// Define um comando ANSI para resetar as cores e estilos do texto para o padrão
#define RESET_COLOR "\x1B[0m"

// Define um comando ANSI para definir a cor de fundo (RGB: 255, 255, 255, branco)
#define BACKGROUND_COLOR "\x1B[48;2;255;255;255m"

// Define um comando ANSI para ativar o estilo de texto em negrito
#define BOLD "\x1B[1m"
