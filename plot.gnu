set terminal png medium

if(!exists("isotope")) isotope='???'
set title "Neutron Fission Spectra for 14.1 Incident on ".isotope

set style line 1 linecolor 1 linetype 10 linewidth 3
set style line 2 linecolor 2 linetype 10 linewidth 3

set xlabel "Energy [MeV]"
set ylabel "Probability"

set key right top

set output isotope.'.png'
plot \
"nudist_n2n.res" using 1:5 with histeps ls 1 title "2 neutrons emitted", \
"nudist_n3n.res" using 1:5 with histeps ls 2 title "3 neutrons emitted"
