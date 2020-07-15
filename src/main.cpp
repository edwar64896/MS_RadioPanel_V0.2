#include <Arduino.h>
#include <gspswitch.h>
#include <gspquad.h>
#include <gspflash.h>
#include <gspserialresponse.h>
#include <gspseven.h>

#define _data   1
#define _clk    2

// pre-implementation declares for serial responders
void fsrCom1  (String);
void fsrCom2  (String);
void fsrCom1sb(String);
void fsrCom2sb(String);
void fsrNav1  (String);
void fsrNav2  (String);
void fsrNav1sb(String);
void fsrNav2sb(String);
void fsrAdf   (String);
void fsrXpd   (String);

// pre-implementation declares for encoders
void qdCom1Lower  (int);
void qdCom2Lower  (int);
void qdNav1Lower  (int);
void qdNav2Lower  (int);
void qdAdfLower   (int);
void qdXpdLower   (int);
void qdCom1Higher (int);
void qdCom2Higher (int);
void qdNav1Higher (int);
void qdNav2Higher (int);
void qdAdfHigher  (int);
void qdXpdHigher  (int);

// pre-implementation declares for switches
void swCom1Tx();
void swCom2Tx();
void swNav1Rx();
void swNav2Rx();

// pre-implementation declares for pushbuttons
void pbNav1id_fn();
void pbNav2id_fn();
void pbAdf_fn();
void pbMkr_fn();
void pbCom1_swp_fn();
void pbCom2_swp_fn();
void pbNav1_swp_fn();
void pbNav2_swp_fn();

// pre-implementation declares for encoder pushbuttons
void pbQdCom1_fn(uint8_t);
void pbQdCom2_fn(uint8_t);
void pbQdNav1_fn(uint8_t);
void pbQdNav2_fn(uint8_t);
void pbQdAdf_fn(uint8_t);
void pbQdXpd_fn(uint8_t);

// data,clock,chipselect/load
// seven segment displays
gspSeven com1   (_data,_clk,3);
gspSeven com2   (_data,_clk,5);
gspSeven com1sb (_data,_clk,4);
gspSeven com2sb (_data,_clk,6);
gspSeven nav1   (_data,_clk,7);
gspSeven nav2   (_data,_clk,9);
gspSeven nav1sb (_data,_clk,8);
gspSeven nav2sb (_data,_clk,10);
gspSeven adf    (_data,_clk,11);
gspSeven xpd    (_data,_clk,12);

// serial responders
gspSerialResponse srCom1    ("=A",7,fsrCom1);
gspSerialResponse srCom2    ("=B",7,fsrCom2);
gspSerialResponse srCom1sb  ("=C",7,fsrCom1sb);
gspSerialResponse srCom2sb  ("=D",7,fsrCom2sb);
gspSerialResponse srNav1    ("=E",6,fsrNav1);
gspSerialResponse srNav2    ("=F",6,fsrNav2);
gspSerialResponse srNav1sb  ("=G",6,fsrNav1sb);
gspSerialResponse srNav2sb  ("=H",6,fsrNav2sb);
gspSerialResponse srAdf     ("=I",6,fsrAdf);
gspSerialResponse srXpd     ("=J",4,fsrXpd);

//quad encoders//
gspQuad   qdCom1    (15, 16, qdCom1Lower, qdCom1Higher);
gspQuad   qdCom2    (17, 18, qdCom2Lower, qdCom2Higher);
gspQuad   qdNav1    (19, 20, qdNav1Lower, qdNav1Higher);
gspQuad   qdNav2    (21, 22, qdNav2Lower, qdNav2Higher);
gspQuad   qdAdf     (23, 24, qdAdfLower,  qdAdfHigher);
gspQuad   qdXpd     (25, 26, qdXpdLower,  qdXpdHigher);

//pushbuttons (encoders)//
gspSwitch pbQdCom1  (43,2,pbQdCom1_fn,gspSwitch_MODE_PUSHBUTTON_RELEASE_COUNTER_AUTORESET_CB);
gspSwitch pbQdCom2  (44,2,pbQdCom2_fn,gspSwitch_MODE_PUSHBUTTON_RELEASE_COUNTER_AUTORESET_CB);
gspSwitch pbQdNav1  (45,2,pbQdNav1_fn,gspSwitch_MODE_PUSHBUTTON_RELEASE_COUNTER_AUTORESET_CB);
gspSwitch pbQdNav2  (46,2,pbQdNav2_fn,gspSwitch_MODE_PUSHBUTTON_RELEASE_COUNTER_AUTORESET_CB);
gspSwitch pbQdAdf   (47,4,pbQdAdf_fn,gspSwitch_MODE_PUSHBUTTON_RELEASE_COUNTER_AUTORESET_CB);
gspSwitch pbQdXpd   (48,4,pbQdXpd_fn,gspSwitch_MODE_PUSHBUTTON_RELEASE_COUNTER_AUTORESET_CB);

//leds//
gspFlash flCom1     (27);
gspFlash flCom2     (28);
gspFlash flNav1     (29);
gspFlash flNav2     (30);
gspFlash flMrkr     (31);
gspFlash flAdf      (32);

