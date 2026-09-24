# Splendor

`Splendor` is the first building block of the SplendorAI project.

It contains the digital implementation of the **Splendor Duel** board game. The implementation is intended to be reusable by other building blocks such as `AITrainer` and `UI`.

## Structure

```text
Splendor/

├── CMakeLists.txt
├── README.md
├── .gitignore
│
├── bin/
│   └── .gitkeep
│
├── doc/
│
├── inc/
│   ├── Action.hpp
│   ├── CardRow.hpp
│   ├── DecisionMaker.hpp
│   ├── Effect.hpp
│   ├── Game.hpp
│   ├── GameState.hpp
│   ├── Juwel.hpp
│   ├── JuwelBoard.hpp
│   ├── JuwelCard.hpp
│   ├── JuwelCardBuilder.hpp
│   ├── JuwelCardPyramid.hpp
│   ├── Player.hpp
│   └── VictoryCondition.hpp
│
├── mak/
│
├── src/
│   ├── Game.cpp
│   ├── GameState.cpp
│   ├── Juwel.cpp
│   ├── Player.cpp
│   └── main.cpp
│
└── tst/
    └── GameTest.cpp
```

## Components

### SplendorLib

`SplendorLib` is the reusable library containing the implementation of the game.

Production code that represents Splendor Duel's rules, game state, cards, jewels, board, players, and game logic belongs in this library.

The library does not contain an application `main()` function.

### Core game components

The game implementation is divided into small components with clearly defined responsibilities:

* **`Juwel`**
  Defines the different jewel types used by the game.

* **`JuwelCollection`**
  Stores and manages collections of jewels. It supports adding, removing, counting, and randomly taking jewels.

* **`Effect`**
  Defines the effects that can be associated with jewel cards.

* **`JuwelCard`**
  Represents a jewel card, including its cost, bonus, effects, crowns, and victory points.

* **`JuwelCardBuilder`**
  Provides a convenient way to construct jewel cards while keeping card creation separate from the card representation.

* **`CardRow`**
  Provides the common behavior for a row of cards with a closed stack and a fixed number of open cards.

* **`JuwelCardPyramid`**
  Manages the three levels of jewel cards used by the game.

* **`JuwelBoard`**
  Represents the jewel board and manages the jewels currently available on the board.

* **`VictoryCondition`**
  Defines the conditions that determine when a player has won the game.

* **`DecisionMaker`**
  Defines the interface used by a player to determine which action to take.

* **`Player`**
  Represents a player and owns the player's inventory, purchased cards, privilege scrolls, and `DecisionMaker`.

* **`Action`**
  Represents an action that can be selected by a `DecisionMaker` and subsequently validated and executed by the game.

* **`GameState`**
  Represents a snapshot of the game state. It is intended to provide a read-only view of the current game situation to components such as `DecisionMaker`.

* **`Game`**
  Owns the authoritative mutable game state and the two players. It is responsible for coordinating the different game components and validating and executing actions.

### Splendor

`Splendor` is the executable used to run the digital game.

It provides the application's `main()` function and links against `SplendorLib`.

The application is responsible for constructing the appropriate `DecisionMaker` objects and passing them to `Game`.

### SplendorTests

`SplendorTests` contains the unit tests for the Splendor implementation.

It links against `SplendorLib` and Google Test.

## Game architecture

The game is designed around a separation between the authoritative game state and the state used to make decisions.

```text
main()
 │
 ├── creates DecisionMaker 1
 ├── creates DecisionMaker 2
 │
 ▼
Game
 │
 ├── owns Player 1
 │     └── owns DecisionMaker 1
 │
 └── owns Player 2
       └── owns DecisionMaker 2
```

During gameplay, the decision-making flow is:

```text
Game
 │
 │ creates snapshot
 ▼
GameState
 │
 │ inspected by
 ▼
DecisionMaker
 │
 │ chooses
 ▼
Action
 │
 │ submitted to
 ▼
Game
 │
 │ validates & executes
 ▼
Game
```

`Game` owns the actual mutable state of the game.

`GameState` provides a snapshot that can be inspected by decision-making components without giving them direct access to the mutable game.

Each `Player` owns its own `DecisionMaker`. The application creates the decision makers and passes ownership to `Game`, which transfers them to the corresponding players.

Actions are ultimately validated and executed by `Game`, keeping game-rule enforcement inside the game implementation.

## Component relationships

```text
                         Game
                          │
          ┌───────────────┼──────────────────┐
          │               │                  │
          ▼               ▼                  ▼
       Player 1        Player 2        Game Components
          │               │                  │
          ▼               ▼          ┌───────┼───────────────┐
   DecisionMaker   DecisionMaker     ▼       ▼               ▼
                                  CardPyramid Board    VictoryCondition
                                      │       │
                                      ▼       ▼
                                   CardRow  JuwelCollection
                                      │
                                      ▼
                                  JuwelCard
                                      │
                              ┌───────┴───────┐
                              ▼               ▼
                             Cost            Bonus
```

The components are intentionally kept small and focused. Game rules should be implemented at the appropriate level rather than duplicating rule logic across the individual components.

## Dependency structure

```text
                    SplendorLib
                   /           \
                  ▼             ▼
          Splendor.exe    SplendorTests.exe
              │                  │
          main.cpp          Google Test
```

This ensures that the same production code is used by both the application and the tests.

## Build

From the root of the repository:

```powershell
cmake -S . -B build

cmake --build build --config Debug
```

The generated binaries are placed in:

```text
Splendor/bin/Debug/
```

For example:

```text
Splendor/bin/Debug/

├── Splendor.exe
├── SplendorLib.lib
└── SplendorTests.exe
```

## Testing

Run the complete test suite with:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

Individual tests can also be executed directly:

```powershell
.\Splendor\bin\Debug\SplendorTests.exe
```

## Development guidelines

### Production code

Game rules and reusable game functionality should be implemented in `SplendorLib`.

Application-specific code belongs in the `Splendor` executable.

Unit tests belong in `tst/` and should test the public behavior of the game implementation.

### Ownership and movement

Game components should own the data they are responsible for.

The ownership hierarchy is:

```text
Game
├── Player 1
│   └── DecisionMaker 1
│
└── Player 2
    └── DecisionMaker 2
```

When game objects are physically moved between components, prefer move semantics rather than unnecessary copying.

For example, cards can be moved from a closed card stack into an open slot, and jewels can be moved from the jewel bag onto the board.

### Encapsulation

Game state should not be modified directly from outside the component that owns it.

Public interfaces should expose the operations that are valid for a component while keeping its internal representation private.

For example, `Game` owns the authoritative game state, `Player` owns the player's inventory and decision maker, while `GameState` provides a snapshot for decision-making.

### Rule ownership

Each component should handle its own structural responsibilities.

For example:

* `CardRow` manages card storage, drawing, and refilling.
* `JuwelCardPyramid` manages the different card rows.
* `JuwelBoard` manages jewels occupying board positions.
* `Player` manages the player's inventory and owned cards.
* `Game` is responsible for validating and coordinating game actions.
* `VictoryCondition` evaluates whether the victory requirements have been met.
* `DecisionMaker` determines which action a player wants to perform.

Avoid adding game-specific rules to low-level components when those rules belong to `Game`.

### CMake

New production functionality should be added explicitly to `SplendorLib` in `CMakeLists.txt`.

New tests should be added to `SplendorTests`.

The library should remain independent of the executable and test application.
