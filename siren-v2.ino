/*
 * Have any question about this code? Feel free to contact me
 * Discord: NANO#1039
 * Mail: nano@nexion.xyz or p.nanock@gmail.com
 */
int select_type;  // The type of siren selected
int auto_type;  // Type of siren selected for the auto siren mode
volatile int period_indicator = 0;  // This variable is used for a few siren types to allow the button to interrupt the actual siren and jump to the next one
int k; // This variable is used to define the siren tone in some siren types
int speaker = 10;  // The pin the speaker is plugged in

// The variables below are used to fix a problem caused by some pushbuttons
unsigned long lastDebounceTime = 0; // Used to prevent button from being spammy/buggy
const int DEBOUNCE_DELAY = 300;   // the debounce time; increase if the output flickers; decrease if you want to be able to spam the button


void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), next, HIGH);  //When the pin 2 (button) is triggered, it overrides the arduino to jump to the next siren type
  interrupts();
  Serial.print("Siren is on standby...\n");
}
  
void loop()
{
  if(select_type == 1) // French firefighters
  {
    delay(1000); // Each tone (low and high) last 1 second
    if(period_indicator == 0)
    {
      period_indicator = 1; // Preparing to put the higher tone
      tone(speaker, 435); // Making a 435Hz tone
    }
    else // If the tone isn't supposed to be low
    {
      period_indicator = 0;  // Preparing to put the lower tone
      tone(speaker, 488);  // Making a 488Hz tone
    }
  }
  
  if(select_type == 2) // French Police
  {
    delay(500); // Each tone (low and high) last 1/2 second
    if(period_indicator == 0)
    {
      period_indicator = 1;
      tone(speaker, 435);
    }
    else
    {
      period_indicator = 0;
      tone(speaker, 580);
    }
  }

  if(select_type == 3) // French EMS
  {
    delay(140); // Each tone (low and high) last 1/2 second
    if(period_indicator == 0)
    {
      period_indicator = 1;
      tone(speaker, 420);
    }
    else if (period_indicator == 1) {
      period_indicator = 2;
      tone(speaker, 516);
    }
    else if (period_indicator == 2) {
      period_indicator = 3;
      tone(speaker, 420);
    }
    else
    {
      period_indicator = 0;
      k = 700;
      noTone(speaker);
      while((k+=1) < 1200) // To make a crescendo to 1200Hz
      {
        delayMicroseconds(3000);
        if(select_type == 4)
        {
          break;
        }
      }
    }
  }
  
  if(select_type == 4) // American Yelp
  {
    while((k+=1) < 1200) // To make a crescendo to 1200Hz
    {
      tone(speaker, k);
      delayMicroseconds(100);
      if(select_type == 5)
      {
        break;
      }
    }
    delayMicroseconds(250);
    while((k-=1) >= 500)
    {
      tone(speaker, k);
      delayMicroseconds(100);
      if(select_type == 5)
      {
        break;
      }
    }
    delayMicroseconds(250);
  }
  
  if(select_type == 5)  // Automatic siren
  {
    // Between each period: Horn
    // Type 0: Yelp
    // Type 1: Wail
    // Type 2: Fast
    // Type 3: Power call
    // Type 4: Horn
    // Type 5: High/Low
    
    auto_type = random(6);
    randomSeed(analogRead(random(8)));
    if(auto_type == 0) {
      Serial.print("Type selected: Yelp\n");
      period_indicator = 0;
      while(period_indicator < 3) // To make sure we have 3 cycles of it
      {
        period_indicator++;
        while((k+=1) < 1200)
        {
          tone(speaker, k);
          delayMicroseconds(100);
          if(select_type == 1)
          {
            break;
          }
        }
        delayMicroseconds(250);
        while((k-=1) >= 500)
        {
          tone(speaker, k);
          delayMicroseconds(100);
          if(select_type == 1)
          {
            break;
          }
        }
        if(select_type == 1)
        {
          break;
        }
        delayMicroseconds(250);
      }
      while((k+=1) < 800)
      {
        tone(speaker, k);
        delayMicroseconds(100);
        if(select_type == 1)
        {
          break;
        }
      }
    }
    if(auto_type == 1) {
      Serial.print("Type selected: Wail\n");
      while(k++ < 1300)
      {
        tone(speaker, k);
        delayMicroseconds(50);
        if(select_type == 1)
        {
          break;
        }
      }
      delay(1750);
      while(k-- >= 500)
      {
        tone(speaker, k);
        delayMicroseconds(3000);      
        if(select_type == 1)
        {
          break;
        }
      }
      while(k++ < 800)
      {
        tone(speaker, k);
        delayMicroseconds(50);
        if(select_type == 1)
        {
          break;
        }
      }
    }
    if(auto_type == 2) {
      Serial.print("Type selected: Fast\n");
      period_indicator = 0;
      while(period_indicator < 20) // To make sure we have 3 cycles of it
      {
        period_indicator++;
        while((k+=2) < 1200)
        {
          tone(speaker, k);
          if(select_type == 1)
          {
            break;
          }
        }
        while((k-=2) >= 500)
        {
          tone(speaker, k);
          if(select_type == 1)
          {
            break; //If ever we change the siren type, we stop doing this one
          }
        }
        if(select_type == 1)
        {
          break;  //If ever we change the siren type, we stop doing this one
        }
      }
      tone(speaker, 800);
    }
    
    if(auto_type == 3) {
      Serial.print("Type selected: Power call\n");
      period_indicator = 0;
      while(period_indicator < 4) // To make sure we have 3 cycles of it
      {
        period_indicator++;
        k=900;
        tone(speaker, k);
        delay(250);
        while((k-=1) > 600)
        {
          tone(speaker, k);
          delayMicroseconds(1500);
          if(select_type == 1)
          {
            break;
          }
        }
        if(select_type == 1)
        {
          break;
        }
      }
      while((k+=1) < 800)
      {
        tone(speaker, k);
        delayMicroseconds(100);
        if(select_type == 1)
        {
          break;
        }
      }
    }
    
    if(auto_type == 4) {
      Serial.print("Type selected: Horn\n");
      period_indicator = 0;
      while(period_indicator < 2501) // To make sure it lasts a bit
      {
        period_indicator++;
        tone(speaker, 400);
        delayMicroseconds(25);
        tone(speaker, 450);
        delayMicroseconds(25);
        if(select_type == 1)
        {
          break;
        }
      }
    }
    
    if(auto_type == 5) {
      Serial.print("Type selected: High/Low\n");
      k = 0;
      while(k++ < 4)
      {
        delay(600);
        if(period_indicator == 0)
        {
          period_indicator = 1;
          tone(speaker, 800);
        }
        else  //작동주기 확인등이 켜졌을 시
        {
            period_indicator = 0;
            tone(speaker, 600);
        }
        if(select_type == 1)
        {
          break;
        }
      }
    }
  }
}


