/*
 * Copyright (c) 2015 by Thomas Trojer <thomas@trojer.net>
 * Decawave DW1000 library for arduino.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (c) 2019 by Yu-Ti Kuo <bobgash2@gmail.com>
 * Decawave DW1000 library for arduino.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file DeepSleepTest.ino
 * Use this to test deepSleep Function with your DW1000 from Arduino.
 * It performs an arbitrary setup of the chip and prints some information.
 * The NetworkAddress will save into the AON Memory and Restore from the AON Memory.
 * 
 * @todo
 *  - make real check of connection (e.g. change some values on DW1000 and verify)
 */

#include <SPI.h>
#include <DW1000.h>

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

void setup() {
  // DEBUG monitoring
  Serial.begin(115200);
  // initialize the driver
  DW1000.begin(PIN_IRQ, PIN_RST);
  DW1000.select(PIN_SS);
  Serial.println(F("DW1000 initialized ..."));
  // general configuration
  DW1000.newConfiguration();
  DW1000.setDeviceAddress(5);
  DW1000.setNetworkId(10);
  DW1000.commitConfiguration();
  Serial.println(F("Committed configuration ..."));
  // wait a bit
  delay(1000);
}

void loop() {
  // DEBUG chip info and registers pretty printed
  char msg[128];
  DW1000.getPrintableDeviceIdentifier(msg);
  Serial.print(F("Device ID: ")); Serial.println(msg);
  DW1000.getPrintableExtendedUniqueIdentifier(msg);
  Serial.print(F("Unique ID: ")); Serial.println(msg);
  DW1000.getPrintableNetworkIdAndShortAddress(msg);
  Serial.print(F("Network ID & Device Address: ")); Serial.println(msg);
  DW1000.getPrintableDeviceMode(msg);
  Serial.print(F("Device mode: ")); Serial.println(msg);
  // wait a bit
  Serial.println(F("Write the new configuration Address 6"));
  DW1000.setDeviceAddress(6);
  DW1000.setNetworkId(12);
  DW1000.commitConfiguration();
  Serial.println(F("DW1000 take a deep sleep."));
  DW1000.deepSleep();
  delay(1000);
  Serial.println(F("DW1000 wake up!"));
  DW1000.spiWakeup();

  DW1000.getPrintableDeviceIdentifier(msg);
  Serial.print(F("Device ID: ")); Serial.println(msg);
  DW1000.getPrintableExtendedUniqueIdentifier(msg);
  Serial.print(F("Unique ID: ")); Serial.println(msg);
  DW1000.getPrintableNetworkIdAndShortAddress(msg);
  Serial.print(F("Network ID & Device Address: ")); Serial.println(msg);
  DW1000.getPrintableDeviceMode(msg);
  Serial.print(F("Device mode: ")); Serial.println(msg);
  // wait a bit
  Serial.println(F("Write the new configuration Address 5"));
  DW1000.setDeviceAddress(5);
  DW1000.setNetworkId(10);
  DW1000.commitConfiguration();
  Serial.println(F("DW1000 take a deep sleep."));
  DW1000.deepSleep();
  delay(1000);
  Serial.println(F("DW1000 wake up!"));
  DW1000.spiWakeup();
}
