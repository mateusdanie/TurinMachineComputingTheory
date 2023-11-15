#include <entities.h>

State* load_graph(std::vector<std::string> *input_alphabet, std::vector<std::string> *ribbon_alphabet, std::string_view file_name)
{
    std::fstream graph_file(file_name.data());

    if (!graph_file.is_open())
    {
        throw std::runtime_error("[ERRO]: Nao foi possivel ler o arquvio ! Saindo do programa ...");
    }

    State *start_list_ptr = nullptr;
    State *final_list_ptr = nullptr;    
    State *aux_ptr = nullptr;
    State *aux2_ptr = nullptr;
    uint32_t transaction_count;

    for (std::string file_line; std::getline(graph_file, file_line);)
    {
        if (file_line.empty())
            continue;

        size_t index{file_line.find_first_of(' ')};

        std::string_view line_view = file_line;

        std::string_view prefix = line_view.substr(0, index);

        std::string_view target = line_view.substr(index);

        std::istringstream stream{target.data()};

        if(prefix == "E")
        {
            uint32_t count = 0;
            std::string value = "";

            while(stream >> value)
            {
                State *new_state = new State();

                new_state->identifier = value;
                new_state->status = "";
                new_state->next_state = nullptr;
                new_state->transition_functions = new std::vector<TransitionFunction *>;
                
                if(count == 0)
                {
                    start_list_ptr = new_state;
                }
                else if (count == 1)
                {
                    start_list_ptr->next_state = new_state;
                    final_list_ptr = new_state;
                }
                else
                {
                    final_list_ptr->next_state = new_state;
                    final_list_ptr = new_state;
                }
                
                count++;
            }
        }
        else if(prefix == "A")
        {
            std::string value = "";
            
            while(stream >> value)
            {
                input_alphabet->push_back(value);
            }
        }
        else if(prefix == "F")
        {
            std::string value = "";
            
            while(stream >> value)
            {
                ribbon_alphabet->push_back(value);
            }
        }
        else if(prefix == "D")
        {
            std::string value = "";

            aux_ptr = start_list_ptr;

            stream >> value;

            while(aux_ptr->next_state != nullptr)
            {
                if(aux_ptr->identifier == value)
                {
                    break;
                }
                else
                {
                    aux_ptr = aux_ptr->next_state;
                }
            }
        }
        else if(prefix == "S")
        {
            stream >> aux_ptr->status;
        }
        else if(prefix == "T")
        {
            std::string value_read = "";
            std::string value_write = "";
            std::string head_movement = "";
            std::string target_state = "";

            stream >> value_read >> value_write >> head_movement >> target_state;
            
            aux2_ptr = start_list_ptr;

            TransitionFunction *transition = new TransitionFunction();

            transition->read = value_read;
            transition->write = value_write;
            transition->head_movement = head_movement;

            while(aux2_ptr->next_state != nullptr)
            {
                if(aux2_ptr->identifier == target_state)
                {
                    transition->next_state = aux2_ptr;
                    break;
                }
                else
                {
                    aux2_ptr = aux2_ptr->next_state;

                    if(aux2_ptr->identifier == target_state)
                    {
                        transition->next_state = aux2_ptr;
                        break;
                    }
                }
            }

            aux_ptr->transition_functions->push_back(transition);
        }
        else
        {
            continue;
        }
    }

    return start_list_ptr;
}

/*
void readGraph(State *Start, char *InputAlphabet, char *Ribbonalphabet, char *FilePath)
{


        else if (strcmp(content_sliced,"T") == 0)
        {
            // Aux2 = Start_List;
            // while(content_sliced != NULL){
            //     content_sliced = strtok(NULL, slice_delimitatator);
            //     if(j == 0 && content_sliced  != NULL)
            //         Aux->TransitionsFunctions[i].Read = content_sliced;
            //     else if (j == 1 && content_sliced  != NULL)
            //         Aux->TransitionsFunctions[i].Write = content_sliced;
            //     else if (j == 2 && content_sliced  != NULL)
            //         Aux->TransitionsFunctions[i].HeadMovement = content_sliced;
            //     else if (j == 3 && content_sliced  != NULL)
            //         while (Aux2->Next_State != NULL)
            //         {
            //             if(strcmp(Aux2->Identifier, content_sliced) == 0){
            //                 break;
            //             }else{
            //                 Aux2 = Aux2->Next_State;
            //             }
            //         }

            //        Aux->TransitionsFunctions[i].Next_State = Aux2;
            //     j++;
            // }   
            // i++;
        }
    }

/*
    // Aux = Start_List;
    // while (Aux->Next_State != NULL)
    // {
    //     printf("%s ", Aux->Identifier);
    //     Aux = Aux->Next_State;
    // }
}*/

