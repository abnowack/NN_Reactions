#!/bin/bash

./NN_reactions.exe -i 92235 -n 100000 -f 2 nudist_n2n.res
./NN_reactions.exe -i 92235 -n 100000 -f 3 nudist_n3n.res
gnuplot -e "isotope='U235'" plot.gnu
./NN_reactions.exe -i 92238 -n 100000 -f 2 nudist_n2n.res
./NN_reactions.exe -i 92238 -n 100000 -f 3 nudist_n3n.res
gnuplot -e "isotope='U238'" plot.gnu
