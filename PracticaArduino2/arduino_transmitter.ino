/**
 * @file arduino_transmitter.ino
 * @brief Transmisor de tramas PRT-7 para Arduino
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 * 
 * Este sketch envía tramas del protocolo PRT-7 por el puerto serial.
 * Conecta el Arduino por USB y abre el puerto serial en tu programa C++.
 * 
 * Configuración:
 * - Velocidad: 9600 baud
 * - Board: Arduino Uno/Mega/Nano (cualquiera sirve)
 * - Puerto: El que asigne tu sistema operativo
 */

// Mensaje de ejemplo que se transmitirá
// Puedes modificar este array para enviar diferentes mensajes
const char* tramas[] = {
  "L,H",
  "L,O",
  "L,L",
  "M,2",
  "L,A",
  "L,Space",  // Espacio especial
  "L,W",
  "M,-2",
  "L,O",
  "L,R",
  "L,L",
  "L,D"
};

const int numTramas = 12;
int tramaActual = 0;
bool transmisionCompleta = false;

void setup() {
  // Inicializar comunicación serial a 9600 baud
  Serial.begin(9600);
  
  // Esperar a que se establezca la conexión
  delay(2000);
  
  Serial.println("Arduino PRT-7 Transmisor Iniciado");
  Serial.println("Esperando 3 segundos antes de transmitir...");
  delay(3000);
}

void loop() {
  if (!transmisionCompleta) {
    if (tramaActual < numTramas) {
      // Enviar la trama actual
      Serial.println(tramas[tramaActual]);
      
      // Avanzar a la siguiente trama
      tramaActual++;
      
      // Esperar 1 segundo entre tramas
      delay(1000);
    } else {
      // Transmisión completa
      Serial.println("FIN");
      transmisionCompleta = true;
    }
  }
  
  // Si ya terminó, no hacer nada (mantener el Arduino en espera)
  if (transmisionCompleta) {
    delay(10000);  // Espera de 10 segundos
  }
}

