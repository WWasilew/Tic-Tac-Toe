# Tic-Tac-Toe

![image alt](https://github.com/WWasilew/Tic-Tac-Toe/blob/e7b0e1941271bee0507c519105f02f50bd544813/logo.png)

This is a simple implementation of the classic Tic-Tac-Toe game written in C, with the added feature of allowing players to customize the board size. The game is a great demonstration of fundamental programming concepts, including arrays, loops, and user input handling.

## Features

- **Customizable Board Size:** Play on a board of any size (e.g., 3x3, 5x5).
- **Player vs Player:** Two players can compete in turn-based gameplay.
- **Player vs Computer:** Challenge the computer, which uses the Minimax algorithm for optimal moves.
- **Win Condition Detection:** Automatically detects when a player wins or the game ends in a draw.
- **User-Friendly Interface:** Text-based interface with clear instructions.

## Technology Stack

- **Programming Language:** C

## Getting Started

Follow these steps to compile and play the game on your local machine.

### Prerequisites

- A C compiler (e.g., GCC) installed on your system.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/WWasilew/Tic-Tac-Toe.git
   ```
2. Navigate to the project directory:
   ```bash
   cd Tic-Tac-Toe
   ```

### Compilation

1. Compile the source code using your C compiler:
   ```bash
   gcc -o tic_tac_toe tictactoe.c
   ```

### Running the Game

1. Run the compiled program:
   ```bash
   ./tic_tac_toe
   ```
2. Follow the on-screen instructions to select the board size and play the game.

## How to Play

1. **Choose the board size:** Enter the desired size of the board (e.g., 3 for a 3x3 board).
2. **Choose game mode:** Select whether to play against another player or the computer.
3. **Take turns:** Players take turns entering their moves by specifying the row and column number.
4. **Win or Draw:** The game ends when a player achieves the required number of marks in a row, column, or diagonal, or when the board is full (resulting in a draw).


## Project Structure

```
Tic-Tac-Toe/
├── tictactoe.c      # Main game logic
├── README.md        # Project documentation
└── LICENSE          # License information
```

## Contributing

Contributions are welcome! If you'd like to improve the game or add new features, follow these steps:

1. Fork the project.
2. Create your feature branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add some feature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature-name
   ```
5. Open a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

Created by [WWasilew](https://github.com/WWasilew). Feel free to reach out for questions or suggestions!

