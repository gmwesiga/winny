#ifndef TYPEREQUEST_H
#define TYPEREQUEST_H

#include <Basic.H>
#include <Constants.H>

/**
 * A RQID (Request ID) field / element object is a long integer
 */
typedef long  REQID;


/**
 * A Request is a data object whose fields/ elements represent the
 * data info of a particular request.
 */
struct Request {
    /** 
     * Read the private id field which contains a RQID value. id is unique for
     * each Request generated. It is meant to be used in situations where the
     * system needs to track down and identify this request individually from 
     * the rest.
     */
    REQID id();

    /**
     * operation field contains a RQOPERATION value, used to 
     * encode and decode the OPERATION that was requested by the user
     */
    REQOP operation; 

    /**
     * client field. this is a MemAddress to the IInterface object that 
     * captured this request and is waiting for response output
     * null by default
     */
    MemAddress client; 

    //address to additional data required to perform operation.
    MemAddress args; 

    ///priority field contains an int value equal to one of the values defined
    ///by the priority constants. This field is used to determine the urgency 
    ///treatment of this request. Urgent requests can not be processed
    ///in background. Currently there are two levels.
    /// URGENT == 1 AND BACKGROUND 0;
    int priority;

    /*Id() needs to be unique for each request, so we implement it here*/
    Request();

    /*copy construct semantics defined not to increment internal id counter*/
    Request(const Request& another);

    REQID& operator=(const Request& another);

};//end of RequestInfo

#endif /* TYPEREQUEST_H */
