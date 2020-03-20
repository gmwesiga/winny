/** \file
 * Contains the definitions of the user io procedures
 * The procedures here are currently defined in terms of an Iscreen
 * object operations. The definition of the Iscreen object is there-
 * for assumed to be known.
 */

#include <IScreen.h> /**< Source of known definition operations*/
#include <Winny.H>   /**< Source of unknown definitions to be defined*/
#include <map>       /**< current implementation of instance id table*/

using Winny::UI;

/**
 * Table for mapping external IDs to internal Iscreen* addresses
 */
std::map<ID,IScreen*>instances;

int UI::run(ID instance, MemAddress commDataAdd , double waitTime){
    instances[instance]->runUntilInput(commDataAdd,waitTime);
};

static int UI::writeSystemResponse(ID id, MemAddress addr);


/**
 * holds the next value in a sequence of ids to be assigned to next 
 * screen created, initially 1
 */
long nextId =1;

ID UI::newInstance(){
    instances[nextId] = IScreen::screen();
    nextId++;
    return instances[nextId];
};