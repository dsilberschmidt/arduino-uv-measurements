#include <Arduino_MKRENV.h>

String etiqueta = "";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!ENV.begin()) {
    Serial.println("Error: no se pudo iniciar el MKR ENV Shield");
    while (1);
  }

  Serial.println("Listo. Podés escribir una etiqueta (ej: sombra toldo)");
  Serial.println("Las lecturas comenzarán en 5 segundos...");
  delay(5000);
}

void loop() {
  // Leer si hay texto desde el usuario
  if (Serial.available() > 0) {
    etiqueta = Serial.readStringUntil('\n');
    etiqueta.trim();  // Quita espacios extras o \r
  }

  float uva = ENV.readUVA();
  float uvb = ENV.readUVB();
  float uvIndex = ENV.readUVIndex();

  Serial.print("UVA: "); Serial.print(uva, 2);
  Serial.print(" | UVB: "); Serial.print(uvb, 2);
  Serial.print(" | Índice UV: "); Serial.print(uvIndex, 2);

  if (etiqueta.length() > 0) {
    Serial.print(" | Etiqueta: "); Serial.println(etiqueta);
    etiqueta = "";  // Limpiar luego de usar
  } else {
    Serial.println();
  }

  delay(5000);
}
