/* PROJETO DE ORTA INTELIGENTE
 * Automacao da irrigacao e coleta de dados
 * 
 * @claudio monteiro
 * @douglas carvalho
 *
 */

// incluir pacotes
#include <dht.h>
dht DHT;

// definir conexoes dos pinos e variaveis 
const int pin_relay = 6;
const int pin_umidadesolo = A0;
const int pin_dht = 5;
const int pin_ldr = A1;

int valor_umidadesolo;
int valor_ldr;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Inicializando sistema");

  // definir pin do relay como output
  pinMode(pin_relay, OUTPUT);

}


void loop() {

  //--------------------- LEITURAS

  // inicar com relay inativo 
  digitalWrite(pin_relay,1);  

  // ler umidade do solo
  valor_ldr = analogRead(pin_ldr);

  // ler umidade do solo
  valor_umidadesolo = analogRead(pin_umidadesolo);
  valor_umidadesolo = map(valor_umidadesolo,550,0,0,100);

  // ler DHT
  int chk = DHT.read11(pin_dht);

//--------------------- PRINT DAS INFORMACOES NO SERIAL
    
// printar valores no serial
  Serial.print("Umidade do Solo: ");Serial.print(valor_umidadesolo);Serial.println("%");
  Serial.print("Umidade do Ar: ");Serial.print(DHT.humidity);Serial.println("");
  Serial.print("Temperatura: ");Serial.print(DHT.temperature);Serial.println("");
  Serial.print("Luminosidade: ");Serial.print(valor_ldr);Serial.println("");

//--------------------- ACIONAR BOMBA DE AGUA

      if (valor_umidadesolo < 60){
        Serial.println("LIGAR BOMBA"); Serial.println("");
        digitalWrite(pin_relay, 0);   
        delay(5); // ligar agua por 5 segundos
        } 


delay(1000*6); // 10min delay [experimento rodando com 6 seg, multiplicar por 100 pra chegar em 10min]
  

}
