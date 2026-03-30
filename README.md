# Philosophers

A C implementation of the Dining Philosophers Problem using threading and mutexes to learn concurrent programming.

## Quick Start

```bash
cd philo
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [times_each_must_eat]
```

**Parameters:**
- `number_of_philosophers`: Number of philosophers at the table
- `time_to_die`: Time in milliseconds before a philosopher dies of hunger
- `time_to_eat`: Duration of a meal in milliseconds
- `time_to_sleep`: Duration of sleep in milliseconds
- `times_each_must_eat`: Optional - simulation stops when all philosophers have eaten this many times

**Example:**
```bash
./philo 5 800 200 200        # Run with 5 philosophers
./philo 4 410 200 200 10     # Stop after each eats 10 times
```

## Project Overview

The Dining Philosophers Problem is a classic synchronization challenge: N philosophers sit around a table with one fork between each pair. To eat, a philosopher must hold both adjacent forks. The program must handle concurrent access to shared resources (forks) while preventing deadlocks and starvation.

## Key Concepts

**Threads**: Each philosopher runs as an independent thread executing the same routine.

**Mutexes**: Protect shared resources (forks) from simultaneous access by multiple threads.

**Synchronization**: Coordinate thread execution to ensure no philosopher gets stuck waiting indefinitely.

**Timestamps**: Track all actions with millisecond precision from program start.

## Core Data Structures

**t_philo**: Represents a philosopher
- Thread ID and philosopher number
- References to left and right forks
- Meal count and last meal timestamp
- Associated mutexes for synchronization

**t_tfork**: Represents a fork
- Fork ID and busy status
- Mutex for exclusive access

**t_simulation**: Manages the entire simulation
- Arrays of philosophers and forks
- Timing parameters (time_to_die, time_to_eat, time_to_sleep)
- Control flags and shared mutexes

## Output Format

```
[timestamp] [philosopher_id] [action]
```

Actions: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`


## Requirements

- Prevent deadlocks (philosophers shouldn't get stuck indefinitely)
- Prevent starvation (all philosophers should get a chance to eat)
- Ensure thread-safe output (no message interleaving)
- Use precise millisecond timing for all events

