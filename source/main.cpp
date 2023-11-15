#include "main.h"

State *graph = nullptr;
std::vector<std::string> *input_alphabet = new std::vector<std::string>;
std::vector<std::string> *ribbon_alphabet = new std::vector<std::string>;

int main(int argc, char * argv[])
{
    try
    {
        /*if(argc < 2 || argc > 2)
        {
            printf("[Aviso]: Numero invalido de parametros !\n[Info]: Siga o exemplo: TuringMachine.exe caminho/para/arquivo.extensão");
            return EXIT_FAILURE;
        }

        graph = load_graph(input_alphabet, ribbon_alphabet, argv[1]);*/

        graph = load_graph(input_alphabet, ribbon_alphabet, "../TuringMachine.txt");

        // Turing Machine Logic

        return EXIT_SUCCESS;
    }
    catch(std::runtime_error ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}