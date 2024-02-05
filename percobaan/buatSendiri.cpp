#include <Arduino.h>

int jumlahPulse = 0;
bool printPulse = false;
// int index;
bool ledState = false;
unsigned long previousMillis = 0;
const long interval = 100;

// put function definitions here:
void IRAM_ATTR hitungPulse()
{
    jumlahPulse++;
}
void IRAM_ATTR deteksiIndex()
{
    printPulse = true;
    // jumlahPulse=0;
}

void setup()
{
    Serial.begin(9600);
    // put your setup code here, to run once:
    pinMode(D4, OUTPUT); // pin untuk led terintegrasi (notifikasi)
    pinMode(D1, INPUT_PULLUP);
    pinMode(D2, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(D1), hitungPulse, RISING);
    attachInterrupt(digitalPinToInterrupt(D2), deteksiIndex, RISING);
}

void loop()
{
    if (printPulse)
    {
        Serial.print("pulse = ");
        Serial.print(jumlahPulse);
        Serial.println();
        jumlahPulse = 0;
        printPulse = false;
    }
    unsigned long currentMillis = millis();

    if (printPulse)
        if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;
            digitalWrite(2, HIGH);
        }
    digitalWrite(2, LOW);
}
