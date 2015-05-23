#ifndef _DW_BRIDGE_
#define _DW_BRIDGE_

#include <Arduino.h>

#define START_BYTE			0x01
#define STOP_BYTE			0x04
#define INTERNAL_BUFFER 	64

template<class retT, class argT>
class DWFP
{
public:
    DWFP();
	
    void attach(retT (*function)(argT));
    retT operator()(argT arg) const;
    bool attached();
    void detach();

private:
    
    class ptrdummy;
    ptrdummy *obj_callback;
    
    union
    {
        retT (*c_callback)(argT);                   
        retT (ptrdummy::*method_callback)(argT);   
    };
};

typedef enum {
	IDLE_STATE = 0,
	CMD_STATE,
	DATA_STATE
}DW_SYNC_STATE;

typedef struct {
	uint8_t  cmd;
	uint8_t  data[INTERNAL_BUFFER];
	uint16_t len;
}dwsyn_prtcl;

typedef dwsyn_prtcl* DWSYN_PRTCL;

class DW_SYNC {
	public : 
		DW_SYNC(Stream *ser);
		DWFP<void, dwsyn_prtcl*> read_cb;
		void process();
		void send(uint8_t cmd, const String &data);
		void send(uint8_t cmd, uint8_t data[], uint8_t len);
		
		uint16_t convertDataToUInt16(DWSYN_PRTCL dw);
		int16_t convertDataToInt16(DWSYN_PRTCL dw);
		String convertDataToString(DWSYN_PRTCL dw);
		
	private :
		Stream *_serial;
		uint8_t _state;
		dwsyn_prtcl dw;
		void read_process(uint8_t data);
};

#endif /* _DW_BRIDGE_ */