//Fun program to run the winning buttons on the climbing wall.  The wall has three arcade buttons along the top
//and pushing each will light up eight LEDs on the wall, buttons and LED sets will be colour coded (red, yellow,
//green), plus an external rocker switch to control power.  Each set of LEDs will have a shift register (74HC595)
//controlling them, so three digital outputs per colour, plus three digital inputs for switches, 12 pins total.
//based on code courtesy of EEEnthusiast.com

int grn_DS_pin = 12;
int grn_STCP_pin = 11;
int grn_SHCP_pin = 10;

int red_DS_pin = 9;
int red_STCP_pin = 8;
int red_SHCP_pin = 7;

int yl_DS_pin = 6;
int yl_STCP_pin = 5;
int yl_SHCP_pin = 4;

int grn_button = 3;
int red_button = 2;
int yl_button = 1;

boolean registers[8];   //stores LED output states for shift register

void setup()
{
  // Set pins 4-12 as outputs to control 24 LEDs
  for (int i = 4;i<13;i++)
    pinMode(i,OUTPUT);
  // Set pins 1-3 as inputs with internal pullup resistors for switches
  for (int i = 1;i<=4;i++)
    pinMode(i,INPUT_PULLUP);
  writereg(1,2,3);
}

void loop() //check for each button press and then light up the corresponding LEDs
{
int sensor_value = digitalRead(grn_button);
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

//uploads to shift register the current settings in 'registers[]'
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

//function that blinks LEDs on a shift register.  Three colours to choose from
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
