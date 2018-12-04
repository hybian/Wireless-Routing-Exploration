#ifndef AODV_H
#define AODV_H

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

// DEFINES
//   These channels are more likely to have less interference for 802.15.4 networks
#define RREQ_CHANNEL 15 // Broadcast
#define RREP_CHANNEL 20 // Unicast
#define DATA_CHANNEL 25 // Unicast

#define RREQ_PORT 61618
#define RREP_PORT 61619
#define DATA_PORT 61620

#define MAX_NEIGHBORS 5

#define DEBUG 1

#define MAX_BUFFER_SIZE 10

// PROTOTYPE FUNCTIONS
void reset_routing_tables();

// GLOBAL VARIABLES
//   Sockets
static struct udp_socket rreq_conn;
static struct udp_socket rrep_conn;
static struct udp_socket data_conn;

//   Socket Callback Funcs
static void rreq_cb(
    struct udp_socket *c,
    void *ptr,
    const uip_ipaddr_t *source_addr,
    uint16_t source_port,
    const uip_ipaddr_t *dest_addr,
    uint16_t dest_port,
    const uint8_t *data,
    uint16_t datalen
);

//   Socket Callback Funcs
static void data_cb(
    struct udp_socket *c,
    void *ptr,
    const uip_ipaddr_t *source_addr,
    uint16_t source_port,
    const uip_ipaddr_t *dest_addr,
    uint16_t dest_port,
    const uint8_t *data,
    uint16_t datalen
);

//   Socket Callback Funcs
static void rrep_cb(
    struct udp_socket *c,
    void *ptr,
    const uip_ipaddr_t *source_addr,
    uint16_t source_port,
    const uip_ipaddr_t *dest_addr,
    uint16_t dest_port,
    const uint8_t *data,
    uint16_t datalen
);

// Packet Formating
struct data_pkt
{
    int humidity;
    int temperature;
    int dest_addr;                // IP address to which data packets are to be transmitted
    int src_addr;
};

struct rreq_pkt
{
    int hop_count;     // The number of hops from the Originator IP Address to the node handling the request.
    int rreq_id;       // A sequence number uniquely identifying the particular RREQ when taken in conjunction with the originating node's IP address.
    int dest_addr;     // The IP address of the destination for which a route is desired.
    int dest_seq_no;   // The latest sequence number received in the past by the originator for any route towards the destination.
    int origin_addr;   // The IP address of the node which originated the Route Request.
    int origin_seq_no; // The current sequence number to be used in the route entry pointing towards the originator of the route request.
};

struct rrep_pkt
{
    int hop_count;   // The number of hops from the Originator IP Address to the Destination IP Address.
    int dest_addr;   // The IP address of the destination for which a route is supplied.
    int dest_seq_no; // The destination sequence number associated to the route.
    int origin_addr; // The IP address of the node which originated the RREQ for which the route is supplied.
    int lifetime;    // The time in milliseconds for which nodes receiving the RREP consider the route to be valid.
};

/**
 * AODV is a routing protocol, and it deals with route table management.
   Route table information must be kept even for short-lived routes,
   such as are created to temporarily store reverse paths towards nodes
   originating RREQs.
   */
struct routing_table_entry
{
    int dest_addr;
    int dest_seq_no;          // Crucial to avoiding routing loops
    // int valid_dest_sq_n;
    int valid;              // valid if link isn't broken or deactivated. invalid routes are not active
    // int nwk_iface;
    int hop_count;          // number of hops needed to reach destination
    int next_hop;
    // int precursors;
    int lifetime;           // expiration or deletion time of the route
};

#endif