const int channel = 1;

int RotaryPot1;
int RotaryPot2;
int RotaryPot3;
int RotaryPot4;
int RotaryPot5;
int RotaryPot6;
int RotaryPot7;

int FaderPot1;
int FaderPot2;
int FaderPot3;
int FaderPot4;

//Threshold:

//RotaryPotis:
int OldRotaryPotVal1 = 0;
int NewRotaryPotVal1 = 0;
int MappedRotaryPotVal1 = 0;
int NewMappedRotaryPotVal1 = 0;

int OldRotaryPotVal2 = 0;
int NewRotaryPotVal2 = 0;
int MappedRotaryPotVal2 = 0;
int NewMappedRotaryPotVal2 = 0;

int OldRotaryPotVal3 = 0;
int NewRotaryPotVal3 = 0;
int MappedRotaryPotVal3 = 0;
int NewMappedRotaryPotVal3 = 0;

int OldRotaryPotVal4 = 0;
int NewRotaryPotVal4 = 0;
int MappedRotaryPotVal4 = 0;
int NewMappedRotaryPotVal4 = 0;

int OldRotaryPotVal5 = 0;
int NewRotaryPotVal5 = 0;
int MappedRotaryPotVal5 = 0;
int NewMappedRotaryPotVal5 = 0;

int OldRotaryPotVal6 = 0;
int NewRotaryPotVal6 = 0;
int MappedRotaryPotVal6 = 0;
int NewMappedRotaryPotVal6 = 0;

int OldRotaryPotVal7 = 0;
int NewRotaryPotVal7 = 0;
int MappedRotaryPotVal7 = 0;
int NewMappedRotaryPotVal7 = 0;

//FaderPotis:
int MappedFaderPotVal = 0;

int OldFaderPotVal1 = 0;
int NewFaderPotVal1 = 0;
int MappedFaderPotVal1 = 0;
int NewMappedFaderPotVal1 = 0;

int OldFaderPotVal2 = 0;
int NewFaderPotVal2 = 0;
int MappedFaderPotVal2 = 0;
int NewMappedFaderPotVal2 = 0;

int OldFaderPotVal3 = 0;
int NewFaderPotVal3 = 0;
int MappedFaderPotVal3 = 0;
int NewMappedFaderPotVal3 = 0;

int OldFaderPotVal4 = 0;
int NewFaderPotVal4 = 0;
int MappedFaderPotVal4 = 0;
int NewMappedFaderPotVal4 = 0;

const int RotaryPotThreshold = 30;
const int FaderPotThreshold = 20;

//TOUCHSCREEN:
int Y1 = A5;
int X2 = A4;
int Y2 = A3;
int X1 = A2;

int TouchX;
int OldTouchXVal = 0;
int NewTouchXVal = 0;
int MappedTouchXVal = 0;
int NewMappedTouchXVal = 0;

int TouchY;
int OldTouchYVal = 0;
int NewTouchYVal = 0;
int MappedTouchYVal = 0;
int NewMappedTouchYVal = 0;

const int TouchXThreshold = 20;
const int TouchYThreshold = 20;



//LED:
int SER_Pin = 4;   
int RCLK_Pin = 5;  
int SRCLK_Pin = 6; 

// define number of registers(74HC595)
#define number_of_74hc595s 4

 // define number of accessable register-pins
#define numOfRegisterPins number_of_74hc595s * 8

// create arry to write registers
boolean registers[numOfRegisterPins];

int VolumeLED=A8;                                                               
int TeensyLED=13;

int LEDRotaryPoti1;
int LEDRotaryPoti2;
int LEDRotaryPoti3;
int LEDRotaryPoti4;

int MappedLEDRotaryPoti1Val;

// select pins of potentiometer multiplexer
int PotMultiplexerSelectA=0;
int PotMultiplexerSelectB=1;
int PotMultiplexerSelectC=2;
int PotMultiplexerSelectD=3;
 
// analog multiplexer
int Multiplexer1Kanal=A9;

void setup() 
{
  pinMode(23, INPUT_PULLUP);

  Serial.begin(38400);
  
  pinMode(PotMultiplexerSelectA,OUTPUT);
  pinMode(PotMultiplexerSelectB,OUTPUT);
  pinMode(PotMultiplexerSelectC,OUTPUT);
  pinMode(PotMultiplexerSelectD,OUTPUT);
  
  pinMode(Multiplexer1Kanal,INPUT);
  
  pinMode(VolumeLED,OUTPUT);
  pinMode(TeensyLED,OUTPUT);
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
}

