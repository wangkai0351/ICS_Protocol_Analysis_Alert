#include "ndpi_protocols.h"

#ifdef NDPI_PROTOCOL_SBUS


/*SBus command codes*/
#define SBUS_RD_COUNTER                0x00
#define SBUS_RD_DISPLAY_REGISTER       0x01
#define SBUS_RD_FLAG                   0x02
#define SBUS_RD_INPUT                  0x03
#define SBUS_RD_RTC                    0x04
#define SBUS_RD_OUTPUT                 0x05
#define SBUS_RD_REGISTER               0x06
#define SBUS_RD_TIMER                  0x07
#define SBUS_WR_COUNTER                0x0A
#define SBUS_WR_FLAG                   0x0B
#define SBUS_WR_RTC                    0x0C
#define SBUS_WR_OUTPUT                 0x0D
#define SBUS_WR_REGISTER               0x0E
#define SBUS_WR_TIMER                  0x0F
#define SBUS_RDWR_MULTI_MEDIAS         0x13
#define SBUS_RD_PCD_STATUS_CPU0        0x14
#define SBUS_RD_PCD_STATUS_CPU1        0x15
#define SBUS_RD_PCD_STATUS_CPU2        0x16
#define SBUS_RD_PCD_STATUS_CPU3        0x17
#define SBUS_RD_PCD_STATUS_CPU4        0x18
#define SBUS_RD_PCD_STATUS_CPU5        0x19
#define SBUS_RD_PCD_STATUS_CPU6        0x1A
#define SBUS_RD_PCD_STATUS_OWN         0x1B
#define SBUS_RD_SBUS_STN_NBR           0x1D
#define SBUS_RD_USER_MEMORY            0x1E
#define SBUS_RD_PROGRAM_LINE           0x1F
#define SBUS_RD_PROGRAM_VERSION        0x20
#define SBUS_RD_TEXT                   0x21
#define SBUS_RD_ACTIVE_TRANSITION      0x22
#define SBUS_WR_USER_MEMORY            0x23
#define SBUS_WR_PROGRAM_LINE           0x24
#define SBUS_WR_TEXT                   0x25
#define SBUS_RUN_PROCEDURE_CPU0        0x28
#define SBUS_RUN_PROCEDURE_CPU1        0x29
#define SBUS_RUN_PROCEDURE_CPU2        0x2A
#define SBUS_RUN_PROCEDURE_CPU3        0x2B
#define SBUS_RUN_PROCEDURE_CPU4        0x2C
#define SBUS_RUN_PROCEDURE_CPU5        0x2D
#define SBUS_RUN_PROCEDURE_CPU6        0x2E
#define SBUS_RUN_PROCEDURE_OWN         0x2F
#define SBUS_RUN_PROCEDURE_ALL         0x30
#define SBUS_RESTART_COLD_CPU1         0x32
#define SBUS_RESTART_COLD_CPU2         0x33
#define SBUS_RESTART_COLD_CPU3         0x34
#define SBUS_RESTART_COLD_CPU4         0x35
#define SBUS_RESTART_COLD_CPU5         0x36
#define SBUS_RESTART_COLD_CPU6         0x37
#define SBUS_RESTART_COLD_OWN          0x38
#define SBUS_RESTART_COLD_ALL          0x39
#define SBUS_STOP_PROCEDURE_CPU0       0x3C
#define SBUS_STOP_PROCEDURE_CPU1       0x3D
#define SBUS_STOP_PROCEDURE_CPU2       0x3E
#define SBUS_STOP_PROCEDURE_CPU3       0x3F
#define SBUS_STOP_PROCEDURE_CPU4       0x40
#define SBUS_STOP_PROCEDURE_CPU5       0x41
#define SBUS_STOP_PROCEDURE_CPU6       0x42
#define SBUS_STOP_PROCEDURE_OWN        0x43
#define SBUS_STOP_PROCEDURE_ALL        0x44
#define SBUS_RD_STATUSFLAG_ACCU        0x46
#define SBUS_RD_BYTE                   0x47
#define SBUS_RD_HALT_FAILURE_REG       0x48
#define SBUS_RD_INDEX_REGISTER         0x49
#define SBUS_RD_INSTRUCTION_POINTER    0x4A
#define SBUS_FIND_HISTORY              0x4B
#define SBUS_WR_STATUSFLAG_ACCU        0x50
#define SBUS_WR_BYTE                   0x51
#define SBUS_WR_INDEX_REGISTER         0x52
#define SBUS_WR_INSTRUCTION_POINTER    0x53
#define SBUS_CLEAR_ALL                 0x5A
#define SBUS_CLEAR_FLAGS               0x5B
#define SBUS_CLEAR_OUTPUTS             0x5C
#define SBUS_CLEAR_REGISTERS           0x5D
#define SBUS_CLEAR_TIMERS              0x5E
#define SBUS_RESTART_WARM_CPU1         0x64
#define SBUS_RESTART_WARM_CPU2         0x65
#define SBUS_RESTART_WARM_CPU3         0x66
#define SBUS_RESTART_WARM_CPU4         0x67
#define SBUS_RESTART_WARM_CPU5         0x68
#define SBUS_RESTART_WARM_CPU6         0x69
#define SBUS_RESTART_WARM_OWN          0x6A
#define SBUS_RESTART_WARM_ALL          0x6B
#define SBUS_CHANGE_BLOCK              0x6E
#define SBUS_CLEAR_HISTORY_FAILURE     0x6F
#define SBUS_DELETE_PROGRAM_LINE       0x70
#define SBUS_GO_CONDITIONAL            0x71
#define SBUS_INSERT_PROGRAM_LINE       0x72
#define SBUS_LOCAL_CYCLE               0x73
#define SBUS_ALL_CYCLES                0x74
#define SBUS_MAKE_TEXT                 0x75
#define SBUS_EXECUTE_SINGLE_INSTR      0x76
#define SBUS_SINGLE_STEP               0x77
#define SBUS_XOB_17_INTERRUPT          0x82
#define SBUS_XOB_18_INTERRUPT          0x83
#define SBUS_XOB_19_INTERRUPT          0x84
#define SBUS_RD_HANGUP_TIMEOUT         0x91
#define SBUS_RD_DATA_BLOCK             0x96
#define SBUS_WR_DATA_BLOCK             0x97
#define SBUS_MAKE_DATA_BLOCK           0x98
#define SBUS_CLEAR_DATA_BLOCK          0x99
#define SBUS_CLEAR_TEXT                0x9A
#define SBUS_RD_BLOCK_ADDRESSES        0x9B
#define SBUS_RD_BLOCK_SIZES            0x9C
#define SBUS_RD_CURRENT_BLOCK          0x9D
#define SBUS_RD_CALL_STACK             0x9E
#define SBUS_RD_DBX                    0x9F
#define SBUS_RD_USER_EEPROM_REGISTER   0xA1
#define SBUS_WR_USER_EEPROM_REGISTER   0xA3
#define SBUS_ERASE_FLASH               0xA5
#define SBUS_RESTART_COLD_FLAG         0xA6
#define SBUS_WR_SYSTEM_BUFFER          0xA7
#define SBUS_RD_SYSTEM_BUFFER          0xA8
#define SBUS_RD_WR_PCD_BLOCK           0xA9
#define SBUS_GET_DIAGNOSTIC            0xAA
#define SBUS_RD_SYSTEM_INFORMATION     0xAB
#define SBUS_CHANGE_BLOCKS_ON_RUN      0xAC
#define SBUS_FLASHCARD_TELEGRAM        0xAD
#define SBUS_DOWNLOAD_FIRMWARE         0xAE
#define SBUS_WEB_SERVER_SERIAL_COMM    0xAF

struct sbus_heard{
  u_int32_t len;
  u_int8_t version,type;
  u_int16_t squence;
};




void dissectSBUS(char *payload,int payload_len,json_object *commandlist)
{

	char *p = payload;
	u_int8_t c;
	char theDate[32];
	char value[20]={0};
	time_t theTime = time(NULL);
	int obj_len;
#ifndef WIN32	 	 
	  struct tm result; 	 
#endif

	if(payload_len < 11)
		return ;
	if(payload[8]!=0x00)   //respone return
		return;              
	struct json_object *sbus_object = json_object_new_object();
	strftime(theDate, 32, "%d/%b/%Y %H:%M:%S", localtime_r(&theTime,&result) );
	c = *(p + 10);
	switch (c){
	 	case SBUS_RD_COUNTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read counter(s)"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_DISPLAY_REGISTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read display register"));
			json_object_object_add(sbus_object,"value",json_object_new_string(value));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_FLAG:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read flag"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_INPUT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read input"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_RTC:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read real time clock"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_OUTPUT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read output"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_REGISTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read register"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_TIMER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read timer"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
		case SBUS_WR_COUNTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write counter"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_FLAG:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write flag"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_RTC:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write real time clock"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_OUTPUT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write output"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_REGISTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write register"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_TIMER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write timer"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RDWR_MULTI_MEDIAS:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write multi medias"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PCD_STATUS_CPU0:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read PCD status, CPU 0"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PCD_STATUS_CPU1:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read PCD status, CPU 1"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PCD_STATUS_CPU2:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read PCD status, CPU 2"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PCD_STATUS_CPU3:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read PCD status, CPU 3"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PCD_STATUS_CPU4:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read PCD status, CPU 4"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PCD_STATUS_CPU5:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read PCD status, CPU 5"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PCD_STATUS_CPU6:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read PCD status, CPU 6"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PCD_STATUS_OWN:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read PCD status own"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_SBUS_STN_NBR:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read S-Bus station number"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_USER_MEMORY:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read user memory"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PROGRAM_LINE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read program line"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_PROGRAM_VERSION:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read firmware version"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_TEXT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read text"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_ACTIVE_TRANSITION:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read active transition"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_USER_MEMORY:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write user memory"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_PROGRAM_LINE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write program line"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_TEXT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write text"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_CPU0:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure*, CPU 0"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_CPU1:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure*, CPU 1"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_CPU2:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure*, CPU 2"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_CPU3:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure*, CPU 3"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_CPU4:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure*, CPU 4"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_CPU5:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure*, CPU 5"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_CPU6:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure*, CPU 6"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_OWN:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure* own CPU"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RUN_PROCEDURE_ALL:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Run procedure* All CPUs"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_CPU1:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold CPU 1"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_CPU2:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold CPU 2"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_CPU3:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold CPU 3"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_CPU4:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold CPU 4"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_CPU5:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold CPU 5"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_CPU6:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold CPU 6"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_OWN:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold own CPU"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_ALL:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold all CPUs"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_CPU0:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure, CPU 0"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_CPU1:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure, CPU 1"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_CPU2:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure, CPU 2"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_CPU3:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure, CPU 3"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_CPU4:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure, CPU 4"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_CPU5:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure, CPU 5"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_CPU6:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure, CPU 6"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_OWN:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure own CPU"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_STOP_PROCEDURE_ALL:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Stop procedure All CPUs"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_STATUSFLAG_ACCU:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read arithmetic status and ACCU"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_BYTE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read byte"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_HALT_FAILURE_REG:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read halt failure register"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_INDEX_REGISTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read index register"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_INSTRUCTION_POINTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read instruction pointer"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_FIND_HISTORY:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Find history"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_STATUSFLAG_ACCU:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write arithmetic staus and ACCU"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_BYTE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write byte"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_INDEX_REGISTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write index register"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_INSTRUCTION_POINTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write instruction pointer"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CLEAR_ALL:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Clear all F, O, R, T"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CLEAR_FLAGS:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Clear flags"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CLEAR_OUTPUTS:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Clear outputs"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CLEAR_REGISTERS:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Clear registers"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CLEAR_TIMERS:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Clear timers"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_WARM_CPU1:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart warm CPU 1"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_WARM_CPU2:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart warm CPU 2"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_WARM_CPU3:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart warm CPU 3"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_WARM_CPU4:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart warm CPU 4"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_WARM_CPU5:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart warm CPU 5"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_WARM_CPU6:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart warm CPU 6"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_WARM_OWN:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart warm own CPU"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_WARM_ALL:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart warm all CPU"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CHANGE_BLOCK:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Change block"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CLEAR_HISTORY_FAILURE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Clear history failure"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_DELETE_PROGRAM_LINE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Delete program line"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_GO_CONDITIONAL:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Go conditional"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_INSERT_PROGRAM_LINE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Insert program line"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_LOCAL_CYCLE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Local cycles"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_ALL_CYCLES:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("All cycles"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_MAKE_TEXT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Make text"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_EXECUTE_SINGLE_INSTR:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Execute single instruction"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_SINGLE_STEP:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Single step"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_XOB_17_INTERRUPT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("XOB 17 interrupt"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_XOB_18_INTERRUPT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("XOB 18 interrupt"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_XOB_19_INTERRUPT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("XOB 19 interrupt"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_HANGUP_TIMEOUT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read hangup timeout"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_DATA_BLOCK:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read data block"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_DATA_BLOCK:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write data block"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_MAKE_DATA_BLOCK:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Make data block"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CLEAR_DATA_BLOCK:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Clear data block"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CLEAR_TEXT:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Clear text"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_BLOCK_ADDRESSES:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read block address"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_BLOCK_SIZES:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read block sizes"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_CURRENT_BLOCK:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read current block"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_CALL_STACK:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read call stack"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_DBX:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read DBX"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_USER_EEPROM_REGISTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read user EEPROM register"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_USER_EEPROM_REGISTER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write user EEPROM register"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_ERASE_FLASH:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Erase flash"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RESTART_COLD_FLAG:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Restart cold flag"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WR_SYSTEM_BUFFER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Write system buffer"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_SYSTEM_BUFFER:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read system buffer"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_GET_DIAGNOSTIC:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Get diagnostic"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_RD_SYSTEM_INFORMATION:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Read system information"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_CHANGE_BLOCKS_ON_RUN:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Changes blocks on run"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_FLASHCARD_TELEGRAM:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Flashcard telegram"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_DOWNLOAD_FIRMWARE:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Download FW"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		case SBUS_WEB_SERVER_SERIAL_COMM:
			json_object_object_add(sbus_object,"time",json_object_new_string(theDate));
			json_object_object_add(sbus_object,"command",json_object_new_string("Web server serial communication"));
			json_object_object_add(sbus_object,"value",json_object_new_string("NULL"));
			json_object_array_add(commandlist,sbus_object);
			break;
		default:
			break;
				
		
	 	}

	


	  
			
  
}

void ndpi_search_SBUS(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  u_int16_t dport = 0, sport = 0;

  NDPI_LOG(NDPI_PROTOCOL_SBUS, ndpi_struct, NDPI_LOG_DEBUG, "search s_bus.\n");

  if(packet->udp != NULL) {
    if(packet->payload_packet_len >= 8) {
		struct sbus_heard *t = (struct sbus_heard*)packet->payload;
		u_int16_t len = ntohs(t->len);
	   if(packet->payload_packet_len == len) {
	       NDPI_LOG(ndpi_search_SBUS, ndpi_struct, NDPI_LOG_DEBUG, "s_bus detected.\n");
	       ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_SBUS, NDPI_PROTOCOL_UNKNOWN);
	      return;
	
	  }

	
      }    
  }

}

void init_SBUS_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS S_BUS", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_SBUS,
				      ndpi_search_SBUS,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif

