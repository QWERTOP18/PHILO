#include "system.h"





int main(int argc, char **argv)
{
    t_sys *sys;

    sys = system_init(argc, argv);
    // Start the simulation
    //...
    system_exit(sys, 0);
}