//switches//
gspSwitch swCom     (33,"A45","A46");
gspSwitch swNav     (34,swNav1Rx,swNav2Rx);

//pushbuttons//
gspSwitch pbCom1_swp(39,"A06");
gspSwitch pbCom2_swp(40,"A12");
gspSwitch pbNav1_swp(41,"A18");
gspSwitch pbNav2_swp(42,"A24");

gspSwitch pbNav1id  (35,"A48");
gspSwitch pbNav2id  (36,"A49");
gspSwitch pbAdf     (37,"A52");
gspSwitch pbMkr     (38,"A53");

///////////////////////////////////////////////////////////////////////////////
void setup() {

  Serial.begin(115200);

  // put your setup code here, to run once:

  gspGrouped::register_instance(&com1 );
  gspGrouped::register_instance(&com2 );
  gspGrouped::register_instance(&com1sb );
  gspGrouped::register_instance(&com2sb );
  gspGrouped::register_instance(&nav1 );
  gspGrouped::register_instance(&nav2 );
  gspGrouped::register_instance(&nav1sb );
  gspGrouped::register_instance(&nav2sb );
  gspGrouped::register_instance(&adf );
  gspGrouped::register_instance(&xpd );

  gspGrouped::register_instance(&qdCom1);
  gspGrouped::register_instance(&qdCom2);
  gspGrouped::register_instance(&qdNav1);  
  gspGrouped::register_instance(&qdNav2);  
  gspGrouped::register_instance(&qdAdf);  
  gspGrouped::register_instance(&qdXpd);  
  
  gspGrouped::register_instance(&flCom1);
  gspGrouped::register_instance(&flCom2);
  gspGrouped::register_instance(&flNav1);
  gspGrouped::register_instance(&flNav2);
  gspGrouped::register_instance(&flMrkr);
  gspGrouped::register_instance(&flAdf);
  
  gspGrouped::register_instance(&swCom);
  gspGrouped::register_instance(&swNav);
  
  gspGrouped::register_instance(&pbNav1id);
  gspGrouped::register_instance(&pbNav2id);
  gspGrouped::register_instance(&pbAdf);
  gspGrouped::register_instance(&pbMkr);
  gspGrouped::register_instance(&pbCom1_swp);
  gspGrouped::register_instance(&pbCom2_swp);
  gspGrouped::register_instance(&pbNav1_swp);
  gspGrouped::register_instance(&pbNav2_swp);

  gspGrouped::register_instance(&pbQdCom1);
  gspGrouped::register_instance(&pbQdCom2);
  gspGrouped::register_instance(&pbQdNav1);
  gspGrouped::register_instance(&pbQdNav2);
  gspGrouped::register_instance(&pbQdAdf);
  gspGrouped::register_instance(&pbQdXpd);

  gspGrouped::register_instance(&srCom1);
  gspGrouped::register_instance(&srCom2);
  gspGrouped::register_instance(&srCom1sb);
  gspGrouped::register_instance(&srCom2sb);
  gspGrouped::register_instance(&srNav1);
  gspGrouped::register_instance(&srNav2);
  gspGrouped::register_instance(&srNav1sb);
  gspGrouped::register_instance(&srNav2sb);
  gspGrouped::register_instance(&srAdf);
  gspGrouped::register_instance(&srXpd);

  gspQuad::startCheckAll();
}

///////////////////////////////////////////////////////////////////////////////
void loop() {
 
  gspSwitch::checkAll();
  gspFlash::checkAll();
  gspSeven::checkAll();
  gspSerialResponse::checkAll();

}
///////////////////////////////////////////////////////////////////////////////

//COM1
void fsrCom1(String szParam) {
  com1.displayNums(szParam);
}

//COM1-standby
void fsrCom1sb(String szParam) {
  com1sb.displayNums(szParam);
}

//COM2
void fsrCom2(String szParam) {
  com2.displayNums(szParam);
}

//COM2-standby
void fsrCom2sb(String szParam) {
  com2sb.displayNums(szParam);
}

//NAV1
void fsrNav1(String szParam) {
  nav1.displayNums(szParam);
}

//NAV1-standby
void fsrNav1sb(String szParam) {  
  nav1sb.displayNums(szParam);
}

//NAV2
void fsrNav2(String szParam) {
  nav2.displayNums(szParam);
}

//NAV2-standby
void fsrNav2sb(String szParam) {
  nav2sb.displayNums(szParam);
}

//ADF
void fsrAdf(String szParam) {
  adf.displayNums(szParam); // TODO FIX FOR LOWER group
}

//XPDR
void fsrXpd(String szParam) {
  xpd.displayNums(szParam); // TODO FIX FOR LOWER group
}

// Toggle Switches
void swCom1Tx() {

}

void swCom2Tx() {

}

void swNav1Rx() {

}

void swNav2Rx() {

}


void qdCom1Lower  (int dif) {
  pbQdCom1.counterAutoResetHoldoff();   
  switch (pbQdCom1.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A01");
    break;
    case 2:
      gspGrouped::gspStream.println("A03");
    break;
  }
};

