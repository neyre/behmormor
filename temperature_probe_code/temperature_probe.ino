#include <max6675.h>
#include <Wire.h>

// declarations for the max6675 boards on SPI
int thermoDO = 19; //called SO on the max6675
int thermoCS = 23; //called CS on the max6675
int thermoCLK = 18; //called SCK on the max6675

int thermoCS2 = 5;

bool unit_F = true; //true = °F - false = °C
 
 
// CLK/SCK, CS, DO/SO
MAX6675 thermocouple(18, 23, 19);
MAX6675 thermocouple2(18, 22, 19); 
MAX6675 thermocouple3(18, 21, 19); 


void setup() {
  Serial.begin(115200);
  Serial.println("MAX6675 test");

  delay(500);
}

//Send Serial Data
void Command_WRITE(){
    Serial.print("0.00,");
    if (unit_F) {
        Serial.print(thermocouple.readFahrenheit());
        Serial.print(",");
        Serial.print(thermocouple2.readFahrenheit());
        Serial.print(",");
        Serial.print(thermocouple3.readFahrenheit());
    }
    else if (!unit_F) {
        Serial.print(thermocouple.readCelsius());
        Serial.print(",");
        Serial.print(thermocouple2.readCelsius());
        Serial.print(",");
        Serial.print(thermocouple3.readCelsius());
    }
    Serial.println(",0.00");
    // Serial.println(",0.00,0.00");
}

//Parsing Serial Commands
void handleSerialCommand(){   

   if (Serial.available()>0){
        String msg = Serial.readStringUntil('\n');

        if (msg.indexOf("CHAN;")== 0){  //Ignore this Setting
            Serial.print("#OK");
        }
        else if (msg.indexOf("UNITS;")== 0){

            if (msg.substring(6,7)=="F"){   //Change to Farenheit
                unit_F = true;
                Serial.println("#OK Farenheit");
            }
            else if (msg.substring(6,7)=="C"){  //Change to Celsius
                unit_F = false;
                Serial.println("#OK Celsius");
            }

        }
        else if (msg.indexOf("READ")==0){   //Send Temps
           Command_WRITE();

       }
   }

}


void loop()
{
    handleSerialCommand();
    delay(500);
}
