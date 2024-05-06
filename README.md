# Thread-Manager

2 main functionalities in this library:

1) Ability to define functions that will be executed automatically and in parallel without the need for defining threads manually. Only the function level code and the maximum
   number of threads need to be defined for library usage.
2) Ability to create non-blocking functions that will execute and can be blocked later on to allow for parallel processing. This is especially handy with I/O or distributed computing where one process is waiting for other information and can continue until it needs to retrieve the information.  
