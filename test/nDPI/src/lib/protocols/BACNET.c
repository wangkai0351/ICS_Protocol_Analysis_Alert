#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_BACNET

struct bacnet_heard{
  u_int8_t type,fun;
  u_int16_t len;
};

void ndpi_search_BacNet(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
 
  NDPI_LOG(NDPI_PROTOCOL_BACNET, ndpi_struct, NDPI_LOG_DEBUG, "Search BacNet.\n");

  if(packet->udp != NULL) {
    if(packet->payload_packet_len >= 4) {
		struct bacnet_heard *h = (struct bacnet_heard*)packet->payload;
		u_int16_t len = ntohs(h->len);
	   if(packet->payload_packet_len == len + 8) {
	       NDPI_LOG(ndpi_search_BacNet, ndpi_struct, NDPI_LOG_DEBUG, "BacNet Detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_BACNET, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }

	
      }    
  }

}

void init_BacNet_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS BacNet", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_BACNET,
				      ndpi_search_BacNet,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif

