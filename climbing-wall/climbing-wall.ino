//Fun program to run the winning buttons on the climbing wall.  The wall has three arcade buttons along the top
//and pushing each will light up eight LEDs on the wall. Buttons and LED sets will be colour coded (red, yellow,
//green), plus an external rocker switch to control power.  Each set of LEDs will have a shift register (74HC595)
//controlling them, so three outputs per colour, plus three digital inputs for switches, 12 pins total.
//based on code courtesy of EEEnthusiast.com.
//
//For each button press, a series of blink pattern functions are called.
//
//Uses Arduino nano, three 74HC595 shift registers, 24 LEDs (8 ea of green, yellow, red), and three momentary
//push buttons.

const int grn_DS_pin = 12;
const int grn_STCP_pin = 11;
const int grn_SHCP_pin = 10;

const int red_DS_pin = 9;
const int red_STCP_pin = 8;
const int red_SHCP_pin = 7;

const int yl_DS_pin = A0;
const int yl_STCP_pin = A1;
const int yl_SHCP_pin = A2;

const int grn_button = 4;
const int red_button = 3;
const int yl_button = 2;

boolean registers[7];   //stores LED output states for shift register, for eight LEDs, 0-7

void setup()
{
  // Set pins 7-12 and A0-A2 as outputs to control 24 LEDs
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  for(int i=7; i<=12; i++)
    pinMode(i,OUTPUT);

  
  // Set pins 2-4 as inputs with internal pullup resistors for switches
  for(int i=2; i<=4; i++)
    pinMode(i,INPUT_PULLUP);

  // turn off all lights to start    
  for(int i=0; i<=7; i++)
      registers[i]= LOW;
  writereg(grn_DS_pin,grn_STCP_pin,grn_SHCP_pin);
  writereg(red_DS_pin,red_STCP_pin,red_SHCP_pin);
  writereg(yl_DS_pin,yl_STCP_pin,yl_SHCP_pin);

  //blink a bunch of lights to indicate readiness
  entirewall(50);
}

void loop() //check for each button press and then light up the corresponding LEDs
{
if (digitalRead(grn_button) == LOW) {
   // LEDblink(grn_DS_pin,grn_STCP_pin,grn_SHCP_pin);    
    LEDrandom(grn_DS_pin,grn_STCP_pin,grn_SHCP_pin);
    entirewall(45);
    delay(500);
    allblink(grn_DS_pin,grn_STCP_pin,grn_SHCP_pin);
  }

if (digitalRead(red_button) == LOW) {
   // LEDblink(red_DS_pin,red_STCP_pin,red_SHCP_pin);
    LEDrandom(red_DS_pin,red_STCP_pin,red_SHCP_pin);
    entirewall(45);
    delay(500);
    allblink(red_DS_pin,red_STCP_pin,red_SHCP_pin);
  }

if (digitalRead(yl_button) == LOW) {
   // LEDblink(yl_DS_pin,yl_STCP_pin,yl_SHCP_pin);
    LEDrandom(yl_DS_pin,yl_STCP_pin,yl_SHCP_pin);
    entirewall(45);
    delay(500);
    allblink(yl_DS_pin,yl_STCP_pin,yl_SHCP_pin);
  }
}

//function that uploads to shift register the current settings in 'registers[]'
void writereg(int DS_pin, int STCP_pin, int SHCP_pin)
{
digitalWrite(STCP_pin, LOW);
for(int i=7; i>=0; i--)
  {
    digitalWrite(SHCP_pin, LOW);
    digitalWrite(DS_pin, registers[i] );
    digitalWrite(SHCP_pin, HIGH);
  }
digitalWrite(STCP_pin, HIGH);
}

/*  Used this function for testing.  Not used in the final version but I want to keep the code.
//function that blinks LEDs on a shift register in order up then down.  
void LEDblink(int DS_pin, int STCP_pin, int SHCP_pin)
{
  for(int j=0; j<=2; j++)                    //repeat pattern j times
  {
    for(int i=0; i<=7; i++)                    //cycle LEDs from 0-7
    {
      registers[i] = HIGH;
      registers[i-1] = LOW;
      delay(100);
      writereg(DS_pin,STCP_pin,SHCP_pin);
    }
    for(int i=7; i>=0; i--)                   //cycle LEDs from 7-0
    {
      registers[i] = HIGH;
      registers[i+1] = LOW;
      writereg(DS_pin,STCP_pin,SHCP_pin);
      delay(100);
    }
    registers[0] = LOW;                      // turns off last LED at end of loop, previous for loop leaves this HIGH.
    writereg(DS_pin,STCP_pin,SHCP_pin);
  } 
} */

//function that blinks LEDs randomly
void LEDrandom(int DS_pin, int STCP_pin, int SHCP_pin)
{
    int randomLED;
    for(int i=0; i<=25; i++)
    {
      randomLED = random(0,8);
      registers[randomLED] = HIGH;
      writereg(DS_pin,STCP_pin,SHCP_pin);
      delay(50);
      registers[randomLED] = LOW;
      writereg(DS_pin,STCP_pin,SHCP_pin);
      delay(50);
    }
}

//function that blinks all eight LEDs on and off j times.
void allblink(int DS_pin, int STCP_pin, int SHCP_pin)
{
    for(int j=0; j<=10; j++)
    {
      for(int i=0; i<=7; i++)
        registers[i] = HIGH;
      writereg(DS_pin,STCP_pin,SHCP_pin);
      delay(75);
      for(int i=0; i<=7; i++)
        registers[i] = LOW;
      writereg(DS_pin,STCP_pin,SHCP_pin);
      delay(75);
    }   
}

//function that blinks randomly accross the entire wall.
void entirewall(int blinks) {
  for(int i=0; i<=blinks; i++)  {
    int randomLED;    
    int randomsection = random(1,4);
    if (randomsection == 1) {
        randomLED = random(0,8);
        registers[randomLED] = HIGH;
        writereg(grn_DS_pin,grn_STCP_pin,grn_SHCP_pin);
        delay(50);
        registers[randomLED] = LOW;
        writereg(grn_DS_pin,grn_STCP_pin,grn_SHCP_pin);
        delay(50);        
    } else if (randomsection == 2) {
        randomLED = random(0,8);
        registers[randomLED] = HIGH;
        writereg(red_DS_pin,red_STCP_pin,red_SHCP_pin);
        delay(50);
        registers[randomLED] = LOW;
        writereg(red_DS_pin,red_STCP_pin,red_SHCP_pin);
        delay(50);    
    } else if (randomsection == 3) {
        randomLED = random(0,8);
        registers[randomLED] = HIGH;
        writereg(yl_DS_pin,yl_STCP_pin,yl_SHCP_pin);
        delay(50);
        registers[randomLED] = LOW;
        writereg(yl_DS_pin,yl_STCP_pin,yl_SHCP_pin);
        delay(50); 
    }
  }
}