// write registers                         
void writeRegisters()
{

  // set clock pins to active-LOW in order to write
  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--)
  {
    digitalWrite(SRCLK_Pin, LOW);                                                                                           

    int val = registers[i];

    // write pin with val
    digitalWrite(SER_Pin, val);
    // set clock pins to HIGH to conclude writing process
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

// set LED
void setRegisterPin(int index, int value)
{
  registers[index] = value;
}

//______________________________________________________TOUCHSCREEN____________________________________________________

int readX()                                                                   
{
  // "roll" breakout-board-pins to read x-axis
  pinMode(Y1, INPUT);
  pinMode(X2, OUTPUT);
  pinMode(Y2, INPUT);
  pinMode(X1, OUTPUT);

  digitalWrite(X2, LOW);
  digitalWrite(X1, HIGH);

  // allow leiter to load
  delay(5);

  // return value
  return analogRead(Y1);
}

int readY()
{
  // "roll" breakout-board-pins to read y-axis
  pinMode(Y1, OUTPUT);
  pinMode(X2, INPUT);
  pinMode(Y2, OUTPUT);
  pinMode(X1, INPUT);

  digitalWrite(Y1, LOW);
  digitalWrite(Y2, HIGH);

  delay(5);

  return analogRead(X2);
  
                         

//define touch screen areas to trigger LED-bars
void TouchXSend()
  {
    int stateX;
  
    if((MappedTouchXVal > 0) && (MappedTouchXVal < 8))
    {
      stateX = 0;
    }  
    if((MappedTouchXVal > 7) && (MappedTouchXVal < 16))
    {
      stateX = 1;
    }  
    if((MappedTouchXVal > 15) && (MappedTouchXVal < 23))
    {
      stateX = 2;
    }  
    if((MappedTouchXVal > 22) && (MappedTouchXVal < 30))
    {
      stateX = 3;
    }  
    if((MappedTouchXVal > 29) && (MappedTouchXVal < 37))
    { 
      stateX = 4;
    }  
    if((MappedTouchXVal > 36) && (MappedTouchXVal < 45))
    {
      stateX = 5;
    }  
    if((MappedTouchXVal > 44) && (MappedTouchXVal < 54))
    {
      stateX = 6;
    }  
    if((MappedTouchXVal > 53) && (MappedTouchXVal < 65))
    {
      stateX = 7;
    }    
    if((MappedTouchXVal > 64) && (MappedTouchXVal < 78))
    {
      stateX = 8;
    }    
    if((MappedTouchXVal > 77) && (MappedTouchXVal < 88))
    {
      stateX = 9;
    }    
    if((MappedTouchXVal > 87) && (MappedTouchXVal < 97))
    {
      stateX = 10;
    }    
    if((MappedTouchXVal > 96) && (MappedTouchXVal < 104))
    {
      stateX = 11;
    }    
    if((MappedTouchXVal > 103) && (MappedTouchXVal < 111))
    {
      stateX = 12;
    }    
    if((MappedTouchXVal > 110) && (MappedTouchXVal < 128))
    {
      stateX = 13;
    }    
    
    //activate LEDs             
    switch (stateX)
    {
      case 0:
        setRegisterPin(11, HIGH);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);           
        writeRegisters();      
      break;
      
      case 1:
        setRegisterPin(11, LOW);
        setRegisterPin(12, HIGH);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);            
        writeRegisters(); 
      break;
      
      case 2:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, HIGH);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);       
        writeRegisters();    
      break;
      
      case 3:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, HIGH);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);    
        writeRegisters(); 
      break;  
  
      case 4:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, HIGH);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);  
        writeRegisters();    
      break; 
  
      case 5:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, HIGH);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);  
        writeRegisters();    
      break; 
  
      case 6:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, HIGH);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);  
        writeRegisters();   
      break;
  
      case 7:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, HIGH);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);  
        writeRegisters();   
      break;
       
      case 8:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, HIGH);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);  
        writeRegisters();   
      break;       
       
      case 9: 
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, HIGH); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);  
        writeRegisters();   
      break;    

      case 10:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, HIGH); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);  
        writeRegisters();    
      break;   

      case 11:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, HIGH);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, LOW);  
        writeRegisters();    
      break;   

      case 12:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, HIGH);     
        setRegisterPin(24, LOW);  
        writeRegisters();    
      break;   

      case 13:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, HIGH);  
        writeRegisters();    
      break;   

      default:
        setRegisterPin(11, LOW);
        setRegisterPin(12, LOW);
        setRegisterPin(13, LOW);
        setRegisterPin(14, LOW);
        setRegisterPin(15, LOW);
        setRegisterPin(16, LOW);
        setRegisterPin(17, LOW);
        setRegisterPin(18, LOW);
        setRegisterPin(19, LOW);
        setRegisterPin(20, LOW); 
        setRegisterPin(21, LOW); 
        setRegisterPin(22, LOW);     
        setRegisterPin(23, LOW);     
        setRegisterPin(24, HIGH);        
    }   

    //send MIDI
    usbMIDI.sendControlChange(12, MappedTouchXVal, channel);    
    //Debug log
    Serial.println("x: ");
    //limit output frequency
    Serial.println(MappedTouchXVal);                                        
    delay(10);
  }

