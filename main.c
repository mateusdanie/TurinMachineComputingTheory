#include <stdio.h>
#include <stdlib.h>
#include "Headers/main.h"

struct State* Start = NULL;
char* InputAlphabet;
char* Ribbonalphabet;

int main(){
    readGraph(Start, &InputAlphabet, &Ribbonalphabet);
}