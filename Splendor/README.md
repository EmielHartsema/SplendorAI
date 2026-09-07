# Splendor

`Splendor` is the first building block of the SplendorAI project.

It contains the digital implementation of the **Splendor** board game. The implementation is intended to be reusable by other building blocks such as `AITrainer` and `UI`.

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
│   └── Game.hpp
│
├── mak/
│
├── src/
│   ├── Game.cpp
│   └── main.cpp
│
└── tst/
    └── GameTest.cpp
```

## Components

### SplendorLib

`SplendorLib` is the reusable library containing the implementation of the game.

Production code that represents Splendor's rules and state belongs in this library.

The library does not contain an application `main()` function.

### Splendor

`Splendor` is the executable used to run the digital game.

It provides the application's `main()` function and links against `SplendorLib`.

### SplendorTests

`SplendorTests` contains the unit tests for the Splendor implementation.

It links against `SplendorLib` and Google Test.

## Dependency structure

```text
                 SplendorLib
                /           \
               ▼             ▼
        Splendor.exe    SplendorTests.exe
             │                │
          main.cpp       Google Test
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

Game rules and reusable game functionality should be implemented in `SplendorLib`.

Application-specific code belongs in the `Splendor` executable.

Unit tests belong in `tst/` and should test the public behavior of the game implementation.

New production functionality should be added explicitly to `SplendorLib` in `CMakeLists.txt`.

```
```