void TouchYSend()
  {
    int stateY;
  
    if((MappedTouchYVal > 0) && (MappedTouchYVal < 6))
    {
      stateY = 0;
    }  
    if((MappedTouchYVal > 5) && (MappedTouchYVal < 17))
    {
      stateY = 1;
    }  
    if((MappedTouchYVal > 16) && (MappedTouchYVal < 28))
    {
      stateY = 2;
    }  
    if((MappedTouchYVal > 27) && (MappedTouchYVal < 45))
    {
      stateY = 3;
    }  
    if((MappedTouchYVal > 44) && (MappedTouchYVal < 56))
    { 
      stateY = 4;
    }  
    if((MappedTouchYVal > 55) && (MappedTouchYVal < 80))
    {
      stateY = 5;
    }  
    if((MappedTouchYVal > 79) && (MappedTouchYVal < 90))
    {
      stateY = 6;
    }  
    if((MappedTouchYVal > 89) && (MappedTouchYVal < 98))
    {
      stateY = 7;
    }    
    if((MappedTouchYVal > 97) && (MappedTouchYVal < 107))
    {
      stateY = 8;
    }    
    if((MappedTouchYVal > 106) && (MappedTouchYVal < 118))
    {
      stateY = 9;
    }    
    if((MappedTouchYVal > 117) && (MappedTouchYVal < 128))
    {
      stateY = 10;
    }    
     
    switch (stateY) 
    {
      case 0:
        setRegisterPin(0, HIGH);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW);       
      writeRegisters();      
      
      break;
      
      case 1:
        setRegisterPin(0, LOW);
        setRegisterPin(1, HIGH);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW);       
        writeRegisters(); 
      break;
      
      case 2:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, HIGH);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW);       
        writeRegisters();    
      break;
      
      case 3:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, HIGH);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW);       
        writeRegisters(); 
      break;  
  
      case 4:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, HIGH);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW); 
        writeRegisters();    
      break; 
  
      case 5:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, HIGH);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW); 
        writeRegisters();    
      break; 
  
      case 6:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, HIGH);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW); 
        writeRegisters();   
      break;
  
      case 7:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, HIGH);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW); 
        writeRegisters();   
      break;
       
      case 8:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, HIGH);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW); 
        writeRegisters();   
      break;       
       
      case 9: 
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, HIGH); 
        setRegisterPin(10, LOW); 
        writeRegisters();   
      break;    

      case 10:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, HIGH); 
        writeRegisters();    
      break;    
      
      default:
        setRegisterPin(0, LOW);
        setRegisterPin(1, LOW);
        setRegisterPin(2, LOW);
        setRegisterPin(3, LOW);
        setRegisterPin(4, LOW);
        setRegisterPin(5, LOW);
        setRegisterPin(6, LOW);      
        setRegisterPin(7, LOW);
        setRegisterPin(8, LOW);
        setRegisterPin(9, LOW); 
        setRegisterPin(10, LOW); 
        writeRegisters();     
    }      

        usbMIDI.sendControlChange(12, MappedTouchYVal, channel);
        Serial.println("y: ");
        Serial.println(MappedTouchYVal);
        delay(10);
  }    

void Touchscreen()                
  {
    //read values
    int TouchX = readX();
    int TouchY = readY();
   
    //adjust and invert x-axis values
    TouchX = TouchX-100;
    TouchX = abs(TouchX-850);
        
    TouchY = abs(TouchY-100);
    
    //map value
    if((TouchX > 40) && (TouchY < 850))
    {
      //map MIDI                
      MappedTouchXVal = map(TouchX, 30, 880, 0, 127);
      MappedTouchYVal = map(TouchY, 30, 800, 0, 127);
  
      //call LED-setting functions
      TouchYSend();
      TouchXSend();
           
    }   
  }

  

