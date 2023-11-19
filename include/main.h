#include <entities.h>

State* load_graph(std::vector<std::string> *input_alphabet, std::vector<std::string> *ribbon_alphabet, std::string_view file_name)
{
    std::fstream graph_file(file_name.data());

    if (!graph_file.is_open())
    {
        throw std::runtime_error("[ERROR]: Unable to read the file ! Leaving the program...");
    }

    State *start_list_ptr = nullptr;
    State *final_list_ptr = nullptr;    
    State *aux_ptr = nullptr;
    State *aux2_ptr = nullptr;
    uint32_t transaction_count;
    uint32_t initial_count;

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
            std::string value;
            bool multiple_status = false;

            while(stream >> value)
            {
                if(multiple_status)
                {
                    aux_ptr->status += " " + value;
                }
                else
                {
                    aux_ptr->status = value;
                    multiple_status = true;
                }
            }
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

    aux_ptr = start_list_ptr;

    bool found = false;

    while(aux_ptr->next_state != nullptr)
    {
        std::istringstream find_stream(aux_ptr->status);
        std::string status;

        while(find_stream >> status)
        {
            if(status == "Initial")
            {
                found = true;
                break;
            }
        }

        if(found)
            break;

        aux_ptr	= aux_ptr->next_state;

        if(aux_ptr->next_state == nullptr)
            break;
    }

    if(!found)
        throw std::runtime_error("[ERROR]: Initial status not informed ! Leaving the program...");

    return aux_ptr;
}