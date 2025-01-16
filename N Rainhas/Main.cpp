#include "Engine.h"
#include "NQueens.h"

//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    Engine::window.Size(800, 800);
    Engine::window.Title("NQueens");
    Engine::Run(new NQueens);

    return 0;
}

//--------------------------------------------------------------------------------------------------
