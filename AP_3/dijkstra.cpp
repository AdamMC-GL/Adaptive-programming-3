#include <string>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <bits/stdc++.h>
#include "dijkstra.h"
using namespace std;

vector<Step> Trip::dijkstra(const string& start_node, const string& end_node, int mode) {
    //Mode: 1=flight 2=drive 3= train
    unordered_map<string, Step> best_connections; // to-how

    unordered_map<string, double> heuristics;

    for (auto &node: all_nodes) {
        heuristics[node] = std::numeric_limits<int>::max(); // set all nodes to infinity
    }
    heuristics[start_node] = 0;

    unordered_map<string, double> to_visit;
    to_visit[start_node] = 0;

    string current_node = start_node;
    while (current_node != end_node) {
        to_visit.erase(current_node); //remove current_node from to_visit
        vector<Step> possible_steps = {};

        // get connected steps
        for (auto &step: steps) {
            if (step.name_start == current_node) { //todo: and not start node?
                possible_steps.push_back(step);
            }
        }
        //
        double effort;
        for (auto &possible_step: possible_steps) {
            switch(mode) {
                case 1:
                    effort = Flight(possible_step).calculate_cost();
                    break;
                case 2:
                    effort = Drive(possible_step).calculate_kilometers();
                    break;
                default:
                    effort = Train_ride(possible_step).calculate_duration();
                    break;
            }
            effort += heuristics[possible_step.name_start];
            if (effort < heuristics[possible_step.name_end]) {
                heuristics[possible_step.name_end] = effort;
                best_connections[possible_step.name_end] = possible_step;
                to_visit[possible_step.name_end] = effort;
            }

        }

        //get new current node
        int lowest = to_visit.begin()->second;
        current_node = to_visit.begin()->first;
        for (auto const &x: to_visit){
            if (x.second < lowest) {
                current_node = x.first;
            }
        }
    }


    vector<Step> best_route {};

    while(current_node != start_node){
        best_route.insert(best_route.begin(), best_connections[current_node]);
        current_node = best_connections[current_node].name_start;
    }
    return best_route;
}



void Trip::create_steps(){
    // Create the nodes and links to one another
    steps.push_back({"A", "B", 2});
    steps.push_back({"A", "C", 5});
    steps.push_back({"B", "E", 7});
    steps.push_back({"C", "E", 2});
    steps.push_back({"B", "D", 9});
    steps.push_back({"D", "F", 3});
    steps.push_back({"E", "F", 3});

    //and for the other way
    unsigned int end = steps.size();
    for(unsigned int i = 0; i < end; i++){
        steps.push_back({steps[i].name_end, steps[i].name_start, steps[i].effort});
    }

}

void Trip::compare_to(string start_node, string end_node){
    // Calculate fastest routes
    vector<Step> best_route = dijkstra(start_node, end_node, 1);
    double flight_cost = 0;
    cout << "Best route for flying: ";
    for(auto & i : best_route){
        flight_cost += Flight(i).calculate_cost();
        cout << i.name_start << " -> " << i.name_end << ", ";
    }
    cout << "Total cost: " << flight_cost << ",-. Chance of losing baggage: " << (100/(flight_cost+1)) << "%" << endl;


    best_route = dijkstra(start_node, end_node, 2);
    int drive_km = 0;
    cout << "Best route for driving: ";
    for(auto & i : best_route){
        drive_km += Drive(i).calculate_kilometers();
        cout << i.name_start << " -> " << i.name_end << ", ";
    }
    cout << "Total km: " << drive_km << "km" << endl;

    best_route = dijkstra(start_node, end_node, 3);
    int train_duration = 0;
    cout << "Best route by train: ";
    for(auto & i : best_route){
        train_duration += Train_ride(i).calculate_duration();
        cout << i.name_start << " -> " << i.name_end << ", ";
    }
    cout << "Total duration: " << train_duration << " minutes" << endl << endl;

}

void Trip::remove_step(string start_node, string end_node){
    for(unsigned int i = 0; i < steps.size(); i++){
        if (steps[i].name_start == start_node && steps[i].name_end == end_node){
            steps.erase(steps.begin() + i);
        }
    }

}

void Trip::add_step(string start_node, string end_node, double effort){
    steps.push_back({start_node, end_node, effort});
}

void Trip::change_step_effort(string start_node, string end_node, double new_effort){

    for(auto & step : steps){
        if (step.name_start == start_node && step.name_end == end_node){
            step.effort = new_effort;
        }
    }
}

Train_ride::Train_ride(Step const& step)
{
    this->effort = step.effort;
}

int Train_ride::calculate_duration(){
    duration_min = (sin(effort) + 1) * effort;
    return duration_min;
}

Flight::Flight(Step const& step)
{
    this->effort = step.effort;
}

double Flight::calculate_cost(){

    cost = 10 + (effort * 0.13); // https://www.statista.com/statistics/269532/cost-per-seat-per-kilometer-of-selected-airlines/
    return cost;
}

Drive::Drive(Step const& step)
{
    this->effort = step.effort;
}

int Drive::calculate_kilometers(){
    kilometers = effort;
    return kilometers;
}

