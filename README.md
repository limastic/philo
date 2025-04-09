# 🧠 Philosophers — Multithreading, Mutexes, and Synchronization in C

**"I never thought philosophy would be so deadly."**

---

## 📌 About the Project

This project simulates the classic **Dining Philosophers Problem**, a concurrency problem that teaches how to safely manage **shared resources** (forks) between **multiple threads**. It demonstrates how deadlocks, starvation, and race conditions can arise — and how to prevent them using synchronization techniques like **mutexes**.

---

## ✅ What I’ve Done

- Implemented the full simulation using **threads** and **mutexes** in C.
- Simulated philosophers sitting at a table, each trying to:
  - **Take two forks**
  - **Eat**
  - **Sleep**
  - **Think**
  - Repeat the cycle without dying from starvation.
- Carefully managed resource locking to avoid:
  - **Deadlocks**
  - **Data races**
  - **Starvation**
  - **Mixed console output**
- Added clean, timestamped logging and accurate death detection (within 10ms of the event).

---

## 🌱 What I’ve Learned

- The fundamentals of **multithreading** in C using `pthread`.
- How to use **mutexes** to protect shared data and avoid concurrency issues.
- Importance of **precise timing**, synchronization, and careful thread lifecycle management.
- Designing a concurrent program where multiple actors interact independently but must follow strict rules to avoid chaos.

---

## 🧪 How It Works

Each philosopher:
- Picks up the left and right forks if they can.
- Eats for a defined duration.
- Puts down the forks (and make them available for others).
- Sleeps for a defined duration.
- Thinks until ready to eat again.

The simulation ends when:
- A philosopher **dies** of starvation (misses `time_to_die` threshold).
- All philosophers eat a set number of times (if the optional argument is provided).

---

## 📥 Arguments

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Total number of philosophers and forks.
- `time_to_die`: Time (ms) before a philosopher dies if not eating.
- `time_to_eat`: Time (ms) a philosopher spends eating.
- `time_to_sleep`: Time (ms) a philosopher sleeps.
- `number_of_times_each_philosopher_must_eat` (optional): If provided, simulation stops once all philosophers eat at least this many times.

---

## 🔒 Output Format

```
[timestamp_in_ms] [philosopher_id] has taken a fork
[timestamp_in_ms] [philosopher_id] is eating
[timestamp_in_ms] [philosopher_id] is sleeping
[timestamp_in_ms] [philosopher_id] is thinking
[timestamp_in_ms] [philosopher_id] died
```

> Output is synchronized and displayed clearly, without mixed lines.

---

## 🛠️ Compilation & Execution

```
cd philo
make
./philo 5 800 200 200
./philo 5 800 200 200 3
```



---

## 🧼 Code Norms & Safety

- Fully norm-compliant.
- No global variables.
- No memory leaks (checked with Valgrind).
- Deadlock-free.
- Output synced for readability.
- Strict error handling and input validation.

---

## 🎓 Final Thoughts

This project taught me how **tricky concurrent programming** is. It made abstract problems like deadlock and starvation *real*, and pushed me to write efficient, race-condition-free C code using **threads and mutexes**.


