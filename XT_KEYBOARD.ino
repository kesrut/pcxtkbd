#include <PS2KeyAdvanced.h>

#define ps_clk 3  // PS CLOCK DATA
#define ps_data 4 // PS DATA PIN

uint16_t c;

PS2KeyAdvanced keyboard;

unsigned char translationTable [256];

#define xt_clk 2 // XT CLOCK PIN
#define xt_data 5 // XT DATA PIN

void setupTable () {
  for (int i=0;i<256;i++) {
    translationTable[i]=0xff;  
  }
  translationTable[PS2_KEY_SCROLL]=0x46;
  translationTable[PS2_KEY_CAPS]=0x3A;
  translationTable[PS2_KEY_PAUSE]=0x5f;
  translationTable[PS2_KEY_L_SHIFT]=0x2A;
  translationTable[PS2_KEY_R_SHIFT]=0x36;
  translationTable[PS2_KEY_L_CTRL]=0x1D;
  translationTable[PS2_KEY_L_ARROW]=0x4B;
  translationTable[PS2_KEY_R_ARROW]=0x4D;
  translationTable[PS2_KEY_UP_ARROW]=0x48;
  translationTable[PS2_KEY_DN_ARROW]=0x50;
  translationTable[PS2_KEY_DELETE]=0x53;
  translationTable[PS2_KEY_ESC]=0x01;
  translationTable[PS2_KEY_BS]=0x0E;
  translationTable[PS2_KEY_TAB]=0x0F;
  translationTable[PS2_KEY_ENTER]=0x1C;
  translationTable[PS2_KEY_SPACE]=0x39;
  translationTable[PS2_KEY_KP0]=0x52;
  translationTable[PS2_KEY_KP1]=0x4F;
  translationTable[PS2_KEY_KP2]=0x50;
  translationTable[PS2_KEY_KP3]=0x51;
  translationTable[PS2_KEY_KP4]=0x4B;
  translationTable[PS2_KEY_KP5]=0x4C;
  translationTable[PS2_KEY_KP6]=0x4D;
  translationTable[PS2_KEY_KP7]=0x47;
  translationTable[PS2_KEY_KP8]=0x48;
  translationTable[PS2_KEY_KP9]=0x49;
  translationTable[PS2_KEY_OPEN_SQ]=0x1A;
  translationTable[PS2_KEY_CLOSE_SQ]=0x1B;
  translationTable[PS2_LOCK_NUM]=0x45;
  //translationTable[PS2_KEY_KP_DOT]=0x53;
  translationTable[PS2_KEY_KP_PLUS]=0x4E;
  translationTable[PS2_KEY_KP_MINUS]=0x4A;
  translationTable[PS2_KEY_KP_TIMES]=0x37; 
  translationTable[PS2_KEY_KP_DIV]=0x35; 
  translationTable[PS2_KEY_0]=0x0B;
  translationTable[PS2_KEY_1]=0x02;
  translationTable[PS2_KEY_2]=0x03;
  translationTable[PS2_KEY_3]=0x04;
  translationTable[PS2_KEY_4]=0x05;
  translationTable[PS2_KEY_5]=0x06;
  translationTable[PS2_KEY_6]=0x07;
  translationTable[PS2_KEY_7]=0x08;
  translationTable[PS2_KEY_8]=0x09;
  translationTable[PS2_KEY_9]=0x0A;
  //translationTable[PS2_KEY_APOS]=0x28; 
  translationTable[PS2_KEY_COMMA]=0x33;
  translationTable[PS2_KEY_MINUS]=0x0C;
  translationTable[PS2_KEY_DOT]=0x34;
  translationTable[PS2_KEY_DIV]=0x35;
  translationTable[PS2_KEY_SINGLE]=28;    
  translationTable[PS2_KEY_A]=0x1E;
  translationTable[PS2_KEY_B]=0x39;
  translationTable[PS2_KEY_C]=0x2E;
  translationTable[PS2_KEY_D]=0x20;
  translationTable[PS2_KEY_E]=0x12;
  translationTable[PS2_KEY_F]=0x21;
  translationTable[PS2_KEY_G]=0x22;
  translationTable[PS2_KEY_H]=0x23;
  translationTable[PS2_KEY_I]=0x17;
  translationTable[PS2_KEY_J]=0x24;
  translationTable[PS2_KEY_K]=0x25;
  translationTable[PS2_KEY_L]=0x26;
  translationTable[PS2_KEY_M]=0x32;
  translationTable[PS2_KEY_N]=0x31;
  translationTable[PS2_KEY_O]=0x18;
  translationTable[PS2_KEY_P]=0x19;
  translationTable[PS2_KEY_Q]=0x10;
  translationTable[PS2_KEY_R]=0x13;
  translationTable[PS2_KEY_S]=0x1F;
  translationTable[PS2_KEY_T]=0x14;
  translationTable[PS2_KEY_U]=0x16;
  translationTable[PS2_KEY_V]=0x2E;
  translationTable[PS2_KEY_W]=0x11;
  translationTable[PS2_KEY_X]=0x2D;
  translationTable[PS2_KEY_Y]=0x15;
  translationTable[PS2_KEY_Z]=0x2c;
  translationTable[PS2_KEY_EQUAL]=0x0D;  
  translationTable[PS2_KEY_F1]=0x3B;
  translationTable[PS2_KEY_F2]=0x3C;
  translationTable[PS2_KEY_F3]=0x3D;
  translationTable[PS2_KEY_F4]=0x3E;
  translationTable[PS2_KEY_F5]=0x3F;
  translationTable[PS2_KEY_F6]=0x40;
  translationTable[PS2_KEY_F7]=0x41;
  translationTable[PS2_KEY_F8]=0x42;
  translationTable[PS2_KEY_F9]=0x43;
  translationTable[PS2_KEY_F10]=0x44;
  translationTable[PS2_KEY_F11]=0x85;
  translationTable[PS2_KEY_F12]=0x86;
}

