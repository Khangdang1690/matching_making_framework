# Multiplayer Game Matchmaking Queue

A C++ matchmaking framework that uses a queue-based system to group players into balanced games based on skill rating (MMR).

## How It Works

1. Players enqueue into a waiting pool
2. Matchmaker sorts players by MMR and groups them using a sliding-window algorithm
3. Only players within a configurable MMR gap are matched together
4. Unmatched outliers remain in the queue for the next cycle

## Build & Run

```bash
g++ -std=c++17 -Wall -Wextra -o matchmaker main.cpp Player.cpp RankedPlayer.cpp Matchmaker.cpp
./matchmaker
```

## Project Structure

| File | Description |
|------|-------------|
| `Player.h / .cpp` | Base player class (ID, name, MMR) |
| `RankedPlayer.h / .cpp` | Derived class with rank tier and win/loss stats |
| `Matchmaker.h / .cpp` | Queue management and matching algorithm |
| `main.cpp` | Driver program demonstrating the system |

## Task Distribution

### Tam (33.3%)
- `Player.h` and `Player.cpp`
- Base class design (constructors, getters, setters)
- Virtual `display()` and `operator<<` overload

### Khang (33.3%)
- `RankedPlayer.h` and `RankedPlayer.cpp`
- Inheritance from Player, `Tier` enum
- Win/loss tracking and `display()` override

### Tuan (33.3%)
- `Matchmaker.h`, `Matchmaker.cpp`, and `main.cpp`
- Queue + sort-and-partition matching algorithm
- Driver program and demo output
