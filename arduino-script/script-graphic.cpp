// ====================================================
// =  Código conjunto LM35 + DHT11 (Retorno Gráfico)  =
// ====================================================

#include "DHT.h" // importando biblioteca do DHT
#define dht_type DHT11  // definindo o tipo do DTH PARA dht11 (existem outros DHT, DHT22, DHT23 etc)

// ================= DEIFINIÇÃO DE VARIÁVEIS ====================
// ---- DHT11
int dht_pin = A1; // porta de escuta do DHT11 (pino)
DHT dht_1 = DHT(dht_pin, dht_type); // variável do tipo DHT recebendo a porta(analógico 1) e tipo do dht (DHT11)
// ---- LM35
int pinoSensor = 5; // porta de escuta
int valorLido = 0; // variável para receber o valor lido (variável auxiliar)
float temperatura = 0; //Variável que armazenará a e irá imprimir a temperatura
int linha = 0; // variáveis para controlar a quantidade de linhas


// ======================= FUNÇÃO DE SETUP INICIAL =========================
// --- executa uma única vez
void setup() {
    dht_1.begin(); // inicializando os componentes para a leitura do sensor DHT11
    Serial.begin(9600); // inicializando a comunicação do serial(console) para receber os dados em 9600 bauds.
}

// ======================= FUNÇÃO DE LOOP ===========================
// --- executa constantemente, repetindo
void loop() {
    // --- DTH11 (umidade)
    float umidade = dht_1.readHumidity(); // capturando os dados de Umidade em Decimal (float = ponto flutuante)

    // --- LM35 (temperatura)
    valorLido = analogRead(pinoSensor); // capturando os dados de maneira analógica
    temperatura = valorLido * 0.00488; // convertendo os dados analógicos para milivolts -> 5 volts/ 1023 = 0,0048 precisão do A/D
    temperatura = temperatura * 100; // convertendo os  milivolts para celsius (a cada 10mV == 1 grau Celsius)

    // apresentando a temperatura em celsius
    Serial.print(temperatura);
    Serial.print("\n");
    Serial.print(",");

    // inicia a impressão dos dados de umidade, fica sempre iniciando
    if(isnan(umidade)){
        
    } else {
        Serial.println(umidade);
    }

    linha++; // incrementa a quantidade de linhas (leitura)

    // verifica se é maior que 100 linhas 
    if(linha > 2){
        Serial.flush(); // Limpa o console
        linha = 0; // se sim, volta do 0, para limitar a leitura para apenas as ultimas 100 leituras (100 linhas)
    }
    delay (1000); //Tempo 1 seg para realizar a próxima leitura;=
}