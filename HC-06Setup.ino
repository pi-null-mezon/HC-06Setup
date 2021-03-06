/*------------------------------------------------------------------------------------------------------------
Microprogram for Arduino that gets you a simple interface to AT commands interchange between
Arduino board and Bluetooth module HC-06. Just compile (with appropriate values), upload, open serial port
monitor and wait. Do not forget to plug in your HC-06 (you can do int on the fly). Take in mind that after
the speed change, the HC-06 will stop to respond on commands, that were sent with another speed. Therefore,
second time you want to change settings, you have to recompile project with appropriate speed of COM port.  
Taranov Alex, 2014
-------------------------------------------------------------------------------------------------------------*/

#define BUFFER_LENGTH 64 // the size of the serial receive buffer for ATmega328
#define SERIAL_SPEED 9600 // HC-06 works on 9600 bps when you get it from manufacturer
#define DELAY 1000 // in ms

char buffer[BUFFER_LENGTH];
const char at[] = "AT"; 
const char at_version[] = "AT+VERSION";

//VALUES FOR MODIFICATION----------------------------------------------------------------------------------------------
const char at_baud[] = "AT+BAUD4"; // Change the end-number by your self: AT+BAUD#, if # == 4 then 9600, if # ==8 115200
const char at_pin[] = "AT+PIN1234"; // Change the end-number by your self: AT+PIN#
const char at_name[] = "AT+NAMEHC-06"; // Change the end-string by your self: AT+NAME#
//---------------------------------------------------------------------------------------------------------------------

void setup()
{
  Serial.begin(SERIAL_SPEED);
}

void loop()
{ 
  Serial.println("Start scanning: ");
  
  ask_command(at); // minus one, because strings contain \0 symbol at their end, but HC-06 have to be programmed without this symbol 

  ask_command(at_version);

  ask_command(at_baud); 

  ask_command(at_name); 

  ask_command(at_pin); 
}

void ask_command(const char *command)
{
  Serial.print("We ask: \t");
  delay(DELAY);

  Serial.print(command); 
 
  delay(DELAY);
  Serial.print('\n');
  
  if(Serial.available())
  { 
    Serial.print("Device says:\t"); 
     
    Serial.readBytes(buffer,BUFFER_LENGTH);   
    Serial.print(buffer);
    
    Serial.print('\n');
  }
  else
  {
    Serial.println("No answers...");
  }  
}


