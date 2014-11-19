//
//  main.cpp
//  SiebDesEratosthenes
//
//  Created by Gerloff, Christian on 26.10.14.
//  Copyright (c) 2014 Gerloff, Christian. All rights reserved.
//

#include <iostream>
#include "tbb/tbb.h"
#include <iomanip>
#include <time.h>
#include <math.h>
using std::setw;
using namespace tbb;
using namespace std;


int main(int argc, const char * argv[]) {
    tbb::task_scheduler_init  init(4);
    static int zahlenReihe = 1000000000;
    concurrent_vector<bool> vec(zahlenReihe, false);
    
    
    tick_count t0 = tick_count::now();
    // Siebe alle Primzahlen
    
    parallel_for(4, zahlenReihe, 2, [&](int j) {
        vec[j] = true;
    });
    
    for (int i = 3; i <= int(sqrt(zahlenReihe)); i++) {
        if (vec[i] == false) {
            parallel_for(i*i, zahlenReihe, 2*i, [&](int j) {
                vec[j] = true;
            });
        }
    }
    
    tick_count t1 = tick_count::now();
    
    printf("Zeit für Algorithmus: %g seconds\n", (t1-t0).seconds());

    
    return 0;
}
