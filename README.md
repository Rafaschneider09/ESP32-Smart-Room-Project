# ESP32 Smart Room

A personal project to control my room's window, AC, fan and lights from my phone using an ESP32. The ESP32 receives commands over Wi-Fi and turns them into actions: infrared signals for the AC and fan, relays for the window motor, and a smart light for the lighting.

## Status

Work in progress. So far, only the window logic exists, and only in simulation.

- [x] Message format designed (JSON)
- [x] Window position logic (0-100%) written and tested in the Wokwi simulator, with LEDs standing in for the relays
- [ ] Receive and parse JSON messages on the ESP32
- [ ] Wi-Fi connection and phone app
- [ ] Infrared control for the AC and fan
- [ ] Smart light control
- [ ] Real hardware: relays wired to the window motor

## How It Works

Planned architecture:

```
phone -> Wi-Fi -> ESP32 -> IR LED (AC, fan)
                        -> 2 relays (window motor)
                        -> smart light
```

The phone sends a small JSON message saying which device to control and what to do. The ESP32 reads it and triggers the matching output.

## Commands

 Device and Actions: 

 AC -> on/off, temperature, mode 
 Fan -> on/off, level 1-3, normal/exhaust mode 
 Lights -> on/off, color, dimmer 
 Window -> move to a position from 0% to 100% 

## Message Format

Each message has a `device`, an `action` and, when needed, a named numeric value:

```json
{"device": "AC", "action": "ligar", "temperatura": 17}
{"device": "ventilador", "action": "ligar", "nivel": 2}
{"device": "janela", "action": "mover", "posicao": 50}
```

Device names and actions are in Portuguese. The ESP32 does not read these messages yet, for now the window values are set directly in the code.

## Window Logic

The window motor has no position sensor, so the ESP32 estimates the position using time:

- 0% = fully open, 100% = fully closed
- Full travel takes about 7000 ms, so each 1% takes 70 ms (to be measured on the real window)
- The ESP32 keeps the estimated current position in a variable

When a new position is requested:

1. Limit the value to the 0-100% range
2. If it equals the current position, do nothing
3. Choose the direction (relay 1 closes, relay 2 opens)
4. Turn that relay on for `distance x 70 ms`, then off
5. Update the current position

Only one relay is activated per move.

Known limitations: the starting position is assumed, and the estimate can drift over time since there is no sensor.

This was my first sketch while working out the logic:

![Window motors - idea sketch](<docs/ESP32 - Window idea.jpeg>)

## How To Run The Simulation

1. Go to [wokwi.com](https://wokwi.com) and create a new ESP32 project (Arduino)
2. Replace the contents of `sketch.ino` and `diagram.json` with the files from this repo
3. Change `posicaoAtual` and `posicaoDesejada` at the top of the sketch and run again

In the diagram, the red LED (pin 26) represents the "close" relay and the green LED (pin 27) represents the "open" relay. The LED stays on for `distance x 70 ms`.