void qdCom2Lower  (int dif) {
  pbQdCom2.counterAutoResetHoldoff();   
  switch (pbQdCom2.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A07");
    break;
    case 2:
      gspGrouped::gspStream.println("A09");
    break;
  }
};

void qdNav1Lower  (int dif) {
  pbQdNav1.counterAutoResetHoldoff();   
  switch (pbQdNav1.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A13");
    break;
    case 2:
      gspGrouped::gspStream.println("A15");
    break;
  }
};

void qdNav2Lower  (int dif) {
  pbQdNav2.counterAutoResetHoldoff();   
  switch (pbQdNav2.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A19");
    break;
    case 2:
      gspGrouped::gspStream.println("A21");
    break;
  }
};

void qdAdfLower   (int dif) {
  pbQdAdf.counterAutoResetHoldoff();   
  switch (pbQdAdf.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A29");
    break;
    case 2:
      gspGrouped::gspStream.println("A30");
    break;
    case 3:
      gspGrouped::gspStream.println("A31");
    break;
    case 4:
      gspGrouped::gspStream.println("A32");
    break;
  }
};

void qdXpdLower   (int dif) {
  pbQdXpd.counterAutoResetHoldoff();
  switch (pbQdXpd.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A38");
    break;
    case 2:
      gspGrouped::gspStream.println("A39");
    break;
    case 3:
      gspGrouped::gspStream.println("A40");
    break;
    case 4:
      gspGrouped::gspStream.println("A41");
    break;
  }   
};

void qdCom1Higher (int dif) {
  pbQdCom1.counterAutoResetHoldoff();
  switch (pbQdCom1.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A02");
    break;
    case 2:
      gspGrouped::gspStream.println("A04");
    break;
  }   
};

void qdCom2Higher (int dif) {
  pbQdCom2.counterAutoResetHoldoff();
  switch (pbQdCom2.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A08");
    break;
    case 2:
      gspGrouped::gspStream.println("A10");
    break;
  }   
};

void qdNav1Higher (int dif) {
  pbQdNav1.counterAutoResetHoldoff();
  switch (pbQdNav1.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A14");
    break;
    case 2:
      gspGrouped::gspStream.println("A16");
    break;
  }   
};

void qdNav2Higher (int dif) {
  pbQdNav2.counterAutoResetHoldoff();
  switch (pbQdNav2.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A20");
    break;
    case 2:
      gspGrouped::gspStream.println("A22");
    break;
  }   
};

void qdAdfHigher  (int dif) {
  pbQdAdf.counterAutoResetHoldoff();
  switch (pbQdAdf.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A25");
    break;
    case 2:
      gspGrouped::gspStream.println("A26");
    break;
    case 3:
      gspGrouped::gspStream.println("A27");
    break;
    case 4:
      gspGrouped::gspStream.println("A28");
    break;
  }   
};

void qdXpdHigher  (int dif) {
  pbQdXpd.counterAutoResetHoldoff();
  switch (pbQdXpd.getCounterValue()) {
    case 0:
    break;
    case 1:
      gspGrouped::gspStream.println("A34");
    break;
    case 2:
      gspGrouped::gspStream.println("A35");
    break;
    case 3:
      gspGrouped::gspStream.println("A36");
    break;
    case 4:
      gspGrouped::gspStream.println("A37");
    break;
  }   
};

void pbQdCom1_fn(uint8_t state) {
  com1sb.stopFlashing();
  switch (state) {
    case 0:
    break;
    case 1:
      com1sb.flashA();
    break;
    case 2:
      com1sb.flashB();
    break;
  }  
}

void pbQdCom2_fn(uint8_t state) {
  com2sb.stopFlashing();
  switch (state) {
    case 0:
    break;
    case 1:
      com2sb.flashA();
    break;
    case 2:
      com2sb.flashB();
    break;
  } 
}

void pbQdNav1_fn(uint8_t state) {
  nav1sb.stopFlashing();
  switch (state) {
    case 0:
    break;
    case 1:
      nav1sb.flashA();
    break;
    case 2:
      nav1sb.flashB();
    break;
  } 
}

void pbQdNav2_fn(uint8_t state) {
  nav2sb.stopFlashing();
  switch (state) {
    case 0:
    break;
    case 1:
      nav2sb.flashA();
    break;
    case 2:
      nav2sb.flashB();
    break;
  } 
}

void pbQdAdf_fn(uint8_t state) {
  adf.stopFlashing();
  switch (state) {
    case 0:
    break;
    case 1:
      adf.flash(1);
    break;
    case 2:
      adf.flash(2);
    break;
    case 3:
      adf.flash(3);
    break;
    case 4:
      adf.flash(4);
    break;
  } 
}

void pbQdXpd_fn(uint8_t state) {
  xpd.stopFlashing();
  switch (state) {
    case 0:
    break;
    case 1:
      xpd.flash(1);
    break;
    case 2:
      xpd.flash(2);
    break;
    case 3:
      xpd.flash(3);
    break;
    case 4:
      xpd.flash(4);
    break;
  } 
}