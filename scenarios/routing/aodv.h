#ifndef AODV_H
#define AODV_H

#define MAX_BUFFER_SIZE 10

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