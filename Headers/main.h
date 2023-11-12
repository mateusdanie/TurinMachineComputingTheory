struct State
{
    //Name
    char Identifier[8];

    //Status is Initial or Final.
    char Status[256];

    //TransictionFunction
    char Read;
    char Write;
    char HeadMovement;
    struct State* Next;
}State;

