#include "main.h"

State *graph = nullptr;
uint32_t ribbon_head = 0;
bool found = false;
std::vector<std::string> *input_alphabet = new std::vector<std::string>;
std::vector<std::string> *ribbon_alphabet = new std::vector<std::string>;

void print_ribbon(std::vector<std::string> ribbon, std::string prefix)
{
    std::string ribbon_str = "";
    bool multiple_elements = false;

    for(std::string element : ribbon)
    {
        if(multiple_elements)
            ribbon_str += " " + element;
        else
        {
            ribbon_str = element;
            multiple_elements = true;
        }
    }

    std::cout << prefix << ribbon_str << std::endl;
}

int main(int argc, char * argv[])
{
    try
    {
        if(argc < 2 || argc > 2)
        {
            printf("[WARNING]: Invalid number of parameters !\n[INFO]: Follow the example: TuringMachine.exe path/to/file.extension");
            return EXIT_FAILURE;
        }

        graph = load_graph(input_alphabet, ribbon_alphabet, argv[1]);

        std::vector<std::string> ribbon = {"µ"};

        std::cout << "Enter a phrase: ";

        std::string phrase;
        std::cin >> phrase;

        for(char c : phrase)
        {
            std::string character = std::string(1, c);

            if(std::find(input_alphabet->begin(), input_alphabet->end(), character) != input_alphabet->end())
            {
                ribbon.push_back(std::string(1, c));
            }
            else
            {
                throw std::runtime_error("[ERROR]: Character \"" + character + "\" doesn't belong to the input alphabet ! Leaving the program...");
            }
        }

        ribbon.push_back("ß");

        for(std::string character : ribbon)
        {
            for(TransitionFunction *transition_function : *(graph->transition_functions))
            {
                if(transition_function->read == character)
                {
                    found = true;

                    print_ribbon(ribbon, "[INFO]: Ribbon before \"" + transition_function->write + "\" write: ");

                    ribbon[ribbon_head] = transition_function->write;

                    print_ribbon(ribbon, "[INFO]: Ribbon after \"" + transition_function->write + "\" write: ");
                    
                    if(transition_function->head_movement == "L")
                    {
                        if(ribbon_head == 0)
                            continue;
                        else
                            ribbon_head -= 1;
                    }
                    else if(transition_function->head_movement == "R")
                    {
                        ribbon_head += 1;
                    }

                    graph = transition_function->next_state;
                    break;
                }
            }

            if(found == false)
                throw std::runtime_error("[ERROR]: The phrase " + phrase + " is not recognized by machine !");
        }

        if(graph->status == "Accept")
            std::cout << "[INFO]: The phrase " + phrase + " is accepted by machine !" << std::endl;
        else if(graph->status == "Reject")
            std::cout << "[INFO]: The phrase " + phrase + " is rejected by machine !" << std::endl;
        else
            std::cout << "[INFO]: The phrase " + phrase + " is not recognized by machine !" << std::endl;

        return EXIT_SUCCESS;
    }
    catch(std::runtime_error ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}