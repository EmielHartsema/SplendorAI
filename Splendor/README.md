# Splendor

`Splendor` is the first building block of the SplendorAI project.

It contains the digital implementation of the **Splendor Duel** board game. The implementation is intended to be reusable by other building blocks such as `AITrainer` and `UI`.

## Structure

```text
Splendor/
├── CMakeLists.txt
├── README.md
├── inc/
│   ├── Actions.hpp
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
│   ├── PendingDecisions.hpp
│   ├── Player.hpp
│   └── VictoryCondition.hpp
├── src/
│   ├── DecisionMaker.cpp
│   ├── Game.cpp
│   ├── GameState.cpp
│   ├── Juwel.cpp
│   ├── Player.cpp
│   └── main.cpp
└── tst/
    └── GameTest.cpp
```

## Components

### SplendorLib

`SplendorLib` is the reusable library containing the implementation of the game.

Production code that represents Splendor Duel's rules, game state, cards, jewels, board, players, decision-making, and game logic belongs in this library.

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

* **`Player`**

  Represents a player and owns the player's inventory, purchased cards, privilege scrolls, and `DecisionMaker`.

* **`Action`**

  Represents an operation that can be performed in the game.

  Actions are immutable descriptions of an intended operation. They are validated and executed by `Game`.

* **`MandatoryAction`**

  Base class for actions that constitute the player's mandatory action for a turn.

  Current mandatory actions include:

  * taking jewels
  * buying a card
  * reserving a card

  Performing a mandatory action normally ends the player's turn.

* **`OptionalAction`**

  Base class for actions that may be performed without ending the player's turn.

  Current optional actions include:

  * refilling the jewel board
  * spending a privilege scroll

  After an optional action, the same player may continue by submitting another action.

* **`PendingDecision`**

  Represents a question/request from `Game` that requires a response from a `DecisionMaker`.

  A pending decision does **not** necessarily mean that an action has already been selected.

  Examples include:

  * requesting the player's next action
  * requesting which crown card to take
  * requesting which jewel category a wildcard bonus should belong to
  * requesting which jewel to steal
  * requesting which jewel to take when an effect requires a choice

* **`DecisionAnswer`**

  Represents an answer to a `PendingDecision`.

  An answer may contain an `Action`, such as `BuyCard`, but not every pending decision necessarily results in an action. Some decisions require another type of answer.

* **`DecisionMaker`**

  Provides the decision-making interface used by a player.

  The `DecisionMaker` receives a `GameState` together with a `PendingDecision` and returns a `DecisionAnswer`.

  Different implementations can represent human players, scripted agents, random agents, AI agents, or future trained models.

* **`GameState`**

  Represents a snapshot of the game state.

  It is intended to provide a read-only representation of the current game situation to components such as `DecisionMaker`, without giving them direct access to the mutable game state.

* **`Game`**

  Owns the authoritative mutable game state and the two players.

  It is responsible for coordinating the different game components, dispatching pending decisions, validating answers, and executing actions.

## Current implementation status

The project builds, and `BuyCardDecisionMaker` can create a `BuyCard` answer for a `ChooseAction` decision. `Player` contains card affordability and purchase logic.

The end-to-end turn flow is not yet working: the latest run reported `The player returned no action.` The game still needs to successfully dispatch the decision to the player's decision maker and execute its answer.

## Game architecture

The game separates **game state**, **decision making**, and **game-rule enforcement**.

The high-level architecture is:

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
                  │ + PendingDecision
                  ▼
            DecisionMaker
                  │
                  │ returns
                  ▼
           DecisionAnswer
                  │
          ┌───────┴────────┐
          │                │
       Action        Other answer
          │                │
          ▼                ▼
        Game          Game handles
          │           requested choice
          │
          ▼
       Validate
          │
      ┌───┴───┐
      │       │
    valid   invalid
      │       │
      ▼       ▼
   Execute   handleInvalidAnswer
      │
      ▼
   Continue game
