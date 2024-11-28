// scenarios.h
#ifndef SCENARIOS_H
#define SCENARIOS_H

#include "ports.h"

void scenario_ns_red_ew_red(void);
void scenario_ns_red_yellow_ew_red(void);
void scenario_ns_green_ew_red(void);
void scenario_ns_yellow_ew_red(void);
void scenario_ns_red_ew_red_yellow(void);
void scenario_ns_red_ew_green(void);
void scenario_ns_red_ew_yellow(void);

void pedestrian_ns_green(void);
void pedestrian_ns_red(void);
void pedestrian_ew_green(void);
void pedestrian_ew_red(void);

void indicators_on(void);
void indicators_off(void);

#endif