/*
 * Initialize Pins & Variables.
 */
int i = 1;
int Switch_Pin ; 
int Led_Pin ;
int Temp_Led = A0;
boolean Button_Last_State = LOW;
boolean Button_Current_State = LOW;
boolean Led_On = LOW;

//================================================== Setup Function ===================================================//
/* 
 * The setup function runs once when you press reset or power the board
 */
void setup() {
  Serial.begin(9600);             // begin serial communication between the arduino and the virtual instrument or the serial monitor.
  pinMode(Temp_Led, INPUT);       // initialize analog pin A0 as an INPUT.
  pinMode(18, INPUT);             // initialize digital pin 18 as an INPUT.
  attachInterrupt(digitalPinToInterrupt(3), blink, CHANGE);     // make interrupt at pin 3 when change happens at it.
  attachInterrupt(digitalPinToInterrupt(2), blink, CHANGE);     // make interrupt at pin 2 when change happens at it.
  attachInterrupt(digitalPinToInterrupt(18), Pin_18, CHANGE);   // make interrupt at pin 18 when change happens at it.
}
//====================================================================================================================//

//================================ Button_Debounce =============================//
/* 
 * This function used to eliminate the effect of the button bouncing effect in the real life 
 * by making a delay (5)ms when the button is pressed
 */
 
boolean Button_Debounce(boolean Last)
{
  boolean Current = digitalRead(Switch_Pin);
  if(Last != Current)
  {
    delay(5);
    Current = digitalRead(Switch_Pin);
  }
  return Current;
}
//==============================================================================//

//================================== Switch =========================================//
/*
 * This function used to make the LED turns on when the button is pressed
 * by checking the Button_Last_State & Button_Current_State.
 * also used for sending the button & the LED current state to the serial monitor.
 */
boolean Switch()
{
  if(Button_Last_State == LOW && Button_Current_State == HIGH)
  {
    Serial.print("Switch at Pin ");
    Serial.print(Switch_Pin);              // Displaying the Switch_Pin number to the serial monitor
    Serial.println(" is pressed");
    Led_On = !Led_On;
    if(Led_On == 1)
    {
      Serial.print("LED at Pin ");
      Serial.print(Led_Pin);               // Displaying the Led_Pin number to the serial monitor
      Serial.println(" is On");
    }else 
    {
      Serial.print("LED at Pin ");
      Serial.print(Led_Pin);               // Displaying the Led_Pin number to the serial monitor
      Serial.println(" is OFF");
    }
  }
  Button_Last_State = Button_Current_State;
  digitalWrite(Led_Pin, Led_On);
  return Led_On;
}
//==================================================================================//

//============================================ Temperature Function============================================//
/*
 * This function used for reading temperature value comes from temperature sensor connected at analog pin A0 
 * and sending this vaule as a continuous serial data with 3 second rate to the serial monitor.
 */
boolean Temperature()
{
  int Temp = analogRead(Temp_Led);     // Read the analog data comes from Pin A0
  float Cel = (Temp/1024.0)*500;       // Convert the value comes from the sensor going through the arduino 10-bit ADC
  float Fahr = (Cel*9)/5 + 32;         // Converting Celsius into Fahrenhiet
  Serial.print("Temperature = ");
  Serial.print(Cel);                   // Displaying the temperature value in Celsius to the serial monitor
  Serial.print(" *C");
  Serial.print("    |    ");
  Serial.print("Temperature = "); 
  Serial.print(Fahr);                  // Displaying the temperature value in Fahrenheit  to the serial monitor
  Serial.println(" *F");
  delay(3000);                         // wait for 3 second.
}
//============================================================================================================//

//================== blink Interrupt Function ==============================//
/*
 * This function used according to the ISR of the Pin 3 Or Pin 2
 * which defind earlier in the code.
 */
void blink()
{
  Button_Current_State = Button_Debounce(Button_Last_State);
  Switch();
}
//===================================================================//

//================== Pin_18 Interrupt Function ==============================//
/*
 * This function used according to the ISR of the Pin 18
 * which defind earlier in the code.
 */
void Pin_18(){
  if(digitalRead(18) == HIGH) i=1;   // check if the button is pressed at pin 18, put i = 1 to ask the user again to put different input pins
}
//===================================================================//

//======================= Loop Function =====================//
/* 
 * The loop function runs over and over again forever
 */
void loop() 
{
  while(i){
  Serial.println("Enter Number for the Switch Pin (pins 2 or 3), then press ENTER");
  delay(1000);                          
  while (Serial.available() == 0);      // Wait here until input buffer has a character
   Switch_Pin = Serial.parseInt();      // get integer number from the user through the virtual terminal and assign it to Switch_Pin.
   Serial.print("The Switch Pin = "); 
   Serial.println(Switch_Pin);        
   pinMode(Switch_Pin, INPUT);          // make Switch_Pin as an INPUT.
  Serial.println("Enter Number for the LED Pin (pins 13 or 12), then press ENTER");
  delay(1000);
  while (Serial.available() == 0);      // Wait here until input buffer has a character
   Led_Pin = Serial.parseInt();         // get integer number from the user through the virtual terminal and assign it to Led_Pin.
   Serial.print("The Led_Pin = "); 
   Serial.println(Led_Pin);
   pinMode(Led_Pin, OUTPUT);            // make Led_Pin as an OUTPUT.
   i--;
  } 
 Temperature();                         // run the Temperature function.
}
//===========================================================//
