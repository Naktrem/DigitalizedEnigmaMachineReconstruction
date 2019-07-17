#include <LedControl.h>
#include <MaxMatrix.h>
 
LedControl lc = LedControl(PB6,PB8,PB7,6);
//DIN,CLK,LOAD

 double counter = 0; 
 double letterCounter = 0; 
 int lco = 0;
 int aState;
 int aLastState;  
 int setRotor = 0;
 int held = 0;
 int rotor1 = 0;
 int rotor2 = 0;
 int rotor3 = 0;
 char* currLetter;

 int r1[26][2]  = {{0, 15 }, {1, 4 }, {2, 25 }, {3, 20 }, {4, 14 }, {5, 7 }, {6, 23 }, {7, 18 }, {8, 2 }, {9, 21 }, {10, 5 }, {11, 12 }, {12, 19 }, {13, 1 }, {14, 6 }, {15, 11 }, {16, 17 }, {17, 8 }, {18, 13 }, {19, 16 }, {20, 9 }, {21, 22 }, {22, 0 }, {23, 24 }, {24, 3 }, {25, 10 }};  
 int r2[26][2]  = {{0, 25 }, {1, 14 }, {2, 20 }, {3, 4 }, {4, 18 }, {5, 24 }, {6, 3 }, {7, 10 }, {8, 5 }, {9, 22 }, {10, 15 }, {11, 2 }, {12, 8 }, {13, 16 }, {14, 23 }, {15, 7 }, {16, 12 }, {17, 21 }, {18, 1 }, {19, 11 }, {20, 6 }, {21, 13 }, {22, 9 }, {23, 17 }, {24, 0 }, {25, 19 }};
 int r3[26][2]  = {{0, 4 }, {1, 7 }, {2, 17 }, {3, 21 }, {4, 23 }, {5, 6 }, {6, 0 }, {7, 14 }, {8, 1 }, {9, 16 }, {10, 20 }, {11, 18 }, {12, 8 }, {13, 12 }, {14, 25 }, {15, 5 }, {16, 11 }, {17, 24 }, {18, 13 }, {19, 22 }, {20, 10 }, {21, 19 }, {22, 15 }, {23, 3 }, {24, 9 }, {25, 2 }};

#define maxDisplays 1 // Number of MAX7219's in use.

byte Buf7219[7]; // "width,height,data[5]" single character buffer.
const int data  = PB15;     // DIN or MOSI
const int load  = PA9;     // CS
const int clock = PA8;     // SCK
  
byte buffer[10];
MaxMatrix m(data, load, clock, maxDisplays);
// Data array is stored in program memory (see memcpy_P for access).
// Parameters are width, height, character data...
// There is a speed improvement for characters with height 8 bits see lib.