//____________________________________________________________ROTARY POTIS____________________________________________________________

void RotaryPotis()
  {
    // set 12. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,HIGH);
    digitalWrite(PotMultiplexerSelectB,HIGH);
    digitalWrite(PotMultiplexerSelectC,LOW);
    digitalWrite(PotMultiplexerSelectD,HIGH);
    delayMicroseconds(50);          
    RotaryPot1=analogRead(Multiplexer1Kanal);
    
    // set 2. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,HIGH);
    digitalWrite(PotMultiplexerSelectB,LOW);
    digitalWrite(PotMultiplexerSelectC,LOW);
    digitalWrite(PotMultiplexerSelectD,LOW);
    delayMicroseconds(50);          
    RotaryPot2=analogRead(Multiplexer1Kanal);
  
    // set 3. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,LOW);
    digitalWrite(PotMultiplexerSelectB,HIGH);
    digitalWrite(PotMultiplexerSelectC,LOW);
    digitalWrite(PotMultiplexerSelectD,LOW);
    delayMicroseconds(50);          
    RotaryPot3=analogRead(Multiplexer1Kanal);
    
    // set 4. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,HIGH);
    digitalWrite(PotMultiplexerSelectB,HIGH);
    digitalWrite(PotMultiplexerSelectC,LOW);
    digitalWrite(PotMultiplexerSelectD,LOW);
    delayMicroseconds(50);          
    RotaryPot4=analogRead(Multiplexer1Kanal);
    
    // set 5. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,LOW);
    digitalWrite(PotMultiplexerSelectB,LOW);
    digitalWrite(PotMultiplexerSelectC,HIGH);
    digitalWrite(PotMultiplexerSelectD,LOW);
    delayMicroseconds(50);          
    RotaryPot5=analogRead(Multiplexer1Kanal);
    
    // set 6. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,HIGH);
    digitalWrite(PotMultiplexerSelectB,LOW);
    digitalWrite(PotMultiplexerSelectC,HIGH);
    digitalWrite(PotMultiplexerSelectD,LOW);
    delayMicroseconds(50);          
    RotaryPot6=analogRead(Multiplexer1Kanal);
  
    // set 11. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,LOW);
    digitalWrite(PotMultiplexerSelectB,HIGH);
    digitalWrite(PotMultiplexerSelectC,LOW);
    digitalWrite(PotMultiplexerSelectD,HIGH);
    delayMicroseconds(50);          
    RotaryPot7=analogRead(Multiplexer1Kanal);
    
   
    NewRotaryPotVal1 = RotaryPot1;
    //check if new value bigger than threshold of 35
    if (abs(NewRotaryPotVal1 - OldRotaryPotVal1) >= 35)
    {
      //map values for MIDI
      MappedRotaryPotVal1 = map(NewRotaryPotVal1, 15, 1023, 0, 127);
      //check if poti is being used
      if (abs(MappedRotaryPotVal1 - NewMappedRotaryPotVal1) >= 1)
      {
      //send MIDI
        usbMIDI.sendControlChange(1, MappedRotaryPotVal1, channel);
        Serial.println("__________RotaryPot1__________");
        Serial.print(MappedRotaryPotVal1);
        delay(10);
      }
      //reset for next comparison 
      OldRotaryPotVal1 = NewRotaryPotVal1;
      NewMappedRotaryPotVal1 = MappedRotaryPotVal1;
     
     //map values for LEDs
     MappedLEDRotaryPoti1Val = map(MappedRotaryPotVal1,0,127,0,255);
     //dim LEDs
     analogWrite(VolumeLED, MappedLEDRotaryPoti1Val);
      
    } 
   
    NewRotaryPotVal2 = RotaryPot2;
    if (abs(NewRotaryPotVal2 - OldRotaryPotVal2) >= RotaryPotThreshold) 
    {
      MappedRotaryPotVal2 = map(NewRotaryPotVal2, 10, 1023, 0, 127);
      if (abs(MappedRotaryPotVal2 - NewMappedRotaryPotVal2) >= 1)
      {
        usbMIDI.sendControlChange(2, MappedRotaryPotVal2, channel);
        Serial.println("__________RotaryPot2__________");
        Serial.print(MappedRotaryPotVal2);
        delay(10);
      }
      OldRotaryPotVal2 = NewRotaryPotVal2;
      NewMappedRotaryPotVal2 = MappedRotaryPotVal2;
    }   
    
    NewRotaryPotVal3 = RotaryPot3;
    if (abs(NewRotaryPotVal3 - OldRotaryPotVal3) >= RotaryPotThreshold) 
    {
      MappedRotaryPotVal3 = map(NewRotaryPotVal3, 10, 1023, 0, 127);
      if (abs(MappedRotaryPotVal3 - NewMappedRotaryPotVal3) >= 1) 
      {
        usbMIDI.sendControlChange(3, MappedRotaryPotVal3, channel);
        Serial.println("__________RotaryPot3__________");
        Serial.print(MappedRotaryPotVal3);
        delay(10);
      }
      OldRotaryPotVal3 = NewRotaryPotVal3;
      NewMappedRotaryPotVal3 = MappedRotaryPotVal3;
    }  
   
    NewRotaryPotVal4 = RotaryPot4;
    if (abs(NewRotaryPotVal4 - OldRotaryPotVal4) >= RotaryPotThreshold) 
    {  
      MappedRotaryPotVal4 = map(NewRotaryPotVal4, 10, 1023, 0, 127);
      if (abs(MappedRotaryPotVal4 - NewMappedRotaryPotVal4) >= 1) 
      {
        usbMIDI.sendControlChange(4, MappedRotaryPotVal4, channel);
        Serial.println("__________RotaryPot4__________");
        Serial.print(MappedRotaryPotVal4);
        delay(10);
      }
      OldRotaryPotVal4 = NewRotaryPotVal4;
      NewMappedRotaryPotVal4 = MappedRotaryPotVal4;  
    }    
   
    NewRotaryPotVal5 = RotaryPot5;
    if (abs(NewRotaryPotVal5 - OldRotaryPotVal5) >= RotaryPotThreshold) 
    {  
      MappedRotaryPotVal5 = map(NewRotaryPotVal5, 10, 1023, 0, 127);
      if (abs(MappedRotaryPotVal5 - NewMappedRotaryPotVal5) >= 1) 
      {
        usbMIDI.sendControlChange(5, MappedRotaryPotVal5, channel);
        Serial.println("__________RotaryPot5__________");
        Serial.print(MappedRotaryPotVal5);
        delay(10);
      }
      OldRotaryPotVal5 = NewRotaryPotVal5;
      NewMappedRotaryPotVal5 = MappedRotaryPotVal5;  
    }  
    
    NewRotaryPotVal6 = RotaryPot6;
    if (abs(NewRotaryPotVal6 - OldRotaryPotVal6) >= RotaryPotThreshold) 
    {  
      MappedRotaryPotVal6 = map(NewRotaryPotVal6, 10, 1023, 0, 127);
      if (abs(MappedRotaryPotVal6 - NewMappedRotaryPotVal6) >= 1) 
      {
        usbMIDI.sendControlChange(6, MappedRotaryPotVal6, channel);
        Serial.println("__________RotaryPot6__________");
        Serial.print(MappedRotaryPotVal6);
        delay(10);
      }
      OldRotaryPotVal6 = NewRotaryPotVal6;
      NewMappedRotaryPotVal6 = MappedRotaryPotVal6;  
    }  
  
      NewRotaryPotVal7 = RotaryPot7;
    if (abs(NewRotaryPotVal7 - OldRotaryPotVal7) >= RotaryPotThreshold) 
    {  
      MappedRotaryPotVal7 = map(NewRotaryPotVal7, 10, 1023, 0, 127);
      if (abs(MappedRotaryPotVal7 - NewMappedRotaryPotVal7) >= 1) 
      {
        usbMIDI.sendControlChange(7, MappedRotaryPotVal7, channel);
        Serial.println("__________RotaryPot7__________");
        Serial.print(MappedRotaryPotVal7);
        delay(10);
      }
      OldRotaryPotVal7 = NewRotaryPotVal7;
      NewMappedRotaryPotVal7 = MappedRotaryPotVal7;  
    }        
  }

