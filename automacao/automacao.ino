/* PROJETO DE ORTA INTELIGENTE
 * Automacao da irrigacao e coleta de dados
 * 
 * @claudio monteiro
 * @douglas carvalho
 *
 */

// definir conexoes dos pinos
int pin_relay = 6;
int pin_umidadesolo = A0;
int valor_umidadesolo ;


void setup() {
  
  Serial.begin(9600);
  Serial.println("Inicializando sistema");

  // definir pin do relay como output
  pinMode(pin_relay,OUTPUT);

}


void loop() {

  // desligar relay 
  digitalWrite(pin_relay,1);  

  // verificar umidade do solo
  valor_umidadesolo = analogRead(pin_umidadesolo);
  valor_umidadesolo = map(valor_umidadesolo,550,0,0,100);

  Serial.print("Umidade do Solo : ");Serial.print(valor_umidadesolo);Serial.println("%");

      if (valor_umidadesolo < 30){
        Serial.println("Ligar bomba de água:");
        digitalWrite(pin_relay, 0);   
        delay(7000); // ligar agua por 7 sec
        } 

    delay(1000*60*10); // 10min delay
  

}
