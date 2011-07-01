#include <stdio.h>
#include "cpptk/cpptk.h"
using namespace Tk;

void hello() {
     puts("Hello C++/Tk!");
}

int main(int, char *argv[])
{
    static char* str = "button .a -text 'Say Hello ppure TCL'\n"
                   "pack .a\n";
     init(argv[0]);

     button(".b") -text("Say Hello") -command(hello);
     pack(".b") -padx(20) -pady(6);

     runEventLoop();
}