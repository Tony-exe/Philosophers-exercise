# Philosophers-exercise
A personal exercise to become better at using thread locks 

The exercise consists in having 5 philosophers around a table, and just 5 sticks on the table. To be able to eat a piece, each one of them has to grab to 2 stick.

The philosophers are 5 threads, and the sticks are 5 mutex. Each one of them has to hold 2 mutex to be able to eat a piece.
If a mutex is aviable, and the other one isn't the philosopher release the mutex, and waits till it can take both mutex.
