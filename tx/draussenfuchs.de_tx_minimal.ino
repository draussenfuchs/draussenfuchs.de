/*

Very basic 70cm-ISM fox-transmitter based on ESP32 and generic transmitter module.
See draussenfuchs.de for details.

--

The MIT License (MIT)

Copyright (c) 2025 Harm, DK4HAA, draussenfuchs.de

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#define FREQ_HZ 880  // Tone frequency of the fox. For reference: c-major-scale: 440 494 523 587 659 698 784 880 988 1047

#define TIME_TO_TX 200           // Time ESP32 will transmit (in ms)
#define TIME_TO_SLEEP  1800      // Time ESP32 will go to sleep (in ms)

#define DATA_PIN 3               // Pin of the ESP32 connected to the data pin of the transmitter module
#define TX_ARTIFICIAL_VCC_PIN 4  // Pin of the ESP32 providing power to the transmitter module due to unused enable pin

#define uS_TO_MS_FACTOR 1000     // Conversion factor for micro seconds to ms

void setup() {
  // set pin modes
  pinMode(TX_ARTIFICIAL_VCC_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // set wakeup timer
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_MS_FACTOR);

  // start TX
  digitalWrite(TX_ARTIFICIAL_VCC_PIN, HIGH);  // enable transmitter module
  digitalWrite(LED_BUILTIN, LOW);             // enable built-in LED
  tone(DATA_PIN, FREQ_HZ);                    // output tone to transmitter

  delay(TIME_TO_TX);                          // wait...

  // stop TX
  noTone(DATA_PIN);                           // stop tone
  digitalWrite(LED_BUILTIN, HIGH);            // disable LED
  digitalWrite(TX_ARTIFICIAL_VCC_PIN, LOW);   // disable transmitter module

  esp_deep_sleep_start();                     // go to deep sleep
}

void loop() {
  // never executed because of deep sleep
}
