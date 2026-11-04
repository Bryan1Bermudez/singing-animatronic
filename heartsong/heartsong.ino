
#include "SoftwareSerial.h"
SoftwareSerial mySerial(10, 11);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define ACTIVATED LOW
boolean isPlaying = false;


# define ACTIVATED LOW

#define CLK 2
#define DT 3
#define SW 4


int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;


int potPin = A0; 
int potVal = 0;




void setup() {
  // put your setup code here, to run once:


	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);






mySerial.begin (9600);
delay(1000);
playFirst();
isPlaying = true;




lastStateCLK = digitalRead(CLK);



  digitalWrite(13, HIGH);   
  delay(100);              
  digitalWrite(13, LOW);   
  delay(100);    






}

void loop() {

currentStateCLK = digitalRead(CLK);

  // put your main code here, to run repeatedly:

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
      playPrevious();
		} else {
      playNext();
		}


	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
      if(isPlaying) {
        pause();
        isPlaying = false;
      } else {
        play();
        isPlaying = true;
      }

			Serial.println("Button pressed!");
		}

		// Remember last button press event
		lastButtonPress = millis();
	}

	// Put in a slight delay to help debounce the reading
	delay(1);








}

void playFirst()
{
  execute_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(15);
  delay(500);
  execute_CMD(0x11,0,1); 
  delay(500);
}
void pause()
{
  execute_CMD(0x0E,0,0);
  delay(500);
}
void play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);
}
void playNext()
{
  execute_CMD(0x01,0,1);
  delay(500);
}
void playPrevious()
{
  execute_CMD(0x02,0,1);
  delay(500);
}
void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}
void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
// Calculate the checksum (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
// Build the command line
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
//Send the command line to the module
for (byte k=0; k<10; k++)
{
mySerial.write( Command_line[k]);
}
}