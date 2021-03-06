// This file contains the member definitions of the master class

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>

#ifdef EMSCRIPTEN
#include "emprintf.h"
#endif

using namespace std;
#include "graph.h"
#include "emprintf.h"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#ifdef MUSE_MPI
#include <mpi.h>
#endif


void graph::set_params(uintptr_t paramsPtr) {
    const float* params = reinterpret_cast<float*>(paramsPtr);
    int cursor = 0;
    
    iterations = (int)params[cursor++];
    temperature = params[cursor++];
    attraction = params[cursor++];
    damping_mult = params[cursor++];

    liquid.iterations = (int)params[cursor++];
    liquid.temperature = params[cursor++];
    liquid.attraction = params[cursor++];
    liquid.damping_mult = params[cursor++];
    liquid.time_elapsed = 0;

    expansion.iterations = (int)params[cursor++];
    expansion.temperature = params[cursor++];
    expansion.attraction = params[cursor++];
    expansion.damping_mult = params[cursor++];
    expansion.time_elapsed = 0;

    cooldown.iterations = (int)params[cursor++];
    cooldown.temperature = params[cursor++];
    cooldown.attraction = params[cursor++];
    cooldown.damping_mult = params[cursor++];
    cooldown.time_elapsed = 0;

    crunch.iterations = (int)params[cursor++];
    crunch.temperature = params[cursor++];
    crunch.attraction = params[cursor++];
    crunch.damping_mult = params[cursor++];
    crunch.time_elapsed = 0;

    simmer.iterations = (int)params[cursor++];
    simmer.temperature = params[cursor++];
    simmer.attraction = params[cursor++];
    simmer.damping_mult = params[cursor++];
    simmer.time_elapsed = 0;
}

void graph::get_params(emscripten::val onComplete){
    float result_buffer[24];
    int cursor = 0;

    result_buffer[cursor++] = iterations;
    result_buffer[cursor++] = temperature;
    result_buffer[cursor++] = attraction;
    result_buffer[cursor++] = damping_mult;

    result_buffer[cursor++] = liquid.iterations;
    result_buffer[cursor++] = liquid.temperature;
    result_buffer[cursor++] = liquid.attraction;
    result_buffer[cursor++] = liquid.damping_mult;

    result_buffer[cursor++] = expansion.iterations;
    result_buffer[cursor++] = expansion.temperature;
    result_buffer[cursor++] = expansion.attraction;
    result_buffer[cursor++] = expansion.damping_mult;

    result_buffer[cursor++] = cooldown.iterations;
    result_buffer[cursor++] = cooldown.temperature;
    result_buffer[cursor++] = cooldown.attraction;
    result_buffer[cursor++] = cooldown.damping_mult;

    result_buffer[cursor++] = crunch.iterations;
    result_buffer[cursor++] = crunch.temperature;
    result_buffer[cursor++] = crunch.attraction;
    result_buffer[cursor++] = crunch.damping_mult;

    result_buffer[cursor++] = simmer.iterations;
    result_buffer[cursor++] = simmer.temperature;
    result_buffer[cursor++] = simmer.attraction;
    result_buffer[cursor++] = simmer.damping_mult;

    onComplete(emscripten::memory_view<float>(24, result_buffer));
}

// constructor -- initializes the schedule variables (as in 
// graph constructor)

void graph::init(uintptr_t edgesPtr, uintptr_t weightsPtr) {
    // MPI parameters
    myid = 0;
    num_procs = 1;
    const int* edges = reinterpret_cast<int*>(edgesPtr);
    const float* weights = reinterpret_cast<float*>(weightsPtr);
    //emprintf("%d, %d", edges[0], edges[1]);

    // initial annealing parameters
    // initial annealing parameters
    STAGE = 0;
    iterations = 0;
    temperature = 2000;
    attraction = 10;
    damping_mult = 1.0;
    min_edges = 20;
    first_add = fine_first_add = true;
    fineDensity = false;

    // Brian's original Vx schedule
    liquid.iterations = 250;
    liquid.temperature = 2000;
    liquid.attraction = 10;
    liquid.damping_mult = 1.0;
    liquid.time_elapsed = 0;

    expansion.iterations = 250;
    expansion.temperature = 2000;
    expansion.attraction = 2;
    expansion.damping_mult = 1.0;
    expansion.time_elapsed = 0;

    cooldown.iterations = 250;
    cooldown.temperature = 2000;
    cooldown.attraction = 1;
    cooldown.damping_mult = .1;
    cooldown.time_elapsed = 0;

    crunch.iterations = 100;
    crunch.temperature = 250;
    crunch.attraction = 1;
    crunch.damping_mult = .25;
    crunch.time_elapsed = 0;

    simmer.iterations = 150;
    simmer.temperature = 250;
    simmer.attraction = .5;
    simmer.damping_mult = 0.0;
    simmer.time_elapsed = 0;

    // scan .int file for node info
    from_array(edges, weights, edgeCount);

    // populate node positions and ids
    //emprintf("%d", num_nodes);
    positions.reserve(num_nodes);
    map<int, int>::iterator cat_iter;
    for (cat_iter = id_catalog.begin();
         cat_iter != id_catalog.end();
         cat_iter++)
        positions.push_back(Node(cat_iter->first));

    /*
    // output positions .ids for debugging
    for ( int id = 0; id < num_nodes; id++ )
      cout << positions[id].id << endl;
    */

    // read .int file for graph info
    read_array(edges, weights, edgeCount);

    // initialize density server
    density_server.Init();
    this->init_parms(42, 32.0/40.0, -1.0);
    for (int i = 0; i < num_nodes; i++) {
        density_server.Add(positions[i], fineDensity);
    }
}

