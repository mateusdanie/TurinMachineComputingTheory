#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TransitionFunction
{
    char Read;
    char Write;
    char HeadMovement;
    struct State* Next_State;
}TransitionFunction;


struct State
{
    //Name
    char* Identifier;

    //Status is Initial or Final.
    char* Status;

    //TransictionsFunctions
    struct TransitionFunction* TransitionsFunctions;

    struct State* Next_State;
}State;

struct State* readGraph(struct State* Start, char* InputAlphabet, char* Ribbonalphabet){
    FILE *file;
    file = fopen("TuringMachine.txt","r");

    if(file == NULL){
        printf("Arquivo Não pode ser aberto");
        return 0;
    }

    char content[256];
    char* content_sliced;
    char* slice_delimitatator = ",";
    struct State* Aux = NULL;
    struct State* Aux2 = NULL;
    struct State* Start_List = NULL;
    int j = 0;
    int i = 0;

    while (fgets(content, 256, file) != NULL)
    {   

        Aux = NULL;
        content_sliced = strtok(content, " ");
        if(strcmp(content_sliced,"E") == 0){
            while(content_sliced != NULL){
                content_sliced = strtok(NULL, slice_delimitatator);
                if(i == 0 && content_sliced != NULL){
                    struct State* New_State = (struct State *)malloc(sizeof(struct State));
                    New_State->Identifier = content_sliced;
                    Start_List = New_State;
                }else if (i == 1 && content_sliced != NULL)
                {
                    struct State* New_State = (struct State *)malloc(sizeof(struct State));
                    New_State->Identifier = content_sliced;
                    Start_List->Next_State = New_State;
                    Aux = New_State;
                }else if(i > 1 && content_sliced != NULL)
                {
                    struct State* New_State = (struct State *)malloc(sizeof(struct State));
                    New_State->Identifier = content_sliced;
                    Aux->Next_State = New_State;   
                    Aux = Aux->Next_State;
                }

                i++;
            }
        }else if(strcmp(content_sliced,"A") == 0)
        {   
            while(content_sliced != NULL){
                content_sliced = strtok(NULL, slice_delimitatator);
                if(content_sliced  != NULL)
                    strcat(InputAlphabet,content_sliced);
            }
        }else if(strcmp(content_sliced,"F") == 0)
        {   
            while(content_sliced != NULL){
                content_sliced = strtok(NULL, slice_delimitatator);
                if(content_sliced  != NULL)
                    strcat(Ribbonalphabet,content_sliced);
            }   
        }else if(strcmp(content_sliced,"D") == 0)
        {   
            Aux = Start_List;
            j = 0;
            i = 0;
            content_sliced = strtok(NULL, slice_delimitatator);
            while (Aux->Next_State != NULL)
            {
                if(strcmp(Aux->Identifier, content_sliced) == 0){
                    break;
                }else{
                    Aux = Aux->Next_State;
                }
            }
            
        }else if (strcmp(content_sliced,"S") == 0)
        {
            content_sliced = strtok(NULL, slice_delimitatator);
            Aux->Status = (char *) malloc(sizeof(content_sliced));
            Aux->Status = content_sliced;
        }else if (strcmp(content_sliced,"T") == 0)
        {
            Aux2 = Start_List;
            while(content_sliced != NULL){
                content_sliced = strtok(NULL, slice_delimitatator);
                if(j == 0 && content_sliced  != NULL)
                    Aux->TransitionsFunctions[i].Read = content_sliced;
                else if (j == 1 && content_sliced  != NULL)
                    Aux->TransitionsFunctions[i].Write = content_sliced;
                else if (j == 2 && content_sliced  != NULL)
                    Aux->TransitionsFunctions[i].HeadMovement =content_sliced;
                else if (j == 3 && content_sliced  != NULL)
                    while (Aux2->Next_State != NULL)
                    {
                        if(strcmp(Aux2->Identifier, content_sliced) == 0){
                            break;
                        }else{
                            Aux2 = Aux2->Next_State;
                        }
                    }

                   Aux->TransitionsFunctions[i].Next_State = Aux2;
                j++;
            }   
            i++;
        }
        
        
}

    return 0;
}
