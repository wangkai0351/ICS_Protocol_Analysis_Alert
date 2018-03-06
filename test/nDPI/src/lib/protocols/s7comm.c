#include "ndpi_protocols.h"
//#include "../third-party/json-c/json_object.h"

#ifdef NDPI_PROTOCOL_S7COMM

struct tpkt {
  u_int8_t version, reserved;
  u_int16_t len;
};

struct ISO_COTP{
	u_int8_t len, type,refence;
};



void dissects7comm(char *payload,int payload_len,json_object *commandlist)
{
  char *s7comm=payload+sizeof(struct tpkt)+sizeof(struct ISO_COTP);
  u_int8_t type=*(s7comm+1);
  char theDate[32];
  char cmd[20]={0};
  char value[20]={0};
  u_int8_t bloctype=0;
  char blocknum[6]={0};
  time_t theTime = time(NULL);
  int needadd=0;
#ifndef WIN32	 	 
  struct tm result;	 	 
#endif
  if(type==1)  
/*
0x00 - CPU services CPU 服务 *
0xF0 - Setup communication 通信设置 *
0x04 - Read Variable 读取变量 *
0x05 - Write Variable 写入变量 *
0x1A - Request download 请求下载 *
0x1B - Download block 下载块 *
0x1C - Download ended 下载结束 *
0x1D - Start upload 开始上传 *
0x1E–Upload 上传 *
0x1F - End upload 结束上传 *
0x28 - PLC Control PLC 控制 *
0x29 - PLC Stop PLC 停机 *
*/
 {
  	  struct json_object *s7_object = json_object_new_object();
	  strftime(theDate, 32, "%d/%b/%Y %H:%M:%S", localtime_r(&theTime,&result) );	
                 u_int8_t  command=*(s7comm+10);
	  u_int8_t command_length;
	  switch (command){
	  	case 0x29:
                                      if(payload_len>30)
            	{
            	    				needadd=1;
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("PLC STOP"));
					json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
					json_object_array_add(commandlist,s7_object);
            	}
			//printf( "s7 command:S7 STOP.\n");
		break;
		
		case 0x28:
			if(payload_len>42)
				{
				    needadd=1;
					command_length=*(s7comm+30);
					bloctype=*(s7comm+23);
					//memcpy(bloctype,s7comm+22,2);
					memcpy(blocknum,s7comm+24,5);
					//memcpy(cmd,s7comm+31,command_length);
					switch(bloctype){
						case '8':
                        sprintf(value,"%s,%s","OB",blocknum);
						break;
						case 'E':
                        sprintf(value,"%s,%s","FB",blocknum);
						break;
						case 'C':
                        sprintf(value,"%s,%s","FC",blocknum);
						break;
						case 'A':
                        sprintf(value,"%s,%s","DB",blocknum);
						break;
						case 'B':
                        sprintf(value,"%s,%s","SDB",blocknum);
						break;
						case 'F':
                        sprintf(value,"%s,%s","SFB",blocknum);
						break;
						case 'D':
                        sprintf(value,"%s,%s","SFC",blocknum);
						break;
						default:
                        sprintf(value,"%s,%s",(char)bloctype,blocknum);
						break;
						}
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("PLC CONTROL"));
					json_object_object_add(s7_object,"value",json_object_new_string(value));
					json_object_array_add(commandlist,s7_object);
					//printf( "s7 command:S7 PLC CONTROL.\n");
				}
            			break;
		case 0x1a:
			if(payload_len>48)
				{
					needadd=1;
					memset(value,0,20);				
					bloctype=*(s7comm+21);
					memcpy(blocknum,s7comm+22,5);
					switch(bloctype){
						case '8':
                        sprintf(value,"%s,%s","OB",blocknum);
						break;
						case 'E':
                        sprintf(value,"%s,%s","FB",blocknum);
						break;
						case 'C':
                        sprintf(value,"%s,%s","FC",blocknum);
						break;
						case 'A':
                        sprintf(value,"%s,%s","DB",blocknum);
						break;
						case 'B':
                        sprintf(value,"%s,%s","SDB",blocknum);
						break;
						case 'F':
                        sprintf(value,"%s,%s","SFB",blocknum);
						break;
						case 'D':
                        sprintf(value,"%s,%s","SFC",blocknum);
						break;
						default:
                        sprintf(value,"%s,%s",(char)bloctype,blocknum);
						break;
					}
						
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("REQUEST DOWNLOAD"));
					json_object_object_add(s7_object,"value",json_object_new_string(value));
					json_object_array_add(commandlist,s7_object);
					
				}
            			break;

		case 0xf0:
			if(payload_len>24)
				{
				    needadd=1;
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("SETUP COMMUNICATION"));
					json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
					json_object_array_add(commandlist,s7_object);
					//printf( "s7 command:Parameter: (Setup communication).\n");
				}
  
          			break;

            		case 0x00://CPU services 
            			if(payload_len>0)
            				{
 				    needadd=1;
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("CPU SERVICE"));
					json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
					json_object_array_add(commandlist,s7_object);	
            				}
            			break;
            		case 0x04://Read Variable
            			if(payload_len>0)
            				{
 				    needadd=1;
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("READ VARIABLE"));
					json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
					json_object_array_add(commandlist,s7_object);	
            				}
            			break; 
		case 0x05: //Write variable
			if(payload_len>0)
				{
				    needadd=1;
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("WRITE VARIABLE"));
					json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
					json_object_array_add(commandlist,s7_object);		
				}
           			break;
           		case 0x1b:
			if(payload_len>0)
				{
					needadd=1;
					memset(value,0,20);				
					bloctype=*(s7comm+21);
					memcpy(blocknum,s7comm+22,5);
					switch(bloctype){
						case '8':
                        sprintf(value,"%s,%s","OB",blocknum);
						break;
						case 'E':
                        sprintf(value,"%s,%s","FB",blocknum);
						break;
						case 'C':
                        sprintf(value,"%s,%s","FC",blocknum);
						break;
						case 'A':
                        sprintf(value,"%s,%s","DB",blocknum);
						break;
						case 'B':
                        sprintf(value,"%s,%s","SDB",blocknum);
						break;
						case 'F':
                        sprintf(value,"%s,%s","SFB",blocknum);
						break;
						case 'D':
                        sprintf(value,"%s,%s","SFC",blocknum);
						break;
						default:
                        sprintf(value,"%s,%s",(char)bloctype,blocknum);
						break;
					}
						
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string(" DOWNLOAD BLOCK"));
					json_object_object_add(s7_object,"value",json_object_new_string(value));
					json_object_array_add(commandlist,s7_object);
					
				}
            			break;
            		case 0x1c:
			if(payload_len>0)
				{
					needadd=1;
					memset(value,0,20);				
					bloctype=*(s7comm+21);
					memcpy(blocknum,s7comm+22,5);
					switch(bloctype){
						case '8':
                        sprintf(value,"%s,%s","OB",blocknum);
						break;
						case 'E':
                        sprintf(value,"%s,%s","FB",blocknum);
						break;
						case 'C':
                        sprintf(value,"%s,%s","FC",blocknum);
						break;
						case 'A':
                        sprintf(value,"%s,%s","DB",blocknum);
						break;
						case 'B':
                        sprintf(value,"%s,%s","SDB",blocknum);
						break;
						case 'F':
                        sprintf(value,"%s,%s","SFB",blocknum);
						break;
						case 'D':
                        sprintf(value,"%s,%s","SFC",blocknum);
						break;
						default:
                        sprintf(value,"%s,%s",(char)bloctype,blocknum);
						break;
					}
						
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("DOWNLOAD ENDED"));
					json_object_object_add(s7_object,"value",json_object_new_string(value));
					json_object_array_add(commandlist,s7_object);
					
				}
            			break;

            		case 0x1d:
			if(payload_len>0)
				{
					needadd=1;
					memset(value,0,20);				
					bloctype=*(s7comm+21);
					memcpy(blocknum,s7comm+22,5);
					switch(bloctype){
						case '8':
                        sprintf(value,"%s,%s","OB",blocknum);
						break;
						case 'E':
                        sprintf(value,"%s,%s","FB",blocknum);
						break;
						case 'C':
                        sprintf(value,"%s,%s","FC",blocknum);
						break;
						case 'A':
                        sprintf(value,"%s,%s","DB",blocknum);
						break;
						case 'B':
                        sprintf(value,"%s,%s","SDB",blocknum);
						break;
						case 'F':
                        sprintf(value,"%s,%s","SFB",blocknum);
						break;
						case 'D':
                        sprintf(value,"%s,%s","SFC",blocknum);
						break;
						default:
                        sprintf(value,"%s,%s",(char)bloctype,blocknum);
						break;
					}
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("START UPLOAD"));
					json_object_object_add(s7_object,"value",json_object_new_string(value));
					json_object_array_add(commandlist,s7_object);
				}
           			break;

            		case 0x1e:
			if(payload_len>0)
				{
					needadd=1;
					memset(value,0,20);				
					bloctype=*(s7comm+21);
					memcpy(blocknum,s7comm+22,5);
					switch(bloctype){
						case '8':
                        sprintf(value,"%s,%s","OB",blocknum);
						break;
						case 'E':
                        sprintf(value,"%s,%s","FB",blocknum);
						break;
						case 'C':
                        sprintf(value,"%s,%s","FC",blocknum);
						break;
						case 'A':
                        sprintf(value,"%s,%s","DB",blocknum);
						break;
						case 'B':
                        sprintf(value,"%s,%s","SDB",blocknum);
						break;
						case 'F':
                        sprintf(value,"%s,%s","SFB",blocknum);
						break;
						case 'D':
                        sprintf(value,"%s,%s","SFC",blocknum);
						break;
						default:
                        sprintf(value,"%s,%s",(char)bloctype,blocknum);
						break;
					}
						
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("UPLOAD BLOCK"));
					json_object_object_add(s7_object,"value",json_object_new_string(value));
					json_object_array_add(commandlist,s7_object);
					
				}
            			break;
            		case 0x1f:
			if(payload_len>0)
				{
					needadd=1;
					memset(value,0,20);				
					bloctype=*(s7comm+21);
					memcpy(blocknum,s7comm+22,5);
					switch(bloctype){
						case '8':
                        sprintf(value,"%s,%s","OB",blocknum);
						break;
						case 'E':
                        sprintf(value,"%s,%s","FB",blocknum);
						break;
						case 'C':
                        sprintf(value,"%s,%s","FC",blocknum);
						break;
						case 'A':
                        sprintf(value,"%s,%s","DB",blocknum);
						break;
						case 'B':
                        sprintf(value,"%s,%s","SDB",blocknum);
						break;
						case 'F':
                        sprintf(value,"%s,%s","SFB",blocknum);
						break;
						case 'D':
                        sprintf(value,"%s,%s","SFC",blocknum);
						break;
						default:
                        sprintf(value,"%s,%s",(char)bloctype,blocknum);
						break;
					}
						
					json_object_object_add(s7_object,"time",json_object_new_string(theDate));
					json_object_object_add(s7_object,"command",json_object_new_string("END UPLOAD"));
					json_object_object_add(s7_object,"value",json_object_new_string(value));
					json_object_array_add(commandlist,s7_object);
					
				}
            			break;
	  	}
	  	/*
	  if(needadd)
	  	json_object_array_add(commandlist,s7_object);
	  	*/
    }

    if(type==7)  

  {
  	  struct json_object *s7_object = json_object_new_object();
	  strftime(theDate, 32, "%d/%b/%Y %H:%M:%S", localtime_r(&theTime,&result) );	
                 u_int8_t  command=*(s7comm+15);
	  u_int8_t command_length;
	  switch (command)
	  {
	  	case 0x44:
            			if(payload_len>0)
            				{
 				    	needadd=1;
 				              u_int8_t sub_function=*(s7comm+16);
 				              switch(sub_function)
 				              {
 				              		case 0x01:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("CPU FUNCTIONS -> READ SZL"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;
 				              }
 				 }
 		break;
 	 
 		case 0x41:
             			if(payload_len>0)
            				{
 				    	needadd=1;
 				              u_int8_t sub_function=*(s7comm+16);
 				              switch(sub_function)
 				              {
 				              		case 0x01:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("PROGRAMMER COMMANDS -> REQUEST  DIAG DATA 1"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

						case 0x0e:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("PROGRAMMER COMMANDS -> REQUEST  DIAG DATA"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

						case 0x13:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("PROGRAMMER COMMANDS -> REQUEST  DIAG DATA 2"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

						case 0x02:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("PROGRAMMER COMMANDS -> VARIABLE  TABLE"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

						case 0x0c:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("PROGRAMMER COMMANDS -> ERASE"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

						case 0x0f:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("PROGRAMMER COMMANDS -> REMOVE  DIAG DATA"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

						case 0x10:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("PROGRAMMER COMMANDS -> FORCES"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

 				              }
            				}
            		break;

            		case 0x42:
             			if(payload_len>0)
            				{
 				    	needadd=1;
 				              u_int8_t sub_function=*(s7comm+16);
 				              switch(sub_function)
 				              {
 				              		case 0x01:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("CYCLIC FUNCITONS -> READ DATA FROM  MEM"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

 				              		case 0x04:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("CYCLIC FUNCITONS -> DISABLE CYCLIC DATA"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;
					}
				}
            		break;

            		case 0x43:
             			if(payload_len>0)
            				{
 				    	needadd=1;
 				              u_int8_t sub_function=*(s7comm+16);
 				              switch(sub_function)
 				              {
 				              		case 0x01:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("BLOCK FUNCTIONS -> LIST BLOCKS"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

 				              		case 0x02:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("BLOCK FUNCTIONS -> LIST BLOCK TYPE"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;

 				              		case 0x03:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("BLOCK FUNCTIONS -> GET BLOSK INFO"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;
					}
				}
            		break;

            		case 0x45:
            		{
            			 if(payload_len>0)
            				{
 				    	needadd=1;
 				              u_int8_t sub_function=*(s7comm+16);
 				              switch(sub_function)
 				              {
 				              		case 0x01:
 				              			json_object_object_add(s7_object,"time",json_object_new_string(theDate));
							json_object_object_add(s7_object,"command",json_object_new_string("SECURITY -> PASSWORD"));
							json_object_object_add(s7_object,"value",json_object_new_string("NULL"));
							json_object_array_add(commandlist,s7_object);	
						break;
					}
            		                             }
            		break;	
            	                }
            	 }
  }

}

void ndpi_search_s7comm(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  u_int16_t dport = 0, sport = 0;

  NDPI_LOG(NDPI_PROTOCOL_S7COMM, ndpi_struct, NDPI_LOG_DEBUG, "search s7comm.\n");

  if(packet->tcp != NULL) {
  

    if(packet->payload_packet_len >= 3
       && (packet->payload[0] == 0x03)
       && (packet->payload[1] == 0x00)
       && (packet->payload[2] == 0x00)) {
	struct tpkt *t = (struct tpkt*)packet->payload;
	u_int16_t len = ntohs(t->len);


	if(packet->payload_packet_len == len) {

	  if(packet->payload[4] == (packet->payload_packet_len - sizeof(struct tpkt) - 1)) {
	    /* ISO 8073/X.224 */
	    if((packet->payload[5] == 0xE0 /* CC Connect Request */)
	       || (packet->payload[5] == 0xD0 /* CC Connect Confirm */)) {
	       NDPI_LOG(NDPI_PROTOCOL_S7COMM, ndpi_struct, NDPI_LOG_DEBUG, "s7comm detected.\n");
		   flow->protocol_need_everypacketcheck=1;
	      ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_S7COMM, NDPI_PROTOCOL_UNKNOWN);
	      return;
	    }
	  }

	
	}
      }  
	else
		{
		NDPI_LOG(NDPI_PROTOCOL_S7COMM, ndpi_struct, NDPI_LOG_DEBUG, "excluding S7COMM\n");
        NDPI_ADD_PROTOCOL_TO_BITMASK(flow->excluded_protocol_bitmask, NDPI_PROTOCOL_S7COMM);
		}
  }

}

void init_s7comm_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id, NDPI_PROTOCOL_BITMASK *detection_bitmask)
{
  ndpi_set_bitmask_protocol_detection("ICS S7comm", ndpi_struct, detection_bitmask, *id,
				      NDPI_PROTOCOL_S7COMM,
				      ndpi_search_s7comm,
				      NDPI_SELECTION_BITMASK_PROTOCOL_TCP_OR_UDP_WITH_PAYLOAD,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

#endif
