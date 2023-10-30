// Pin definitions
#define resetButton 4
#define incrementButton 2
#define decrementButton 3
int bcd1Pins[4] = {6, 7, 8, 9};
int bcd2Pins[4] = {10, 11, 12, 13};

// Array of BCD codes for numbers 0-9
const byte numbersDisplayAnode[10] = {
    0b00000000, // 0
    0b00000001, // 1
    0b00000010, // 2
    0b00000011, // 3
    0b00000100, // 4
    0b00000101, // 5
    0b00000110, // 6
    0b00000111, // 7
    0b00001000, // 8
    0b00001001  // 9
};

// Variables to store units and tens digits
int unitsDigit, tensDigit;

// Delay time for display updates
long delayTime = 2000;

void setup()
{
    pinMode(resetButton, INPUT);
    pinMode(incrementButton, INPUT);
    pinMode(decrementButton, INPUT);
    attachInterrupt(digitalPinToInterrupt(incrementButton), increment, RISING);
    attachInterrupt(digitalPinToInterrupt(decrementButton), decrement, RISING);
    for (int i = 0; i < 4; i++)
    {
        pinMode(bcd1Pins[i], OUTPUT);
        pinMode(bcd2Pins[i], OUTPUT);
    }
    resetDisplay();
    delay(1000);
}

void loop()
{
    if (digitalRead(resetButton) == HIGH)
        resetDisplay();
    increment();
}

// Function to update the BCD display
void lightSegments(int number, int *bcdPins)
{
    byte numberBit = numbersDisplayAnode[number];
    for (int i = 0; i < 4; i++)
    {
        int bit = bitRead(numberBit, i);
        digitalWrite(bcdPins[i], bit);
    }
}
// Function to reset the display
void resetDisplay()
{
    unitsDigit = 0;
    tensDigit = 0;
    lightSegments(unitsDigit, bcd1Pins);
    lightSegments(tensDigit, bcd2Pins);
}
// Function to increment the number
void increment()
{
    unitsDigit++;
    if (unitsDigit > 9)
    {
        tensDigit++;
        unitsDigit = 0;
    }
    if (tensDigit > 9)
        tensDigit = 0;

    lightSegments(unitsDigit, bcd1Pins);
    lightSegments(tensDigit, bcd2Pins);
    delay(delayTime);
}
// Function to decrement the number
void decrement()
{
    unitsDigit--;
    if (unitsDigit < 0)
    {
        tensDigit--;
        unitsDigit = 9;
    }
    if (tensDigit < 0)
        tensDigit = 9;

    lightSegments(unitsDigit, bcd1Pins);
    lightSegments(tensDigit, bcd2Pins);
    delay(delayTime);
}
