/*Project: THREE JUB RIDDLE.  The arduino will monitor sensors for fluid levels in each jub, read buttons, and turn on/off relays controlling water pumps that move H20 from jug to jug  
 * 
 * Riddle: You have three water tanks; tank A (5 gallons), tank B (12 gallons), & tank C (8 gallons). Tank B is full with water while tanks A & C are empty.  
 * you must move water between the tanks to get fill tanks B and C to at least 50%. After each movement of fluid, at least one tank must be 75% full. 
 * If not, the system will reset and all fluid will be drained back into Tank B.Moving fluid from one tank to another will drain fluid from the dispensing 
 * tank until it is completely empty OR the receiving tank is completely full.

 * Developed by: Tyler Dahl | Room Escape San Antonio USA
 * Date:03-03-2023
 * Email: tyler@escaperoomsa.com
 * No rights retained for this project as it is a hack job of many others code. 
 * 
 * If you improve this code please let me know.
 * 
 * NOTE If you plan to integrate ethernet shields, pins 11,12,13 are used to communicate with the Network sheild and can not be used.
 */

/////////////////////////////////           DECLARE VARIABLES   /////////////////////////////

/////////////////////////////////        DECLARE AND ASSIGN BUTTONS TO RESPECTIVE ARDUINO PINS     ///////////////////
const int  Button_A2C = 22;
const int  Button_A2B = 24;
const int  Button_B2A = 26;
const int  Button_B2C = 28;
const int  Button_C2A = 30;
const int  Button_C2B = 32;

/////////////////////////////////        DECLARE AND ASSIGN H20 SENSORS TO RESPECTIVE ARDUINO PINS     ///////////////////
const int  A_Top = 34;
const int  A_Bottom = 36;
const int  A_Fail = 38;
const int  B_Top = 40;
const int  B_Bottom = 42;
const int  B_Fail = 44;
const int  C_Top = 46;
const int  C_Bottom = 48;
const int  C_Fail = 50;

/////////////////////////////////       DECLARE AND ASSIGN PUMP RELAYS TO RESPECTIVE ARDUINO PINS     ///////////////////
const int A_to_B = 31;
const int A_to_C  = 33;
const int B_to_A = 35;
const int B_to_C = 37;
const int C_to_A = 39;
const int C_to_B = 41;

/////////////////////////////////       DECLARE AND ASSIGN WIN/LOSE PERIPHERAL PROPS TO RESPECTIVE ARDUINO PINS     ///////////////////
const int resetEffects = 51;
const int winEffects = 53;

/////////////////////////////////        DECLARE AND DEFINE STATUS VARIABLES      ///////////////////
bool pumpState = false;
bool gameReset = false;
bool gameWin = false;
bool  Button_A2C_State = false;
bool  Button_A2B_State = false;
bool  Button_B2A_State = false;
bool  Button_B2C_State = false;
bool  Button_C2A_State = false;
bool  Button_C2B_State = false;

///////////////////////////////////////   SETUP    ///////////////////////////////////////
void setup()
{
/////////////////////////////////        ASSIGN PINMODES TO RESPECTIVE VARIABLES     ///////////////////
pinMode (Button_A2C, INPUT);
pinMode (Button_A2B, INPUT);
pinMode (Button_B2A, INPUT); 
pinMode (Button_B2C, INPUT);
pinMode (Button_C2A, INPUT);
pinMode (Button_C2B, INPUT);
pinMode (A_Top, INPUT);
pinMode (A_Bottom, INPUT);
pinMode (A_Fail, INPUT); 
pinMode (B_Top, INPUT);
pinMode (B_Bottom, INPUT);
pinMode (B_Fail, INPUT);
pinMode (C_Top, INPUT);
pinMode (C_Bottom, INPUT);
pinMode (C_Fail, INPUT);
pinMode (A_to_B, OUTPUT);
pinMode (A_to_C, OUTPUT); 
pinMode (B_to_A, OUTPUT);
pinMode (B_to_C, OUTPUT);
pinMode (C_to_A, OUTPUT);
pinMode (C_to_B, OUTPUT);
pinMode (resetEffects, OUTPUT);
pinMode (winEffects, OUTPUT);
}

void loop()
{
///////////////////////////////////////// IF ANY PUMP IS RUNNING SET PUMP STATE TO TRUE /////////////////////////////////////////
if (digitalRead(A_to_B) == HIGH || digitalRead(A_to_C) == HIGH || digitalRead(B_to_A) == HIGH || digitalRead(B_to_C) == HIGH || digitalRead(C_to_A) == HIGH || digitalRead(C_to_B) == HIGH)
{
  pumpState = true;
}
else
{
  pumpState = false;
}

//////////////////////////////////// WHEN ALL PUMPS OFF, READ SENSORS FOR WIN / LOSE CONDITION ///////////////////////////////
if (pumpState == false)
{
  if (digitalRead(A_Fail) == LOW && digitalRead(B_Fail) == LOW && digitalRead(C_Fail) == LOW)
  {
    gameReset = true;
    resetGame();
  }

  if (digitalRead(B_Bottom) == HIGH && digitalRead(C_Bottom) == HIGH && digitalRead(C_Fail) == HIGH)
  {
    gameWin = true;
    winGame();
  }
}

//////////////////////////////////////////// PLAYER PRESS VARIOUS BUTTON TO MOVE WATER BETWEEN TANKS /////////////////////////////////////////////////////////////////////
if (digitalRead(Button_A2B) == HIGH)
  {
    Button_A2B_State = true;
    run_Pumps;
  }
  else
    {
     Button_A2B_State = false; 
    }  
if (digitalRead(Button_A2C) == HIGH)
  {
    Button_A2C_State = true;
    run_Pumps;
  }
  else
    {
     Button_A2C_State = false; 
    }
if (digitalRead(Button_B2A) == HIGH)
  {
    Button_B2A_State = true;
    run_Pumps;
  }
  else
    {
     Button_B2A_State = false; 
    }  
if (digitalRead(Button_B2C) == HIGH)
  {
    Button_B2C_State = true;
    run_Pumps;
  }
  else
    {
     Button_B2C_State = false; 
    }  
if (digitalRead(Button_C2A) == HIGH)
  {
    Button_C2A_State = true;
    run_Pumps;
  }
  else
    {
     Button_C2A_State = false; 
    }  
if (digitalRead(Button_C2B) == HIGH)
  {
    Button_C2B_State = true;
    run_Pumps;
  }        
  else
    {
     Button_C2B_State = false; 
    }
}

void run_Pumps()
{
if (Button_A2B_State == true)
  {
    if (digitalRead(B_Top) == LOW && digitalRead(A_Bottom) == HIGH)
      {
        if (digitalRead(A_to_C) == LOW && digitalRead(B_to_A) == LOW && digitalRead(B_to_C) == LOW && digitalRead(C_to_A) == LOW && digitalRead(C_to_B) == LOW)
          {
            digitalWrite(A_to_B, HIGH);
          }
      }
      else 
        {
          digitalWrite(A_to_B, LOW);   
          Button_A2B_State = false;                  
        }          
   }
      
if (Button_A2C_State == true)
  {
    if (digitalRead(C_Top) == LOW && digitalRead(A_Bottom) == HIGH)
      {
        if (digitalRead(A_to_B) == LOW && digitalRead(B_to_A) == LOW && digitalRead(B_to_C) == LOW && digitalRead(C_to_A) == LOW && digitalRead(C_to_B) == LOW)
          {
            digitalWrite(A_to_C, HIGH);
          }
      }
      else 
        {
          digitalWrite(A_to_C, LOW);   
          Button_A2C_State = false;                  
        }       
    }

if (Button_B2A_State == true)
  {
    if (digitalRead(A_Top) == LOW && digitalRead(B_Bottom) == HIGH)
    {
      if (digitalRead(A_to_B) == LOW && digitalRead(A_to_C) == LOW && digitalRead(B_to_C) == LOW && digitalRead(C_to_A) == LOW && digitalRead(C_to_B) == LOW)
      {
        digitalWrite(B_to_A, HIGH);
      }
    }
    else 
      {
        digitalWrite(B_to_A, LOW);       
      }
  }

if (Button_B2C_State == true)
  {
    if (digitalRead(C_Top) == LOW && digitalRead(B_Bottom) == HIGH)
    {
      if (digitalRead(A_to_B) == LOW && digitalRead(A_to_C) == LOW && digitalRead(B_to_A) == LOW && digitalRead(C_to_A) == LOW && digitalRead(C_to_B) == LOW)
      {
        digitalWrite(B_to_C, HIGH);
      }
    }
    else 
      {
        digitalWrite(B_to_C, LOW);       
      }
  }    
  
if (Button_C2A_State == true)
  {  
    if ( digitalRead(A_Top) == LOW && digitalRead(C_Bottom) == HIGH)
    {
      if (digitalRead(A_to_B) == LOW && digitalRead(A_to_C) == LOW && digitalRead(B_to_A) == LOW && digitalRead(B_to_C) == LOW && digitalRead(C_to_B) == LOW)
      {
        digitalWrite(C_to_A, HIGH);
      }
    }
    else 
      {
        digitalWrite(C_to_A, LOW);       
      }
  }
  
if (Button_C2B_State == true)
  {
    if (digitalRead(B_Top) == LOW && digitalRead(C_Bottom) == HIGH)
    {
      if (digitalRead(A_to_B) == LOW && digitalRead(A_to_C) == LOW && digitalRead(B_to_A) == LOW && digitalRead(B_to_C) == LOW && digitalRead(C_to_A) == LOW)
      {
        digitalWrite(C_to_B, HIGH);
      }
    }
    else 
      {
        digitalWrite(C_to_B, LOW);       
      }  
   }
}

void resetGame()
{
  /////////////////////////////// RESET GAME AND REFILL PRIMARY TANK ////////////////////////////////
  if (gameReset = true)
  {
    digitalWrite(resetEffects, HIGH);
    if (digitalRead(B_Top) == LOW)
    { 
      if (digitalRead(A_Bottom) == HIGH)
      {
        digitalWrite(A_to_B, HIGH);
      }
  
      if (digitalRead(C_Bottom) == HIGH)
      {
        digitalWrite(C_to_B, HIGH);
      }
    }      
    else
    {
      gameReset = false;
    }

  } 
}

void winGame()
{
  if (gameWin = true)
  {
    digitalWrite(winEffects,HIGH);
  }
}