void setup() 
{
  setupTable () ; 
  keyboard.begin( ps_data, ps_clk );
#ifdef DEBUG
  Serial.begin(9600) ; 
#endif  
  pinMode(xt_clk, OUTPUT) ; 
  pinMode(xt_data, OUTPUT) ; 
  digitalWrite(xt_clk, HIGH) ; 
  digitalWrite(xt_data, HIGH) ; 
}

void _write(unsigned char value)
{ 
   while (digitalRead(xt_clk) != HIGH) ; 
   unsigned char bits[8] ;
   byte p = 0 ; 
   byte j = 0 ;
   for (j=0 ; j < 8; j++)
   {
     if (value & 1) bits[j] = 1 ;
     else bits[j] = 0 ; 
     value = value >> 1 ; 
   }
   digitalWrite(xt_clk, LOW) ; 
   digitalWrite(xt_data, HIGH) ; 
   delayMicroseconds(120) ; 
   digitalWrite(xt_clk, HIGH) ; 
   delayMicroseconds(66) ;
   digitalWrite(xt_clk, LOW) ; 
   delayMicroseconds(30) ;
   digitalWrite(xt_clk, HIGH) ; 
   byte i = 0 ; 
   for (i=0; i < 8; i++)
   {
      digitalWrite(xt_clk, HIGH) ; 
      digitalWrite(xt_data, bits[p]) ; 
      delayMicroseconds(95) ;
      digitalWrite(xt_clk, LOW) ;
      digitalWrite(xt_data, LOW) ; 
      p++ ; 
   } 
   digitalWrite(xt_clk, HIGH) ; 
   digitalWrite(xt_data, LOW) ;  
   delay(1) ;
}

byte i = 0 ;
unsigned char ascan;

void loop() 
{
  if( keyboard.available() )
  {
  // read the next key
  c = keyboard.read();
  if( c > 0 )
    {
#if defined(ARDUINO_ARCH_AVR)
    Serial.print( F( "Value " ) );
    Serial.print( c, HEX );
    Serial.print( F( " - Status Bits " ) );
    Serial.print( c >> 8, HEX );
    Serial.print( F( "  Code " ) );
#elif defined(ARDUINO_ARCH_SAM)
    Serial.print( "Value " );
    Serial.print( c, HEX );
    Serial.print( " - Status Bits " );
    Serial.print( c >> 8, HEX );
    Serial.print( "  Code " );
#endif
    Serial.println( c & 0xFF, HEX );
    }
    if( !( c & PS2_BREAK ) ) 
  {
    ascan = translationTable[c & 0xff];
    _write(ascan ) ;
  }

  if( ( c & PS2_BREAK ) ) 
  {
     ascan = translationTable[c & 0xff];
     _write(ascan | 0x80) ;
  }
  }
  
  if (digitalRead(xt_clk) == LOW) // power-on self test
  {
    delay(10) ;
    _write(0xAA) ;
  }
}
