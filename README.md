# Mini Arcade
## Assembly

![illuminated_view](https://github.com/sklf81/Mini-Arcade/blob/master/images/png/final_view.png)

![open_illuminated_view]((https://github.com/sklf81/Mini-Arcade/blob/main/images/png/illuminated_view.png))

![battery_view](https://github.com/sklf81/Mini-Arcade/blob/master/images/png/battery_view.png)

![open_side_view](https://github.com/sklf81/Mini-Arcade/blob/master/images/png/open_side.png)

### Notes
- The Mount for the OLED-Display is pretty tight
  - Caution when mounting
- Screwholes for the Joystick are misaligned
  - If Mounted with only two diagonal screws will fit nonetheless
- STL for the left side-panel provided
  - For the right panel mirror it either in FreeCAD (Model provided) or in your slicer-program
- Screws can be attached directly without inserts

Details can be gathered from the images above.

## Components 
| Component | Amount | Reference |
|-----------|--------|-----------|
| Joystick  | 1      | https://components101.com/modules/joystick-module |
| 8x8-Dot-Matrix-Module | 1 | https://www.instructables.com/DOT-Matrix-8x8-Using-Arduino/ |
| Arduino Nano | 1 | https://store.arduino.cc/products/arduino-nano |
| 9V Battery | 1 | - |
| INOX A2 M2 Screws 5x10 | 28 | - |
| Circular Toggle Switch | 1 | - |
| OLED Display SSD1306 128x32 | 1 | https://www.aeq-web.com/arduino-i2c-128x32-oled-display/|


## Software
Software for the game "snake" is provided:

|	File/Folder	|	Description	|	
|---|---|
|`/snakegame_lib`| Library for implementing snake |
|`/snakegame_lib/Snake.cpp`| Implemented methods for class 'Snake' |
|`/snakegame_lib/SnakeGame.cpp`| Implemented methods for class 'SnakeGame' |
|`/snakegame_lib/SnakeGame.h`| Headerfile for 'snakegame_lib' |
|`/snakegame_sketch` | Arduino: sketch-folder |
|`/snakegame_sketch/HeartlySystem5x7.h`| Custom font for OLED-display |
|`/snakegame_sketch/snakegame_sketch.ino`| ARduino-sketch |
|`source_test.cpp`| Example for utilizing 'snakegame_lib' |
|`snake.exe` | Executable for 'source_test.cpp' |
