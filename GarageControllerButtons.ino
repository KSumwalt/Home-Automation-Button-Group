//CAN Message format
//  canMsg.can_id  = unitID;          //CAN id - Use for sending device ID
//  canMsg.can_dlc = 4;               //CAN data length
//  canMsg.data[0] = btn->getID();    //Device ID message is intended for 0xFF = Any
//  canMsg.data[1] = 1;               //Message Content 1=button press 2=LED Control 3=Reqquest LED Status
//  canMsg.data[2] = 1;               //If button press: button number
//  canMsg.data[3] = 1;               //If button press: pressed type 1=single 2=double 3=long
//  canMsg.data[2] = 1;               //If LED control: LED number
//  canMsg.data[3] = 1;               //If LED control:  0=Off 1=On
////  canMsg.data[4] = 0x00;          //Rest all with 0
////  canMsg.data[5] = 0x00;
////  canMsg.data[6] = 0x00;
////  canMsg.data[7] = 0x00;

#include <SPI.h>
#include <mcp2515.h>
#include <PinButton.h>

//Unit ID is used to know which Button Panel is sending the message.
//  This should start at 0 and go up by 1 for each added Button Panel
#define unitID 0x01

#define LED01 19
#define LED02 18
#define LED03 17
#define LED04 16
#define LED05 15
#define LED06 14

#define SINGLEPRESS 1
#define DOUBLEPRESS 2
#define LONGPRESS 3

const unsigned int btnPin01 = 3;
const unsigned int btnPin02 = 4;
const unsigned int btnPin03 = 5;
const unsigned int btnPin04 = 6;
const unsigned int btnPin05 = 7;
const unsigned int btnPin06 = 8;

// Create a new button object for each button.
PinButton myButton01(btnPin01);
PinButton myButton02(btnPin02);
PinButton myButton03(btnPin03);
PinButton myButton04(btnPin04);
PinButton myButton05(btnPin05);
PinButton myButton06(btnPin06);


struct can_frame canMsg;
MCP2515 mcp2515(10); 

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println();

  pinMode(LED01, OUTPUT);
  pinMode(LED02, OUTPUT);
  pinMode(LED03, OUTPUT);
  pinMode(LED04, OUTPUT);
  pinMode(LED05, OUTPUT);
  pinMode(LED06, OUTPUT);
  digitalWrite(LED01, HIGH);
  digitalWrite(LED02, HIGH);
  digitalWrite(LED03, HIGH);
  digitalWrite(LED04, HIGH);
  digitalWrite(LED05, HIGH);
  digitalWrite(LED06, HIGH);

  canMsg.can_id  = unitID;
  canMsg.can_dlc = 2;
  canMsg.data[0] = 0xFF; //Messages out from the Button Panel are intended for any device which wants to use them
  canMsg.data[1] = 0x03;
  canMsg.data[2] = 0x00;
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();

  Serial.println("Garage Buttons");
  Serial.print("My Unit ID: ");
  Serial.println(unitID);

  delay (5000);


  //Request the status of the LEDs to sync them with the controller
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message
}

void buttonPressed (int pressedButton, int pressType) {

  canMsg.can_id  = unitID;          //CAN id as 0x036
  canMsg.can_dlc = 4;               //CAN data length as 3
  canMsg.data[0] = 0xAA;             //Unit ID the message is intended for - 0xAA = the controller
  canMsg.data[1] = 1;                //1=button press
  canMsg.data[2] = pressedButton;    //button #
  canMsg.data[3] = pressType;        //Update the pressed type 1=single 2=double 3=long

//  Serial.print("Button: ");
//  Serial.println(pressedButton);
//  Serial.print("Press Type: ");
//  Serial.println(pressType);
//  Serial.println();
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message
//  Serial.print("Message Sent: ");
//    Serial.print(canMsg.can_id, HEX); // print ID
//    Serial.print(" "); 
//    Serial.print(canMsg.can_dlc, HEX); // print DLC
//    Serial.print(" ");
//    
//    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
//      Serial.print(canMsg.data[i],HEX);
//      Serial.print(" ");
//    }
//   Serial.println(); 
}

