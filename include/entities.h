#pragma once

#include <libs.h>

typedef struct TransitionFunction
{
    char read;
    char write;
    char head_movement;
    struct State* next_state;
} TransitionFunction;

typedef struct State
{
    std::string identifier;
    std::string status;
    struct TransitionFunction* transitions_functions;
    struct State* next_state;
} State;