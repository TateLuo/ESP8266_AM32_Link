/*
 * ESP-01S / ESP8266 port of the original AVR one-wire passthrough bridge.
 *
 * Purpose:
 * - Bridge the USB-TTL adapter's UART pins (GPIO3 RX / GPIO1 TX) to a
 *   single AM32 / BLHeli style signal wire.
 * - Preserve the original behavior: when the host drives RX low, the ESC
 *   signal line is actively pulled low; otherwise the signal line is released
 *   and TX mirrors the level seen on the ESC signal line.
 *
 * Wiring on ESP-01S:
 * - USB-TTL TX  -> GPIO3 (RX)
 * - USB-TTL RX  -> GPIO1 (TX)
 * - ESC signal  -> GPIO2
 * - GND         -> common ground
 *
 * Important boot constraint:
 * - GPIO2 must stay high during reset/boot. The connected ESC signal line
 *   must not hold it low while the ESP-01S is powering up.
 *
 * Board target:
 * - "Generic ESP8266 Module" or any ESP-01/ESP-01S target in the ESP8266
 *   Arduino core.
 */

#include <Arduino.h>

static const uint8_t HOST_RX_PIN = 3;  // GPIO3, UART RX pin from USB-TTL TX
static const uint8_t HOST_TX_PIN = 1;  // GPIO1, UART TX pin to USB-TTL RX
static const uint8_t OW_PIN = 2;       // GPIO2, ESC signal line

static inline bool hostRxIsHigh() {
  return digitalRead(HOST_RX_PIN) == HIGH;
}

static inline bool owIsHigh() {
  return digitalRead(OW_PIN) == HIGH;
}

static inline void setHostTxHigh() {
  digitalWrite(HOST_TX_PIN, HIGH);
}

static inline void setHostTxLow() {
  digitalWrite(HOST_TX_PIN, LOW);
}

static inline void driveOwLow() {
  pinMode(OW_PIN, OUTPUT);
  digitalWrite(OW_PIN, LOW);
}

static inline void releaseOw() {
  // Drive high briefly for a sharper rising edge, then release to pull-up.
  pinMode(OW_PIN, OUTPUT);
  digitalWrite(OW_PIN, HIGH);
  pinMode(OW_PIN, INPUT_PULLUP);
}

void setup() {
  // We need GPIO1/GPIO3 as raw pins, not as the hardware UART.
  Serial.end();
  ESP.wdtDisable();

  pinMode(HOST_RX_PIN, INPUT_PULLUP);
  pinMode(HOST_TX_PIN, OUTPUT);
  setHostTxHigh();

  releaseOw();
}

void loop() {
  // Wait for the host line to become active (UART idle is high).
  while (hostRxIsHigh()) {
  }

  while (true) {
    // Host is driving a low bit/start bit: pull the one-wire line low too.
    driveOwLow();
    setHostTxLow();

    while (!hostRxIsHigh()) {
    }

    // Host released the line: release one-wire and mirror ESC response to TX.
    releaseOw();

    while (hostRxIsHigh()) {
      if (owIsHigh()) {
        setHostTxHigh();
      } else {
        setHostTxLow();
      }
    }
  }
}
