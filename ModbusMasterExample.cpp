#include <Arduino.h>
#include <ModbusMaster.h>		// import necessary libraries
#define Battery_Voltage_Address 0x30A0 // Register we want to read
#define MAX485_DE      D13		// Send/receive signal
#define usbSerial Serial		
ModbusMaster node; 			// instantiate ModbusMaster object
double load = 1;				// Setting load output to ON


void preTransmission1()		// Sets pre-transmission signal (trans)
{
  digitalWrite(MAX485_DE, 1);
}


void postTransmission1()		// Sets post-transmission signal (rec)
{
  digitalWrite(MAX485_DE, 0);
}


void setLoad(){				// Turns controller output ON/OFF
    if (load == 1){
    Serial.println("Output ON");
    node.writeSingleCoil(0x0000, 1); // Write the value to the register
    delay(1000);  
  }
  else{
    Serial.println("Output OFF");
    node.writeSingleCoil(0x0000, 0);
    delay(1000);  
  }
}


int readModbusRegister(uint16_t regAddress)
{
  uint8_t result;
  uint16_t data;
  int value = -1;
  int numRead = 1;


  Serial.print("Reading Modbus Register at address: 0x");
  Serial.println(regAddress, HEX);


  result = node.readInputRegisters(regAddress, numRead); // Read register


  if (result == node.ku8MBSuccess) { 		// Check for success
    Serial.print("   Response Bytes: ");
    for (uint8_t i = 0; i < numRead; i++) {
      Serial.print(node.getResponseBuffer(i), HEX);
      Serial.print(" ");
    }
    Serial.println();


    for (uint8_t i = 0; i < numRead; i++) {
    }
    data = node.getResponseBuffer(0);
    value = data;


  } else {							// Else error
    Serial.print("Error reading input register " + String(regAddress) +  ". Error code: ");
    Serial.println(result, HEX);
  }


  delay(1000);
  return value;						// return register value
}


void setup()
{
  pinMode(MAX485_DE, OUTPUT);		// Set pin modes and values
  digitalWrite(MAX485_DE, 0);


  Serial.begin(9600);				// Begin serial communication
  Serial1.begin(9600);
  node.begin(1, Serial1);			// Modbus slave ID 1, Serial1


  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission1);
  node.postTransmission(postTransmission1);
}


void loop()
{ int res = 0;
  res = readModbusRegister(Battery_Voltage_Address); // Read/print address
  delay(1*60*1000);						// Wait 5 mins
}
