# Philosophers

In this project, you will learn the basics of threading and synchronization mechanisms. You will implement a simulation of the classic ["Dining Philosophers"](https://en.wikipedia.org/wiki/Dining_philosophers_problem) problem, exploring how to create and manage threads, as well as how to use mutexes for safe resource sharing.


## Learning Outcomes

Through this project, you will:
- Gain a deeper understanding of threading, synchronization, and resource sharing.
- Learn to handle real-world concurrency issues such as deadlocks and race conditions.
- Explore the use of mutexes in a practical context.

---

## Functionality

### Key Concepts:
1. Philosophers alternate between three states: **eating**, **thinking**, and **sleeping**.
2. Philosophers require two forks (one on the left and one on the right) to eat.
3. The simulation must ensure:
   - Philosophers do not starve.
   - State changes and logs are consistent.
   - Deadlocks and data races are avoided.
4. Key rules:
    - One thread per philosopher.
    - Mutexes are used to protect the state of forks.
5. I've additionally added a monitoring thread that monitors the states of philosophers and triggers a shutdown whenever a philospher dies or all of them have eaten the appropriate amount of meals.
6. There is also a syncing mechanic at the beginning of the simulation that ensures all philosophers start their life at close to the same time. This is implemented by a mutex that is locked and blocks each philosopher from starting their simulation until all philosophers and the monitoring thread have bene created. The monitoring thread unlocks the mutex.



## Usage

Download the repository, then us `make` for compilation.
You can start the binary with the following input arguments:<br>

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

- number_of_philosophers: Number of philosophers (and forks).
- time_to_die: Time (in milliseconds) a philosopher can go without eating before dying.
- time_to_eat: Time (in milliseconds) a philosopher spends eating.
- time_to_sleep: Time (in milliseconds) a philosopher spends sleeping.
- number_of_times_each_philosopher_must_eat (optional): Stops the simulation once all philosophers have eaten this number of times.
```

