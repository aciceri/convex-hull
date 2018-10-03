reset

set terminal wxt enhanced persist
set size 1,1
set style line 12 lc rgb'#808080' lt 0 lw 1
set grid back ls 12

set style line 1 \
    linecolor rgb '#0000ffd' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.0

set style line 2 \
    linecolor rgb '#ff0000' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.0 

plot "points.dat" with points linestyle 1 title "", \
     "hull.dat" with lines linestyle 2 title ""
