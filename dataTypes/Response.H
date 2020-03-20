#ifndef TYPERESPONSE_H
#define TYPERESPONSE_H

///defines REQID, which is needed
#include <Basic.H>
#include <Request.H>  
#include <../gmdataset.h>

/**
 * Structured data object with fields representing the system's response
 * from operating a REQOP
 */

struct Response {

    //tells if operaton was succefull
    int ok;

    //contains a message about the operation.
    variable message;

    //contains data for query operations
    dataset data;

    //the originating request's id
    REQID requestId;

    //the actual request sent for this respons;
    Request request;

    //default constructor;
    Response():ok(1), data(0,0){};
};

#endif /* TYPERESPONSE_H */
