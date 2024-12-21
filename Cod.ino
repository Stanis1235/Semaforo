#define esperaDoSemafero 20
#define minimoDoBotao 0

#define esperaDoAmarelo 5
#define esperaDoVermelho 10


#define Grren 0
#define Yellow 1
#define Red 2

#define Botao 2

int pinoLed[3] = {8, 4, 7};

int EDS = Grren;

int pino;

unsigned long espera = 0;

unsigned long espera2 = 0;

boolean mudarEspera = true;

boolean botaoPresionado = false;



void setup(){
  Serial.begin(9600);
  
  for (pino = 0; pino <= 2; pino++){
   	pinMode(pinoLed[pino], OUTPUT);
  }
  
  pinMode(Botao, INPUT_PULLUP);
  
  attachInterrupt(0, atc, FALLING);
  
  UpDate();
  
}

void loop(){

  if (millis() - espera >= esperaDoSemafero * 1000 || botaoPresionado){
  	Pessoas();
  }
  
  delay(10);
}



void UpDate(){
  for (pino = 0; pino <= 2; pino++){
   	digitalWrite(pinoLed[pino], LOW);
  }
  
  digitalWrite(pinoLed[EDS], HIGH);
}

void Pessoas(){
  if (mudarEspera){
    espera2 = millis();
    mudarEspera = false;
  }
  
  if (millis() - espera2 >= (esperaDoVermelho + esperaDoAmarelo) * 1000){
    EDS = Grren;
    UpDate();
    espera = millis();
    mudarEspera = true;
    botaoPresionado = false;
  }else if (millis() - espera2 >= esperaDoAmarelo * 1000){
    EDS = Red;
    UpDate();
  }else{
    EDS = Yellow;
    UpDate();
  }
}

void atc(){
  if (millis() - espera >= minimoDoBotao * 1000){
    botaoPresionado = true;
  }
}