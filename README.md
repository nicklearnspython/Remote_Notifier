# Remote_Notifier
Using an ESP8266, allow users with press a button to send a rebellion "bat signal" to move the motors of the connected objects.

## Components
* ESP8266 (WiFi enabled Arduino)
* TB6612FNG Dual Motor Driver Carrier (Pololu)
* Solarbotics GM2 224:1 Gear Motor Offset Output (Pololu)
* 2 buttons
* 2 LEDs(green and red)
* Solarbotics GMW (GM2/3/8/9 Gear Motor Mount)(Pololu)
* Screw Terminal Block: 2-Pin, 0.1″ Pitch, Side Entry (Pololu)

## Wiring
### ESP8266 ("ESP")
* GPIO5:  D1  <--> MD12    
* GPIO4:  D2  <--> MD11       
* GPIO0:  D3  <--> MD10      
* GPIO2:  D4  <--> MD9        
* GPIO14: D5  <--> Red LED   
* GPIO12: D6  <--> Green LED
* GPIO13: D7  <--> Button 1  
* GPIO15: D8  <--> Button 2  
* Vin         <--> 5V
* GND         <--> GND

### Motor Driver ("MD")
* GND:      MD1  <--> GND
* VCC:      MD2  <--> 5V
* AO1:      MD3  <--> Motor Input 1
* AO2:      MD4  <--> Motor Input 2
* VMOT:     MD7  <--> 5V
* GND:      MD8  <--> GND
* PWMA:     MD9  <--> ESP-D4
* AIN2:     MD10 <--> ESP-D3
* AIN1:     MD11 <--> ESP-D2
* Standby:  MD12 <--> ESP-D1
