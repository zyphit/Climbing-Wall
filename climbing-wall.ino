//Fun program to run the winning buttons on the climbing wall.  The wall has three arcade buttons along the top
//and pushing each will light up eight LEDs on the wall. Buttons and LED sets will be colour coded (red, yellow,
//green), plus an external rocker switch to control power.  Each set of LEDs will have a shift register (74HC595)
//controlling them, so three outputs per colour, plus three digital inputs for switches, 12 pins total.
//based on code courtesy of EEEnthusiast.com.
//
//Uses Arduino nano, three 74HC595 shift registers, 24 LEDs (8 ea of green, yellow, red), and three momentary
//push buttons.

int grn_DS_pin = 12;
int grn_STCP_pin = 11;
int grn_SHCP_pin = 10;

int red_DS_pin = 9;
int red_STCP_pin = 8;
int red_SHCP_pin = 7;

int yl_DS_pin = A0;
int yl_STCP_pin = A1;
int yl_SHCP_pin = A2;

int grn_button = 4;
int red_button = 3;
int yl_button = 2;

int sensor_value = HIGH; //checks state of button presses (low = pressed)

boolean registers[8];   //stores LED output states for shift register

void setup()
{
  // Set pins 7-12 and A0-A2 as outputs to control 24 LEDs
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);

  // Set pins 2-4 as inputs with internal pullup resistors for switches
  for (int i =2;i<=4;i++)
    pinMode(i,INPUT_PULLUP);

  // turn off all ights to start    
  for(int i = 0; i<8; i++)
    {
      registers[i]= LOW;
    }
    writereg(grn_DS_pin,grn_STCP_pin,grn_SHCP_pin);
    writereg(red_DS_pin,red_STCP_pin,red_SHCP_pin);
    writereg(yl_DS_pin,yl_STCP_pin,yl_SHCP_pin);
}

void loop() //check for each button press and then light up the corresponding LEDs
{
sensor_value = digitalRead(grn_button);
if (sensor_value == HIGH) {
    delay(5);
  } else {
    LEDblink(grn_DS_pin,grn_STCP_pin,grn_SHCP_pin);
    }

sensor_value = digitalRead(red_button);
if (sensor_value == HIGH) {
    delay(5);
  } else {
    LEDblink(red_DS_pin,red_STCP_pin,red_SHCP_pin);
    }

sensor_value = digitalRead(yl_button);
if (sensor_value == HIGH) {
    delay(5);
  } else {
    LEDblink(yl_DS_pin,yl_STCP_pin,yl_SHCP_pin);
    }
}

//function that uploads to shift register the current settings in 'registers[]'
void writereg(int DS_pin, int STCP_pin, int SHCP_pin)
{
digitalWrite(STCP_pin, LOW);
for (int i = 7; i>=0; i--)
  {
    digitalWrite(SHCP_pin, LOW);
    digitalWrite(DS_pin, registers[i] );
    digitalWrite(SHCP_pin, HIGH);
  }
digitalWrite(STCP_pin, HIGH);
}

//function that blinks LEDs on a shift register.  Lights up either green or red or yellow depending on input parameters
void LEDblink(int DS_pin, int STCP_pin, int SHCP_pin)
{
    for(int j = 0; j<3; j++)                    //repeat pattern j times
    {
    for(int i = 0; i<8; i++)                    //cycle LEDs from 0-7
    {
      registers[i] = HIGH;
      registers[i-1] = LOW;
      delay(100);
      writereg(DS_pin,STCP_pin,SHCP_pin);
    }
    for(int i = 7; i>=0; i--)                   //cycle LEDs from 7-0
    {
      registers[i] = HIGH;
      registers[i+1] = LOW;
      writereg(DS_pin,STCP_pin,SHCP_pin);
      delay(100);
    }
    for(int i = 0; i<8; i++)                    // turn off all ights at the end of the loop    
    {
      registers[i]= LOW;
    }
    writereg(DS_pin,STCP_pin,SHCP_pin);
    }
}
