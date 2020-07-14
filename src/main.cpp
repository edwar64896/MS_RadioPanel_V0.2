#include <Arduino.h>
#include <gspswitch.h>
#include <gspquad.h>
#include <gspflash.h>
#include <gspserialresponse.h>
#include <gspseven.h>

#define _data   1
#define _clk    2

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
void fsrDme1  (String);
void fsrDme2  (String);

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

void swCom1Tx();
void swCom2Tx();
void swNav1Rx();
void swNav2Rx();

void pbNav1id_fn();
void pbNav2id_fn();
void pbAdf_fn();
void pbMkr_fn();
void pbCom1_swp_fn();
void pbCom2_swp_fn();
void pbNav1_swp_fn();
void pbNav2_swp_fn();

//data,clock,chipselect/load

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

gspQuad   qdCom1    (15, 16, qdCom1Lower, qdCom1Higher);
gspQuad   qdCom2    (17, 18, qdCom2Lower, qdCom2Higher);
gspQuad   qdNav1    (19, 20, qdNav1Lower, qdNav1Higher);
gspQuad   qdNav2    (21, 22, qdNav2Lower, qdNav2Higher);
gspQuad   qdAdf     (23, 24, qdAdfLower,  qdAdfHigher);
gspQuad   qdXpd     (25, 26, qdXpdLower,  qdXpdHigher);

gspFlash flCom1     (27);
gspFlash flCom2     (28);
gspFlash flNav1     (29);
gspFlash flNav2     (30);
gspFlash flMrkr     (31);
gspFlash flAdf      (32);

gspSwitch swCom     (33,swCom1Tx,swCom2Tx);
gspSwitch swNav     (34,swNav1Rx,swNav2Rx);

gspSwitch pbNav1id  (35,pbNav1id_fn);
gspSwitch pbNav2id  (36,pbNav2id_fn);
gspSwitch pbAdf     (37,pbAdf_fn);
gspSwitch pbMkr     (38,pbMkr_fn);
gspSwitch pbCom1_swp(39,pbCom1_swp_fn);
gspSwitch pbCom2_swp(40,pbCom2_swp_fn);
gspSwitch pbNav1_swp(41,pbNav1_swp_fn);
gspSwitch pbNav2_swp(42,pbNav2_swp_fn);


void setup() {

  Serial.begin(115200);

  // put your setup code here, to run once:

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

int ii=0;

void loop() {
 
  gspSwitch::checkAll();
  gspFlash::checkAll();
  gspSerialResponse::checkAll();

}


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

}

//XPDR
void fsrXpd(String szParam) {

}

//DME1
void fsrDme1(String szParam) {

}

//DME2
void fsrDme2(String szParam) {

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


//pushbutton functions
void pbNav1id_fn(){

};

void pbNav2id_fn(){

};

void pbAdf_fn(){

};

void pbMkr_fn(){

};

void pbCom1_swp_fn(){

};

void pbCom2_swp_fn(){

};

void pbNav1_swp_fn(){
  
};

void pbNav2_swp_fn(){

};

void qdCom1Lower  (int dif){

};

void qdCom2Lower  (int dif){

};

void qdNav1Lower  (int dif){

};

void qdNav2Lower  (int dif){

};

void qdAdfLower   (int dif){

};

void qdXpdLower   (int dif){

};

void qdCom1Higher (int dif){

};

void qdCom2Higher (int dif){

};

void qdNav1Higher (int dif){

};

void qdNav2Higher (int dif){

};

void qdAdfHigher  (int dif){

};

void qdXpdHigher  (int dif){

};