graph::graph(int proc_id, int tot_procs, char *int_file) {

    // MPI parameters


    myid = proc_id;
    num_procs = tot_procs;

    // initial annealing parameters
    STAGE = 0;
    iterations = 0;
    temperature = 2000;
    attraction = 10;
    damping_mult = 1.0;
    min_edges = 20;
    first_add = fine_first_add = true;
    fineDensity = false;

    // Brian's original Vx schedule
    liquid.iterations = 250;
    liquid.temperature = 2000;
    liquid.attraction = 10;
    liquid.damping_mult = 1.0;
    liquid.time_elapsed = 0;

    expansion.iterations = 250;
    expansion.temperature = 2000;
    expansion.attraction = 2;
    expansion.damping_mult = 1.0;
    expansion.time_elapsed = 0;

    cooldown.iterations = 50;
    cooldown.temperature = 2000;
    cooldown.attraction = 1;
    cooldown.damping_mult = .1;
    cooldown.time_elapsed = 0;

    crunch.iterations = 10;
    crunch.temperature = 250;
    crunch.attraction = 1;
    crunch.damping_mult = .25;
    crunch.time_elapsed = 0;

    simmer.iterations = 150;
    simmer.temperature = 250;
    simmer.attraction = .5;
    simmer.damping_mult = 0.0;
    simmer.time_elapsed = 0;

    // scan .int file for node info
    scan_int(int_file);

    // populate node positions and ids
    positions.reserve(num_nodes);
    map<int, int>::iterator cat_iter;
    for (cat_iter = id_catalog.begin();
         cat_iter != id_catalog.end();
         cat_iter++)
        positions.push_back(Node(cat_iter->first));

    /*
    // output positions .ids for debugging
    for ( int id = 0; id < num_nodes; id++ )
      cout << positions[id].id << endl;
    */

    // read .int file for graph info
    read_int(int_file);

    // initialize density server
    density_server.Init();

}



void graph::read_array(const int *edges, const float *weights, int edgeCount) {
    int id1, id2;
    float edge_weight;
    for (int i = 0; i < edgeCount; i++) {
        id1 = edges[i * 2 + 0];
        id2 = edges[i * 2 + 1];
        //emprintf("%d, %d", id1, id2);
        edge_weight = weights[i];
        edge_weight /= highest_sim;
        edge_weight = edge_weight * fabs(edge_weight);
        (neighbors[id_catalog[id1]])[id_catalog[id2]] = edge_weight;
        (neighbors[id_catalog[id2]])[id_catalog[id1]] = edge_weight;
    }

}


void graph::from_array(const int *edges, const float *weights, int edgeCount) {
    int id1, id2;
    float edge_weight;
    highest_sim = -1.0;
    for (int i = 0; i < edgeCount; i++) {
        id1 = edges[i * 2 + 0];
        id2 = edges[i * 2 + 1];
        edge_weight = weights[i];
        if (highest_sim < edge_weight)
            highest_sim = edge_weight;
        id_catalog[id1] = 1;
        id_catalog[id2] = 1;
        //emprintf("%d, %d", id1, id2);
        //cout << id1 << ' ' << id2 << ' ' << id_catalog[id1] << ' ' << id_catalog[id2] << endl;

    }
    // label nodes with sequential integers starting at 0
    map<int, int>::iterator cat_iter;
    int id_label;
    for (cat_iter = id_catalog.begin(), id_label = 0;
         cat_iter != id_catalog.end(); cat_iter++, id_label++)
        cat_iter->second = id_label;
    num_nodes = id_catalog.size();

}

// The following subroutine scans the .int file for the following
// information: number nodes, node ids, and highest similarity.  The
// corresponding graph globals are populated: num_nodes, id_catalog,
// and highest_sim.

