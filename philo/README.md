*This project has been created as part of the 42 curriculum by siwhusse.*

# Philosophers

> I never thought philosophy would be so deadly

## Description

The **Philosophers** project is a simulation of the classic [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), a well-known concurrency problem in computer science.

A number of philosophers sit at a round table with a bowl of spaghetti in the center. Each philosopher alternates between **eating**, **thinking**, and **sleeping**. To eat, a philosopher must pick up two forks — one on their left and one on their right. After eating, they put the forks back down, sleep, and then start thinking again.

The simulation ends when:
- A philosopher **dies of starvation** (has not eaten within `time_to_die` milliseconds), or
- All philosophers have eaten the required number of meals (if specified).

Each philosopher is represented as a **thread**, and each fork is protected by a **mutex** to prevent data races.

### Key Rules

- Philosophers do not communicate with each other.
- A death message must be displayed within **10 ms** of the philosopher's actual death.
- No data races are allowed.
- No global variables are used.

## Instructions

### Compilation

```bash
cd philo
make
```

The `Makefile` supports the following rules: `all`, `clean`, `fclean`, `re`.

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time a philosopher can go without eating before dying |
| `time_to_eat` (ms) | Time it takes for a philosopher to eat (holding two forks) |
| `time_to_sleep` (ms) | Time a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(optional)* Simulation stops when all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, no one should die
./philo 5 800 200 200

# 1 philosopher, will die (only one fork available)
./philo 1 800 200 200

# Simulation stops after each philosopher eats 7 times
./philo 5 800 200 200 7

# Tight timing, no one should die
./philo 4 410 200 100
```

### Output Format

Each state change is logged as:

```
timestamp_in_ms philosopher_number action
```

Possible actions:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

Example output:
```
0 1 is thinking
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
0 4 has taken a fork
0 4 has taken a fork
0 4 is eating
1 1 has taken a fork
```

## Resources

### References

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — LLNL](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock(3) — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday(2) — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [Mutex vs Semaphore — GeeksforGeeks](https://www.geeksforgeeks.org/mutex-vs-semaphore/)
- [Data Race — ThreadSanitizer documentation](https://clang.llvm.org/docs/ThreadSanitizer.html)

### AI Usage

AI tools were used as a learning aid during this project for the following purposes:
- **Clarifying multithreading concepts**: Understanding how POSIX threads work, thread lifecycle, and how threads share memory.
- **Understanding mutex behavior**: Learning when and why to lock/unlock mutexes to avoid data races and deadlocks.
- **Reviewing documentation**: Getting explanations of `pthread` and `gettimeofday` man pages in simpler terms.

All code was written, tested, and debugged by hand. AI was not used to generate any source code for this project.