/* PROJETO JARDIM INTELIGENTE
 * Automacao da irrigacao e coleta de dados
 * 
 * @claudio monteiro
 * @douglas carvalho
 * 
 */
 
#define relay_pin1 2

int key = 0;
int clocke = 0;

void setup() { 
  pinMode(relay_pin1, OUTPUT);
 Serial.begin(9600); 
} 



void loop() { 

  if (clocke < (60*9) or clocke > (60*15) ){
     clockSwitch(relay_pin1, 0);
    } else {
     clockSwitch(relay_pin1, 1);
      }

}

void clockSwitch(int pin_value, bool write_in){
      clocke += 1;
      digitalWrite(pin_value, write_in);
      delay(60000);   
  }