PROGMEM const unsigned char CH[] = {
3, 8, B0000000, B0000000, B0000000, B0000000, B0000000, // space
1, 8, B1011111, B0000000, B0000000, B0000000, B0000000, // !
3, 8, B0000011, B0000000, B0000011, B0000000, B0000000, // "
5, 8, B0010100, B0111110, B0010100, B0111110, B0010100, // #
4, 8, B0100100, B1101010, B0101011, B0010010, B0000000, // $
5, 8, B1100011, B0010011, B0001000, B1100100, B1100011, // %
5, 8, B0110110, B1001001, B1010110, B0100000, B1010000, // &
1, 8, B0000011, B0000000, B0000000, B0000000, B0000000, // '
3, 8, B0011100, B0100010, B1000001, B0000000, B0000000, // (
3, 8, B1000001, B0100010, B0011100, B0000000, B0000000, // )
5, 8, B0101000, B0011000, B0001110, B0011000, B0101000, // * 
5, 8, B0001000, B0001000, B0111110, B0001000, B0001000, // +
2, 8, B10110000, B1110000, B0000000, B0000000, B0000000, // ,
4, 8, B0001000, B0001000, B0001000, B0001000, B0000000, // -
2, 8, B1100000, B1100000, B0000000, B0000000, B0000000, // .
4, 8, B1100000, B0011000, B0000110, B0000001, B0000000, // /
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // 0
3, 8, B1000010, B1111111, B1000000, B0000000, B0000000, // 1
4, 8, B1100010, B1010001, B1001001, B1000110, B0000000, // 2
4, 8, B0100010, B1000001, B1001001, B0110110, B0000000, // 3
4, 8, B0011000, B0010100, B0010010, B1111111, B0000000, // 4
4, 8, B0100111, B1000101, B1000101, B0111001, B0000000, // 5
4, 8, B0111110, B1001001, B1001001, B0110000, B0000000, // 6
4, 8, B1100001, B0010001, B0001001, B0000111, B0000000, // 7
4, 8, B0110110, B1001001, B1001001, B0110110, B0000000, // 8
4, 8, B0000110, B1001001, B1001001, B0111110, B0000000, // 9
2, 8, B01010000, B0000000, B0000000, B0000000, B0000000, // :
2, 8, B10000000, B01010000, B0000000, B0000000, B0000000, // ;
3, 8, B0010000, B0101000, B1000100, B0000000, B0000000, // <
3, 8, B0010100, B0010100, B0010100, B0000000, B0000000, // =
3, 8, B1000100, B0101000, B0010000, B0000000, B0000000, // >
4, 8, B0000010, B1011001, B0001001, B0000110, B0000000, // ?
5, 8, B0111110, B1001001, B1010101, B1011101, B0001110, // @
4, 8, B1111110, B0010001, B0010001, B1111110, B0000000, // A
4, 8, B1111111, B1001001, B1001001, B0110110, B0000000, // B
4, 8, B0111110, B1000001, B1000001, B0100010, B0000000, // C
4, 8, B1111111, B1000001, B1000001, B0111110, B0000000, // D
4, 8, B1111111, B1001001, B1001001, B1000001, B0000000, // E
4, 8, B1111111, B0001001, B0001001, B0000001, B0000000, // F
4, 8, B0111110, B1000001, B1001001, B1111010, B0000000, // G
4, 8, B1111111, B0001000, B0001000, B1111111, B0000000, // H
3, 8, B1000001, B1111111, B1000001, B0000000, B0000000, // I
4, 8, B0110000, B1000000, B1000001, B0111111, B0000000, // J
4, 8, B1111111, B0001000, B0010100, B1100011, B0000000, // K
4, 8, B1111111, B1000000, B1000000, B1000000, B0000000, // L
5, 8, B1111111, B0000010, B0001100, B0000010, B1111111, // M
5, 8, B1111111, B0000100, B0001000, B0010000, B1111111, // N
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // O
4, 8, B1111111, B0001001, B0001001, B0000110, B0000000, // P
4, 8, B0111110, B1000001, B1000001, B10111110, B0000000, // Q
4, 8, B1111111, B0001001, B0001001, B1110110, B0000000, // R
4, 8, B1000110, B1001001, B1001001, B0110010, B0000000, // S
5, 8, B0000001, B0000001, B1111111, B0000001, B0000001, // T
4, 8, B0111111, B1000000, B1000000, B0111111, B0000000, // U
5, 8, B0001111, B0110000, B1000000, B0110000, B0001111, // V
5, 8, B0111111, B1000000, B0111000, B1000000, B0111111, // W
5, 8, B1100011, B0010100, B0001000, B0010100, B1100011, // X
5, 8, B0000111, B0001000, B1110000, B0001000, B0000111, // Y
4, 8, B1100001, B1010001, B1001001, B1000111, B0000000, // Z
2, 8, B1111111, B1000001, B0000000, B0000000, B0000000, // [
4, 8, B0000001, B0000110, B0011000, B1100000, B0000000, // backslash
2, 8, B1000001, B1111111, B0000000, B0000000, B0000000, // ]
3, 8, B0000010, B0000001, B0000010, B0000000, B0000000, // hat
4, 8, B1000000, B1000000, B1000000, B1000000, B0000000, // _
2, 8, B0000001, B0000010, B0000000, B0000000, B0000000, // `
4, 8, B0100000, B1010100, B1010100, B1111000, B0000000, // a
4, 8, B1111111, B1000100, B1000100, B0111000, B0000000, // b
4, 8, B0111000, B1000100, B1000100, B0000000, B0000000, // c // JFM MOD.
4, 8, B0111000, B1000100, B1000100, B1111111, B0000000, // d
4, 8, B0111000, B1010100, B1010100, B0011000, B0000000, // e
3, 8, B0000100, B1111110, B0000101, B0000000, B0000000, // f
4, 8, B10011000, B10100100, B10100100, B01111000, B0000000, // g
4, 8, B1111111, B0000100, B0000100, B1111000, B0000000, // h
3, 8, B1000100, B1111101, B1000000, B0000000, B0000000, // i
4, 8, B1000000, B10000000, B10000100, B1111101, B0000000, // j
4, 8, B1111111, B0010000, B0101000, B1000100, B0000000, // k
3, 8, B1000001, B1111111, B1000000, B0000000, B0000000, // l
5, 8, B1111100, B0000100, B1111100, B0000100, B1111000, // m
4, 8, B1111100, B0000100, B0000100, B1111000, B0000000, // n
4, 8, B0111000, B1000100, B1000100, B0111000, B0000000, // o
4, 8, B11111100, B0100100, B0100100, B0011000, B0000000, // p
4, 8, B0011000, B0100100, B0100100, B11111100, B0000000, // q
4, 8, B1111100, B0001000, B0000100, B0000100, B0000000, // r
4, 8, B1001000, B1010100, B1010100, B0100100, B0000000, // s
3, 8, B0000100, B0111111, B1000100, B0000000, B0000000, // t
4, 8, B0111100, B1000000, B1000000, B1111100, B0000000, // u
5, 8, B0011100, B0100000, B1000000, B0100000, B0011100, // v
5, 8, B0111100, B1000000, B0111100, B1000000, B0111100, // w
5, 8, B1000100, B0101000, B0010000, B0101000, B1000100, // x
4, 8, B10011100, B10100000, B10100000, B1111100, B0000000, // y
3, 8, B1100100, B1010100, B1001100, B0000000, B0000000, // z
3, 8, B0001000, B0110110, B1000001, B0000000, B0000000, // {
1, 8, B1111111, B0000000, B0000000, B0000000, B0000000, // |
3, 8, B1000001, B0110110, B0001000, B0000000, B0000000, // }
4, 8, B0001000, B0000100, B0001000, B0000100, B0000000, // ~
};
// the setup function runs once when you press reset or power the board

