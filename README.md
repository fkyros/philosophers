# philosophers
classic concurrency problem, proposed by Dijkstra, where many threads try to access/write a single variable

execute with `helgrind` to check for posible race conditions
```
valgrind --tool=helgrind ./philo <params>
```
