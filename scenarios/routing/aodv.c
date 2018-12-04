/* @source my routing application
** @author: Omar Taylor (omtaylor@iastate.edu)
*/

#include "contiki.h"
#include "aodv.h"
#include "dev/leds.h"
#include "net/ipv6/udp-socket.h"
#include "dev/cc2420/cc2420.h"

#include <stdio.h>

// PROCESSES DECLARATION
PROCESS(boot_process, "Prepares node for routing"); // Separating initiation process
PROCESS(data_process, "Data handler");              // Data should be able to be handled asyncrously
PROCESS(rreq_process, "RREQ packet handler");       //   from routing process

AUTOSTART_PROCESSES(&boot_process, &data_process, &rreq_process);

//   Routing Tables
static struct routing_table_entry routing_tbl_entry[MAX_NEIGHBORS];

PROCESS_THREAD(boot_process, ev, data)
{
    PROCESS_EXITHANDLER({
#if DEBUG
        printf("Closings socket connections.\n");
#endif
        udp_socket_close(&rreq_conn);
        udp_socket_close(&rrep_conn);
        udp_socket_close(&data_conn);
    });

    PROCESS_BEGIN();

    reset_routing_tables();

    // RREQ Init
    if (!udp_socket_register(&rreq_conn, NULL, &rreq_cb))
    {
        printf("RREQ socket registration failed.\n");
        PROCESS_EXIT();
    }

    if (!udp_socket_bind(&rreq_conn, RREQ_PORT))
    {
        printf("RREQ socket binding failed.\n");
        PROCESS_EXIT();
    }

#if DEBUG
    printf("RREQ is listening on port %ld.\n", RREQ_PORT);
#endif

    // RREP Init
    if (!udp_socket_register(&rrep_conn, NULL, &rrep_cb))
    {
        printf("RREP socket registration failed.\n");
        PROCESS_EXIT();
    }

    if (!udp_socket_bind(&rrep_conn, RREP_PORT))
    {
        printf("RREP socket binding failed.\n");
        PROCESS_EXIT();
    }

#if DEBUG
    printf("RREP is listening on port %ld.\n", RREP_PORT);
#endif

    // DATA Init
    if (!udp_socket_register(&data_conn, NULL, &data_cb))
    {
        printf("Data socket registration failed.\n");
        PROCESS_EXIT();
    }

    if (!udp_socket_bind(&data_conn, DATA_PORT))
    {
        printf("Data socket binding failed.\n");
        PROCESS_EXIT();
    }

#if DEBUG
    printf("DATA is listening on port %ld.\n", DATA_PORT);
#endif

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

void reset_routing_tables()
{
    int i;
    for (i = 0; i < MAX_NEIGHBORS; i++)
    {
        routing_tbl_entry[i].dest_addr = 0;
        routing_tbl_entry[i].dest_seq_no = 0;
        routing_tbl_entry[i].hop_count = INT16_MAX;
        routing_tbl_entry[i].lifetime = 0;
        routing_tbl_entry[i].next_hop = 0;
        routing_tbl_entry[i].valid = 0;
    }
}

static void rreq_cb(struct udp_socket *c,
                    void *ptr,
                    const uip_ipaddr_t *source_addr,
                    uint16_t source_port,
                    const uip_ipaddr_t *dest_addr,
                    uint16_t dest_port,
                    const uint8_t *data,
                    uint16_t datalen)
{
}

static void data_cb(
    struct udp_socket *c,
    void *ptr,
    const uip_ipaddr_t *source_addr,
    uint16_t source_port,
    const uip_ipaddr_t *dest_addr,
    uint16_t dest_port,
    const uint8_t *data,
    uint16_t datalen) {}

static void rrep_cb(
    struct udp_socket *c,
    void *ptr,
    const uip_ipaddr_t *source_addr,
    uint16_t source_port,
    const uip_ipaddr_t *dest_addr,
    uint16_t dest_port,
    const uint8_t *data,
    uint16_t datalen) {}
