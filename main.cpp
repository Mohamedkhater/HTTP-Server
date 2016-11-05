/*
 * File:   main.cpp
 * Author: amr
 *
 * Created on October 24, 2016, 8:43 PM
 */

#include <iostream>

#include "src/server/Server.h"

/*
 *
 */
int main(int argc, char ** argv) {
    Server* server = new Server(4001);
    server->run();

    return 0;
}
