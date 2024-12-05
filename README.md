# README: Conexión y Configuración del Proyecto de Metrónomo y Notas Musicales

Este proyecto combina un metrónomo y un sistema para tocar notas musicales utilizando un Arduino, sensores, y una pantalla LCD de **16x2**. A continuación, se describen las conexiones de hardware y el propósito de cada componente.



## **Componentes Requeridos**
1. **Arduino Uno** o compatible.
2. **Pantalla LCD con módulo I2C** (16x2).
3. **Buzzer piezoeléctrico** (2 unidades).
4. **Potenciómetros** (2 unidades).
5. **Sensores táctiles o botones** (5 unidades).
6. **Cables y protoboard**.
7. **Fuente de alimentación o conexión USB**.



## **Esquema de Conexiones**

### **1. Pantalla LCD (I2C)**
- Conecta el módulo I2C al Arduino:
  - `VCC` -> `5V`
  - `GND` -> `GND`
  - `SDA` -> Pin `A4` (en Arduino Uno)
  - `SCL` -> Pin `A5` (en Arduino Uno)

### **2. Potenciómetros**
- Potenciómetro 1 (selección de octava):
  - Conecta el pin central al pin `A0` del Arduino.
  - Conecta un extremo a `5V` y el otro a `GND`.
  
- Potenciómetro 2 (selección de BPM):
  - Conecta el pin central al pin `A1` del Arduino.
  - Conecta un extremo a `5V` y el otro a `GND`.

### **3. Buzzer**
- Buzzer para las notas musicales:
  - Conecta el terminal positivo al pin `9` del Arduino.
  - Conecta el terminal negativo a `GND`.

- Buzzer para el metrónomo:
  - Conecta el terminal positivo al pin `8` del Arduino.
  - Conecta el terminal negativo a `GND`.

### **4. Sensores Táctiles o Botones**
- Conecta cada sensor al Arduino como sigue:
  - Sensor de "DO" -> Pin `2`
  - Sensor de "RE" -> Pin `3`
  - Sensor de "MI" -> Pin `4`
  - Sensor de "FA" -> Pin `5`
  - Sensor de "SOL" -> Pin `6`
  
- Conecta el otro terminal de cada sensor a `GND`.
- Si usas botones, agrega resistencias pull-down de 10kΩ entre los pines del botón y `GND`.



## **Funcionalidad del Código**

1. **Pantalla LCD:**
   - Muestra la octava seleccionada (1-3) y el BPM (29-252) en la pantalla **16x2**:
     - Línea 1: `Octava: X`
     - Línea 2: `BPM: Y`
2. **Potenciómetros:**
   - El potenciómetro 1 selecciona la octava para las notas musicales.
   - El potenciómetro 2 ajusta el BPM del metrónomo.
3. **Metrónomo:**
   - Genera un tono corto según el BPM configurado.
4. **Notas Musicales:**
   - Los sensores activan las notas `DO`, `RE`, `MI`, `FA`, y `SOL` con frecuencias ajustadas a la octava seleccionada.



## **Cómo Usar el Proyecto**

1. **Conecta los componentes siguiendo el esquema anterior.**
2. **Carga el código en el Arduino desde el IDE de Arduino.**
3. **Abre el monitor serie (9600 baudios) para verificar el estado del sistema.**
4. **Ajusta los potenciómetros para seleccionar octava y BPM.**
5. **Toca los sensores para reproducir las notas musicales.**
6. **Escucha el metrónomo para mantener el ritmo deseado.**



## **Actualizaciones para la Pantalla LCD de 16x2**

El código está diseñado para trabajar con la pantalla **16x2**. Cambios relevantes:
- El contenido mostrado en la pantalla se ajusta al espacio limitado de 16 caracteres por línea.
- Las funciones `lcd.print` aseguran que los valores de octava y BPM se sobrescriban correctamente sin desbordar el texto.
