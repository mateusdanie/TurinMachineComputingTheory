#include "main.h"

State *start_state = nullptr;
std::vector<std::string> *input_alphabet = new std::vector<std::string>;
std::vector<std::string> *ribbon_alphabet = new std::vector<std::string>;

int main(int argc, char * argv[])
{
    /*if(argc < 2 || argc > 2)
    {
        printf("[Aviso]: Numero invalido de parametros !\n[Info]: Siga o exemplo: TuringMachine.exe caminho/para/arquivo.extensão");
        return EXIT_FAILURE;
    }*/

    //readGraph(Start, &InputAlphabet, &Ribbonalphabet, "../TuringMachine.txt"  /*argv[0]*/);

    load_graph(start_state, input_alphabet, ribbon_alphabet, "../TuringMachine.txt");

    return EXIT_SUCCESS;
}