# Robot Path Tracking System

This project consists of an Arduino-based robot control system with Bluetooth connectivity and path logging capabilities, along with a Python-based visualization tool for analyzing the robot's movement patterns.

## Hardware Requirements

### Arduino Setup

- Arduino Board
- Bluetooth Module
- SD Card Module
- Motor Drivers (BTS)
- Motors (B1 and B2)

### Pin Connections

#### SD Card Module

- GND → GND
- VCC → 5V
- MISO → Pin 12
- MOSI → Pin 11
- SCK → Pin 13
- CS → Pin 4

#### Motor Connections (BTS)

- B1_R_PWM → Pin 5
- B1_L_PWM → Pin 6
- B2_R_PWM → Pin 9
- B2_L_PWM → Pin 10

## Software Components

### 1. Arduino Code (robot_control.ino)

Controls the robot's movements and logs data to SD card:

- Bluetooth command reception
- Motor control
- Movement logging to SD card
- Supports various movement commands (forward, backward, left, right)

#### Movement Commands

- 'F' - Forward
- 'B' - Backward
- 'L' - Left turn
- 'R' - Right turn
- 'S' - Stop
- 'G' - Forward-Left
- 'I' - Forward-Right
- 'H' - Backward-Left
- 'J' - Backward-Right
- 'X' - Special Dance Movement

#### Turning Mechanism

- Right turn: 8 commands = 90 degrees
- Left turn: 7 commands = 90 degrees

### 2. Python Visualization (plot_trajectory.py)

Visualizes the robot's movement path from logged data:

- Reads path.txt from SD card
- Plots trajectory with start/end points
- Shows movement direction with arrows
- Displays total movement count

## File Structure

```
robot_project/
│
├── Arduino/
│   └── robot_control/
│       └── robot_control.ino
│
├── Python/
│   └── visualization/
│       └── plot_trajectory.py
│
└── path.txt
```

## Setup Instructions

### Arduino Setup

1. Connect all hardware components according to pin connections
2. Upload robot_control.ino to Arduino board
3. Insert formatted SD card (FAT32)
4. Power up the system

### Python Visualization Setup

1. Install required Python packages:
   ```bash
   pip install matplotlib numpy
   ```
2. Copy path.txt from SD card to the same directory as plot_trajectory.py
3. Run the visualization:
   ```bash
   python plot_trajectory.py
   ```

## Usage

### Robot Operation

1. Power on the robot
2. Connect via Bluetooth
3. Send movement commands
4. Movement data is automatically logged to path.txt

### Data Analysis

1. Transfer path.txt from SD card to computer
2. Run plot_trajectory.py
3. View the generated movement visualization

## Log File Format

path.txt structure:

```
Movement Log Start
forward
right
forward
left
...
```

## Notes

- SD card must be formatted in FAT32
- Each new run creates a fresh path.txt file
- Only main movements (forward, backward, left, right) are logged
- Visualization starts from center of plot

## Troubleshooting

### Common Issues

1. SD Card Initialization Failed

   - Check SD card format (must be FAT32)
   - Verify pin connections
   - Try reducing SPI clock speed

2. Bluetooth Connection Issues

   - Check baud rate (default 9600)
   - Verify Bluetooth module connections

3. Movement Tracking Issues
   - Ensure path.txt is being written correctly
   - Check SD card write permissions
   - Verify proper command reception

## Contributing

Feel free to submit issues and enhancement requests.

## License

This project is open source and available under the MIT License.
