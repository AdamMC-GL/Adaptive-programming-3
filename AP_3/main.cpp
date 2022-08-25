#include "dijkstra.h"
int main() {
    Trip t1;
    t1.create_steps();
    t1.all_nodes = {"A", "B", "C", "D", "E", "F"};
    t1.compare_to("A", "F");
    t1.compare_to("D", "A"); // has different routes for different vehicles
    t1.compare_to("B", "B"); // no route
    t1.compare_to("F", "E");
    t1.compare_to("E", "C");

    t1.add_step("Y", "X", 5);
    t1.change_step_effort("E", "C", 999);
    t1.remove_step("D", "A");

    for(unsigned int i = 0; i < t1.steps.size(); i++){
        cout << t1.steps[i].name_start << " > " << t1.steps[i].name_end << ". Effort: " << t1.steps[i].effort << endl;
    }

}

