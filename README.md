# Dining-Philosphers-Simulation
A simulation of the dining philosophers problem 


## Compiling
In the linux terminal, go to the directory of the program and run the command "gcc -pthread dine.c -o dine"

## Running the program
Run the program using ./dine [eatNum][philospherNum]
Where eatNum is a positive integer representing the number of times a philospher will eat
Where philospherNum is the number of philosphers

## Design
This program uses the Room attendant solution to the dining philospher's problem.
The room attendant keeps one philospher away from the table and thus allowing one philospher to eat continuously until finished

The room attendant will then allow another philospher to sit at the table, thus preventing deadlock.

## Limitations
The output will not always be in order

## References

1. General algorithm - https://moodle.socs.uoguelph.ca/pluginfile.php/19533/mod_resource/content/1/OS%2012%20.1-%20Mutual%20Exclusion%20%28c%29.pdf
2. Pthread implementation - used as reference for thread and semaphore functions - http://pseudomuto.com/development/2014/03/01/dining-philosophers-in-c/
