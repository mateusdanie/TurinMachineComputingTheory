#pragma once

typedef struct TransitionFunction
{
    char Read;
    char Write;
    char HeadMovement;
    struct State* Next_State;
} TransitionFunction;

typedef struct State
{
    //Name
    char* Identifier;
    //Status is Initial or Final.
    char* Status;
    //TransictionsFunctions
    struct TransitionFunction* TransitionsFunctions;
    struct State* Next_State;
} State;