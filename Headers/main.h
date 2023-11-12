struct TransitionFunction
{
    char Read;
    char Write;
    char HeadMovement;
    struct State* Next;
}TransitionFunction;


struct State
{
    //Name
    char Identifier[8];

    //Status is Initial or Final.
    char Status[256];

    //TransictionsFunctions
    struct TransitionFunction* TransitionsFunctions;
}State;