```

`Game` owns the actual mutable state of the game.

`GameState` provides a snapshot that can be inspected by decision-making components without giving them direct access to the mutable game.

Each `Player` owns its own `DecisionMaker`.

The application creates the decision makers and transfers ownership to `Game`, which transfers them to the corresponding players.

## Pending decisions

A central design principle is that `Game` asks questions rather than assuming that every interaction can immediately produce an action.

A `PendingDecision` represents the question being asked.

For example:

```text
Game:
    "It is Player 1's turn.
     What mandatory action do you want to perform?"

                │
                ▼

        PendingDecision

                │
                ▼

        DecisionMaker

                │
                ▼

        DecisionAnswer
          = BuyCard(...)
```

The same mechanism can be used for decisions that happen as a consequence of an action.

For example:

```text
Player performs BuyCard
        │
        ▼
Player receives a crown that
requires a crown-card choice
        │
        ▼
Game creates PendingDecision
        │
        ▼
DecisionMaker selects crown card
```

This means that secondary choices do not need to be embedded into the original action.

The same mechanism can later be used for effects such as:

* choosing the jewel category of a wildcard jewel;
* choosing a jewel to steal from an opponent;
* choosing a jewel from the board when an effect requires a choice;
* selecting a crown card;
* other choices introduced by card effects.

## Actions

`Action` is the base type for operations that can be performed by `Game`.

Actions are intended to be immutable.

The following hierarchy describes the intended action model; not all listed actions are implemented yet.

The action hierarchy is:

```text
Action
├── MandatoryAction
│   ├── TakeJuwels
│   ├── BuyCard
│   └── ReserveCard
│
└── OptionalAction
    ├── RefillJuwelBoard
    └── UsePrivilege
```

### Mandatory actions

Mandatory actions constitute the main action of a player's turn.

Examples:

```text
TakeJuwels
BuyCard
ReserveCard
```

After a valid mandatory action is executed, the player's turn normally ends and the next player becomes active.

### Optional actions

Optional actions do not end the player's turn.

Examples:

```text
RefillJuwelBoard
UsePrivilege
```

For example, refilling the jewel board is not itself the player's main turn action.

The flow can therefore be:

```text
Player 1
   │
   ├── RefillJuwelBoard
   │
   │   same player continues
   │
   └── BuyCard
           │
           ▼
       turn ends
           │
           ▼
       Player 2
```

Refilling the board also gives the opponent a privilege scroll according to the game rules.

Similarly, receiving a privilege scroll is a **consequence of another player's action**, not an action the player chooses.

Spending a privilege scroll, however, is an optional action.

## DecisionMaker contract

The conceptual interface is:

```text
DecisionAnswer DecisionMaker::chooseAction(
    GameState state,
    PendingDecision decision
);
```

The exact C++ interface may differ, but the semantic contract should remain the same:

1. `Game` creates a `GameState` snapshot.
2. `Game` creates a `PendingDecision`.
3. `Game` gives both to the active player's `DecisionMaker`.
4. The `DecisionMaker` returns a `DecisionAnswer`.
5. `Game` validates the answer.
6. If valid, `Game` executes it.
7. If invalid, `Game` invokes its invalid-answer handling policy.

The `DecisionMaker` is responsible for attempting to produce a correct answer.

`Game` nevertheless validates every answer before applying it because `Game` is the authoritative owner of the rules.

## Invalid decision-maker answers

Decision makers may return invalid answers.

This is especially important for future AI implementations. An untrained or poorly trained AI may initially produce many invalid actions.

The game must therefore never assume that a `DecisionMaker` is correct.

The intended behavior is:

```text
DecisionMaker
      │
      ▼
DecisionAnswer
      │
      ▼
Game validates answer
      │
 ┌────┴────┐
 │         │
valid    invalid
 │         │
 ▼         ▼
execute  handleInvalidAnswer()
```

The game should **not** repeatedly ask the decision maker until it produces a valid answer, because this can create an infinite retry loop.

Invalid-answer handling should instead be centralized in a `handleInvalidAnswer` mechanism so that different policies can be implemented later.

The initial policy is:

```text
invalid answer
      │
      ▼
reject answer
      │
      ▼
