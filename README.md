# Multiplayer Game Matchmaking Queue

A C++ matchmaking system that groups players into fair games based on skill rating (MMR). Supports two match types: Normal (casual) and Ranked (competitive with a winner).

## How It Works

1. Players join either the Normal or Ranked queue
2. Each player has a name, MMR (skill rating), and rank (Bronze–Diamond)
3. The matchmaker groups similar-skill players using a sliding-window algorithm
4. Players too far apart in skill stay in the queue for next time
5. Ranked matches also determine a winner (highest MMR player)

## Build & Run
 
```bash
g++ -std=c++17 -Wall -Wextra -o matchmaker main.cpp Player.cpp Match.cpp RankedMatch.cpp Matchmaker.cpp
./matchmaker
```

## Project Structure

| File | Description |
|------|-------------|
| `Player.h / .cpp` | Player class (ID, name, MMR, rank tier) |
| `Match.h / .cpp` | Base match class (normal/casual matches) |
| `RankedMatch.h / .cpp` | Derived match class (competitive, picks a winner) |
| `Matchmaker.h / .cpp` | Queue management and matching algorithm |
| `Queue.h` | Custom templated queue using a circularly linked list |
| `main.cpp` | Interactive menu-driven program |

## Task Distribution

### Tam (33.3%)
- `Player.h` and `Player.cpp`
- Player class design (constructors, getters, setters, rank tier)
- `display()` method and `operator<<` overload

### Khang (33.3%)
- `Match.h`, `Match.cpp`, `RankedMatch.h`, `RankedMatch.cpp`
- Match/RankedMatch inheritance and polymorphic `display()`
- Winner determination logic in RankedMatch

### Tuan (33.3%)
- `Matchmaker.h`, `Matchmaker.cpp`, `Queue.h`, and `main.cpp`
- Custom queue (circularly linked list) + matching algorithm
- Interactive menu and program flow
