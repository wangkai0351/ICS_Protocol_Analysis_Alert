#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_ETHERNET

struct ethernetiphead {
  u_int16_t cmd,len;
  u_int32_t session,status;
  u_int64_t context;
  u_int32_t option;
};



void ndpi_search_ethernetip(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  u_int16_t dport = 0, sport = 0;

  NDPI_LOG(NDPI_PROTOCOL_ETHERNET, ndpi_struct, NDPI_LOG_DEBUG, "search ethernetip.\n");

  if(packet->tcp != NULL) {
    if(packet->payload_packet_len >= 24) {
		struct ethernetiphead *t = (struct ethernetiphead*)packet->payload;
		u_int16_t len = ntohs(t->len);
	   if(packet->payload_packet_len == len+24) {
	       NDPI_LOG(ndpi_search_ethernetip, ndpi_struct, NDPI_LOG_DEBUG, "ethernetip detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_ETHERNET, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }
      }    
  }

}

void init_ethernetip_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS Etherntetip", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_ETHERNET,
				      ndpi_search_ethernetip,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif
