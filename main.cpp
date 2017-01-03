#include "Logging.h"
#include <pthread.h>
#include "Globals.h"
#include <iostream>

int main() {
    struct datastruct d;
    d.data1 = 1;
    d.data2 = 2;



    Logging log = Logging(&d);
    log.run();
    //Consumer * poly = &log;
    //poly->run();
    
}
