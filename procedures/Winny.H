/** \file
 * specifies all the sub-tasks/ operations involved in the complex job
 * of the winny-client module.
 * 
 * the job of the winny-client module is to monitor the user interface
 * and for each command entered, request for, receive and write out
 * the system response back to the user.
 * 
 * 
 * PART A
 * User-Input-Output Instructions: These are instructions 
 * to get user-requests from the user input-output module
 * and to send system-responses back.
 *
 * PART A.1
 * Instructions to retrieve and send user-requests:
 *      uiDriver::readRequest
 *      netDriver::SendUserRequest
 * 
 * Part A.2
 * Instructions to Retrieve and Write System Responses:
 *      ioWriteSystemResponse /uiDriver::WriteSystemResponse
 *      ioReceiveSystemResponse
 * 
 * PART B
 * Component Activation and Address Configuration Instructions
 * These are needed only because of the need for concurrency
 * and the need to handle possible changes of addresses
 * of local or remote components.
 * 
 * PART B.1.
 * Instruction to retrieve user-supplied options from config 
 * file.
 *      ioSyncWithUserConfig
 *      update default hard-coded options with user supplied 
 *      options
 */

#include <gmdataset.h> // For Request object field data types 


/**
 * \brief WinnyMachine namespace is a container of all the operations
 * performed by the WinnyVirtual Machine
 */
namespace Winny{

    #include <Request.H>
    #include <Response.H>

    /**
     * Most Machine operations that block and wait can be passed a value
     * of seconds to wait. upon expiry of which the operation will return
     * a timeout error. The value NO_WAIT is a constant value that tells
     * the machine to wait indefinitely untill the machine is shutdown or
     * untill the wait event occurs
     */
    const double NO_WAIT = 0.0;

    /**
     * \brief UI, short for User Interface is the component that 
     * mediates communication between the system and the user.
     * 
     * The UI can be activated and polled for any new data or 
     * commands entered by the user. It can also be feed with system
     * responses, which it then displays to the user
     */
    class UI{
    public:

        /**
         * \brief runs ui module to get next command. 
         * 
         * Activate the specified UI to run. pause and wait on it until
         * it finishes by default(when user enters a new command) or until
         * set timeout expires. 
         * 
         * @param[in] instance contains of the ui instance to read from
         * @param[in,out] commDataAdd contains address to a memory to put
         * the ui should put the RequestOperation.
         * @param[in] waitTime The max time to wait for user to enter
         * a request
         * @param[out] returnStatus 0 for time out, anyother code for
         * success 
         */
        static int run(ID instance, MemAddress commDataAdd , double waitTime);
        
        /**
         * \brief write response data at address addr to UI indentified by id
         * 
         * @param[in]instance contains the id of the instance to read from
         * @param[in]respAdd The address to the Response Data
         */
        static int writeSystemResponse(ID id, MemAddress addr);

        /**
         * Constructs a new UI instance and returns it's id that must be used
         * to refer to it laterl
         */
        static ID newInstance();
    };

    /**
     * Link is the component that transports commands and responses
     * to and from the physically separate clients and the Service.
     * 
     */
    class Link{
    public:
        /**
         * Retrieve any new pending responses waiting on link,
         * if Link has no pending responses, try waiting for some
         * time specified in waitTime. If time expires before
         * server sends any response on link, return TIMEOUT status else
         * copy response to internal memory and return address of that
         * location in addr
         * 
         * @param[in] waitTime Specifies how long to try waiting for
         * the server to send the system response
         * @param[out] addr    Contains the address to location where
         * returned response was stored on exit
         * @param[out] Status  Contains code that reports if operation
         * succeded (1) or failed o or timedout (TIMEOUT)
         */
        static int receiveSystemResponse(MemAddress addr, double waitTime);

        /**
         * Send command data specified at location addr across link to
         * the System service.
         * 
         * @param[in] addr Specifies the location of the command data to
         * send to the service
         */
        static int sendCommand(MemAddress addr);

        /**
         * Change this link's Remote Node Address to the address specified in
         * remAddr
         */ 
        static void setRemoteNodeAddress();

        /**
         */
        static int status();
    };
};
