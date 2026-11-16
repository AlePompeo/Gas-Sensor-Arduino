# 🔥 Arduino Safety Monitor — Gas, Fiamme e Temperatura

> **Arduino environmental safety monitor**: gas (MQ sensor), flame (IR) and temperature (NTC thermistor, Steinhart-Hart) detection with graded buzzer alerts, adaptive 16x2 LCD and Bluetooth data streaming. Italian documentation.

![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-00979D?logo=arduino&logoColor=white) ![Sensors](https://img.shields.io/badge/Sensors-gas%20%C2%B7%20flame%20%C2%B7%20temperature-d32f2f) ![Bluetooth](https://img.shields.io/badge/Bluetooth-serial-0082FC?logo=bluetooth&logoColor=white)

Sistema di monitoraggio ambientale basato su **Arduino** in grado di rilevare perdite di gas, presenza di fiamme e temperature anomale in tempo reale, con avvisi sonori graduali, display LCD adattivo e trasmissione dati via Bluetooth.

---

## 📌 Descrizione

Il progetto implementa un sistema di sicurezza domestica/industriale che acquisisce continuamente i dati da tre sensori ambientali e reagisce in maniera proporzionale al livello di rischio rilevato. Il sistema distingue tra situazioni di **allerta lieve** e **pericolo elevato**, modulando di conseguenza il buzzer, il display LCD e i messaggi seriali inviati via Bluetooth.

---

## ✨ Funzionalità

- **Rilevamento gas** — lettura analogica continua del sensore MQ (in ppm)
- **Rilevamento fiamme** — sensore IR per la presenza di fiamme vicine o lontane
- **Misurazione temperatura** — termistore NTC con formula di Steinhart-Hart per conversione precisa in °C
- **Buzzer graduato** — allerta soft (`600 Hz`) o warning critico (`2000/1000 Hz`) in base alla combinazione di rischi
- **Display LCD 16×2** — messaggi di stato scrollanti, luminosità adattiva tramite fotoresistore con media mobile su buffer circolare
- **Backlight adattiva** — il display si spegne automaticamente in assenza di rischi e in condizioni di luce ambientale sufficiente; può essere forzato ON da un pulsante fisico
- **Trasmissione Bluetooth** — dati di temperatura, gas e stato fiamma inviati via seriale ogni ciclo
- **Livelli di rischio combinati** — gestione di 14 scenari distinti (singoli e combinati) con messaggi specifici per ognuno

---

## 🧠 Logica di Funzionamento

### Sensori e soglie

| Sensore | Pin | Soglia bassa | Soglia alta |
|---------|-----|-------------|-------------|
| Gas (MQ) | `A0` | 350 ppm | 500 ppm |
| Fiamma (IR) | `A1` | > 500 (no fiamma) | < 70 (fiamma intensa) |
| Temperatura (NTC) | `A4` | 45 °C | 60 °C |
| Fotoresistore | `A5` | — | — |

### Livelli di allerta Buzzer

| Scenario | Tipo allerta |
|----------|-------------|
| Gas + Fiamma + Temperatura elevati | ⚠️ Warning critico |
| Gas alto + Fiamma | ⚠️ Warning critico |
| Gas + Temperatura > 60°C | ⚠️ Warning critico |
| Fiamma intensa + Temperatura > 60°C | ⚠️ Warning critico |
| Gas basso, Fiamma debole, Temperatura moderata | 🔔 Soft alert |

### Ciclo display (Activity Loop)

```
[0 – 2000]    → Testo scrollante animato
[2000 – 2001] → Invio dati Bluetooth
[2001 – 2300] → Messaggio stato corrente (rischio specifico)
[2300+]       → Info sensori (Gas ppm + Temperatura °C) → reset
```

### Luminosità LCD

La luminosità del backlight è calcolata tramite una **parabola inversa** sul valore grezzo del fotoresistore, poi mediata su un **buffer circolare da 550 campioni** per eliminare il flickering. Il valore minimo garantito è 140/255 quando ci sono rischi attivi.

---

## 🔌 Schema Pin

| Componente | Pin Arduino |
|------------|------------|
| LCD RS, EN, D4–D7 | 3, 2, 4, 5, 6, 7 |
| LCD Backlight (PWM) | 9 |
| Buzzer | 11 |
| Pulsante display | 8 |
| Sensore gas (MQ) | A0 |
| Sensore fiamma (IR) | A1 |
| Termistoro NTC | A4 |
| Fotoresistore | A5 |

---

## 📁 Struttura del Progetto

```
.
├── main.ino           # Setup e loop principale
├── controller.h       # Logica buzzer, display e activity loop
└── functions.h        # Sensori, librerie, costanti e funzioni di supporto
```

---

## 🛠️ Dipendenze

- [LiquidCrystal](https://www.arduino.cc/reference/en/libraries/liquidcrystal/) — libreria standard Arduino per display LCD HD44780
- `math.h` — calcolo logaritmico per la formula di Steinhart-Hart del termistoro

---

## ⚙️ Compilazione e Upload

1. Aprire il progetto con **Arduino IDE** (versione 1.8.x o 2.x)
2. Selezionare la board corretta (es. **Arduino Uno**)
3. Verificare le connessioni hardware secondo lo schema pin
4. Caricare lo sketch con **Upload** (`Ctrl+U`)
5. Aprire il **Serial Monitor** a `9600 baud` per visualizzare i dati Bluetooth

---

## 📄 Licenza

Tutti i diritti riservati © — il contenuto di questo repository non può essere copiato, distribuito o utilizzato senza esplicito permesso dell'autore.

---

*Keywords: Arduino, gas sensor, MQ sensor, flame sensor, NTC thermistor, Steinhart-Hart, LCD 16x2, Bluetooth, safety monitor, embedded, IoT.*
