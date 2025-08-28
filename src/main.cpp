#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// defines 
#define BUTTON_UP 142 // change back to 14
#define BUTTON_DOWN 15
#define BUTTON_ON 16
#define EMER_STOP 17

#define BUTTON_TIMER 14 // change to another

// functions 
bool chech_button(const uint8_t BUTTON_NUM, bool* flag);

// objects
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  // set communication and lcd
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("PlFm1.0");
  lcd.setCursor(8, 0);
  lcd.print("Timer:");
  lcd.setCursor(0, 1);
  lcd.print("Mode: ");
  lcd.setCursor(10, 1);
  lcd.print("Hz: ");

  // set pins        

  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_ON, INPUT_PULLUP);
  pinMode(BUTTON_ON, INPUT_PULLUP);
  pinMode(EMER_STOP, INPUT_PULLUP);
  pinMode(BUTTON_TIMER, INPUT_PULLUP);

  

}

// variables 
uint8_t speed = 15;
uint32_t timer_mins = 5;
bool on = 0;
bool flag_on = 0;

bool flag_up = 0;
bool flag_down = 0;
bool flag_timer = 0;

uint32_t time_on_start = millis();

void loop() {
  if (digitalRead(17) == 1) // safety measure time
  {
    // do our shit
    // note: all buttons are reversed

// on button
    if (!digitalRead(BUTTON_ON) && flag_on == 0)
    {
      delay(15);
      if (!digitalRead(BUTTON_ON))
      {
        flag_on = 1;

        // actual action
        on = !on;

      }
    }
    if (digitalRead(BUTTON_ON) && flag_on)
    flag_on = !digitalRead(BUTTON_ON);


// up button 
    if (!digitalRead(BUTTON_UP) && flag_up == 0)
    {
      delay(15);
      if (!digitalRead(BUTTON_UP))
      {
        flag_up = 1;

        // actual action
        speed++;
      }
    }
    flag_up = !digitalRead(BUTTON_UP);


// down button
    if (!digitalRead(BUTTON_DOWN) && flag_down == 0)
    {
      delay(15);
      if (!digitalRead(BUTTON_DOWN))
      {
        flag_down = 1;

        // actual action
        speed--;
      }
    }
    flag_down = !digitalRead(BUTTON_DOWN);

// timer button
    if (!digitalRead(BUTTON_TIMER) && flag_timer == 0)
    {
      delay(15);
      if (!digitalRead(BUTTON_TIMER))
      {
        flag_timer = 1;

        // actual action
        timer_mins++;
        if (timer_mins > 10)
        {
          timer_mins = 1;
        }
      }
    }
    flag_timer = !digitalRead(BUTTON_TIMER);





  }
  else
  {

    // turn off



  }


  // set state lcd
  lcd.setCursor(5, 1);
  if (on)
  {
    lcd.print("ON ");
    if (millis() - time_on_start < timer_mins * 60 * 1000)
    {
      // turn on
      // set speed

    }
    else
    {
      // turn of
      on = 0;
    }
  }
  else
  {
    lcd.print("OFF");
    time_on_start = millis();

  }

  // set speed to lcd
  if (speed > 30)
  {
    speed = 30;
  }
  if (speed < 1)
  {
    speed = 1;
  }

  lcd.setCursor(14, 1);
  if (speed > 9)
  {
    lcd.print(speed);
  }
  else
  {
    lcd.print(" ");
    lcd.print(speed);
  }

  // set timer
  lcd.setCursor(14, 0);

  if (timer_mins != 10)
  {
    lcd.print(" ");
  }
  lcd.print(timer_mins);

  // global delay
  delay(10);
}

// bool chech_button(const uint8_t BUTTON_NUM, bool* flag){  
//   bool res = false;
//   if (!digitalRead(BUTTON_NUM) && flag == 0)
//   {
//     delay(15);
//     if (!digitalRead(BUTTON_NUM))
//     {
//       *flag = 1;

//       // actual action
//       res = true;
//     }
//   }
//   *flag = !digitalRead(BUTTON_NUM);
//   return res;
// }

