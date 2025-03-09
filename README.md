# FFontinental Office Management System

Welcome to **FFontinental**, a simulation of an office management system built in C. This program allows you to create and manage offices, divisions, and workers in a grid-based map. You can build offices, add divisions, hire workers, and navigate through the map to manage your offices.

---

## Features

- **Map Navigation**: Move north, south, east, or west on a 30x30 grid to explore and build offices.
- **Office Management**:
  - Build offices with unique names and IDs.
  - Delete offices when no longer needed.
- **Division Management**:
  - Add divisions with unique names and IDs.
  - Each division can have up to 5 types of workers: CEO, Director, Supervisor, Manager, and Staff.
- **Worker Management**:
  - Hire workers and assign them to specific divisions.
  - Workers are assigned salaries based on their positions.
- **Interactive CLI**: A user-friendly command-line interface for managing the system.

---

## How to Run

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/your-repo-name.git
   cd your-repo-name
2. **Compile the code**:
    ```bash
    gcc -o ffontinental your_file_name.c
3. **Run the program**:
    ```bash
    ./ffontinental

## Usage

1. **Start the Program:**
    The program will prompt you to create your first office. Enter FFontinental Office as the name.
2. **Main Menu:**
    You will see a menu with the following options:
    - **Add Division:** Create a new division in the current office.
    - **Add Worker:** Hire a worker and assign them to a division.
    - **View Office:** View details of the current office, including divisions and workers.
    - **View All Offices:** Display a list of all offices on the map.
    - **Delete Office:** Remove the current office.
    - **Move:** Navigate the map to explore or build new offices.
    - **Exit:** Exit the program.
3. **Navigation:**
    - Use the **Move** option to navigate the map. You can move north, south, east, or west.
    - If you land on an empty space, you can build a new office.
4. **Building Offices:**
    - When you build an office, you must provide a unique name. The program will generate a unique ID for the office.
5. **Managing Workers:**
    - Workers are assigned to divisions based on their roles (CEO, Director, Supervisor, Manager, Staff).
    - Each worker is assigned a unique ID and salary based on their position.

## Code Structure

1. **struct land:** Represents a land plot on the map. It can be an office or empty.
2. **struct division:** Represents a division within an office. It contains a table of workers.
3. **struct workers:** Represents a worker with details like ID, name, position, and salary.
4. **map[30][30]:** A 2D array representing the 30x30 grid map.
5. **traverse():** Handles movement on the map.
6. **printMenu():** Displays the main menu and handles user input.

## Contributing

Contributions are welcome!