char chars[26][2] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

 

void setup() {
  // initialize digital pin PB1 as an output.
  pinMode(PC13, OUTPUT);
  pinMode(PB12, INPUT);
  pinMode(PB13, INPUT);
  pinMode(PB14, INPUT);
  pinMode(PB15, INPUT);
  pinMode(PB9, INPUT);
  pinMode(PA8, INPUT);
  pinMode(PA9, INPUT);
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0, 15);
  aLastState = digitalRead(PB13); 
  lc.setDigit(0,0,0,false);
  lc.setDigit(0,1,0,false);
  lc.setDigit(0,2,0,false);
  lc.setDigit(0,3,0,false);
  lc.setDigit(0,4,0,false);
  lc.setDigit(0,5,0,false);
  m.init();
  m.setIntensity(15);
}

int runThrough(int input, boolean forward, int pos, int rotor[26][2]) {

    if (forward) {
      input = (input+pos) % 26;

      return rotor[input][1];
    } else {
      for (int i = 0; i< 26; i++) {
        if (input == rotor[i][1]) {
          int output = (rotor[i][0]-pos);
          while (output<0) {
            output = 26+output;
          }
          output = output % 26;

          return output;
        }
      }
    }
    return -1;
}


// the loop function runs over and over again forever
void loop() {
  
  if(counter > 26){
    counter = 0;
  }
  if(counter < -0.5){
    counter = 26;
  }

  if(letterCounter > 25){
    letterCounter = 0;
  }
  if(letterCounter < -0.5){
    letterCounter = 25;
  }

   if(setRotor > 2 && digitalRead(PB12) == HIGH){
        Serial.println("Rotor1: " + rotor1);
        Serial.println("Rotor2: " + rotor2);
        Serial.println("Rotor3: " + rotor3);
        int encrypted = 0;
        if(digitalRead(PB9) == HIGH){
          encrypted = runThrough(letterCounter, true, rotor1, r1);
          encrypted = runThrough(letterCounter, true, rotor2, r2);
          encrypted = runThrough(letterCounter, true, rotor3, r3);
          encrypted = runThrough(letterCounter, false, rotor3, r3);
          encrypted = runThrough(letterCounter, false, rotor2, r2);
          encrypted = runThrough(letterCounter, false, rotor1, r1);
        }else{
          encrypted = runThrough(letterCounter, false, rotor1, r1);
          encrypted = runThrough(letterCounter, false, rotor2, r2);
          encrypted = runThrough(letterCounter, false, rotor3, r3);
          encrypted = runThrough(letterCounter, true, rotor3, r3);
          encrypted = runThrough(letterCounter, true, rotor2, r2);
          encrypted = runThrough(letterCounter, true, rotor1, r1);
        }
        if(rotor1 < 26){
          rotor1++;  
          lc.setDigit(0,1,(int)(rotor1/10) % 10,false);
          lc.setDigit(0,0,(int)rotor1 % 10,false); 
        }else{
          rotor1 = 0;
          rotor2++;         
          if(rotor2 < 26){
            rotor2++;
            lc.setDigit(0,3,(int)(rotor2/10) % 10,false);
            lc.setDigit(0,2,(int)rotor2 % 10,false); 
          }else{
            rotor2 = 0;
            rotor3++;
            lc.setDigit(0,3,(int)(rotor2/10) % 10,false);
            lc.setDigit(0,2,(int)rotor2 % 10,false); 
            lc.setDigit(0,5,(int)(rotor3/10) % 10,false);
            lc.setDigit(0,4,(int)rotor3 % 10,false); 
          }
          lc.setDigit(0,1,(int)(rotor1/10) % 10,false);
          lc.setDigit(0,0,(int)rotor1 % 10,false); 
          lc.setDigit(0,3,(int)(rotor2/10) % 10,false);
          lc.setDigit(0,2,(int)rotor2 % 10,false); 
        }

      
        printString(">");
        delay(1000);
        printString(chars[encrypted]);
        delay(1000);
   }
  
  if(setRotor == 0){
    rotor1 = counter;
    lc.setDigit(0,1,(int)(counter/10) % 10,false);
    lc.setDigit(0,0,(int)counter % 10,false); 
  }else if(setRotor == 1){
    rotor2 = counter;
    lc.setDigit(0,3,(int)(counter/10) % 10,false);
    lc.setDigit(0,2,(int)counter % 10,false);
  }else if(setRotor == 2){
    rotor3 = counter;
    lc.setDigit(0,5,(int)(counter/10) % 10,false);
    lc.setDigit(0,4,(int)counter % 10,false);
    
  }
  
  if(digitalRead(PB12) == HIGH){
    delay(500);
    setRotor ++;
    if(setRotor > 2){
      setRotor == 0;
    }
    counter = 0;
  }else{
    held = 0;
  }

  while (digitalRead(PB12) == HIGH){
    held++;
    delay(500);
    if(held > 2){
      lc.setDigit(0,0,0,false);
      lc.setDigit(0,1,0,false);
      lc.setDigit(0,2,0,false);
      lc.setDigit(0,3,0,false);
      lc.setDigit(0,4,0,false);
      lc.setDigit(0,5,0,false);
      counter = 0;
      setRotor = 0;
      aState = 0;
      aLastState = 0;
    }
  }

  aState = digitalRead(PB13); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(PB14) != aState) { 
       counter = counter + 0.5;
       letterCounter = letterCounter + 0.5;
     } else {
       counter = counter - 0.5;
       letterCounter = letterCounter - 0.5;
       }
     Serial.print("Position: ");
     Serial.println(counter);
     if(setRotor > 2){
       currLetter = chars[(int)round(letterCounter)];
       printString(chars[(int)round(letterCounter)]);
     }

   } 
   aLastState = aState;

}

void printString(char* s){
  int col = 0;
  while (*s != 0){
    if (*s < 32) continue;
    char c = *s - 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(col, 0, buffer);
    m.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;   
  }
}