void graph::scan_int(char *filename) {

    cout << "Proc. " << myid << " scanning .int file ..." << endl;

    // Open (sim) File
    ifstream fp(filename);
    if (!fp) {
        cout << "Error: could not open " << filename << ".  Program terminated." << endl;
#ifdef MUSE_MPI
        MPI_Abort ( MPI_COMM_WORLD, 1 );
#else
        exit(1);
#endif
    }

    // Read file, parse, and add into data structure
    int id1, id2;
    float edge_weight;
    highest_sim = -1.0;
    while (!fp.eof()) {
        fp >> id1 >> id2 >> edge_weight;

        // ignore negative weights!
        if (edge_weight <= 0) {
            cout << "Error: found negative edge weight in " << filename << ".  Program stopped." << endl;
#ifdef MUSE_MPI
            MPI_Abort ( MPI_COMM_WORLD, 1 );
#else
            exit(1);
#endif
        }

        if (highest_sim < edge_weight)
            highest_sim = edge_weight;

        id_catalog[id1] = 1;
        id_catalog[id2] = 1;
    }

    fp.close();

    if (id_catalog.size() == 0) {
        cout << "Error: Proc. " << myid << ": " << filename << " is empty.  Program terminated." << endl;
#ifdef MUSE_MPI
        MPI_Abort ( MPI_COMM_WORLD, 1 );
#else
        exit(1);
#endif
    }

    // label nodes with sequential integers starting at 0
    map<int, int>::iterator cat_iter;
    int id_label;
    for (cat_iter = id_catalog.begin(), id_label = 0;
         cat_iter != id_catalog.end(); cat_iter++, id_label++)
        cat_iter->second = id_label;

    /*
    // output id_catalog for debugging:
    for ( cat_iter = id_catalog.begin();
          cat_iter != id_catalog.end();
          cat_iter++ )
      cout << cat_iter->first << "\t" << cat_iter->second << endl;
    */

    num_nodes = id_catalog.size();
}

// read in .parms file, if present

void graph::read_parms(char *parms_file) {

    // read from .parms file
    ifstream parms_in(parms_file);
    if (!parms_in) {
        cout << "Error: could not open .parms file!  Program stopped." << endl;
#ifdef MUSE_MPI
        MPI_Abort ( MPI_COMM_WORLD, 1 );
#else
        exit(1);
#endif
    }

    cout << "Processor " << myid << " reading .parms file." << endl;

    // read in stage parameters
    string parm_label;    // this is ignored in the .parms file

    // initial parameters
    parms_in >> parm_label >> iterations;
    parms_in >> parm_label >> temperature;
    parms_in >> parm_label >> attraction;
    parms_in >> parm_label >> damping_mult;

    // liquid stage
    parms_in >> parm_label >> liquid.iterations;
    parms_in >> parm_label >> liquid.temperature;
    parms_in >> parm_label >> liquid.attraction;
    parms_in >> parm_label >> liquid.damping_mult;

    // expansion stage
    parms_in >> parm_label >> expansion.iterations;
    parms_in >> parm_label >> expansion.temperature;
    parms_in >> parm_label >> expansion.attraction;
    parms_in >> parm_label >> expansion.damping_mult;

    // cooldown stage
    parms_in >> parm_label >> cooldown.iterations;
    parms_in >> parm_label >> cooldown.temperature;
    parms_in >> parm_label >> cooldown.attraction;
    parms_in >> parm_label >> cooldown.damping_mult;

    // crunch stage
    parms_in >> parm_label >> crunch.iterations;
    parms_in >> parm_label >> crunch.temperature;
    parms_in >> parm_label >> crunch.attraction;
    parms_in >> parm_label >> crunch.damping_mult;

    // simmer stage
    parms_in >> parm_label >> simmer.iterations;
    parms_in >> parm_label >> simmer.temperature;
    parms_in >> parm_label >> simmer.attraction;
    parms_in >> parm_label >> simmer.damping_mult;

    parms_in.close();

    // print out parameters for double checking
    if (myid == 0) {
        cout << "Processor 0 reports the following inputs:" << endl;
        cout << "inital.iterations = " << iterations << endl;
        cout << "initial.temperature = " << temperature << endl;
        cout << "initial.attraction = " << attraction << endl;
        cout << "initial.damping_mult = " << damping_mult << endl;
        cout << " ..." << endl;
        cout << "liquid.iterations = " << liquid.iterations << endl;
        cout << "liquid.temperature = " << liquid.temperature << endl;
        cout << "liquid.attraction = " << liquid.attraction << endl;
        cout << "liquid.damping_mult = " << liquid.damping_mult << endl;
        cout << " ..." << endl;
        cout << "simmer.iterations = " << simmer.iterations << endl;
        cout << "simmer.temperature = " << simmer.temperature << endl;
        cout << "simmer.attraction = " << simmer.attraction << endl;
        cout << "simmer.damping_mult = " << simmer.damping_mult << endl;
    }

}

// init_parms -- this subroutine initializes the edge_cut variables
// used in the original VxOrd starting with the edge_cut parameter.
// In our version, edge_cut = 0 means no cutting, 1 = maximum cut.
// We also set the random seed here.

void graph::init_parms(int rand_seed, float edge_cut, float real_parm) {

    // first we translate edge_cut the former tcl sliding scale
    //CUT_END = cut_length_end = 39000.0 * (1.0 - edge_cut) + 1000.0;
    CUT_END = cut_length_end = 40000.0 * (1.0 - edge_cut);

    // cut_length_end cannot actually be 0
    if (cut_length_end <= 1.0)
        cut_length_end = 1.0;

    float cut_length_start = 4.0 * cut_length_end;

    // now we set the parameters used by ReCompute
    cut_off_length = cut_length_start;
    cut_rate = (cut_length_start - cut_length_end) / 400.0;

    // finally set the number of iterations to leave .real coords fixed
    int full_comp_iters;
    full_comp_iters = liquid.iterations + expansion.iterations +
                      cooldown.iterations + crunch.iterations + 3;

    // adjust real parm to iterations (do not enter simmer halfway)
    if (real_parm < 0)
        real_iterations = (int) real_parm;
    else if (real_parm == 1)
        real_iterations = full_comp_iters + simmer.iterations + 100;
    else
        real_iterations = (int) (real_parm * full_comp_iters);

    tot_iterations = 0;
    if (real_iterations > 0)
        real_fixed = true;
    else
        real_fixed = false;

    /*
    // output edge_cutting parms (for debugging)
    cout << "Processor " << myid << ": "
         << "cut_length_end = CUT_END = " << cut_length_end
         << ", cut_length_start = " << cut_length_start
         << ", cut_rate = " << cut_rate << endl;
    */

    // set random seed
    srand(rand_seed);

}

// The following subroutine reads a .real file to obtain initial
// coordinates.  If a node is missing coordinates the coordinates
// are computed 

void graph::read_real(char *real_file) {
    cout << "Processor " << myid << " reading .real file ..." << endl;

    // read in .real file and mark as fixed
    ifstream real_in(real_file);
    if (!real_in) {
        cout << "Error: proc. " << myid << " could not open .real file." << endl;
#ifdef MUSE_MPI
        MPI_Abort ( MPI_COMM_WORLD, 1 );
#else
        exit(1);
#endif
    }

    int real_id;
    float real_x, real_y;
    while (!real_in.eof()) {
        real_id = -1;
        real_in >> real_id >> real_x >> real_y;
        if (real_id >= 0) {
            positions[id_catalog[real_id]].x = real_x;
            positions[id_catalog[real_id]].y = real_y;
            positions[id_catalog[real_id]].fixed = true;

            /*
            // output positions read (for debugging)
            cout << id_catalog[real_id] << " (" << positions[id_catalog[real_id]].x
                 << ", " << positions[id_catalog[real_id]].y << ") "
                 << positions[id_catalog[real_id]].fixed << endl;
            */

            // add node to density grid
            if (real_iterations > 0)
                density_server.Add(positions[id_catalog[real_id]], fineDensity);
        }

    }

    real_in.close();
}

// The read_part_int subroutine reads the .int
// file produced by convert_sim and gathers the nodes and their
// neighbors in the range start_ind to end_ind.

void graph::read_int(char *file_name) {

    ifstream int_file;

    int_file.open(file_name);
    if (!int_file) {
        cout << "Error (worker process " << myid << "): could not open .int file." << endl;
#ifdef MUSE_MPI
        MPI_Abort ( MPI_COMM_WORLD, 1 );
#else
        exit(1);
#endif
    }

    cout << "Processor " << myid << " reading .int file ..." << endl;

    int node_1, node_2;
    float weight;

    while (!int_file.eof()) {
        weight = 0;        // all weights should be >= 0
        int_file >> node_1 >> node_2 >> weight;
        if (weight)        // otherwise we are at end of file
            // or it is a self-connected node
        {
            // normalization from original vxord
            weight /= highest_sim;
            weight = weight * fabs(weight);

            // initialize graph
            if ((node_1 % num_procs) == myid)
                (neighbors[id_catalog[node_1]])[id_catalog[node_2]] = weight;
            if ((node_2 % num_procs) == myid)
                (neighbors[id_catalog[node_2]])[id_catalog[node_1]] = weight;
        }
    }
    int_file.close();

    /*
    // the following code outputs the contents of the neighbors structure
    // (to be used for debugging)

    map<int, map<int,float> >::iterator i;
    map<int,float>::iterator j;

    for ( i = neighbors.begin(); i != neighbors.end(); i++ ) {
      cout << myid << ": " << i->first << " ";
        for (j = (i->second).begin(); j != (i->second).end(); j++ )
            cout << j->first << " (" << j->second << ") ";
        cout << endl;
        }
    */

}

/*********************************************
 * Function: ReCompute				         *
 * Description: Compute the graph locations	 *
 * Modified from original code by B. Wylie   *
 ********************************************/

int graph::ReCompute() {

    // carryover from original VxOrd
    int MIN = 1;

    // energy information is across processors
    float tot_energy;

    /*
    // output parameters (for debugging)
    cout << "ReCompute is using the following parameters: "<< endl;
    cout << "STAGE: " << STAGE << ", iter: " << iterations << ", temp = " << temperature
         << ", attract = " << attraction << ", damping_mult = " << damping_mult
         << ", min_edges = " << min_edges << ", cut_off_length = " << cut_off_length
         << ", fineDensity = " << fineDensity << endl;
    */

    /* Compute Energies for individual nodes */
    update_nodes();

    // check to see if we need to free fixed nodes
    tot_iterations++;
    if (tot_iterations >= real_iterations)
        real_fixed = false;


    // ****************************************
    // AUTOMATIC CONTROL SECTION
    // ****************************************

    // STAGE 0: LIQUID
    if (STAGE == 0) {

        if (iterations == 0) {
            start_time = time(NULL);
            if (myid == 0)
                cout << "Entering liquid stage ..." << endl;
        }

        if (iterations < liquid.iterations) {
            temperature = liquid.temperature;
            attraction = liquid.attraction;
            damping_mult = liquid.damping_mult;
            iterations++;
            #ifdef DEBUG
            if (myid == 0)
                cout << "." << endl;
            #endif

        } else {

            stop_time = time(NULL);
            liquid.time_elapsed = liquid.time_elapsed + (stop_time - start_time);
            temperature = expansion.temperature;
            attraction = expansion.attraction;
            damping_mult = expansion.damping_mult;
            iterations = 0;

            tot_energy = get_tot_energy();
            if (myid == 0)
                cout << endl << "Liquid stage completed in " << liquid.time_elapsed
                     << " seconds, total energy = " << tot_energy << "." << endl;

            // go to next stage
            STAGE = 1;
            start_time = time(NULL);

            if (myid == 0)

                cout << "Entering expansion stage ..." << endl;
        }
    }

    // STAGE 1: EXPANSION
    if (STAGE == 1) {

        if (iterations < expansion.iterations) {

            // Play with vars
            if (attraction > 1) attraction -= .05;
            if (min_edges > 12) min_edges -= .05;
            cut_off_length -= cut_rate;
            if (damping_mult > .1) damping_mult -= .005;
            iterations++;
            #ifdef DEBUG
            if (myid == 0) cout << "." << endl;
            #endif

        } else {

            stop_time = time(NULL);
            expansion.time_elapsed = expansion.time_elapsed + (stop_time - start_time);
            min_edges = 12;
            damping_mult = cooldown.damping_mult;

            tot_energy = get_tot_energy();
            if (myid == 0)
                cout << endl << "Finished expansion stage in " << expansion.time_elapsed
                     << " seconds, total energy = " << tot_energy << "." << endl;

            STAGE = 2;
            attraction = cooldown.attraction;
            temperature = cooldown.temperature;
            iterations = 0;
            start_time = time(NULL);

            if (myid == 0)
                cout << "Entering cool-down stage ..." << endl;
        }
    }

        // STAGE 2: Cool down and cluster
    else if (STAGE == 2) {

        if (iterations < cooldown.iterations) {

            // Reduce temperature
            if (temperature > 50) temperature -= 10;

            // Reduce cut length
            if (cut_off_length > cut_length_end) cut_off_length -= cut_rate * 2;
            if (min_edges > MIN) min_edges -= .2;
            //min_edges = 99;
            iterations++;
            #ifdef DEBUG
            if (myid == 0)
                cout << "." << endl;
            #endif

        } else {

            stop_time = time(NULL);
            cooldown.time_elapsed = cooldown.time_elapsed + (stop_time - start_time);
            cut_off_length = cut_length_end;
            temperature = crunch.temperature;
            damping_mult = crunch.damping_mult;
            min_edges = MIN;
            //min_edges = 99; // In other words: no more cutting

            tot_energy = get_tot_energy();
            if (myid == 0)
                cout << endl << "Completed cool-down stage in " << cooldown.time_elapsed
                     << " seconds, total energy = " << tot_energy << "." << endl;

            STAGE = 3;
            iterations = 0;
            attraction = crunch.attraction;
            start_time = time(NULL);

            if (myid == 0)
                cout << "Entering crunch stage ..." << endl;
        }
    }

        // STAGE 3: Crunch
    else if (STAGE == 3) {

        if (iterations < crunch.iterations) {
            iterations++;
            #ifdef DEBUG
            if (myid == 0) cout << "." << endl;
            #endif
        } else {

            stop_time = time(NULL);
            crunch.time_elapsed = crunch.time_elapsed + (stop_time - start_time);
            iterations = 0;
            temperature = simmer.temperature;
            attraction = simmer.attraction;
            damping_mult = simmer.damping_mult;
            min_edges = 99;
            fineDensity = true;

            tot_energy = get_tot_energy();
            if (myid == 0)
                cout << endl << "Finished crunch stage in " << crunch.time_elapsed
                     << " seconds, total energy = " << tot_energy << "." << endl;

            STAGE = 5;
            start_time = time(NULL);

            if (myid == 0)
                cout << "Entering simmer stage ..." << endl;
        }
    }

        // STAGE 5: Simmer
    else if (STAGE == 5) {

        if (iterations < simmer.iterations) {
            if (temperature > 50) temperature -= 2;
            iterations++;
            #ifdef DEBUG
            if (myid == 0) cout << "." << endl;
            #endif
        } else {
            stop_time = time(NULL);
            simmer.time_elapsed = simmer.time_elapsed + (stop_time - start_time);

            tot_energy = get_tot_energy();
            if (myid == 0)
                cout << endl << "Finished simmer stage in " << simmer.time_elapsed
                     << " seconds, total energy = " << tot_energy << "." << endl;

            STAGE = 6;

            if (myid == 0)
                cout << "Layout calculation completed in " <<
                     (liquid.time_elapsed + expansion.time_elapsed +
                      cooldown.time_elapsed + crunch.time_elapsed +
                      simmer.time_elapsed)
                     << " seconds (not including I/O)."
                     << endl;
        }
    }

        // STAGE 6: All Done!
    else if (STAGE == 6) {

        /*
        // output parameters (for debugging)
        cout << "ReCompute is using the following parameters: "<< endl;
        cout << "STAGE: " << STAGE << ", iter: " << iterations << ", temp = " << temperature
             << ", attract = " << attraction << ", damping_mult = " << damping_mult
             << ", min_edges = " << min_edges << ", cut_off_length = " << cut_off_length
             << ", fineDensity = " << fineDensity << endl;
        */

        return 0;
    }

    // ****************************************
    // END AUTOMATIC CONTROL SECTION
    // ****************************************

    // Still need more recomputation
    return 1;

}

// update_nodes -- this function will complete the primary node update
// loop in layout's recompute routine.  It follows exactly the same
// sequence to ensure similarity of parallel layout to the standard layout

void graph::update_nodes() {

    vector<int> node_indices;            // node list of nodes currently being updated
    float old_positions[2 * MAX_PROCS];    // positions before update
    float new_positions[2 * MAX_PROCS];    // positions after update

    bool all_fixed;                        // check if all nodes are fixed

    // initial node list consists of 0,1,...,num_procs
    for (int i = 0; i < num_procs; i++)
        node_indices.push_back(i);

    // next we calculate the number of nodes there would be if the
    // num_nodes by num_procs schedule grid were perfectly square
    int square_num_nodes = (int) (num_procs + num_procs * floor((float) (num_nodes - 1) / (float) num_procs));

    for (int i = myid; i < square_num_nodes; i += num_procs) {

        // get old positions
        get_positions(node_indices, old_positions);

        // default new position is old position
        get_positions(node_indices, new_positions);

        if (i < num_nodes) {

            // advance random sequence according to myid
            for (int j = 0; j < 2 * myid; j++)
                rand();

            // calculate node energy possibilities
            if (!(positions[i].fixed && real_fixed))
                update_node_pos(i, old_positions, new_positions);

            // advance random sequence for next iteration
            for (int j = 2 * myid; j < 2 * (node_indices.size() - 1); j++)
                rand();

        } else {
            // advance random sequence according to use by
            // the other processors
            for (int j = 0; j < 2 * (node_indices.size()); j++)
                rand();
        }

        // check if anything was actually updated (e.g. everything was fixed)
        all_fixed = true;
        for (unsigned int j = 0; j < node_indices.size(); j++)
            if (!(positions[node_indices[j]].fixed && real_fixed))
                all_fixed = false;

        // update positions across processors (if not all fixed)
        if (!all_fixed) {
#ifdef MUSE_MPI
            MPI_Allgather ( &new_positions[2*myid], 2, MPI_FLOAT,
                            new_positions, 2, MPI_FLOAT, MPI_COMM_WORLD );
#endif

            // update positions (old to new)
            update_density(node_indices, old_positions, new_positions);
        }

        /*
        if ( myid == 0 )
          {
            // output node list (for debugging)
            for ( unsigned int j = 0; j < node_indices.size(); j++ )
              cout << node_indices[j] << " ";
            cout << endl;
          }
        */

        // compute node list for next update
        for (unsigned int j = 0; j < node_indices.size(); j++)
            node_indices[j] += num_procs;

        while (node_indices[node_indices.size() - 1] >= num_nodes)
            node_indices.pop_back();

    }

    // update first_add and fine_first_add
    first_add = false;
    if (fineDensity) fine_first_add = false;

}

// The get_positions function takes the node_indices list
// and returns the corresponding positions in an array.

void graph::get_positions(vector<int> &node_indices,
                          float return_positions[2 * MAX_PROCS]) {

    // fill positions
    for (unsigned int i = 0; i < node_indices.size(); i++) {
        return_positions[2 * i] = positions[node_indices[i]].x;
        return_positions[2 * i + 1] = positions[node_indices[i]].y;
    }

}

// update_node_pos -- this subroutine does the actual work of computing
// the new position of a given node.  num_act_proc gives the number
// of active processes at this level for use by the random number
// generators.

void graph::update_node_pos(int node_ind,
                            float old_positions[2 * MAX_PROCS],
                            float new_positions[2 * MAX_PROCS]) {

    float energies[2];            // node energies for possible positions
    float updated_pos[2][2];    // possible positions
    float pos_x, pos_y;

    // old VxOrd parameter
    float jump_length = .010 * temperature;

    // subtract old node
    density_server.Subtract(positions[node_ind], first_add, fine_first_add, fineDensity);

    // compute node energy for old solution
    energies[0] = Compute_Node_Energy(node_ind);

    // move node to centroid position
    Solve_Analytic(node_ind, pos_x, pos_y);
    positions[node_ind].x = updated_pos[0][0] = pos_x;
    positions[node_ind].y = updated_pos[0][1] = pos_y;
    /*
    // ouput random numbers (for debugging)
    int rand_0, rand_1;
    rand_0 = rand();
    rand_1 = rand();
    cout << myid << ": " << rand_0 << ", " << rand_1 << endl;
    */

    // Do random method (RAND_MAX is C++ maximum random number)
    updated_pos[1][0] = updated_pos[0][0] + (.5 - rand() / (float) RAND_MAX) * jump_length;
    updated_pos[1][1] = updated_pos[0][1] + (.5 - rand() / (float) RAND_MAX) * jump_length;

    // compute node energy for random position
    positions[node_ind].x = updated_pos[1][0];
    positions[node_ind].y = updated_pos[1][1];
    energies[1] = Compute_Node_Energy(node_ind);

    /*
    // output update possiblities (debugging):
    cout << node_ind << ": (" << updated_pos[0][0] << "," << updated_pos[0][1]
         << "), " << energies[0] << "; (" << updated_pos[1][0] << ","
         << updated_pos[1][1] << "), " << energies[1] << endl;
    */

    // add back old position
    positions[node_ind].x = old_positions[2 * myid];
    positions[node_ind].y = old_positions[2 * myid + 1];
    if (!fineDensity && !first_add)
        density_server.Add(positions[node_ind], fineDensity);
    else if (!fine_first_add)
        density_server.Add(positions[node_ind], fineDensity);

    // choose updated node position with lowest energy

    if (energies[0] < energies[1]) {
        new_positions[2 * myid] = updated_pos[0][0];
        new_positions[2 * myid + 1] = updated_pos[0][1];
        positions[node_ind].energy = energies[0];
    } else {
        new_positions[2 * myid] = updated_pos[1][0];
        new_positions[2 * myid + 1] = updated_pos[1][1];
        positions[node_ind].energy = energies[1];
    }

}

// update_density takes a sequence of node_indices and their positions and
// updates the positions by subtracting the old positions and adding the
// new positions to the density grid.

void graph::update_density(vector<int> &node_indices,
                           float old_positions[2 * MAX_PROCS],
                           float new_positions[2 * MAX_PROCS]) {

    // go through each node and subtract old position from
    // density grid before adding new position
    for (unsigned int i = 0; i < node_indices.size(); i++) {
        positions[node_indices[i]].x = old_positions[2 * i];
        positions[node_indices[i]].y = old_positions[2 * i + 1];
        density_server.Subtract(positions[node_indices[i]],
                                first_add, fine_first_add, fineDensity);

        positions[node_indices[i]].x = new_positions[2 * i];
        positions[node_indices[i]].y = new_positions[2 * i + 1];
        density_server.Add(positions[node_indices[i]], fineDensity);
    }

}

/********************************************
* Function: Compute_Node_Energy			    *
* Description: Compute the node energy		*
* This code has been modified from the      *
* original code by B. Wylie.                *
*********************************************/

float graph::Compute_Node_Energy(int node_ind) {

    /* Want to expand 4th power range of attraction */
    float attraction_factor = attraction * attraction *
                              attraction * attraction * 2e-2;

    map<int, float>::iterator EI;
    float x_dis, y_dis;
    float energy_distance, weight;
    float node_energy = 0;

    // Add up all connection energies
    for (EI = neighbors[node_ind].begin(); EI != neighbors[node_ind].end(); ++EI) {
        // Get edge weight
        weight = EI->second;

        // Compute x,y distance
        x_dis = positions[node_ind].x - positions[EI->first].x;
        y_dis = positions[node_ind].y - positions[EI->first].y;

        // Energy Distance
        energy_distance = x_dis * x_dis + y_dis * y_dis;
        if (STAGE < 2) energy_distance *= energy_distance;

        // In the liquid phase we want to discourage long link distances
        if (STAGE == 0) energy_distance *= energy_distance;

        node_energy += weight * attraction_factor * energy_distance;
    }

    // output effect of density (debugging)
    //cout << "[before: " << node_energy;

    // add density
    node_energy += density_server.GetDensity(positions[node_ind].x, positions[node_ind].y,
                                             fineDensity);

    // after calling density server (debugging)
    //cout << ", after: " << node_energy << "]" << endl;

    // return computated energy
    return node_energy;
}


/*********************************************
* Function: Solve_Analytic			         *
* Description: Compute the node position     *
* This is a modified version of the function *
* originally written by B. Wylie		     *
*********************************************/

void graph::Solve_Analytic(int node_ind, float &pos_x, float &pos_y) {

    map<int, float>::iterator EI;
    float total_weight = 0;
    float x_dis, y_dis, x_cen = 0, y_cen = 0;
    float x = 0, y = 0, dis;
    float damping, weight;

    // Sum up all connections
    for (EI = neighbors[node_ind].begin(); EI != neighbors[node_ind].end(); ++EI) {
        weight = EI->second;
        total_weight += weight;
        x += weight * positions[EI->first].x;
        y += weight * positions[EI->first].y;
        //emprintf("%f, %f", x, y);
    }

    // Now set node position
    if (total_weight > 0) {

        // Compute centriod
        x_cen = x / total_weight;
        y_cen = y / total_weight;
        damping = 1.0 - damping_mult;
        pos_x = damping * positions[node_ind].x + (1.0 - damping) * x_cen;
        pos_y = damping * positions[node_ind].y + (1.0 - damping) * y_cen;
    }

    // No cut edge flag (?)
    if (min_edges == 99) return;

    // Don't cut at end of scale
    if (CUT_END >= 39500) return;

    float num_connections = sqrtf(neighbors[node_ind].size());
    float maxLength = 0;

    map<int, float>::iterator maxIndex;

    // Go through nodes edges... cutting if necessary
    for (EI = maxIndex = neighbors[node_ind].begin();
         EI != neighbors[node_ind].end(); ++EI) {

        // Check for at least min edges
        if (neighbors[node_ind].size() < min_edges) continue;

        x_dis = x_cen - positions[EI->first].x;
        y_dis = y_cen - positions[EI->first].y;
        dis = x_dis * x_dis + y_dis * y_dis;
        dis *= num_connections;

        // Store maximum edge
        if (dis > maxLength) {
            maxLength = dis;
            maxIndex = EI;
        }
    }

    // If max length greater than cut_length then cut
    if (maxLength > cut_off_length) neighbors[node_ind].erase(maxIndex);

}


// write_coord writes out the coordinate file of the final solutions

void graph::write_coord(const char *file_name) {

    ofstream coordOUT(file_name);
    if (!coordOUT) {
        cout << "Could not open " << file_name << ".  Program terminated." << endl;
#ifdef MUSE_MPI
        MPI_Abort ( MPI_COMM_WORLD, 1 );
#else
        exit(1);
#endif
    }

    cout << "Writing out solution to " << file_name << " ..." << endl;

    for (unsigned int i = 0; i < positions.size(); i++) {
        coordOUT << positions[i].id << "\t" << positions[i].x << "\t" << positions[i].y << endl;
    }
    coordOUT.close();

}

// write_sim -- outputs .edges file, takes as input .coord filename,
// with .coord extension

void graph::write_sim(const char *file_name) {

    string prefix_name(file_name, strlen(file_name) - 7);
    prefix_name = prefix_name + ".iedges";

    // first we overwrite, then we append
    ofstream simOUT;
    if (myid == 0)
        simOUT.open(prefix_name.c_str());
    else
        simOUT.open(prefix_name.c_str(), ios::app);

    if (!simOUT) {
        cout << "Could not open " << prefix_name << ". Program terminated." << endl;
#ifdef MUSE_MPI
        MPI_Abort ( MPI_COMM_WORLD, 1 );
#else
        exit(1);
#endif
    }


    cout << "Proc. " << myid << " writing to " << prefix_name << " ..." << endl;


    // the following code outputs the contents of the neighbors structure

    map<int, map<int, float> >::iterator i;
    map<int, float>::iterator j;

    for (i = neighbors.begin(); i != neighbors.end(); i++)
        for (j = (i->second).begin(); j != (i->second).end(); j++)
            simOUT << positions[i->first].id << "\t"
                   << positions[j->first].id << "\t"
                   << j->second << endl;

    simOUT.close();

}

// get_tot_energy adds up the energy for each node to give an estimate of the
// quality of the minimization.

float graph::get_tot_energy() {

    float my_tot_energy, tot_energy;
    my_tot_energy = 0;
    for (int i = myid; i < num_nodes; i += num_procs)
        my_tot_energy += positions[i].energy;

    //vector<Node>::iterator i;
    //for ( i = positions.begin(); i != positions.end(); i++ )
    //	tot_energy += i->energy;

#ifdef MUSE_MPI
    MPI_Reduce ( &my_tot_energy, &tot_energy, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD );
#else
    tot_energy = my_tot_energy;
#endif

    return tot_energy;

}

bool graph::run(int batchIterations) {
    int this_iter = 0;
    bool more = true;
    while (this_iter < batchIterations) {
        more = (bool) ReCompute();
        if (!more) {
            break;
        }
        this_iter++;
    }
    //emprintf("%f, %f", positions[0].x, positions[0].y);
    //emprintf("Now at: %d, energy: %f", this->tot_iterations, this->get_tot_energy());
    return more;
}

void graph::get_positions_buffer(float* result_buffer) {
    for(auto const& value: positions) {
        result_buffer[value.id * 2 + 0] = value.x;
        result_buffer[value.id * 2 + 1] = value.y;
    }
}

// The following subroutine draws the graph with possible intermediate
// output (int_out is set to 0 if not proc. 0).  int_out is the parameter
// passed by the user, and coord_file is the .coord file.

void graph::draw_graph(int int_out, char *coord_file) {

    // layout graph (with possible intermediate output)
    int count_iter = 0, count_file = 1;
    char int_coord_file[MAX_FILE_NAME + MAX_INT_LENGTH];
    while (ReCompute())
        if ((int_out > 0) && (count_iter == int_out)) {
            // output intermediate solution
            sprintf(int_coord_file, "%s.%d", coord_file, count_file);
            write_coord(int_coord_file);

            count_iter = 0;
            count_file++;
        } else
            count_iter++;

}

void graph::get_positions_js(emscripten::val onComplete) {
    float result_buffer[num_nodes * 2];
    get_positions_buffer(result_buffer);
    //result_buffer[0] = num_nodes;
    onComplete(emscripten::memory_view<float>(num_nodes * 2, result_buffer));
}

int main() {
    cout << "this is a graph. lol. changed. lol123" <<endl;
    return 0;
}
