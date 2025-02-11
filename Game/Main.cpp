#include "Engine.h"
#include "NQueens.h"

//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    Engine::window.SetSize(800, 800);
    Engine::window.SetTitle("NQueens");
    Engine::Run(new NQueens);

    return 0;
}

//--------------------------------------------------------------------------------------------------