//_________________________________________________________FADER POTIS_______________________________________________________  

void FaderPotis()
  { 
    set 7. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,LOW);
    digitalWrite(PotMultiplexerSelectB,HIGH);
    digitalWrite(PotMultiplexerSelectC,HIGH);
    digitalWrite(PotMultiplexerSelectD,LOW);
    delayMicroseconds(50);          
    FaderPot1=analogRead(Multiplexer1Kanal); 
    
    set 8. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,HIGH);
    digitalWrite(PotMultiplexerSelectB,HIGH);
    digitalWrite(PotMultiplexerSelectC,HIGH);
    digitalWrite(PotMultiplexerSelectD,LOW);
    delayMicroseconds(50);          
    FaderPot2=analogRead(Multiplexer1Kanal); 
    
    set 9. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,LOW);
    digitalWrite(PotMultiplexerSelectB,LOW);
    digitalWrite(PotMultiplexerSelectC,LOW);
    digitalWrite(PotMultiplexerSelectD,HIGH);
    delayMicroseconds(50);          
    FaderPot3=analogRead(Multiplexer1Kanal); 
    
    set 10. multiplexer-channel
    digitalWrite(PotMultiplexerSelectA,HIGH);
    digitalWrite(PotMultiplexerSelectB,LOW);
    digitalWrite(PotMultiplexerSelectC,LOW);
    digitalWrite(PotMultiplexerSelectD,HIGH);
    delayMicroseconds(50);          
    FaderPot4=analogRead(Multiplexer1Kanal); 
    
    set 11. multiplexer-channel
    NewFaderPotVal1 = FaderPot1;
    if (abs(NewFaderPotVal1 - OldFaderPotVal1) >= FaderPotThreshold)
    {
      MappedFaderPotVal1 = map(NewFaderPotVal1, 10, 1023, 0, 127);
      if (abs(MappedFaderPotVal1 - NewMappedFaderPotVal1) >= 1)
      {
        usbMIDI.sendControlChange(8, MappedFaderPotVal1, channel);
        Serial.print("Fader1:");
        Serial.println(MappedFaderPotVal1);
        delay(10);
      }
      OldFaderPotVal1 = NewFaderPotVal1;
      NewMappedFaderPotVal1 = MappedFaderPotVal1;
    }
    
    NewFaderPotVal2 = FaderPot2;
    if (abs(NewFaderPotVal2 - OldFaderPotVal2) >= FaderPotThreshold) 
    {
      MappedFaderPotVal2 = map(NewFaderPotVal2, 10, 1023, 0, 127);
      if (abs(MappedFaderPotVal2 - NewMappedFaderPotVal2) >= 1) 
      {
        usbMIDI.sendControlChange(9, MappedFaderPotVal2, channel);
        Serial.print("Fader2:");
        Serial.println(MappedFaderPotVal2);
        delay(10);
      }
      OldFaderPotVal2 = NewFaderPotVal2;
      NewMappedFaderPotVal2 = MappedFaderPotVal2;
    }  
    
    NewFaderPotVal3 = FaderPot3;
    if (abs(NewFaderPotVal3 - OldFaderPotVal3) >= FaderPotThreshold) 
    {
      MappedFaderPotVal3 = map(NewFaderPotVal3, 10, 1023, 0, 127);
      if (abs(MappedFaderPotVal3 - NewMappedFaderPotVal3) >= 1) 
      {
        usbMIDI.sendControlChange(10, MappedFaderPotVal3, channel);
        Serial.print("Fader3:");
        Serial.println(MappedFaderPotVal3);
        delay(10);
      }
      OldFaderPotVal3 = NewFaderPotVal3;
      NewMappedFaderPotVal3 = MappedFaderPotVal3;
    }  
    
    NewFaderPotVal4 = FaderPot4;
    if (abs(NewFaderPotVal4 - OldFaderPotVal4) >= FaderPotThreshold) 
    {
      MappedFaderPotVal4 = map(NewFaderPotVal4, 10, 1023, 0, 127);
      if (abs(MappedFaderPotVal4 - NewMappedFaderPotVal4) >= 1) 
      {
        usbMIDI.sendControlChange(11, MappedFaderPotVal4, channel);
        Serial.print("Fader4:");
        Serial.println(MappedFaderPotVal4);
        delay(10);
      }
      OldFaderPotVal4 = NewFaderPotVal4;
      NewMappedFaderPotVal4 = MappedFaderPotVal4;
    }    
  }
  
void loop() 
{
  //set Teensy LED
  digitalWrite(TeensyLED, HIGH);
  
  Touchscreen();
  RotaryPotis();
  FaderPotis();

  //ignore incoming MIDI messages 
  while (usbMIDI.read()) 
  {
  }
  
}

