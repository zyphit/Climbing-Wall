int DS_pin = 8;
int STCP_pin = 9;
int SHCP_pin = 10;
int button = 11;


void setup()
{
pinMode(DS_pin,OUTPUT);
pinMode(STCP_pin,OUTPUT);
pinMode(SHCP_pin,OUTPUT);
pinMode(button,INPUT_PULLUP);
writereg();
}

boolean registers[8];

void writereg()
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

void loop()
{
int sensorVal = digitalRead(button);
if (sensorVal == HIGH) {
    delay(5);
  } else {
    for(int j = 0; j<3; j++)
    {
    for(int i = 0; i<8; i++) 
    {
      registers[i] = HIGH;
      registers[i-1] = LOW;
      delay(100);
      writereg();
    }
    for(int i = 7; i>=0; i--)
    {
      registers[i] = HIGH;
      registers[i+1] = LOW;
      writereg();
      delay(100);
      
    }
    for(int i = 0; i<8; i++)
    {
      registers[i]= LOW;
    }
    writereg();
    }
  }  
}
