const int RELE_FECHAR = 26;
const int RELE_ABRIR = 27;
int posicaoAtual = 20;
int posicaoDesejada = 50;
const int MS_POR_PORCENTO = 70;

int releX() {
  if (posicaoAtual > posicaoDesejada){
    return (posicaoAtual - posicaoDesejada) * MS_POR_PORCENTO;
   } else {
    return (posicaoDesejada - posicaoAtual) * MS_POR_PORCENTO;
  }
}

void RELE_1() {
  digitalWrite(RELE_FECHAR, HIGH);
  delay(releX());
  digitalWrite(RELE_FECHAR, LOW);
  posicaoAtual = posicaoDesejada;
}

void RELE_2() {
  digitalWrite(RELE_ABRIR, HIGH);
  delay(releX());
  digitalWrite(RELE_ABRIR, LOW);
  posicaoAtual = posicaoDesejada;
}

void moverJanela() {
  if (posicaoDesejada > 100) {
     posicaoDesejada = 100;
  } 
  if (posicaoDesejada < 0) {
     posicaoDesejada = 0;
  } 
  if (posicaoDesejada == posicaoAtual) {
    return;
  } 
  if (posicaoAtual < posicaoDesejada) {
    RELE_1();
  } else {
    RELE_2();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(RELE_FECHAR, OUTPUT);
  pinMode(RELE_ABRIR, OUTPUT);
  moverJanela();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}
