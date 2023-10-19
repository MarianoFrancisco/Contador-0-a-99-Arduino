// C++ code
// Inicialization vars
int resetButton = 4, incrementButton = 2, decrementButton = 3;
byte firstDisplay = 0, secondDisplay = 0, i, instruction = 0;
//Methods
bool getBit(byte dataDisplay, int position);
void display(byte myDisplay, byte digitDisplay);
void resetDisplay();
void incrementNumber();
void decrementNumber();
// Start
void setup()
{
  pinMode(resetButton, INPUT);
  for (i = 6; i < 14; i++){//6-13 pins on arduino
    pinMode(i, OUTPUT);
  }
  //interrupt for increment and decrement
  attachInterrupt(digitalPinToInterrupt(incrementButton),incrementNumber,RISING);
  attachInterrupt(digitalPinToInterrupt(decrementButton),decrementNumber,RISING);
}
// Repet data
void loop()
{
  if (digitalRead(resetButton) == HIGH) {
    resetDisplay();
  }
  display(1, firstDisplay);//method for first display
  display(2, secondDisplay);//method for second display
  delay(3000);//time increment
  if (instruction == 0){//first instruction count 0-99
    firstDisplay++;//increment in 1 first display 
    if (firstDisplay == 10){//increment in 1 second display and restart first display
      firstDisplay = 0;
      secondDisplay++;
      if (secondDisplay == 10){//if second display already 9 can't go to 10, we need reset
        secondDisplay = 0;
      }
    }
  }
}

bool getBit(byte dataDisplay, int position){//execute 8 times, 4 first display, 4 second display, then pos -> 7 6 5 4 3 2 1 0
  int myBit = dataDisplay >> position; // Scroll "position" times
  myBit = myBit & 1;//collect the last bit
  return myBit;
}

void display(byte myDisplay, byte digitDisplay)
{
  if (myDisplay == 1){//If is first display
    for (byte i = 0; i < 4; i++){//increment for all pins
      digitalWrite(i + 6, getBit(digitDisplay, i));//The first display start in 6
    }
  } else{//Is second display
    for (byte i = 0; i < 4; i++){//increment for all pins
      digitalWrite(i + 10, getBit(digitDisplay, i));//The second display start in 10
    }
  }
}
//Buttons
//Reset
void resetDisplay(){
  firstDisplay = -1;//-1=0
  secondDisplay = 0;
}
//Increment
void incrementNumber() {
  
}
//Decrement
void decrementNumber() {
  
}