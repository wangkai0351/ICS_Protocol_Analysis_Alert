#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_IEC104

#define M_SP_NA_1  1    /* single-point information 								*/
#define M_DP_NA_1  3    /* double-point information 								*/
#define M_ST_NA_1  5    /* step position information 								*/
#define M_BO_NA_1  7    /* bitstring of 32 bits 								*/
#define M_ME_NA_1  9    /* measured value, normalized value 							*/
#define M_ME_NB_1  11    /* measured value, scaled value 							*/
#define M_ME_NC_1  13    /* measured value, short floating point number 					*/
#define M_IT_NA_1  15    /* integrated totals 									*/
#define M_PS_NA_1  20    /* packed single-point information with status change detection 			*/
#define M_ME_ND_1  21    /* measured value, normalized value without quality descriptor 			*/
#define M_SP_TB_1  30    /* single-point information with time tag CP56Time2a 					*/
#define M_DP_TB_1  31    /* double-point information with time tag CP56Time2a 					*/
#define M_ST_TB_1  32    /* step position information with time tag CP56Time2a 					*/
#define M_BO_TB_1  33    /* bitstring of 32 bit with time tag CP56Time2a 					*/
#define M_ME_TD_1  34    /* measured value, normalized value with time tag CP56Time2a 				*/
#define M_ME_TE_1  35    /* measured value, scaled value with time tag CP56Time2a 				*/
#define M_ME_TF_1  36    /* measured value, short floating point number with time tag CP56Time2a 		*/
#define M_IT_TB_1  37    /* integrated totals with time tag CP56Time2a 						*/
#define M_EP_TD_1  38    /* event of protection equipment with time tag CP56Time2a 				*/
#define M_EP_TE_1  39    /* packed start events of protection equipment with time tag CP56Time2a 		*/
#define M_EP_TF_1  40    /* packed output circuit information of protection equipment with time tag CP56Time2a 	*/
#define C_SC_NA_1  45    /* single command 									*/
#define C_DC_NA_1  46    /* double command 									*/
#define C_RC_NA_1  47    /* regulating step command 								*/
#define C_SE_NA_1  48    /* set point command, normalized value 						*/
#define C_SE_NB_1  49    /* set point command, scaled value 							*/
#define C_SE_NC_1  50    /* set point command, short floating point number 					*/
#define C_BO_NA_1  51    /* bitstring of 32 bits 								*/
#define C_SC_TA_1  58    /* single command with time tag CP56Time2a 						*/
#define C_DC_TA_1  59    /* double command with time tag CP56Time2a 						*/
#define C_RC_TA_1  60    /* regulating step command with time tag CP56Time2a 					*/
#define C_SE_TA_1  61    /* set point command, normalized value with time tag CP56Time2a 			*/
#define C_SE_TB_1  62    /* set point command, scaled value with time tag CP56Time2a 				*/
#define C_SE_TC_1  63    /* set point command, short floating-point number with time tag CP56Time2a 		*/
#define C_BO_TA_1  64    /* bitstring of 32 bits with time tag CP56Time2a 					*/
#define M_EI_NA_1  70    /* end of initialization 								*/
#define C_IC_NA_1  100    /* interrogation command 								*/
#define C_CI_NA_1  101    /* counter interrogation command 							*/
#define C_RD_NA_1  102    /* read command 									*/
#define C_CS_NA_1  103    /* clock synchronization command 							*/
#define C_RP_NA_1  105    /* reset process command 								*/
#define C_TS_TA_1  107    /* test command with time tag CP56Time2a 						*/
#define P_ME_NA_1  110    /* parameter of measured value, normalized value 					*/
#define P_ME_NB_1  111    /* parameter of measured value, scaled value 						*/
#define P_ME_NC_1  112    /* parameter of measured value, short floating-point number 				*/
#define P_AC_NA_1  113    /* parameter activation 								*/
#define F_FR_NA_1  120    /* file ready 									*/
#define F_SR_NA_1  121    /* section ready 									*/
#define F_SC_NA_1  122    /* call directory, select file, call file, call section 				*/
#define F_LS_NA_1  123    /* last section, last segment 							*/
#define F_AF_NA_1  124    /* ack file, ack section 								*/
#define F_SG_NA_1  125    /* segment 										*/
#define F_DR_TA_1  126    /* directory 										*/
#define F_SC_NB_1  127    /* Query Log - Request archive file 							*/


