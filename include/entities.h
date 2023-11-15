#pragma once

#include <libs.h>

typedef struct TransitionFunction
{
    std::string read;
    std::string write;
    std::string head_movement;
    struct State *next_state;
} TransitionFunction;

typedef struct State
{
    std::string identifier;
    std::string status;
    std::vector<struct TransitionFunction *> *transition_functions;
    struct State *next_state;
} State;