#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_ESIO

struct esio_heard{
  u_int32_t esio;
  u_int16_t type,version,len,ID;
};

void ndpi_search_ESIO(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  u_int16_t dport = 0, sport = 0;

  NDPI_LOG(NDPI_PROTOCOL_ESIO, ndpi_struct, NDPI_LOG_DEBUG, "search esio.\n");

  if(packet->udp != NULL) {
    if(packet->payload_packet_len >= 8 &&
		packet->payload[0]==0x45 &&
		packet->payload[1]==0x53 &&
		packet->payload[2]==0x49 &&
		packet->payload[3]==0x4f ) {
		struct esio_heard *t = (struct esio_heard*)packet->payload;
		u_int16_t len = ntohs(t->len);
	   if(packet->payload_packet_len == len) {
	       NDPI_LOG(ndpi_search_ESIO, ndpi_struct, NDPI_LOG_DEBUG, "esio detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_ESIO, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }

	
      }    
  }

}

void init_ESIO_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS ESIO", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_ESIO,
				      ndpi_search_ESIO,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif

