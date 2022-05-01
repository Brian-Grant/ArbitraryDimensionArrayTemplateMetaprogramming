# cs540-04


Brian Grant
Spring 2021

Metaprogramming



run make - to compile mytest.cpp and test_Array-new.cpp

run make mrun - to run mytest

run make run - to run test_Array-new

run make clean to delete execs

Array.hpp contains full implementation
Array.cpp is empty

This was a very challenging assignment.
But also one of the most interesting programming experiences I have had.

This was written in a very test driven development oriented fashion.

Test were written as code was produced

I had a few different designs that did not pan out, which you can see
in my commit history.

mytest has a bool print
set print=true to view output

I left in debug prints inside Array.hpp
To see output there are bool switches to set to true 

I used these to make sure the correct calls were made
and the recurses were correct

These prints would have much less of a performance cost if implemented
as macros that could be switched off and thus compiled out, but
time was a factor. 

I only left them in because I am proud of the adherence to test driven
development in this assignment



Row major iter works

I did not implement column major iter, or const iters because it was
not a requirment.

I am interested in getting column major iters to work and will
implement them in my own time.

In the provided test the only portions commented out are related
to const iter and column major iters


