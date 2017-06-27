
#include <LiquidCrystal.h>
#include <Time.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buzzerpin = 8;
const int resetButtonPin = 6;
const int startStopButtonPin = 7;
const int lightsensor = A1;
const int light;

int setupMinutes = 20;   
int setupSeconds = 0;   


int currentHours = 0;
int currentMinutes = 0;
int currentSeconds = 0;
time_t currentTime = 0;

time_t startTime = 0;
time_t elapsedTime = 0;

int resetButtonState = LOW;
int startButtonState = LOW;
int resetButtonPrevState = LOW;
int startStopButtonPrevState = LOW;
int upButtonPrevState = LOW;
bool resetButtonPressed = false;


const int MODE_IDLE = 0;
const int MODE_SETUP = 1;
const int MODE_RUNNING = 2;
const int MODE_RINGING = 3;

int currentMode = MODE_IDLE;    // 0=idle 1=setup 2=running 3=ringing
                                // Power up --> idle
                                // Reset --> idle
                                //  Start/Stop --> start or stop counter
                                //  Up / Down --> NOP
                                // Reset (long press) --> enter setup
                                //   Start/Stop --> data select
                                //   Up --> increase current data value
                                //   Down --> decrease current data value
                                //   Reset --> exit setup (idle)

int dataSelection = 0;  // Currently selected data for edit (setup mode, changes with Start/Stop)
                        // 0=hours (00-99) 1=minutes (00-59) 2=seconds (00-59)

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(resetButtonPin, INPUT);
  pinMode(startStopButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
    pinMode(lightsensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  startButtonPressed = false;
  upButtonPressed = false;
  downButtonPressed = false;
  light = analogRead(lightsensor);
if(ligt < 10) {
  startButtonPressed = true;
  return startButtonPressed;
  }

  /*
   * Reset button management
   */
  resetButtonPressed = false;
  resetButtonLongPressed = false;
  resetButtonState = digitalRead(resetButtonPin);
  if(resetButtonState != resetButtonPrevState)
  {
    resetButtonPressed = resetButtonState == HIGH;
    resetButtonPrevState = resetButtonState;
  }
  }




  /*
   * Mode management
   */
  switch(currentMode)
  {
    case MODE_IDLE:
      if(resetButtonPressed)
      {
        Reset();
      }
      if(startButtonPressed)
      {
        currentMode = currentMode == MODE_IDLE ? MODE_RUNNING : MODE_IDLE;
        if(currentMode == MODE_RUNNING)
        {
          // STARTING TIMER!
          startTime = now();
        }
      }
      break;

    
      }
      
    case MODE_RUNNING:
    
      if(resetButtonPressed)
      {
        Reset();
        currentMode = MODE_IDLE;
      }
      break;

  }


  /*
   * LCD management
   */
  //lcd.clear();
  lcd.setCursor(0, 0);
  switch(currentMode)
  {
    case MODE_IDLE:
      lcd.print("Timer ready     ");
      lcd.setCursor(0, 1);
      lcd.print(currentMinutes);
      lcd.print(" ");
      lcd.print(currentSeconds);
      lcd.print("    ");
      break;
    
    case MODE_RUNNING:
      lcd.print("Counting down...");
      lcd.setCursor(0, 1);
      if(minute(currentTime) < 10) lcd.print("0");
      lcd.print(minute(currentTime));
      lcd.print(":");
      if(second(currentTime) < 10) lcd.print("0");
      lcd.print(second(currentTime));
      break;
    case MODE_RINGING:
      lcd.print("   RING-RING!   ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
       tone(buzzerpin, 1000);
       delay(1000);     
       tone(buzzer);    
       delay(1000);
       delay(1000);       
       tone(buzzer);    
       delay(1000);
      break;
  }
  delay(10);
}

void Reset()
{
  currentMode = MODE_IDLE;
  currentMinutes = setupMinutes;
  currentSeconds = setupSeconds;
}
