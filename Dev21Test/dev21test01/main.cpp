#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>

int randomIndex = 0;

const int rando[] = {57404,81280,83542,42648,74398,84587,76628,58341,72029,73855,6888,16265,44921,44108,71983,73202,36647,1039,32101,26864,7682,19851,1383,25026,214,51937,86006,36567,32640,21914,66482,79649,84467,80763,26530,224,90805,30718,45009,52379,57744,73114,44453,57444,66354,40457,13530,68134,44044,96227,14275,2800,97857,87117,83432,64385,71298,80958,12921,15792,73910,53942,70703,56047,98544,83453,52714,53582,43039,60360,17373,52425,22191,99136,40209,75953,95100,84947,91038,91233,61888,30735,34369,33189,40173,73972,56844,13892,47237,11862,60796,90783,59288,18423,64567,21722,25467,85772,41764,82539};

int Random()
{
    if (randomIndex == 100)
    {
        randomIndex = 0;
    }
    return rando[randomIndex++];
}

//**************************************************

enum TipoColumna { COLUMNANUMEROSECUENCIAL, COLUMNATEXTOFIJO, COLUMNATEXTOALEATORIO, COLUMNALISTAALEATORIA };

struct NumeroSecuencial
{
    int secuencia;
    char buffer[100];
};

void CNumeroSecuencial(NumeroSecuencial **numeroSecuencial, int incioDeSecuencia)
{
    *numeroSecuencial = (NumeroSecuencial *) malloc(sizeof(NumeroSecuencial));
    (**numeroSecuencial).secuencia = incioDeSecuencia;
}

const char * GenerarNumeroSecuencial(NumeroSecuencial *numeroSecuencial)
{
    int numero = numeroSecuencial->secuencia;
    int numeroTemp = numero;
    int numeros = 0;
    if (numeroTemp == 0)
    {
        numeros = 1;
    }
    else
    {
        while (numeroTemp)
        {
            numeroTemp /= 10;
            numeros++;
        }
    }
    for (int i = numeros - 1; i >= 0; i--)
    {
        numeroSecuencial->buffer[i] = (char)((numero % 10) | '0');
        numero /= 10;
    }
    numeroSecuencial->buffer[numeros] = '\0';
    numeroSecuencial->secuencia++;
    return numeroSecuencial->buffer;
}

void DNumeroSecuencial(NumeroSecuencial *numeroSecuencial)
{
    free(numeroSecuencial);
}

struct TextoFijo
{
    char *texto;
};

void CTextoFijo(TextoFijo **textoFijo, const char *texto)
{
    *textoFijo = (TextoFijo *) malloc(sizeof(TextoFijo));
    (**textoFijo).texto = (char*)calloc(strlen(texto) + 1, sizeof(char));
    strcpy((**textoFijo).texto, texto);
}

const char * GenerarTextoFijo(TextoFijo *textoFijo)
{
    return textoFijo->texto;
}

void DTextoFijo(TextoFijo *textoFijo)
{
    free(textoFijo->texto);
    free(textoFijo);
}

struct TextoAleatorio
{
    int numeroDeCaracteres;
    char *caracteres;
    int (*f)();
    int numeroDeCaracteresAleatorios;
    char caracteresGenerados[1000];
};

void CTextoAleatorio(TextoAleatorio **textoAleatorio, const char *caracteres, int (*f)(), int numeroDeCaracteresAleatorios)
{
    *textoAleatorio = (TextoAleatorio *) malloc(sizeof(TextoAleatorio));
    (**textoAleatorio).numeroDeCaracteres = strlen(caracteres);
    (**textoAleatorio).caracteres = (char*)calloc((**textoAleatorio).numeroDeCaracteres + 1, sizeof(char));
    strcpy((**textoAleatorio).caracteres, caracteres);
    (**textoAleatorio).f = f;
    (**textoAleatorio).numeroDeCaracteresAleatorios = numeroDeCaracteresAleatorios;
}

