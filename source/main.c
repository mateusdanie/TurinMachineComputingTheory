#include "../include/main.h"

//aAbB 

State *Start = NULL;
char *InputAlphabet = NULL; // Equivalente a uma lista de strings ou matrix de caracteres
char *Ribbonalphabet = NULL; // Equivalente a uma lista de strings ou matrix de caracteres

int main(int argc, char * argv[])
{
    /*if(argc < 2 || argc > 2)
    {
        printf("[Aviso]: Numero invalido de parametros !\n[Info]: Siga o exemplo: TuringMachine.exe caminho/para/arquivo.extensão");
        return EXIT_FAILURE;
    }*/

    readGraph(Start, &InputAlphabet, &Ribbonalphabet, "../TuringMachine.txt"  /*argv[0]*/);

    return EXIT_SUCCESS;
}