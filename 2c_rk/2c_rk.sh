set terminal png enhanced size 1280,960

set output "orbites3D.png"
splot "rk2.txt" u 2:3:4 w l title 'Soleil'
set output "orbites3D.png"
replot "rk2.txt" u 5:6:7 w l title 'Terre'

set output "orbites2D.png"
plot "rk2.txt" u 2:3 w l title 'Soleil'
set output "orbites2D.png"
replot "rk2.txt" u 5:6 w l title 'Terre'

set output "r_i.png"
plot "extra2rk.txt" u 1:2 w l title 'r(t)'
set output "vitesse_soleil.png"
plot "extra2rk.txt" u 1:3 w l title 'Vitesse-Soleil'
set output "vitesse_terre.png"
plot "extra2rk.txt" u 1:4 w l title 'Vitesse-Terre'
set output "moment_cinétique.png"
plot "extra2rk.txt" u 1:7 w l title 'Moment Cinétique Totale'
set output "energie.png"
plot "extra2rk.txt" u 1:8 w l title 'Energie Totale'
set output "impulsion.png"
plot "extra2rk.txt" u 1:9 w l title 'Impulsion Totale'

set output "perihelie.png"
plot "pe2rk.txt" u 1:2 w l

exit

