#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_DNP30


#define AL_FUNC_CONFIRM    0x00    /* 00  - Confirm */
#define AL_FUNC_READ       0x01    /* 01  - Read */
#define AL_FUNC_WRITE      0x02    /* 02  - Write */
#define AL_FUNC_SELECT     0x03    /* 03  - Select */
#define AL_FUNC_OPERATE    0x04    /* 04  - Operate */
#define AL_FUNC_DIROP      0x05    /* 05  - Direct Operate */
#define AL_FUNC_DIROPNACK  0x06    /* 06  - Direct Operate No ACK */
#define AL_FUNC_FRZ        0x07    /* 07  - Immediate Freeze */
#define AL_FUNC_FRZNACK    0x08    /* 08  - Immediate Freeze No ACK */
#define AL_FUNC_FRZCLR     0x09    /* 09  - Freeze and Clear */
#define AL_FUNC_FRZCLRNACK 0x0A    /* 10  - Freeze and Clear No ACK */
#define AL_FUNC_FRZT       0x0B    /* 11  - Freeze With Time */
#define AL_FUNC_FRZTNACK   0x0C    /* 12  - Freeze With Time No ACK */
#define AL_FUNC_COLDRST    0x0D    /* 13  - Cold Restart */
#define AL_FUNC_WARMRST    0x0E    /* 14  - Warm Restart */
#define AL_FUNC_INITDATA   0x0F    /* 15  - Initialize Data */
#define AL_FUNC_INITAPP    0x10    /* 16  - Initialize Application */
#define AL_FUNC_STARTAPP   0x11    /* 17  - Start Application */
#define AL_FUNC_STOPAPP    0x12    /* 18  - Stop Application */
#define AL_FUNC_SAVECFG    0x13    /* 19  - Save Configuration */
#define AL_FUNC_ENSPMSG    0x14    /* 20  - Enable Spontaneous Msg */
#define AL_FUNC_DISSPMSG   0x15    /* 21  - Disable Spontaneous Msg */
#define AL_FUNC_ASSIGNCL   0x16    /* 22  - Assign Classes */
#define AL_FUNC_DELAYMST   0x17    /* 23  - Delay Measurement */
#define AL_FUNC_RECCT      0x18    /* 24  - Record Current Time */
#define AL_FUNC_OPENFILE   0x19    /* 25  - Open File */
#define AL_FUNC_CLOSEFILE  0x1A    /* 26  - Close File */
#define AL_FUNC_DELETEFILE 0x1B    /* 27  - Delete File */
#define AL_FUNC_GETFILEINF 0x1C    /* 28  - Get File Info */
#define AL_FUNC_AUTHFILE   0x1D    /* 29  - Authenticate File */
#define AL_FUNC_ABORTFILE  0x1E    /* 30  - Abort File */
#define AL_FUNC_ACTCNF     0x1F    /* 31  - Activate Config */
#define AL_FUNC_AUTHREQ    0x20    /* 32  - Authentication Request */
#define AL_FUNC_AUTHERR    0x21    /* 33  - Authentication Error */
#define AL_FUNC_RESPON     0x81    /* 129 - Response */
#define AL_FUNC_UNSOLI     0x82    /* 130 - Unsolicited Response */
#define AL_FUNC_AUTHRESP   0x83    /* 131 - Authentication Response */


struct data_link_layer{
  u_int16_t start;
  u_int8_t len,control;
  u_int16_t dest,src;
  u_int16_t crc;
};

struct read_object
{
 u_int8_t object;
 u_int8_t  var;
 u_int8_t  def;


};
void alterdnp30(struct json_object *dnp30_object)
{


}

void dissectDnp30(char *payload,int payload_len,json_object *commandlist)
{
	char theDate[32];
	char cmd[20]={0};
	char value[20]={0};
	time_t theTime = time(NULL);
	int obj_len;
#ifndef WIN32	 	 
	  struct tm result; 	 
#endif
    struct json_object *dnp30_object = json_object_new_object();
  

  if(payload_len >= 15 )
  	{
  	 strftime(theDate, 32, "%d/%b/%Y %H:%M:%S", localtime_r(&theTime,&result) );
  	 u_int8_t  fc = *(payload + 12);
	 int last = payload_len-13;
	 struct read_object *t;
	 switch (fc){
	 	case AL_FUNC_CONFIRM:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Confirm"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_READ:
			while(last>=3)
				{
				  t = (struct read_object*)(payload+13);
				  sprintf(value,"Obj=%d,Var=%d ",t->object,t->var);
				  last = last - 3;
			}
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Read"));
			json_object_object_add(dnp30_object,"value",json_object_new_string(value));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_WRITE:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Write"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_SELECT:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Select"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_OPERATE:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Operate"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_DIROP:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Direct Operate"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_DIROPNACK:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Direct Operate No ACK"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_FRZ:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Immediate Freeze"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
		case AL_FUNC_FRZNACK:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Immediate Freeze No ACK"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_FRZCLR:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Freeze and Clear"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_FRZCLRNACK:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Freeze and Clear No ACK"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_FRZT:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Freeze With Time"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_FRZTNACK:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Freeze With Time No ACK"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_COLDRST:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Cold Restart"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_INITDATA:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Initialize Data"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_WARMRST:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Warm Restart"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_INITAPP:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Initialize Application"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_STARTAPP:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Start Application"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_STOPAPP:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Stop Application"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_SAVECFG:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Save Configuration"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_ENSPMSG:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Enable Spontaneous Msg"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_DISSPMSG:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Disable Spontaneous Msg"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_ASSIGNCL:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Assign Classes"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_DELAYMST:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Delay Measurement"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_RECCT:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Record Current Time"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_OPENFILE:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Open File"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_CLOSEFILE:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Close File"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_DELETEFILE:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Delete File"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_GETFILEINF:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Get File Info"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_AUTHFILE:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Authenticate File"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_ABORTFILE:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Abort File"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_ACTCNF:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Activate Config"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_AUTHREQ:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Authentication Request"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_AUTHERR:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Authentication Error"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_RESPON:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Response"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_UNSOLI:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Unsolicited Response"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		case AL_FUNC_AUTHRESP:
			json_object_object_add(dnp30_object,"time",json_object_new_string(theDate));
			json_object_object_add(dnp30_object,"command",json_object_new_string("Authentication Response"));
			json_object_object_add(dnp30_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,dnp30_object);
			break;
		default:
			break;
			
			
			
			
	 	}
    
  
  }
  
 
}



void ndpi_search_DNP30(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  u_int16_t dport = 0, sport = 0;

  NDPI_LOG(NDPI_PROTOCOL_DNP30, ndpi_struct, NDPI_LOG_DEBUG, "search dnp3.0.\n");

  if(packet->tcp != NULL) {
    if(packet->payload_packet_len >= 10) {
		struct data_link_layer *t = (struct data_link_layer*)packet->payload;
		u_int16_t len = ntohs(t->len);
	   if(packet->payload_packet_len == len+5) {
	       NDPI_LOG(ndpi_search_ethernetip, ndpi_struct, NDPI_LOG_DEBUG, "dnp3.0 detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_DNP30, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }

	
      }    
  }

}

void init_DNP30_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS DNP3.0", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_DNP30,
				      ndpi_search_DNP30,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif

