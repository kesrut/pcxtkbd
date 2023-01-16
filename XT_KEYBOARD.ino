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
  translationTable[PS2_KEY_L_ALT] = 0x38 ; 
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
  translationTable[PS2_KEY_SEMI] = 0x27 ;
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
  translationTable[PS2_KEY_KP_ENTER]=0x01; 
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
  translationTable[PS2_KEY_APOS]=0x28; 
  translationTable[PS2_KEY_COMMA]=0x33;
  translationTable[PS2_KEY_MINUS]=0x0C;
  translationTable[PS2_KEY_SCROLL] = 0x46 ;
  translationTable[PS2_KEY_DOT]=0x34;
  translationTable[PS2_KEY_BACK] =0x2B ;
  translationTable[PS2_KEY_SINGLE] = 0x29 ;
  translationTable[PS2_KEY_DIV]=0x35;
  translationTable[PS2_KEY_SINGLE]=28;    
  translationTable[PS2_KEY_A]=0x1E;
  translationTable[PS2_KEY_B]=0x30;
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
  translationTable[PS2_KEY_V]=0x2F;
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
  pinMode(xt_clk, INPUT_PULLUP) ; 
  digitalWrite(xt_data, LOW); //Turns out the inactive state of the KB DATA line should always be LOW, as HIGH will enter "Manufacturing mode" on an IBM XT, continuously toggling the CLK line at 9.1Hz.
  pinMode(xt_data, OUTPUT);
  }

void _write(unsigned char value)
{ 
 while (digitalRead(xt_clk) != HIGH);  //Wait here until host releases CLK

  digitalWrite(xt_clk, LOW) ; //Pull it low before switching to output
  pinMode(xt_clk, OUTPUT); //RTS
  pinMode(xt_data, INPUT_PULLUP); //Let data go high
   delayMicroseconds(120) ; 
  // while (digitalRead(xt_data) != HIGH); //We could wait here, we could cancel the data, we could do many things if we don't get a CTS but.. nah.
   pinMode(xt_clk, INPUT_PULLUP); //Let clk go high for start bit
   delayMicroseconds(66) ;
   digitalWrite(xt_clk, LOW) ; 
  pinMode(xt_clk, OUTPUT);
   delayMicroseconds(30) ;
   byte i = 0 ; 
   for (i=0; i < 8; i++)
   {
    if (value & 1) {
      pinMode(xt_data, INPUT_PULLUP); //Let data go high
    } else {
      digitalWrite(xt_data, LOW);
      pinMode(xt_data, OUTPUT);
    }
    value = value >> 1;
    //Spec says to have data available 2.5us before and after clock pulse.
     pinMode(xt_clk, INPUT_PULLUP); //Let clk go high 
      delayMicroseconds(95) ;
      digitalWrite(xt_clk, LOW) ; 
      pinMode(xt_clk, OUTPUT);
   } 
   //Go to passive clk high, data low
   delayMicroseconds(20) ;

  pinMode(xt_clk, INPUT_PULLUP); //Let clk go high 
  digitalWrite(xt_data, LOW) ;  //Keep data inactive low
  pinMode(xt_data, OUTPUT);
 delay(1) ;
}

byte i = 0 ;
unsigned char ascan;

void loop() 
{
  if( keyboard.available())
  {
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
    switch (c & 0xff)
    {
      case PS2_KEY_L_CTRL: _write(0xE0); _write(0x1D); break ;
      case PS2_KEY_R_ALT: _write(0xE0); _write(0x38); break ;
      case PS2_KEY_INSERT: _write(0xE0); _write(0x52); break ;
      case PS2_KEY_HOME: _write(0xE0); _write(0x47); break ;
      case PS2_KEY_END: _write(0xE0); _write(0x4F); break ;
      case PS2_KEY_DN_ARROW: _write(0xE0); _write(0x50); break ;
      case PS2_KEY_PGDN: _write(0xE0); _write(0x51); break ;
      case PS2_KEY_L_ARROW: _write(0xE0); _write(0x4B); break ;
      case PS2_KEY_R_ARROW: _write(0xE0); _write(0x4D); break ;
      case PS2_KEY_UP_ARROW: _write(0xE0); _write(0x48); break ;
      case PS2_KEY_PGUP: _write(0xE0); _write(0x49); break ;
      case PS2_KEY_DELETE: _write(0xE0); _write(0x53); break ;      
      default:
      {
      ascan = translationTable[c & 0xff];
     _write(ascan) ; break ;
      }
    }
  }

  if( ( c & PS2_BREAK ) ) 
  {
    switch (c & 0xff)
    {
      case PS2_KEY_L_CTRL: _write(0xE0); _write(0x1D | 0x80); break ;
      case PS2_KEY_R_ALT: _write(0xE0); _write(0x38 | 0x80); break ;
      case PS2_KEY_INSERT: _write(0xE0); _write(0x52 | 0x80); break ;
      case PS2_KEY_HOME: _write(0xE0); _write(0x47 | 0x80); break ;
      case PS2_KEY_END: _write(0xE0); _write(0x4F | 0x80); break ;
      case PS2_KEY_DN_ARROW: _write(0xE0); _write(0x50 | 0x80); break ;
      case PS2_KEY_PGDN: _write(0xE0); _write(0x51 | 0x80); break ;
      case PS2_KEY_L_ARROW: _write(0xE0); _write(0x4B | 0x80); break ;
      case PS2_KEY_R_ARROW: _write(0xE0); _write(0x4D | 0x80); break ;
      case PS2_KEY_UP_ARROW: _write(0xE0); _write(0x48 | 0x80); break ;
      case PS2_KEY_PGUP: _write(0xE0); _write(0x49 | 0x80); break ;
      case PS2_KEY_DELETE: _write(0xE0); _write(0x53 | 0x80); break ;   
      default:
      {
        ascan = translationTable[c & 0xff];
      _write(ascan | 0x80) ;
      }
    }
  }
  }

  if (digitalRead(xt_clk) == LOW) // power-on self test
  {
    delay(10);
      _write(0xAA) ; 
      while ( keyboard.available()) keyboard.read(); //Discard buffer on reset
  }
}
