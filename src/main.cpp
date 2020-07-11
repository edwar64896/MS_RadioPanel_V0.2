#include <Arduino.h>
#include <gspswitch.h>
#include <gspquad.h>
#include <gspflash.h>
#include <gspserialresponse.h>
#include <gspseven.h>



gspSeven ld1(4,2,3);

//COM1 =A{7}
void fsrCom1(String szParam) {

  ld1.displayNums(0,szParam);
  Serial.println(szParam);

}

//COM1-standby =C{7}
void fsrCom1sb(String szParam) {

  ld1.displayNums(1,szParam);
  Serial.println(szParam);

}

//COM2 =B{7}
void fsrCom2(String szParam) {
  ld1.displayNums(2,szParam);
  Serial.println(szParam);
}


//COM2-standby =D{7}
void fsrCom2sb(String szParam) {
  ld1.displayNums(3,szParam);
  Serial.println(szParam);
}

//NAV1
void fsrNav1(String szParam) {
  ld1.displayNums(4,szParam);
  Serial.println(szParam);
}

//NAV1-standby
void fsrNav1sb(String szParam) {
  ld1.displayNums(5,szParam);
  Serial.println(szParam);
}

//NAV2
void fsrNav2(String szParam) {
  ld1.displayNums(6,szParam);
  Serial.println(szParam);
}

//NAV2-standby
void fsrNav2sb(String szParam) {
  ld1.displayNums(7,szParam);
  Serial.println(szParam);
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

gspSerialResponse srCom1("=A",7,fsrCom1);
gspSerialResponse srCom2("=B",7,fsrCom2);
gspSerialResponse srCom1sb("=C",7,fsrCom1sb);
gspSerialResponse srCom2sb("=D",7,fsrCom2sb);
gspSerialResponse srNav1("=E",6,fsrNav1);
gspSerialResponse srNav2("=F",6,fsrNav2);
gspSerialResponse srNav1sb("=G",6,fsrNav1sb);
gspSerialResponse srNav2sb("=H",6,fsrNav2sb);
gspSerialResponse srAdf("=I",6,fsrAdf);
gspSerialResponse srXpd("=J",4,fsrXpd);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

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
  //gspGrouped::register_instance(&srDme1);
  //gspGrouped::register_instance(&srDme2);

 //ld1.setDigits();

   delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //gspSwitch::checkAll();
  //gspQuad::checkAll();
  gspSerialResponse::checkAll();
  //delay(100);


}