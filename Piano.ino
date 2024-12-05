#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // LCD

int octavaPot = A0;    // Pin del potenciómetro para seleccionar la octava
int bpmPot = A1;       // Pin del potenciómetro para seleccionar el BPM
int notas = 9;   // Pin del buzzer para notas musicales
int metronomoBuzzer = 8; // Pin del buzzer para el metrónomo

int doSensor = 2;   // Pin para el sensor "DO"
int reSensor = 3;   // Pin para el sensor "RE"
int miSensor = 4;   // Pin para el sensor "MI"
int faSensor = 5;   // Pin para el sensor "FA"
int solSensor = 6;  // Pin para el sensor "SOL"

unsigned long lastMetronomeTime = 0; // Tiempo para controlar el metrónomo
int intervalo = 0;                   // Intervalo calculado en ms para el metrónomo

void setup() {
  lcd.init();          // Inicializar el LCD
  lcd.backlight();     // Encender la retroiluminación del LCD
  lcd.setCursor(0, 0);
  lcd.print("Octava: "); // Mostrar mensaje inicial
  lcd.setCursor(0, 1);
  lcd.print("BPM: ");    // Mostrar BPM inicial

  pinMode(notas, OUTPUT);    // Configurar el buzzer de notas como salida
  pinMode(metronomoBuzzer, OUTPUT);// Configurar el buzzer del metrónomo como salida
  pinMode(doSensor, INPUT); //Se configuran los sensores
  pinMode(reSensor, INPUT);
  pinMode(miSensor, INPUT);
  pinMode(faSensor, INPUT);
  pinMode(solSensor, INPUT);

  Serial.begin(9600); // Inicializar el monitor serie para depuración
}

void loop() {
  // Leer los valores de los potenciómetros
  int potValOctava = analogRead(octavaPot);
  int potValBpm = analogRead(bpmPot);

  // Mapear los valores a octava (1 a 3) y BPM (29 a 252)
  int octave = map(potValOctava, 0, 1023, 1, 4);
  int bpm = map(potValBpm, 0, 1023, 29, 252);
  intervalo = 60000 / bpm; // Convertir BPM a milisegundos por beat

  // Mostrar la octava seleccionada en el LCD
  lcd.setCursor(8, 0);
  lcd.print("     ");        // Borrar el texto anterior
  lcd.setCursor(8, 0);
  lcd.print(octave);

  // Mostrar el BPM seleccionado en el LCD
  lcd.setCursor(5, 1);
  lcd.print("     ");        // Borrar el texto anterior
  lcd.setCursor(5, 1);
  lcd.print(bpm);

  // Activar el metrónomo solo si el BPM no es 29
  if (bpm != 29 && millis() - lastMetronomeTime >= intervalo) {
    tone(metronomoBuzzer, 1000, 50); // Emitir un tono breve para el metrónomo
    lastMetronomeTime = millis();    // Reiniciar el tiempo del metrónomo
  }

  // Detectar si se ha activado algún sensor y tocar la nota correspondiente
  if (digitalRead(doSensor) == LOW) {
    tocarNota(octave, 261, 523, 1046); // DO
  } else if (digitalRead(reSensor) == LOW) {
    tocarNota(octave, 294, 587, 1175); // RE
  } else if (digitalRead(miSensor) == LOW) {
    tocarNota(octave, 329, 659, 1318); // MI
  } else if (digitalRead(faSensor) == LOW) {
    tocarNota(octave, 349, 698, 1397); // FA
  } else if (digitalRead(solSensor) == LOW) {
    tocarNota(octave, 392, 784, 1568); // SOL
  }
}

void tocarNota(int octave, int freq1, int freq2, int freq3) {
  int freq = 0;

  // Seleccionar la frecuencia según la octava
  if (octave == 1) {
    freq = freq1; // Grave
  } else if (octave == 2) {
    freq = freq2; // Normal
  } else if (octave == 3) {
    freq = freq3; // Aguda
  }

  tone(notas, freq, 500); // Tocar la nota durante 500 ms
  delay(500);                   // Pausa entre notas
}
