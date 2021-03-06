/*
  Somfy RTS remote control :

  Copyright (c) 2016, yogui
  
  code inspired from culfw http://culfw.de/culfw.html 
  and from this arduino forum thread : https://forum.arduino.cc/index.php?topic=208346.0
  
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
  Used In/Output atmega328:
  
  D00 : Not used
  D01 : Not used
  D02 : Not used 
  D03 : Output for radio data 
  D04 : Not used 
  D05 : Not used 
  D06 : Not used 
  D07 : Not used 
  D08 : LED
  D09 : Not used 
  D10 : Not used 
  D11 : Not used 
  D12 : Not used 
  D13 : Not used 

  Analog inputs atmega328 :
  
  A00 : not used
  A01 : Input for radio data
  A02 : not used
  A03 : not used
  A04 : not used
  A05 : not used
  A06 : not used
  A07 : not used
  
  Used In/Output Mega:
  
  D03 : Output for radio data 
  D18 : Input for radio data
  D53 : LED

  Function description :

  setup your ADDRESS_REMOTE_1 
  you can print the variable somfy.SomfyData.address to find your remote address

  in the variable somfy.SomfyData.cmd you will have the hex code from the button you press

  
  Possible commande :

	SomfyCmd_My 		My			Stop or move to favourite position
	SomfyCmd_Up 		Up			Move up
	SomfyCmd_MyUp 		My + Up		Set upper motor limit in initial programming mode
	SomfyCmd_Down 		Down		Move down
	SomfyCmd_MyDown 	My + Down	Set lower motor limit in initial programming mode
	SomfyCmd_UpDown 	Up + Down	Change motor limit and initial programming mode
	SomfyCmd_Prog   	Prog		Used for (de-)registering remotes
	SomfyCmd_SunFlag 	Sun + Flag	Enable sun and wind detector (SUN and FLAG symbol on the Telis Soliris RC)
	SomfyCmd_Flag	 	Flag		Disable sun detector (FLAG symbol on the Telis Soliris RC)
  
  I have tested the code on an 
  Arduino nano with an Atmega328p
  Arduino Uno with an Atmega328p
  Arduino Pro mini 5.0V with an Atmega328p
  Arduino MEGA thanks @icare


 */



#include <somfy_rts.h>

#define ADDRESS_REMOTE_1 0x000002

//for TX the output 3 is used 
//for RX the analoge input A1 is used
//for the LED the ouput 8 is used 
//this is fixe define inside the lib 
static somfy_rts somfy;


void setup() {
   
   Serial.begin(115200);
 
   // Initialize Somfy recive
   somfy.beginRecive();
  
}

void loop() {
  //Wenn address different 0  
  if (somfy.SomfyData.address == ADDRESS_REMOTE_1)
  {
    Serial.print("Adress ");
    Serial.println(somfy.SomfyData.address);
    //Check commande   
    if (somfy.SomfyData.cmd)
    {
        Serial.print("Command ");
        Serial.println(somfy.SomfyData.cmd);
    }
    //reset value to see the next change    
    somfy.SomfyData.cmd = SomfyCmd_None;
    somfy.SomfyData.address = 0;
  }
}

