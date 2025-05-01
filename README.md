# Process-Scheduling

Process Scheduling
Welcome to the Process Scheduling project! This repository contains implementations of key operating system concepts such as process scheduling, inter-process communication (IPC), and multithreading, all written in C. It is a great resource for learning and understanding fundamental OS concepts.

## Features
### Process Scheduling Algorithms:
- First Come First Serve (FCFS)
- Shortest Job Next (SJN)
- Priority Scheduling
- Round Robin (RR)
### Inter-Process Communication (IPC):
- Shared memory and pipes (`shared_memory_pipe.c`)
### Multithreading:
- Thread creation and management (`thread_program.c`)
## Getting Started
### Prerequisites
To compile and run the code in this repository, you will need:

- A C compiler (e.g., GCC)
- A terminal or command-line tool
### Cloning the Repository
To clone this repository, use the following command:

```bash
git clone https://github.com/HoomanMoradnia/Process-Scheduling.git
cd Process-Scheduling
```
### Compilation
To compile the desired program, use the following command:

```bash
gcc -o program program.c -lpthread
```
Replace `program.c` with the specific file you want to compile (e.g., `scheduler.c`, `shared_memory_pipe.c`, `thread_program.c`).

### Running the Program
After compilation, you can run the program using:

```bash
./program
```
Follow the on-screen instructions to interact with the program.

## Repository Structure
```Code
├── scheduler.c             # Process scheduling implementation
├── shared_memory_pipe.c    # IPC using shared memory and pipes
├── thread_program.c        # Multithreading demonstration
├── examples/               # Example usage or test cases (if applicable)
└── README.md               # Project documentation
```
## File Descriptions
### `scheduler.c`

This file contains implementations of popular CPU scheduling algorithms such as:

- **First Come First Serve (FCFS)**: Processes are scheduled in the order of their arrival.
- **Shortest Job Next (SJN)**: Processes with the shortest execution time are scheduled first.
- **Priority Scheduling**: Processes are scheduled based on their priority value.
- **Round Robin (RR)**: Processes are scheduled in a cyclic order with a fixed time quantum.
### `shared_memory_pipe.c`

This program demonstrates inter-process communication (IPC) using shared memory and pipes in a parent-child process model.

**Parent Process:**
- Creates a shared memory segment.
- Writes a user-provided string into the shared memory.
- Sends a synchronization signal to the child process using a pipe.
- Cleans up by detaching and removing the shared memory after the child process completes.

**Child Process:**
- Waits for a synchronization signal from the parent through the pipe.
- Reads the string from the shared memory segment.
- Counts and displays the number of characters in the string.
- Detaches from the shared memory after processing.
This program effectively demonstrates the use of shared memory for data sharing and pipes for synchronization between parent and child processes in C.

### `thread_program.c`
This program demonstrates the creation and execution of threads in C using the `pthread` library.

**Two Threads:**
- **Thread 1**: Prints "Thread Hooman" along with an index, five times, with a one-second interval between each print.
- **Thread 2**: Prints "Born in 2004" along with an index, five times, with a one-second interval between each print.

**Main Thread:**
- Creates the two threads.
- Waits for both threads to complete execution using `pthread_join`.
- Prints a completion message upon the termination of both threads.

This program serves as an example of multithreading, showcasing how multiple threads can perform independent tasks concurrently.

## Concepts Covered
This project demonstrates the following key concepts in operating systems:

- **Process Scheduling**: Mechanisms to allocate CPU time to multiple processes.
- **Inter-Process Communication (IPC)**: Using shared memory and pipes for communication between processes.
- **Multithreading**: Creating and managing threads for concurrent execution.

## Contributions
Contributions are welcome! If you'd like to improve or extend the project, feel free to fork the repository and submit a pull request.

## License
This project is open-source and available under the MIT License.