void next() // This function is triggered whenever the button is pressed
{
  /* 
   *   I needed to put the "if" line below to avoid a problem caused by my button not providing 100% of the power directly when pressed.
   *   With this, we avoid the arduino thinking the button is pressed multiple times when it was pressed only once
   */
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    lastDebounceTime = millis();
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    select_type += 1;  // When the button is pressed, we add 1 to the siren type to move on to the next siren
    if(select_type == 1)  //Siren type 4: French firefighters (and EMS)
    {
      // Turn off LED 5 and turn on LED 2
      Serial.print("Siren Type: French Rescue\n");
    }
    if(select_type == 2)  //Siren type 2: French Police
    {
      // Turn off LED 2 and turn on LED 3
      Serial.print("Siren Type: French Police\n");
    }
    if(select_type == 3)  //Siren type 3: French EMS
    {
      // Turn off LED 4 and turn on LED 5
      Serial.print("Siren Type: French EMS\n");
    }
    if(select_type == 4)  //Siren type 3: American Yelp
    {
      // Turn off LED 3 and turn on LED 4
      Serial.print("Siren Type: American Yelp\n");
    }
    if(select_type == 5)  //Siren type 4: Automatic siren
    {
      // Turn off LED 4 and turn on LED 5
      Serial.print("Siren Type: Automatic\n");
    }
    
    if(select_type == 6) // There is no select type above 4, so we take it when it's at 5 to put it back to 1
    { 
      // Turn off LED 5 and turn on LED 2
      select_type = 1;  // We change the siren type back to 1 to make a loop
      period_indicator = 1; // To have the siren to start on it's higher tone, we put the period indicator back to 1
      Serial.print("Cycling...\n");
      Serial.print("Siren Type: French Rescue\n");
    }
  }
  
}
