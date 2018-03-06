#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_OMRON

struct omron_heard{
  u_int8_t icf,Reserved,gatway,dst_net,dst_node,dst_unit,src_net,src_node,src_unit;
  u_int8_t service_id;
  u_int16_t command;
};



static const value_string command_code_cv[] = {
    { 0x0101, "Memory Area Read" },
    { 0x0102, "Memory Area Write" },
    { 0x0103, "Memory Area Fill" },
    { 0x0104, "Multiple Memory Area Read" },
    { 0x0105, "Memory Area Transfer" },
    { 0x0201, "Parameter Area Read" },
    { 0x0202, "Parameter Area Write" },
    { 0x0203, "Parameter Area Clear" },
    { 0x0220, "Data Link Table Read" },
    { 0x0221, "Data Link Table Write" },
    { 0x0304, "Program Area Protect" },
    { 0x0305, "Program Area Protect Clear" },
    { 0x0306, "Program Area Read" },
    { 0x0307, "Program Area Write" },
    { 0x0308, "Program Area Clear" },
    { 0x0401, "Run" },
    { 0x0402, "Stop" },
    { 0x0403, "Reset" },
    { 0x0501, "Controller Data Read" },
    { 0x0502, "Connection Data Read" },
    { 0x0601, "Controller Status Read" },
    { 0x0602, "Network Status Read" },
    { 0x0603, "Data Link Status Read" },
    { 0x0620, "Cycle Time Read" },
    { 0x0701, "Clock Read" },
    { 0x0702, "Clock Write" },
    { 0x0801, "LOOP-BACK Test" },
    { 0x0802, "Broadcast Test Results Read" },
    { 0x0803, "Broadcast Test Data Send" },
    { 0x0920, "Message Read | Message Clear | FAL/FALS Read" },
    { 0x0C01, "Access Right Acquire" },
    { 0x0C02, "Access Right Forced Acquire" },
    { 0x0C03, "Access Right Release" },
    { 0x2101, "Error Clear" },
    { 0x2102, "Error Log Read" },
    { 0x2103, "Error Log Clear" },
    { 0x2201, "File Name Read" },
    { 0x2202, "Single File Read" },
    { 0x2203, "Single File Write" },
    { 0x2204, "Memory Card Format" },
    { 0x2205, "File Delete" },
    { 0x2206, "Volume Label Create/Delete" },
    { 0x2207, "File Copy" },
    { 0x2208, "File Name Change" },
    { 0x2209, "File Data Check" },
    { 0x220A, "Memory Area File Transfer" },
    { 0x220B, "Parameter Area File Transfer" },
    { 0x220C, "Program Area File Transfer" },
    { 0x220F, "File Memory Index Read" },
    { 0x2210, "File Memory Read" },
    { 0x2211, "File Memory Write" },
    { 0x2301, "Forced Set/Reset" },
    { 0x2302, "Forced Set/Reset Cancel" },
    { 0x230A, "Multiple Forced Status Read" },
    { 0x2601, "Name Set" },
    { 0x2602, "Name Delete" },
    { 0x2603, "Name Read" },
    { 0,    NULL                } };


const char*
try_val_to_str_idx(const u_int16_t val, const value_string *vs, int *idx)
{
    int i = 0;


    if(vs) {
        while (vs[i].strptr) {
            if (vs[i].value == val) {
                *idx = i;
                return(vs[i].strptr);
            }
            i++;
        }
    }

    *idx = -1;
    return NULL;
}


void dissectOmron(char *payload,int payload_len,json_object *commandlist)
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
	struct omron_heard *h = (struct omron_heard*)payload;
	c = ntohs(h->command);
	char *cmd_str = try_val_to_str_idx(c, command_code_cv, &cmd_str_idx);
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


void ndpi_search_Omron(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  u_int16_t dport = 0, sport = 0;
  

  NDPI_LOG(NDPI_PROTOCOL_OMRON, ndpi_struct, NDPI_LOG_DEBUG, "search Omron.\n");

  if(packet->udp != NULL) {
    if(packet->payload_packet_len >= 12) {
				
	   if(packet->payload[1]==0x00&&packet->payload[2]==0x02) {
	       NDPI_LOG(ndpi_search_Omron, ndpi_struct, NDPI_LOG_DEBUG, "Omron detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_OMRON, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }

	
      }    
  }

}

void init_Omron_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS Omron", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_OMRON,
				      ndpi_search_Omron,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif

