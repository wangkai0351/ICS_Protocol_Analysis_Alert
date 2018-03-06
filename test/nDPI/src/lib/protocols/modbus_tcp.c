#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_MODBUS_TCP

struct modbus {
  u_int16_t transaction,protocol,len;
  u_int8_t unit;
};

/* Modbus protocol function codes */
#define READ_COILS				1
#define READ_DISCRETE_INPUTS	2
#define READ_HOLDING_REGS		3
#define READ_INPUT_REGS			4
#define WRITE_SINGLE_COIL		5
#define WRITE_SINGLE_REG		6
#define READ_EXCEPT_STAT		7
#define DIAGNOSTICS				8
#define GET_COMM_EVENT_CTRS		11
#define GET_COMM_EVENT_LOG		12
#define WRITE_MULT_COILS		15
#define WRITE_MULT_REGS			16
#define REPORT_SLAVE_ID			17
#define READ_FILE_RECORD		20
#define WRITE_FILE_RECORD		21
#define MASK_WRITE_REG			22
#define READ_WRITE_REG			23
#define READ_FIFO_QUEUE			24
#define ENCAP_INTERFACE_TRANSP	43


static const value_string modbus_code_vals[] = {
    { READ_COILS,             "Read Coils" },
    { READ_DISCRETE_INPUTS,   "Read Discrete Inputs" },
    { READ_HOLDING_REGS,      "Read Holding Registers" },
    { READ_INPUT_REGS,        "Read Input Registers" },
    { WRITE_SINGLE_COIL,      "Write Single Coil" },
    { WRITE_SINGLE_REG,       "Write Single Register" },
    { READ_EXCEPT_STAT,       "Read Exception Status" },
    { DIAGNOSTICS,            "Diagnostics" },
    { GET_COMM_EVENT_CTRS,    "Get Comm. Event Counters" },
    { GET_COMM_EVENT_LOG,     "Get Comm. Event Log" },
    { WRITE_MULT_COILS,       "Write Multiple Coils" },
    { WRITE_MULT_REGS,        "Write Multiple Registers" },
    { REPORT_SLAVE_ID,        "Report Slave ID" },
    { READ_FILE_RECORD,       "Read File Record" },
    { WRITE_FILE_RECORD,      "Write File Record" },
    { MASK_WRITE_REG,         "Mask Write Register" },
    { READ_WRITE_REG,         "Read Write Register" },
    { READ_FIFO_QUEUE,        "Read FIFO Queue" },
    { ENCAP_INTERFACE_TRANSP, "Encapsulated Interface Transport" },
    { 0,                      NULL }
};




void dissectmodbustcp(char *payload,int payload_len,json_object *commandlist)
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

    if(payload_len<8)
		return;
	struct json_object *modbustcp_object = json_object_new_object();
	strftime(theDate, 32, "%d/%b/%Y %H:%M:%S", localtime_r(&theTime,&result) );
    c = *(p + 7);
	char *cmd_str = try_val_to_str_idx(c, modbus_code_vals, &cmd_str_idx);
	if (cmd_str_idx == -1)
        return;
	else
		{
		json_object_object_add(modbustcp_object,"time",json_object_new_string(theDate));
	                json_object_object_add(modbustcp_object,"command",json_object_new_string(cmd_str));
		json_object_object_add(modbustcp_object,"value",json_object_new_string("NULL"));
		json_object_array_add(commandlist,modbustcp_object);


	}

	


	  
			
  
}



void ndpi_search_modbustcp(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  u_int16_t dport = 0, sport = 0;

  NDPI_LOG(NDPI_PROTOCOL_MODBUS_TCP, ndpi_struct, NDPI_LOG_DEBUG, "search modbus_tcp.\n");

  if(packet->tcp != NULL) {
    if(packet->payload_packet_len >= 8) {
		struct modbus *t = (struct modbus*)packet->payload;
		u_int16_t len = ntohs(t->len);
	   if(packet->payload_packet_len == len+6) {
	       NDPI_LOG(NDPI_PROTOCOL_MODBUS_TCP, ndpi_struct, NDPI_LOG_DEBUG, "modbus_tcp detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_MODBUS_TCP, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }

	
      }    
  }

}

void init_mobustcp_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS Modbustcp", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_MODBUS_TCP,
				      ndpi_search_modbustcp,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif
