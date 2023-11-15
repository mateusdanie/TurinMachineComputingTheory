#include <entities.h>

void load_graph(State *start_state, std::vector<std::string> *input_alphabet, std::vector<std::string> *ribbon_alphabet, std::string_view file_name)
{
    std::fstream coordinates_file(file_name.data());

    if (!coordinates_file.is_open())
    {
        throw "[ERROR]: Unable to open tue file ! Leaving the program ...";
    }

    for (std::string file_line; std::getline(coordinates_file, file_line);)
    {
        if (file_line.empty())
            continue;

        size_t index{file_line.find_first_of(' ')};

        std::string_view line_view = file_line;

        std::string_view prefix = line_view.substr(0, index);

        std::string_view target = line_view.substr(index);

        std::istringstream stream{target.data()};
        
        State *start_list_ptr = nullptr;
        State *final_list_ptr = nullptr;

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
                new_state->transitions_functions = nullptr;
                
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
                    start_list_ptr->next_state = new_state;
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

        }
        else if(prefix == "S")
        {

        }
        else if(prefix == "T")
        {

        }
        else
        {
            continue;
        }
    }
}

/*
void readGraph(State *Start, char *InputAlphabet, char *Ribbonalphabet, char *FilePath)
{

    while (fgets(content, 256, file) != NULL)
    {   
        content_sliced = strtok(content, " ");

        else if(strcmp(content_sliced,"A") == 0)
        {   
            while(content_sliced != NULL)
            {
                content_sliced = strtok(NULL, slice_delimitatator);
                if(content_sliced  != NULL)
                    strcat(InputAlphabet, content_sliced);
            }
        }
        else if(strcmp(content_sliced,"F") == 0)
        {   
            while(content_sliced != NULL)
            {
                content_sliced = strtok(NULL, slice_delimitatator);
                if(content_sliced  != NULL)
                    strcat(Ribbonalphabet, content_sliced);
            }   
        }
        else if(strcmp(content_sliced,"D") == 0)
        {   
            Aux = Start_List;
            j = 0;
            i = 0;
            content_sliced = strtok(NULL, slice_delimitatator);
            while (Aux->Next_State != NULL)
            {
                if(strcmp(Aux->Identifier, content_sliced) == 0)
                {
                    break;
                }
                else
                {
                    Aux = Aux->Next_State;
                }
            }
        }
        else if (strcmp(content_sliced,"S") == 0)
        {
            content_sliced = strtok(NULL, slice_delimitatator);
            Aux->Status = content_sliced;
        }
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