struct iec104_heard{
  u_int8_t flag,len;
  u_int32_t apci;
};

void AddToJson(json_object *commandlist,u_int8_t cmd)
{

	char theDate[32];
	char value[20]={0};
	time_t theTime = time(NULL);
	int obj_len;
#ifndef WIN32	 	 
	  struct tm result; 	 
#endif
    struct json_object *iec104_object = json_object_new_object();

	strftime(theDate, 32, "%d/%b/%Y %H:%M:%S", localtime_r(&theTime,&result) );
	switch (cmd){
	 	case M_SP_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("single-point-info"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_DP_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("double-point-info"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ST_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("step position"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_BO_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("bitstring"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ME_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("normalized value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ME_NB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("scaled value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ME_NC_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("short float"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_IT_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("integrated totals"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_PS_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("packed single-point"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ME_ND_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("measured value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_SP_TB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("single-point info"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_DP_TB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("double-point info"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ST_TB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("step position info"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_BO_TB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("bitstring"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ME_TD_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("measured value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ME_TE_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("measured value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_ME_TF_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("measured value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_IT_TB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("integrated totals"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_EP_TD_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("event of protection equipment"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_EP_TF_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("packed output circuit information of protection equipment"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_EP_TE_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("packed start events of protection equipment"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_SC_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("single command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_DC_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("double command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_RC_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("regulating step command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_SE_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("set point command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_SE_NB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("set point command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_SE_NC_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("set point command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_BO_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("bitstring of 32 bits"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_SC_TA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("single command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_DC_TA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("double command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_RC_TA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("regulating step command "));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_SE_TA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("set point command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_SE_TB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("set point command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_SE_TC_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("set point command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_BO_TA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("bitstring of 32 bits"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case M_EI_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("end of initialization"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_IC_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("interrogation command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_CI_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("counter interrogation command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_RD_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("read command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_CS_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("clock synchronization command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_RP_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("reset process command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case C_TS_TA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("test command"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case P_ME_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("parameter of measured value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case P_ME_NB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("parameter of measured value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case P_ME_NC_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("parameter of measured value"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case P_AC_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("parameter activation"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case F_FR_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("file ready"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case F_SR_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("section ready"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case F_SC_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("call directory, select file, call file, call section"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case F_LS_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("last section, last segment"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case F_AF_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("ack file, ack section"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case F_SG_NA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("segment"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case F_DR_TA_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("directory"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
		case F_SC_NB_1:
			json_object_object_add(iec104_object,"time",json_object_new_string(theDate));
			json_object_object_add(iec104_object,"command",json_object_new_string("Query Log"));
			json_object_object_add(iec104_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,iec104_object);
			break;
			
	}



}

void dissectIEC104(char *payload,int payload_len,json_object *commandlist)
{
    struct iec104_heard *t;
	char *p = payload;
	u_int8_t c;


  int last = payload_len;
  while(last>=7)
				{
				  t = (struct iec104_heard*)p;
				  c = *(p + 6);
				  AddToJson(commandlist,c);
				  last = last - t->len - 2;
				  p = p + t->len +2;
				  
			}
  
}


void ndpi_search_Iec104(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  NDPI_LOG(NDPI_PROTOCOL_IEC104, ndpi_struct, NDPI_LOG_DEBUG, "search iec104.\n");

  if(packet->tcp != NULL) {
    if(packet->payload_packet_len >= 6 && packet->payload[0]== 0x68) {
		struct iec104_heard *h = (struct iec104_heard*)packet->payload;
		u_int16_t len = ntohs(h->len);
		while(packet->payload_packet_len >= len + 6 )
			{
               h = (struct iec104_heard*)(packet->payload + len + 2);
			
                len = len + ntohs(h->len);

		}
	    if(packet->payload_packet_len == len + 2) {
	       NDPI_LOG(ndpi_search_Iec104, ndpi_struct, NDPI_LOG_DEBUG, "iec104 detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_IEC104, NDPI_PROTOCOL_UNKNOWN);
	       return;
	   }
     }    
  }

}

void init_IEC104_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS IEC104", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_IEC104,
				      ndpi_search_Iec104,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif

