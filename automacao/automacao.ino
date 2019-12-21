int pin_relay = 6;
int pin_umidadesolo = A0;
int pin_umidadesolo = A0;
int valor_umidadesolo ;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Inicializando sistema");
  delay(2000);

  pinMode(pin_relay,OUTPUT);

}

// ciclos
int cycles = 0;

void loop() {

  // desligar relay 
  digitalWrite(pin_relay,1);  

  // verificar umidade do solo
  valor_umidadesolo = analogRead(pin_umidadesolo);
  valor_umidadesolo = map(valor_umidadesolo,550,0,0,100);
  
  delay(1000*60*10); // 10 min delay
  cycles = cycles + 1;
  
  Serial.print("Ciclo "); Serial.print(cycles); Serial.print(": ");
  Serial.print("Umidade do Solo : ");Serial.print(valor_umidadesolo);Serial.println("%");



  // verificar a cada 6 horas a necessidade de ligar
  if (cycles == 6){

      cycles = 0; // zerar ciclo de 6h

      if (valor_umidadesolo < 20){
        Serial.println("LIGAR");
        digitalWrite(pin_relay, 0);  // ligar relay por 6 ses
        delay(6000);

        } '

  }

}
