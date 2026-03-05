# ESP8266 AM32/BLHeli ESC 1-Wire PC Link

基于 ESP8266 的 AM32 烧录器，移植自 AM32 官方 Wiki 的 Arduino PC Link 方案。

---

## 支持的开发板

ESP-01S / ESP-12E/F / NodeMCU / Wemos D1 Mini，以及所有 ESP8266 系列开发板。

---

## 接线

| ESP8266 | 接到 |
| :--- | :--- |
| GND | 公共地（ESP8266、USB-TTL、电调三者共地） |
| VCC | USB-TTL 的 3.3V |
| CH_PD / EN | 3.3V（必须上拉，否则芯片不工作） |
| RX (GPIO3) | USB-TTL 的 **TX** |
| TX (GPIO1) | USB-TTL 的 **RX** |
| GPIO2 | 电调信号线 |

> ⚠️ **注意**：ESP8266 启动时 GPIO2 必须为高电平。如遇无法启动，先断开电调信号线，等芯片启动后再接上。

---

## 烧录固件

1. Arduino IDE 安装 ESP8266 板级支持包
2. 选择对应板型（或用 Generic ESP8266 Module）
3. GPIO0 接地后上电，进入烧录模式
4. 打开 `.ino` 文件，点击上传

---

## 使用方法

1. 按上表接好线，电调正常供电
2. 打开 AM32 Config Tool 或 BLHeliSuite
3. 选择 USB-TTL 对应的 COM 口，连接即可

---

## 参考

- [AM32 官方 Arduino PC Link 教程](https://wiki.am32.ca/guides/Arduino-PC-Link.html)

---

# ESP8266 AM32/BLHeli ESC 1-Wire PC Link (English)

ESP8266 port of the AM32 Wiki "PC Link by Arduino" project.

## Wiring

| ESP8266 | Connect to |
| :--- | :--- |
| GND | Common ground (ESP8266 + USB-TTL + ESC) |
| VCC | 3.3V from USB-TTL adapter |
| CH_PD / EN | 3.3V pull-up |
| RX (GPIO3) | USB-TTL **TX** |
| TX (GPIO1) | USB-TTL **RX** |
| GPIO2 | ESC signal wire |

> ⚠️ GPIO2 must be HIGH during boot. If the ESP8266 won't start, disconnect the ESC signal wire, power up first, then reconnect.

## Flash

1. Install ESP8266 board support in Arduino IDE
2. Select your board (or Generic ESP8266 Module)
3. Ground GPIO0 and power on to enter flash mode
4. Open `.ino`, click Upload

## Usage

1. Wire up as above, power the ESC normally
2. Open AM32 Config Tool or BLHeliSuite
3. Select the COM port of your USB-TTL adapter and connect
