typedef struct Endereco_virtual
{
    int num_pagina_virtual; // bits mais significativos
    int deslocamento; // bits menos significativos
} Endereco_virtual;

typedef struct Pagina_virtual
{
    // num quadro substitui o num_pagina_virtual e o deslocamento se mantém, para mapear o endereço físico
    int num_quadro;
    int bit_presenca;
    int bit_modificacao;
} Pagina_virtual;

typedef struct Tabela_de_paginas
{
    int num_paginas;
    Pagina_virtual *paginas;  
} Tabela_de_paginas;

typedef struct Processo
{
    int id; // nome do processo
    int num_paginas;
    Tabela_de_paginas *tabela;
} Processo;

typedef struct Quadro
{
    int *dados;
} Quadro;


typedef struct Memoria_secundaria
{
    
} Memoria_secundaria;

typedef struct Memoria_principal
{
    int num_quadros;
    Quadro *quadros;
} Memoria_principal;