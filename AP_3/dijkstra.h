#ifndef AP_3_DIJKSTRA_H
#define AP_3_DIJKSTRA_H

#include <iostream>
#include <vector>
using namespace std;

class Compare{
public:
    virtual void compare_to(string start_node, string end_node) = 0;

};

class Step{
public:
    string name_start;
    string name_end;
    double effort;

};

class Flight: public Step{
public:
    Flight(Step const&); // take over already existing step variable values
    double cost;

    double calculate_cost();
};

class Drive: public Step{
public:
    Drive(Step const&);// take over already existing step variable values
    int kilometers;

    int calculate_kilometers();
};

class Train_ride: public Step{
public:
    Train_ride(Step const& step);// take over already existing step variable values
    int duration_min;

    int calculate_duration();
};



class Trip: public Compare{
public:

    vector<Step> steps;
    vector<string> all_nodes;
    void create_steps();
    void compare_to(string start_node, string end_node);
    vector<Step> dijkstra(const string& start_node, const string& end_node, int mode);

    void remove_step(string start_node, string end_node);
    void add_step(string start_node, string end_node, double effort);

    void change_step_effort(string start_node, string end_node, double new_effort); //todo

};

#endif //AP_3_DIJKSTRA_H
