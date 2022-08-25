#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "dijkstra.h"
using namespace std;


TEST_CASE("Testing if the dijkstra function works on all modes",
"dijkstra"){
    cout << "Starting test" << endl;

    // Create environment
    Trip t1;
    t1.create_steps();
    t1.all_nodes = {"A", "B", "C", "D", "E", "F"};

    // Create routes
    vector<Step> best_route = {};
    best_route = t1.dijkstra("A", "F", 1);
    REQUIRE(((best_route[0].name_start == "A") && (best_route[1].name_start == "C")
    && (best_route[2].name_start == "E") && (best_route[2].name_end == "F")));

    best_route = t1.dijkstra("A", "F", 2);
    REQUIRE(((best_route[0].name_start == "A") && (best_route[1].name_start == "C")
    && (best_route[2].name_start == "E") && (best_route[2].name_end == "F")));

    best_route = t1.dijkstra("A", "F", 3);
    REQUIRE(((best_route[0].name_start == "A") && (best_route[1].name_start == "C")
    && (best_route[2].name_start == "E") && (best_route[2].name_end == "F")));

    cout << "Ending test" << endl;
}

