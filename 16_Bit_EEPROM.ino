/* sketch to write a 16 bit variable to EEPROM 
 * and then retrieve said variable.  The EEPROM 
 * addresses are only 8 bits long, so we need to 
 * break the 16 bit var down when writing and
 * rebuild it when reading.
 */



#include <EEPROM.h>

void setup() {
  Serial.begin(115200);
  Serial.println("\nstartup");

  uint16_t output = 12345; // 12345 = 00110000 00111001
  Serial.print("output = "); Serial.println(output,BIN);
  // break the output into two 8 bit bytes via 
  uint8_t msb, lsb;
  msb = (output>>8) & 0xFF;
  // shift the output variable 8 bits to the left and compare with 0xFF (all ones)
  //    using bitwise AND.  & only returns true if both bits are true 
  // result will be:
  //     00110000 00111001
  //     11111111
  //     --------
  //     00110000 - result

  lsb = output & 0xFF; // now do the same for the least signifacant bits

   // write to EEPROM
  EEPROM.update(0,msb);
  EEPROM.update(1,lsb);
  

  for(int address=0; address<2; address++){
    byte val = EEPROM.read(address);
    Serial.print("address: ");Serial.print(address);
    Serial.print("\tval: ");Serial.print(val, DEC);
    Serial.print("\t\t: ");Serial.print(val, BIN);
    Serial.print("\t: ");Serial.print(val, HEX);
    Serial.println();
  }


  uint8_t msb_in, lsb_in; // create some new bytes and read from EEPROM
  msb_in = EEPROM.read(0);
  lsb_in = EEPROM.read(1);
  
  // create our input number by shifting the most significant bits 8 bytes to the left 
  //    and add our least significant bytes.
  uint16_t input = (msb_in << 8) + lsb_in;

  Serial.print("input = ");Serial.println(input);

}

void loop() {
  // put your main code here, to run repeatedly:

}
