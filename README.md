*This project has been created as part of the 42 curriculum by `jpaulo-b`.*

# **Description**

The 'Philosophers' project is an overview and opportunity to research about threads and mutexes.
The 'dining philosophers problem' is a computer science problem that illustrates resource allocation and deadlock avoidance.
It was created by Edsger Dijkstra (NL) in 1965, a Dutch computer scientist and mathmatician, and states as follow:
   X amount of philosophers sit at a round table with bowls of food.
   Forks are placed in front of each philosopher.
   There are as many forks as philosophers.
   All day the philosophers take turns eating, sleeping, and thinking.
   A philosopher must have two forks in order to eat, and each fork
   may only be used by one philosopher at a time. At any time a
   philosopher can pick up or set down a fork,
   but cannot start eating until picking up both forks.
   The philosophers alternatively eat, sleep, or think.
   While they are eating, they are not thinking nor sleeping,
   while thinking, they are not eating nor sleeping,
   and, of course, while sleeping, they are not eating nor thinking.
Each philosopher will have its thread and the forks will be managed by mutexes to assure that they are not used by more than one philo.
A race condition can occur when multiple philosophers try to pick up the same fork simultaneously. To prevent this, we use mutex lock and unlock.

# **Instructions**

To run the program, you must use the Makefile command 'make' to compile.
Then we must insert ./philo *number of philosophers* *time to die* *time to eat* *time to think* or ./philo "*number of philosophers* *time to die* *time to eat* *time to think* *number_of_times_each_philosopher_must_eat*". This last one is optional.
The test I used more was ./philo 5 800 200 200 and ./philo 5 800 200 200 7

# **Resources**

- Wikipedia: Thread (computing);
- Wikipedia: Lock (computer science);
- Wikipedia: Edsger W. Dijkstra;
- https://youtu.be/LOfGJcVnvAk	NESO ACADEMY - Introduction to Threads;
- https://youtu.be/ldJ8WGZVXZk	Portfolio Courses - Introduction To Threads (pthreads);
- https://youtu.be/uA8X5zNOGw8	Jacob Sorber - How to create and join threads in C (pthreads);
- https://youtu.be/raLCgPK-Igc	Portfolio Courses - Mutex Introduction (pthreads);
- https://youtu.be/YSn8_XdGH7c	Code Vault - Introduction to semaphores in C;
- https://man7.org/linux/man-pages/man2;
- valgrind.org/docs/manual/quick-start.html;
- www.w3schools.com/c/;
- Damas, Luis; "Linguagem C"; FCA; 25ed 2025;
- Pereira, Alexandre; "C e Algoritmos"; Ed. Silabo; 3ed 2023;
- I used Chat-GPT, Gemini and CoPilot to learn the concepts and sometimes to debug (after GDB and Valgrind).
