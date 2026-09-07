# SplendorAI

SplendorAI is a C++ project for developing an AI that can play the board game **Splendor**.

The project is built from independent building blocks. Each building block has its own source code, public headers, tests, documentation and build configuration.

## Project structure

```text
SplendorAI/
├── CMakeLists.txt
├── README.md
│
├── Splendor/
│   ├── CMakeLists.txt
│   ├── README.md
│   ├── bin/
│   ├── doc/
│   ├── inc/
│   ├── mak/
│   ├── src/
│   └── tst/
│
├── AITrainer/
│   ├── CMakeLists.txt
│   ├── README.md
│   ├── bin/
│   ├── doc/
│   ├── inc/
│   ├── mak/
│   ├── src/
│   └── tst/
│
└── UI/
    ├── CMakeLists.txt
    ├── README.md
    ├── bin/
    ├── doc/
    ├── inc/
    ├── mak/
    ├── src/
    └── tst/
```

Not all building blocks exist yet. `Splendor` is the first building block.

## Building

The project uses CMake as its build system.

Configure the project:

```powershell
cmake -S . -B build
```

Build the Debug configuration:

```powershell
cmake --build build --config Debug
```

## Testing

Run all tests with CTest:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

## Building blocks

### Splendor

Contains the digital implementation of the Splendor board game.

### AITrainer

Will contain the functionality used to train and evaluate the Splendor AI.

### UI

Will contain the user interface for interacting with the game and/or AI.

## Dependencies

The project currently uses:

* C++20
* CMake
* Google Test

Google Test is obtained automatically by CMake using `FetchContent`.

## Architecture

The intended dependency structure is:

```text
                    Splendor
                       │
              ┌────────┴────────┐
              │                 │
              ▼                 ▼
         AITrainer              UI
              │                 │
              └────────┬────────┘
                       │
                       ▼
                 SplendorLib
```

`SplendorLib` contains the reusable game implementation. Other building blocks should use this implementation rather than duplicating the game rules.

## Development philosophy

The project is organized around relatively independent building blocks.

Within a building block:

* `inc/` contains public header files.
* `src/` contains production source files.
* `tst/` contains unit tests.
* `doc/` contains documentation.
* `mak/` contains build-related documentation or configuration information.
* `bin/` contains generated build artifacts and is not committed to Git.

CMake describes the dependencies between source files, libraries, executables and tests.

```
```
