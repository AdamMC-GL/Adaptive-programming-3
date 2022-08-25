# Adaptive-programming-3

Be sure to have the CMake file unclude all the cpp files.

Each class of each vehicle mode has the subclass of Step. The Trip class has a list of Steps and contains the subclass of Compare.
The dijkstra() function uses the dijkstra algorithm to find the best route between nodes based on the effort of each node. the mode decides how
the effort is calculated, using the effort calculation function of each vehicle class. The base effort of a Step class is given to the vehicle class. The creation
of a vehicle class includes the Step subclass, but a custom Step class can decide and or replace the current variables of the Step subclass within in the vehicle class.
This is what is used in the dijkstra() function. Upon calculating the effort, a temporary vehicle class is and the current Step it is cheacking is given to the vehicle class as the variables for the Step subclass. This vehicle class is then asked to return an effort calculation.

The compare_to() function uses the dijkstra() function on every mode possible, and then prints each result.


## Unit_testing.cpp

contains 1 Catch2 unit test1

    TEST_CASE("Testing if the dijkstra function works on all modes")
    
## main.cpp

Lays out a couple of different node routes.
