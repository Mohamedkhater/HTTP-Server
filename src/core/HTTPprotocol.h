/*
 * File:   HTTPprotocol.h
 * Author: amr
 *
 * Created on October 24, 2016, 11:17 PM
 */

#ifndef HTTPPROTOCOL_H
#define HTTPPROTOCOL_H

#include "http.h"
#include <string>

class HTTPprotocol
{
    public:
        HTTPprotocol();

        virtual ~HTTPprotocol();

        void set(Protocol);

        void set(std::string);

        Protocol get();

        std::string getString();

    private:
        Protocol _protocol;
};
#endif   /* HTTPPROTOCOL_H */


//~ Formatted by Jindent --- http://www.jindent.com