void checkButtons(){
  // Read hardware pin, convert to click events
  myButton01.update();
  myButton02.update();
  myButton03.update();
  myButton04.update();
  myButton05.update();
  myButton06.update();
  if (myButton01.isSingleClick()) {
//    Serial.println("single");
    buttonPressed(0, SINGLEPRESS);
  }
  if (myButton01.isDoubleClick()) {
//    Serial.println("double");
    buttonPressed(0, DOUBLEPRESS);
  }
  if (myButton01.isLongClick()) {
//    Serial.println("long");
    buttonPressed(0, LONGPRESS);
  }
  if (myButton02.isSingleClick()) {
//    Serial.println("single");
    buttonPressed(1, SINGLEPRESS);
  }
  if (myButton02.isDoubleClick()) {
//    Serial.println("double");
    buttonPressed(1, DOUBLEPRESS);
  }
  if (myButton02.isLongClick()) {
//    Serial.println("long");
    buttonPressed(1, LONGPRESS);
  }  
  if (myButton03.isSingleClick()) {
//    Serial.println("single");
    buttonPressed(2, SINGLEPRESS);
  }
  if (myButton03.isDoubleClick()) {
//    Serial.println("double");
    buttonPressed(2, DOUBLEPRESS);
  }
  if (myButton03.isLongClick()) {
//    Serial.println("long");
    buttonPressed(2, LONGPRESS);
  }
  if (myButton04.isSingleClick()) {
//    Serial.println("single");
    buttonPressed(3, SINGLEPRESS);
  }
  if (myButton04.isDoubleClick()) {
//    Serial.println("double");
    buttonPressed(3, DOUBLEPRESS);
  }
  if (myButton04.isLongClick()) {
//    Serial.println("long");
    buttonPressed(3, LONGPRESS);
  }
  if (myButton05.isSingleClick()) {
//    Serial.println("single");
    buttonPressed(4, SINGLEPRESS);
  }
  if (myButton05.isDoubleClick()) {
//    Serial.println("double");
    buttonPressed(4, DOUBLEPRESS);
  }
  if (myButton05.isLongClick()) {
//    Serial.println("long");
    buttonPressed(4, LONGPRESS);
  }
  if (myButton06.isSingleClick()) {
//    Serial.println("single");
    buttonPressed(5, SINGLEPRESS);
  }
  if (myButton06.isDoubleClick()) {
//    Serial.println("double");
    buttonPressed(5, DOUBLEPRESS);
  }
  if (myButton06.isLongClick()) {
//    Serial.println("long");
    buttonPressed(5, LONGPRESS);
  }

}


void canReceived() {
  // check canMsg.data[1] to determine what the message relates to
  //    1=button press 2=LED Control 3=?
  // If it relates to LED control, use canMsg.data[2] to determine
  //    which LED to act on
  // The state to set on the LED is defined in canMsg.data[3]

//    Serial.print("Message For This Unit: ");
//    Serial.print(canMsg.can_id, HEX); // print ID
//    Serial.print(" "); 
//    Serial.print(canMsg.can_dlc, HEX); // print DLC
//    Serial.print(" ");
//    
//    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
//      Serial.print(canMsg.data[i],HEX);
//      Serial.print(" ");
//    }
//    Serial.println();

    boolean LEDstate = HIGH;
    if (canMsg.data[3] == 1){
      LEDstate = LOW;
    }
  
    //We only care about messages meant to control the LED
    if (canMsg.data[1] == 2) {
//          Serial.print("Switch Case: ");
      switch (canMsg.data[2]) {
        case 0:
//          Serial.println(canMsg.data[2],HEX);
          digitalWrite(LED01, LEDstate);
          break;
        case 1:
//          Serial.println(canMsg.data[2],HEX);
          digitalWrite(LED02, LEDstate);
          break;
        case 2:
//          Serial.println(canMsg.data[2],HEX);
          digitalWrite(LED03, LEDstate);
          break;
        case 3:
//          Serial.println(canMsg.data[2],HEX);
          digitalWrite(LED04, LEDstate);
          break;
        case 4:
//          Serial.println(canMsg.data[2],HEX);
          digitalWrite(LED05, LEDstate);
          break;
        case 5:
//          Serial.println(canMsg.data[2],HEX);
          digitalWrite(LED06, LEDstate);
          break;
      }
    }
}

void loop() {

  checkButtons();

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
//    Serial.print("Message Received: ");
//    Serial.print(canMsg.can_id, HEX); // print ID
//    Serial.print(" "); 
//    Serial.print(canMsg.can_dlc, HEX); // print DLC
//    Serial.print(" ");
//    
//    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
//      Serial.print(canMsg.data[i],HEX);
//      Serial.print(" ");
//    }
//      Serial.println();
//    
//      Serial.print("Message intended for: ");
//      Serial.println(canMsg.data[0]);
//      Serial.print("My Unit ID: ");
//      Serial.println(unitID);

    if (canMsg.data[0] == unitID) {
      //This is meant for us, so act on it
      canReceived();
    }

//    Serial.println();
  }
}
