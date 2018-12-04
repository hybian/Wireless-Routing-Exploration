/* @source my routing application
** @author: Omar Taylor (omtaylor@iastate.edu)
*/

#include "contiki.h"
#include "myrouting.h"

#include <stdio.h>

// DEFINES

#define DEBUG 0

// PROCESSES DECLARATION

PROCESS(myrouting_process, "My routing process");

AUTOSTART_PROCESSES(&myrouting_process);

PROCESS_THREAD(myrouting_process, ev, data)
{
    PROCESS_BEGIN();

    PROCESS_END();
}