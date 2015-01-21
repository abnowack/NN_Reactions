#!/bin/bash

./NN_reactions.exe -i 92235 -n 100000 -f 2 nudist_n2n_u235.res
./NN_reactions.exe -i 92235 -n 100000 -f 3 nudist_n3n_u235.res
gnuplot -e "isotope='U235';n2file='nudist_n2n_u235.res';n3file='nudist_n3n_u235.res'" plot.gnu
./NN_reactions.exe -i 92238 -n 100000 -f 2 nudist_n2n_u238.res
./NN_reactions.exe -i 92238 -n 100000 -f 3 nudist_n3n_u238.res
gnuplot -e "isotope='U238';n2file='nudist_n2n_u238.res';n3file='nudist_n3n_u238.res'" plot.gnu
