#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


//led////////////////////////////////////////////////////////////
const int buttonPin = 2;
int buttonState = 0;
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
byte colDataMatrix[8] = { 
   B01111111,
   B10111111,
   B11011111,
   B11101111,
   B11110111,
   B11111011,
   B11111101,
   B11111110
  };
                      
byte rowDataMatrix[8] = { 
    B00011111,
    B01000010,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B01000010,
    B00111100
  };
byte rowDatabutton[8] = { 
    B00000000,
    B11111111,
    B00100100,
    B11111111,
    B01000010,
    B00111100,
    B11111111,
    B00000000
  };
// 定義顯示器顯示的時間 (延遲時間), 預設 1ms
int delay_time = 1;
/////////////////////////////////////////////////////////////////
int cnt = 0;
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int tonePin=5;//蜂鸣器的pin 

///////////////////////////
unsigned long CT=0,PT=0;
int pauseduration=0;
boolean next_tone = true;

void setup() {
  pinMode(tonePin,OUTPUT);//设置蜂鸣器的pin为输出模式


  //led/////////////////////////////////////////////////
  pinMode(buttonPin, INPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  //////////////////////////////////////////////////////
}

void loop() {
  ////撥放音樂////
  if(next_tone){
   int noteDuration = 1000 / noteDurations[cnt];
   tone(5,melody[cnt],noteDuration);
   
   pauseduration= noteDuration * 1.30;
   next_tone=false;
  }
   /////////////
        
  for(int i = 0; i < 8 ; i++){
       //byte colData = colDataMatrix[i];
    digitalWrite(latchPin,LOW);
          //pickDigit(i);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
          //shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    digitalWrite(latchPin,HIGH);
    delay(delay_time);
   }
   
   CT=millis();
   if((CT-PT)>pauseduration){
     cnt++;
     PT=CT;
     next_tone=true;
   }
   if(cnt>8)cnt=0;
  }

