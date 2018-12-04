/* @source my routing application
** @author: Omar Taylor (omtaylor@iastate.edu)
*/

#include "contiki.h"
#include "aodv.h"
#include "dev/leds.h"

#include <stdio.h>

// DEFINES
//   These channels are more likely to have less interference for 802.15.4 networks
#define RREQ_CHANNEL 15 // Broadcast
#define RREP_CHANNEL 20 // Unicast
#define DATA_CHANNEL 25 // Unicast

#define DEBUG 0

// PROCESSES DECLARATION
PROCESS(boot_process, "Prepares node for routing"); // Separating initiation process
PROCESS(data_process, "Data handler");              // Data should be able to be handled asyncrously
PROCESS(rreq_process, "RREQ packet handler");        //   from routing process

AUTOSTART_PROCESSES(&boot_process, &data_process, &rreq_process);

PROCESS_THREAD(boot_process, ev, data)
{
    PROCESS_BEGIN();

    PROCESS_END();
}

PROCESS_THREAD(data_process, ev, data)
{
    PROCESS_BEGIN();

    PROCESS_END();
}

PROCESS_THREAD(rreq_process, ev, data)
{
    PROCESS_BEGIN();

    PROCESS_END();
}