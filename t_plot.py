import matplotlib.pyplot as plt
import numpy as np


def read_log_file(filename='path.txt'):
    with open(filename, 'r') as file:
        lines = file.readlines()
        if 'Movement Log Start' in lines[0]:
            movements = [line.strip() for line in lines[1:]]
        else:
            movements = [line.strip() for line in lines]
    return movements


def calculate_trajectory(movements):
    x = 10
    y = 10
    angle = 0
    step = 1
    RIGHT_ANGLE_PER_COMMAND = 90/8
    LEFT_ANGLE_PER_COMMAND = 90/8
    x_coords = [x]
    y_coords = [y]

    for move in movements:
        if move == 'forward':
            x += step * np.cos(np.radians(angle))
            y += step * np.sin(np.radians(angle))
        elif move == 'backward':
            x -= step * np.cos(np.radians(angle))
            y -= step * np.sin(np.radians(angle))
        elif move == 'left':
            angle += LEFT_ANGLE_PER_COMMAND
        elif move == 'right':
            angle -= RIGHT_ANGLE_PER_COMMAND

        x_coords.append(x)
        y_coords.append(y)

    return x_coords, y_coords


def plot_trajectory(x_coords, y_coords):
    plt.figure(figsize=(10, 10))
    plt.plot(x_coords, y_coords, 'b-', linewidth=2, label='Path')
    plt.plot(x_coords[0], y_coords[0], 'go', markersize=15, label='Start')
    plt.plot(x_coords[-1], y_coords[-1], 'ro', markersize=15, label='End')

    for i in range(0, len(x_coords)-1, 5):
        dx = x_coords[i+1] - x_coords[i]
        dy = y_coords[i+1] - y_coords[i]
        if dx != 0 or dy != 0:
            plt.arrow(x_coords[i], y_coords[i], dx*0.2, dy*0.2,
                      head_width=0.1, head_length=0.2, fc='blue', ec='blue')

    plt.grid(True)
    plt.axis('equal')
    plt.title('Robot Trajectory')
    plt.xlabel('X Position')
    plt.ylabel('Y Position')
    plt.legend()
    plt.text(0.02, 0.98, f'Total Movements: {len(x_coords)-1}',
             transform=plt.gca().transAxes, fontsize=10,
             verticalalignment='top')
    plt.show()


def main():
    try:
        movements = read_log_file()
        x_coords, y_coords = calculate_trajectory(movements)
        plot_trajectory(x_coords, y_coords)
        print(f"Total movements: {len(movements)}")
        print(f"Starting position: ({x_coords[0]:.2f}, {y_coords[0]:.2f})")
        print(f"Ending position: ({x_coords[-1]:.2f}, {y_coords[-1]:.2f})")
    except FileNotFoundError:
        print("Error: path.txt file not found!")
    except Exception as e:
        print(f"An error occurred: {str(e)}")


if __name__ == "__main__":
    main()
