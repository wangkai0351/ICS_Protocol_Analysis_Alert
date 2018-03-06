#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_RTPS

/* Submessage Type */
#define SUBMESSAGE_PAD                                  (0x01)
#define SUBMESSAGE_DATA                                 (0x02)
#define SUBMESSAGE_NOKEY_DATA                           (0x03)
#define SUBMESSAGE_ACKNACK                              (0x06)
#define SUBMESSAGE_HEARTBEAT                            (0x07)
#define SUBMESSAGE_GAP                                  (0x08)
#define SUBMESSAGE_INFO_TS                              (0x09)
#define SUBMESSAGE_INFO_SRC                             (0x0c)
#define SUBMESSAGE_INFO_REPLY_IP4                       (0x0d)
#define SUBMESSAGE_INFO_DST                             (0x0e)
#define SUBMESSAGE_INFO_REPLY                           (0x0f)

#define SUBMESSAGE_DATA_FRAG                            (0x10)  /* RTPS 2.0 Only */
#define SUBMESSAGE_NOKEY_DATA_FRAG                      (0x11)  /* RTPS 2.0 Only */
#define SUBMESSAGE_NACK_FRAG                            (0x12)  /* RTPS 2.0 Only */
#define SUBMESSAGE_HEARTBEAT_FRAG                       (0x13)  /* RTPS 2.0 Only */

#define SUBMESSAGE_RTPS_DATA_SESSION                    (0x14)  /* RTPS 2.1 only */
#define SUBMESSAGE_RTPS_DATA                            (0x15)  /* RTPS 2.1 only */
#define SUBMESSAGE_RTPS_DATA_FRAG                       (0x16)  /* RTPS 2.1 only */
#define SUBMESSAGE_ACKNACK_BATCH                        (0x17)  /* RTPS 2.1 only */
#define SUBMESSAGE_RTPS_DATA_BATCH                      (0x18)  /* RTPS 2.1 Only */
#define SUBMESSAGE_HEARTBEAT_BATCH                      (0x19)  /* RTPS 2.1 only */
#define SUBMESSAGE_ACKNACK_SESSION                      (0x1a)  /* RTPS 2.1 only */
#define SUBMESSAGE_HEARTBEAT_SESSION                    (0x1b)  /* RTPS 2.1 only */
#define SUBMESSAGE_APP_ACK                              (0x1c)
#define SUBMESSAGE_APP_ACK_CONF                         (0x1d)
#define SUBMESSAGE_HEARTBEAT_VIRTUAL                    (0x1e)
#define SUBMESSAGE_SECURE                               (0x30)

#define SUBMESSAGE_RTI_CRC                              (0x80)


static const value_string rtps_id_vals[] = {
  { SUBMESSAGE_PAD,               "PAD" },
  { SUBMESSAGE_DATA,              "DATA" },
  { SUBMESSAGE_NOKEY_DATA,        "NOKEY_DATA" },
  { SUBMESSAGE_ACKNACK,           "ACKNACK" },
  { SUBMESSAGE_HEARTBEAT,         "HEARTBEAT" },
  { SUBMESSAGE_GAP,               "GAP" },
  { SUBMESSAGE_INFO_TS,           "INFO_TS" },
  { SUBMESSAGE_INFO_SRC,          "INFO_SRC" },
  { SUBMESSAGE_INFO_REPLY_IP4,    "INFO_REPLY_IP4" },
  { SUBMESSAGE_INFO_DST,          "INFO_DST" },
  { SUBMESSAGE_INFO_REPLY,        "INFO_REPLY" },
};


void dissectRTPS(char *payload,int payload_len,json_object *commandlist)
{

	char *p = payload;
	u_int8_t c;
	char theDate[32];
	char value[20]={0};
	time_t theTime = time(NULL);
	int     cmd_str_idx;
	int obj_len;
#ifndef WIN32	 	 
	  struct tm result; 	 
#endif

	if(payload_len < 16)
		return ;
	
	struct json_object *RTPS_object = json_object_new_object();
	strftime(theDate, 32, "%d/%b/%Y %H:%M:%S", localtime_r(&theTime,&result) );
	if(payload[4]==0x01)
		c = *(p + 16);
	else if(payload[4]==0x02)
		c = *(p + 20);
	else 
		c = 0;
	char *cmd_str = try_val_to_str_idx(c, rtps_id_vals, &cmd_str_idx);
	if (cmd_str_idx == -1)
        return;
	else
		{
		json_object_object_add(RTPS_object,"time",json_object_new_string(theDate));
	    json_object_object_add(RTPS_object,"command",json_object_new_string(cmd_str));
		json_object_object_add(RTPS_object,"value",json_object_new_string("NULL"));
		json_object_array_add(commandlist,RTPS_object);


	}

	


	  
			
  
}



void ndpi_search_RTPS(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  NDPI_LOG(NDPI_PROTOCOL_RTPS, ndpi_struct, NDPI_LOG_DEBUG, "search RTPS.\n");

  if(packet->udp != NULL) {
    if(packet->payload_packet_len >= 16 &&
		packet->payload[0]==0x52 &&
		packet->payload[1]==0x54 &&
		packet->payload[2]==0x50 &&
		packet->payload[3]==0x53 ) {
	   if(packet->payload[4]==0x01||packet->payload[4]==0x02) {
	       NDPI_LOG(ndpi_search_RTPS, ndpi_struct, NDPI_LOG_DEBUG, "RTPS detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_RTPS, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }

	
      }    
  }

}

void init_RTPS_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS RTPS", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_RTPS,
				      ndpi_search_RTPS,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif

