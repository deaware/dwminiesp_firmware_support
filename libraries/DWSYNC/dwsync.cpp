#include "dwsync.h"

template<class retT, class argT>
DWFP<retT, argT>::DWFP()
{
    obj_callback = 0;
    c_callback = 0;
}

template<class retT, class argT>
bool DWFP<retT, argT>::attached()
{
    return obj_callback || c_callback;
}

template<class retT, class argT>
void DWFP<retT, argT>::detach()
{
    obj_callback = 0;
    c_callback = 0;
}


template<class retT, class argT>
void DWFP<retT, argT>::attach(retT (*function)(argT))
{
    c_callback = function;
}

template<class retT, class argT>
retT DWFP<retT, argT>::operator()(argT arg) const
{
    if( 0 != c_callback )
    {
        return obj_callback ? (obj_callback->*method_callback)(arg) : (*c_callback)(arg);
    }
    return (retT)0;
}
template class DWFP<void, dwsyn_prtcl*>;

DW_SYNC::DW_SYNC(Stream* ser) :
	_serial(ser),
	_state(IDLE_STATE)
{
	dw.len = 0;
}

void DW_SYNC::send(uint8_t cmd, const String &data) {
	_serial->write(START_BYTE);
	_serial->write(cmd);
	_serial->print(data);
	_serial->write(STOP_BYTE);
}

void DW_SYNC::send(uint8_t cmd, uint8_t data[], uint8_t len) {
	uint8_t i = 0;
	uint8_t _len = len;

	if(_len > INTERNAL_BUFFER) {
		return;
	}
	
	_serial->write(START_BYTE);
	_serial->write(cmd);
	while( i < _len ) {
		_serial->print(data[i]);
	}
	_serial->write(STOP_BYTE);
}

void DW_SYNC::process() {
	while(_serial->available()) {
		read_process(_serial->read());
	}
}

void DW_SYNC::read_process(uint8_t data) {
	switch(_state) {
		case IDLE_STATE :
		if (data == START_BYTE) {
			_state = CMD_STATE;
		}
		break; 
		case CMD_STATE :
		dw.cmd = data;
		_state = DATA_STATE;
		break;
		case DATA_STATE :
		if (data == STOP_BYTE) {
			read_cb(&dw);
			dw.len = 0; 
			_state = IDLE_STATE;
		} else {
			dw.data[dw.len] = data;
			dw.len++;
		}
		break;
		default :
		break;
	}
}

uint16_t DW_SYNC::convertDataToUInt16(DWSYN_PRTCL dw) {
	int16_t ret = 0;
	
	ret = dw->data[1];		
	ret |= (dw->data[0] << 8);
	return ret;	
}

int16_t DW_SYNC::convertDataToInt16(DWSYN_PRTCL dw) {
	int16_t ret = 0;
	
	ret = dw->data[1];		
	ret |= (dw->data[0] << 8);
	return ret;
}

String DW_SYNC::convertDataToString(DWSYN_PRTCL dw) {
	String s;
	uint8_t i = 0;
	uint8_t max_len = dw->len;

	for(i = 0; i < max_len; i++) {
		s.concat((char)dw->data[i]);
	}
	
	return s;
}