const char * GenerarTextoAleatorio(TextoAleatorio *textoAleatorio)
{
    textoAleatorio->caracteresGenerados[0] = '\0';
    for (int i = 0; i < textoAleatorio->numeroDeCaracteresAleatorios; i++)
    {
        char caracterGenerado[2];
        caracterGenerado[1] = '\0';
        caracterGenerado[0] = textoAleatorio->caracteres[(*textoAleatorio->f)() % textoAleatorio->numeroDeCaracteres];
        strcat(textoAleatorio->caracteresGenerados, caracterGenerado);
    }
    return textoAleatorio->caracteresGenerados;
}

void DTextoAleatorio(TextoAleatorio *textoAleatorio)
{
    free(textoAleatorio->caracteres);
    free(textoAleatorio);
}

struct ListaAleatoria
{
    int numeroDeItems;
    char **lista;
    int (*f)();
    char itemElegido[1000];
};

void CListaAleatoria(ListaAleatoria **listaAleatoria, const char **lista, int numeroDeItems, int (*f)())
{
    *listaAleatoria = (ListaAleatoria *) malloc(sizeof(ListaAleatoria));
    (**listaAleatoria).numeroDeItems = numeroDeItems;
    (**listaAleatoria).lista = (char **) calloc(numeroDeItems, sizeof(char **));
    for (int i = 0; i < numeroDeItems; i++)
    {
        (**listaAleatoria).lista[i] = (char*)calloc(strlen(lista[i]) + 1, sizeof(char));
        strcpy((**listaAleatoria).lista[i], lista[i]);
    }
    (**listaAleatoria).f = f;
}

const char * GenerarListaAleatoria(ListaAleatoria *listaAleatoria)
{
    strcpy(listaAleatoria->itemElegido, listaAleatoria->lista[(*listaAleatoria->f)() % listaAleatoria->numeroDeItems]);
    return listaAleatoria->itemElegido;
}

void DListaAleatoria(ListaAleatoria *listaAleatoria)
{
    for (int i = 0; i < listaAleatoria->numeroDeItems; i++)
    {
        free(listaAleatoria->lista[i]);
    }
    free(listaAleatoria->lista);
    free(listaAleatoria);
}

struct Columna
{
    TipoColumna tipoColumna;
    void *columna;
    Columna *siguiente;
};

void CColumna(Columna **columna, void *columnaEspecifica, TipoColumna tipoColumna)
{
    *columna = (Columna *) malloc(sizeof(Columna));
    (**columna).tipoColumna = tipoColumna;
    (**columna).columna = columnaEspecifica;
    (**columna).siguiente = NULL;
}

void DColumna(Columna *columna)
{
    switch (columna->tipoColumna)
    {
        case COLUMNANUMEROSECUENCIAL:
            DNumeroSecuencial((NumeroSecuencial *) columna->columna);
            break;
        case COLUMNATEXTOFIJO:
            DTextoFijo((TextoFijo *) columna->columna);
            break;
        case COLUMNATEXTOALEATORIO:
            DTextoAleatorio((TextoAleatorio *) columna->columna);
            break;
        case COLUMNALISTAALEATORIA:
            DListaAleatoria((ListaAleatoria *) columna->columna);
            break;
    }
    free(columna);
}

struct Generador
{
    char separadorDeColumnas;
    Columna *listaDeColumnas;
    char buffer[100000];
};

void CGenerador(Generador **generador, char separadorDeColumnas)
{
    *generador = (Generador *) malloc(sizeof(Generador));
    (**generador).separadorDeColumnas = separadorDeColumnas;
    (**generador).listaDeColumnas = NULL;
}

Columna * CrearNumeroSecuencialGenerador(int inicioSecuencia)
{
    NumeroSecuencial *numeroSecuencial;
    CNumeroSecuencial(&numeroSecuencial, inicioSecuencia);
    Columna *columna;
    CColumna(&columna, (void *)numeroSecuencial, COLUMNANUMEROSECUENCIAL);
    return columna;
}

Columna * CrearTextoFijoGenerador(const char *texto)
{
    TextoFijo *textoFijo;
    CTextoFijo(&textoFijo, texto);
    Columna *columna;
    CColumna(&columna, (void *)textoFijo, COLUMNATEXTOFIJO);
    return columna;
}

Columna * CrearTextoAleatorioGenerador(const char *caracteres, int (*f)(), int numeroDeCaracteresAleatorios)
{
    TextoAleatorio *textoAleatorio;
    CTextoAleatorio(&textoAleatorio, caracteres, f, numeroDeCaracteresAleatorios);
    Columna *columna;
    CColumna(&columna, (void *)textoAleatorio, COLUMNATEXTOALEATORIO);
    return columna;
}

Columna * CrearListaAleatoriaGenerador(int (*f)(), int numeroDeItems, ...)
{
    va_list vaList;
    va_start(vaList, numeroDeItems);
    char **lista;
    lista = (char **) calloc(numeroDeItems, sizeof(char **));
    for(int i = 0; i < numeroDeItems; i++)
    {
        lista[i] = va_arg(vaList, char *);
    }
    ListaAleatoria *listaAleatoria;
    CListaAleatoria(&listaAleatoria, (const char **)lista, numeroDeItems, f);
    Columna *columna;
    CColumna(&columna, (void *)listaAleatoria, COLUMNALISTAALEATORIA);
    va_end(vaList);
    free(lista);
    return columna;
}

void AgregarColumnaGenerador(Columna *listaDeColumnas, Columna *columna)
{
    if (listaDeColumnas->siguiente == NULL)
    {
        listaDeColumnas->siguiente = columna;
    }
    else
    {
        AgregarColumnaGenerador(listaDeColumnas->siguiente, columna);
    }
}

void AgregarColumnaGenerador(Generador *generador, Columna *columna)
{
    if (generador->listaDeColumnas == NULL)
    {
        generador->listaDeColumnas = columna;
    }
    else
    {
        AgregarColumnaGenerador(generador->listaDeColumnas, columna);
    }
}

void ConfigurarGenerador(Generador *generador, int numeroDeColumnas, ...)
{
    va_list vaList;
    va_start(vaList, numeroDeColumnas);
    for(int i = 0; i < numeroDeColumnas; i++)
    {
        AgregarColumnaGenerador(generador, va_arg(vaList, Columna *));
    }
    va_end(vaList);
}

const char * GenerarGenerador(Generador *generador, int numeroDeFilas)
{
    char separadorDeColumnas[2];
    separadorDeColumnas[0] = generador->separadorDeColumnas;
    separadorDeColumnas[1] = '\0';
    generador->buffer[0] = '\0';
    for(int i = 0; i < numeroDeFilas; i++)
    {
        Columna *p = generador->listaDeColumnas;
        while (p != NULL)
        {
            switch (p->tipoColumna)
            {
                case COLUMNANUMEROSECUENCIAL:
                    strcat(generador->buffer, GenerarNumeroSecuencial((NumeroSecuencial *)p->columna));
                    break;
                case COLUMNATEXTOFIJO:
                    strcat(generador->buffer, GenerarTextoFijo((TextoFijo *)p->columna));
                    break;
                case COLUMNATEXTOALEATORIO:
                    strcat(generador->buffer, GenerarTextoAleatorio((TextoAleatorio *)p->columna));
                    break;
                case COLUMNALISTAALEATORIA:
                    strcat(generador->buffer, GenerarListaAleatoria((ListaAleatoria *)p->columna));
                    break;
            }
            if (p->siguiente != NULL)
            {
                strcat(generador->buffer, separadorDeColumnas);
            }
            p = p->siguiente;
        }
        strcat(generador->buffer, "\n");
    }
    return generador->buffer;
}

void DGenerador(Generador *generador)
{
    Columna *p = generador->listaDeColumnas;
    while (p != NULL)
    {
        Columna *paraLiberar = p;
        p = p->siguiente;
        DColumna(paraLiberar);
    }
    free(generador);
}

//**************************************************

bool test1()
{
//    return false;

    bool assertion = true;
    randomIndex = 0;

    Generador *generador;
    char caracterSeparadorDeColumnas = ';';
    CGenerador(&generador, caracterSeparadorDeColumnas);
    int inicioSecuencia = 0;

    // esta funcion debe ser implementada con varargs, caso contrario el test vale 0 puntos, incluso si es PASSED
    ConfigurarGenerador(generador, 2, CrearNumeroSecuencialGenerador(inicioSecuencia), CrearTextoFijoGenerador("CONTENIDO"));

    if
    (
        strcmp
        (
            GenerarGenerador(generador, 5),
            "0;CONTENIDO\n"
            "1;CONTENIDO\n"
            "2;CONTENIDO\n"
            "3;CONTENIDO\n"
            "4;CONTENIDO\n"
        ) != 0
    )
    {
        assertion = false;
    }

    DGenerador(generador);

    return assertion;

}

bool test2()
{
//    return false;

    bool assertion = true;
    randomIndex = 0;

    Generador *generador;
    char caracterSeparadorDeColumnas = ',';
    CGenerador(&generador, caracterSeparadorDeColumnas);
    int inicioSecuencia = 1;
    int numeroDeCaracteresAleatorios = 3;

    // esta funcion debe ser implementada con varargs, caso contrario el test vale 0 puntos, incluso si es PASSED
    ConfigurarGenerador
    (
        generador,
        3,
        CrearNumeroSecuencialGenerador(inicioSecuencia),
        CrearTextoFijoGenerador("TEXTO"),
        CrearTextoAleatorioGenerador("ABC", &Random, numeroDeCaracteresAleatorios)
    );

    if
    (
        strcmp
        (
            GenerarGenerador(generador, 2),
            "1,TEXTO,CBB\n"
            "2,TEXTO,ABC\n"
        ) != 0
    )
    {
        assertion = false;
    }

    DGenerador(generador);

    return assertion;

}

bool test3()
{
//    return false;

    bool assertion = true;
    randomIndex = 0;

    Generador *generador;
    char caracterSeparadorDeColumnas = ',';
    CGenerador(&generador, caracterSeparadorDeColumnas);
    int inicioSecuencia = 100;

    // esta funcion debe ser implementada con varargs, caso contrario el test vale 0 puntos, incluso si es PASSED
    ConfigurarGenerador
    (
        generador,
        2,
        CrearNumeroSecuencialGenerador(inicioSecuencia),

        // esta funcion debe ser implementada con varargs, caso contrario el test vale 0 puntos, incluso si es PASSED
        CrearListaAleatoriaGenerador(&Random, 5, "uno", "dos", "tres", "cuatro", "cinco")
    );

    if
    (
        strcmp
        (
            GenerarGenerador(generador, 3),
            "100,cinco\n"
            "101,uno\n"
            "102,tres\n"
        ) != 0
    )
    {
        assertion = false;
    }

    DGenerador(generador);

    return assertion;

}

class TestSuite
{
    unsigned int passed;
    unsigned int executed;
    unsigned int id;

public:
    TestSuite() : passed(0), executed(0), id(0)
    {
    }

    void run(bool (*test)(), int points)
    {
        bool r = test();
        passed += ((unsigned int) r) * points;
        executed += points;
        ++id;
        const char *result = r ? "PASSED" : "FAILED";
        printf("Test #%d for %d points => %s\n", id, points, result);
    }

    unsigned int getPassed() const
    {
        return passed;
    }

    unsigned int getExecuted() const
    {
        return executed;
    }
};

int main()
{
    TestSuite testSuite;

    testSuite.run(test1, 10);
    testSuite.run(test2, 40);
    testSuite.run(test3, 40);

    printf("FINAL SCORE: %d / %d\n", testSuite.getPassed(), testSuite.getExecuted());

    return 0;
}