forfeit / skip the player's turn
```

This deliberately treats producing an invalid answer as the responsibility of the `DecisionMaker`.

The policy can later be changed for training environments, debugging, human interaction, or other use cases without changing the core decision-making architecture.

## Buy-card flow

The `BuyCard` flow is the first action being developed end-to-end. Its intended flow is:

The intended flow is:

```text
Game
 │
 │ Player's turn
 ▼
Create GameState
 │
 ▼
Create PendingDecision:
"Choose your mandatory action"
 │
 ▼
DecisionMaker
 │
 │ returns
 ▼
DecisionAnswer
 │
 │ contains
 ▼
BuyCard
 │
 ▼
Game validates:
 │
 ├── card exists
 ├── player can afford card
 ├── card is available to player
 └── other relevant game rules
 │
 ▼
Game executes BuyCard
 │
 ├── pay card cost
 ├── transfer card to player
 ├── apply card bonus
 ├── update points
 ├── update crowns
 └── refill card slot if required
 │
 ▼
Resolve consequences / pending decisions
 │
 ▼
Check victory condition
 │
 ▼
End turn or continue according to rules
```

The important architectural principle is that `BuyCard` itself describes **what the player wants to do**.

`Game` remains responsible for determining whether it is legal and for applying all consequences.

If buying the card creates a secondary choice, such as selecting a crown card, `Game` creates another `PendingDecision` rather than requiring `BuyCard` to contain every possible future choice.

## Component relationships

```text
                             Game
                              │
          ┌───────────────────┼────────────────────┐
          │                   │                    │
          ▼                   ▼                    ▼
       Player 1            Player 2          Game Components
          │                   │                    │
          ▼                   ▼             ┌──────┼───────────────┐
   DecisionMaker        DecisionMaker        ▼      ▼               ▼
                                           Card   Board       VictoryCondition
                                           │        │
                                           ▼        ▼
                                        CardRow  JuwelCollection
                                           │
                                           ▼
                                       JuwelCard
                                           │
                                    ┌──────┴──────┐
                                    ▼             ▼
                                   Cost          Bonus


Game
 │
 ▼
PendingDecision
 │
 ▼
DecisionMaker
 │
 ▼
DecisionAnswer
 │
 └──────────────► Action
                    │
              ┌─────┴─────┐
              ▼           ▼
        Mandatory      Optional
          Action         Action
```

The components are intentionally kept small and focused.

Game rules should be implemented at the appropriate level rather than duplicating rule logic across the individual components.

## Dependency structure

```text
                    SplendorLib
                   /           \
                  ▼             ▼
          Splendor.exe    SplendorTests.exe
              │                 │
          main.cpp         Google Test
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

Public interfaces should expose the operations that are valid for a component while keeping their internal representation private.

For example:

* `Game` owns the authoritative game state.
* `Player` owns the player's inventory and `DecisionMaker`.
* `GameState` provides a snapshot for decision-making.
* `Game` validates and executes actions.

### Rule ownership

Each component should handle its own structural responsibilities.

For example:

* `CardRow` manages card storage, drawing, and refilling.
* `JuwelCardPyramid` manages the different card rows.
* `JuwelBoard` manages jewels occupying board positions.
* `Player` manages the player's inventory and owned cards.
* `Action` represents an intended operation.
* `PendingDecision` represents a question that requires an answer.
* `DecisionMaker` produces answers to pending decisions.
* `Game` validates and coordinates actions and decisions.
* `VictoryCondition` evaluates whether the victory requirements have been met.

Avoid adding game-specific rules to low-level components when those rules belong to `Game`.

### Immutability

Actions and decision questions should be treated as immutable descriptions of intent.

They should contain the information necessary to describe the requested operation, but should not directly modify game state.

Only `Game` should apply mutations to the authoritative game state.

### Decision-making

`DecisionMaker` should not directly modify the game.

It receives:

```text
GameState + PendingDecision
```

and returns:

```text
DecisionAnswer
```

The `DecisionMaker` may be implemented by:

* a human interface;
* a deterministic scripted player;
* a random player;
* a heuristic AI;
* a trained AI model.

The game engine must remain independent of the implementation of the decision maker.

### CMake

New production functionality should be added explicitly to `SplendorLib` in `CMakeLists.txt`.

New tests should be added to `SplendorTests`.

The library should remain independent of the executable and test application.
