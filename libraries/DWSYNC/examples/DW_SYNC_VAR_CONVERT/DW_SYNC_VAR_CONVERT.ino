#include "dwsync.h"

DW_SYNC sync(&Serial);

// Create your own command
#define STRING_TYPE 0x01
#define INT16_TYPE  0x02
#define UIN16_TYPE  0x03

void read_cb(DWSYN_PRTCL args) {
  DWSYN_PRTCL dw = (DWSYN_PRTCL)args;
  switch (dw->cmd) {
    case STRING_TYPE :
      Serial.print("RCV String format : ");
      Serial.println(sync.convertDataToString(dw));
    break;
    case INT16_TYPE :
      Serial.print("RCV Int16 format : ");
      Serial.println(sync.convertDataToInt16(dw));
    break;
    case UIN16_TYPE :
      Serial.print("RCV UInt16 format : ");
      Serial.println(sync.convertDataToUInt16(dw));
    break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sync.read_cb.attach(read_cb);
}

void loop() {
  sync.process();
  delay(1);
}
