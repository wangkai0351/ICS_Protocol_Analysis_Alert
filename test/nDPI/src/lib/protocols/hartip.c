#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_HARTIP

struct hartip_heard{
  u_int8_t version,type,id,status;
  u_int16_t sequence;
  u_int16_t len;
  
};


void dissectHartIp(char *payload,int payload_len,json_object *commandlist)
{

	char *p = payload;
	u_int16_t c;
	char theDate[32];
	char value[20]={0};
	time_t theTime = time(NULL);
	int     cmd_str_idx;
	int obj_len;
#ifndef WIN32	 	 
	  struct tm result; 	 
#endif

	if(payload_len < 12)
		return ;
	u_int8_t icf_flags = *p;
	if (icf_flags & 0x40) {
        return ; 
    }
	struct json_object *omron_object = json_object_new_object();
	strftime(theDate, 32, "%d/%b/%Y %H:%M:%S", localtime_r(&theTime,&result) );
	//c = ntohs(h->command);
	char *cmd_str ;//= try_val_to_str_idx(c, command_code_cv, &cmd_str_idx);
	if (cmd_str_idx == -1)
        return;
	else
		{
		json_object_object_add(omron_object,"time",json_object_new_string(theDate));
	    json_object_object_add(omron_object,"command",json_object_new_string(cmd_str));
		json_object_object_add(omron_object,"value",json_object_new_string("NULL"));
		json_object_array_add(commandlist,omron_object);


	}

	


	  
			
  
}


void ndpi_search_HartIp(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  NDPI_LOG(NDPI_PROTOCOL_HARTIP, ndpi_struct, NDPI_LOG_DEBUG, "search HartIp.\n");

     if(packet->payload_packet_len >= 8) {
		struct hartip_heard *t = (struct hartip_heard*)packet->payload;
		u_int16_t len = ntohs(t->len);
	   if(packet->payload_packet_len == len) {
	       NDPI_LOG(NDPI_PROTOCOL_HARTIP, ndpi_struct, NDPI_LOG_DEBUG, "HartIp detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_HARTIP, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }

	
      }  

}

void init_HartIp_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS HART-IP", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_HARTIP,
				      ndpi_search_HartIp,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif

