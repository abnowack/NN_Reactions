#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <unistd.h>

#include "fissionEvent.h"

const double MIN_ENERGY = 0.;
const double MAX_ENERGY = 15;
const int NBINS = 100;

void output(const std::string &, const std::vector<int> &);

int main(int argc, char **argv) {
    int isotope = 92235;
    double neutron_energy_MeV = 14.1;
    unsigned int events = 1000;
    std::string output_file = "nudist.res";
    unsigned int n_fiss_n = 2;

    int index, c;

    while ((c = getopt(argc, argv, "i:e:n:f:")) != -1)
        switch (c) {
            case 'i':
                isotope = atoi(optarg);
                break;
            case 'e':
                neutron_energy_MeV = atof(optarg);
                break;
            case 'n':
                events = atoi(optarg);
                break;
            case 'f':
                n_fiss_n = atoi(optarg);
                break;
            default:
                std::cout << "i = isotope" << std::endl;
                std::cout << "e = energy" << std::endl;
                std::cout << "n = events" << std::endl;
                return 1;
        }

    for (index = optind; index < argc; index++) {
        if (index == optind)
            output_file = argv[index];
    }

    double nubar = 2.523670;
    double time = 0.;

    int maxerrorlength = 10000;
    char errors[maxerrorlength];

    std::vector<int> hist(NBINS, 0);

    fissionEvent::setCorrelationOption(3);

    for (int i = 0; i < events; i++) {
        std::unique_ptr<fissionEvent> fe(new fissionEvent(isotope, time, nubar, neutron_energy_MeV, 1));
        int errorlength = maxerrorlength;
        fe->getFREYAerrors(&errorlength, &errors[0]);
        if (errorlength > 1) {
            std::cout << errors << std::endl;
            exit(1);
        }
        int nneutrons = fe->getNeutronNu();
        if (nneutrons == n_fiss_n) {
            for (int n1 = 0; n1 < nneutrons; n1++) {
                double eng = fe->getNeutronEnergy(n1);
                int energy_bin_index = (int) (eng / (MAX_ENERGY - MIN_ENERGY) * NBINS);
                if (energy_bin_index >= 0 && energy_bin_index < NBINS)
                    hist[energy_bin_index]++;
            }
        }
    }
    output(output_file, hist);

    return 0;
}

void output(const std::string &name, const std::vector<int> &hist) {
    std::ofstream file(name);
    auto sum = std::accumulate(hist.begin(), hist.end(), 0);
    double bin_width = (MAX_ENERGY - MIN_ENERGY) / NBINS;
    for (int i = 0; i < hist.size(); i++)
        file << MIN_ENERGY + bin_width * i << " - " << MIN_ENERGY + bin_width * (i + 1) << " : " << 1. * hist[i] / sum << std::endl;

    return;
}