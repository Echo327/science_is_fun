set terminal png enhanced size 1280,960

set output "orbites3D.png"
splot "rk10.txt" u 2:3:4 w l title 'Soleil'
set output "orbites3D.png"
replot "rk10.txt" u 5:6:7 w l title 'Mercure'
set output "orbites3D.png"
replot "rk10.txt" u 8:9:10 w l title 'Venus'
set output "orbites3D.png"
replot "rk10.txt" u 11:12:13 w l title 'Terre'
set output "orbites3D.png"
replot "rk10.txt" u 14:15:16 w l title 'Mars'
set output "orbites3D.png"
replot "rk10.txt" u 17:18:19 w l title 'Jupiter'
set output "orbites3D.png"
replot "rk10.txt" u 20:21:22 w l title 'Saturne'
set output "orbites3D.png"
replot "rk10.txt" u 23:24:25 w l title 'Uranus'
set output "orbites3D.png"
replot "rk10.txt" u 26:27:28 w l title 'Neptune'
set output "orbites3D.png"
replot "rk10.txt" u 29:30:31 w l title 'Pluton'

set output "orbites2D.png"
plot "rk10.txt" u 2:3 w l title 'Soleil'
set output "orbites2D.png"
replot "rk10.txt" u 5:6 w l title 'Mercure'
set output "orbites2D.png"
replot "rk10.txt" u 8:9 w l title 'Venus'
set output "orbites2D.png"
replot "rk10.txt" u 11:12 w l title 'Terre'
set output "orbites2D.png"
replot "rk10.txt" u 14:15 w l title 'Mars'
set output "orbites2D.png"
replot "rk10.txt" u 17:18 w l title 'Jupiter'
set output "orbites2D.png"
replot "rk10.txt" u 20:21 w l title 'Saturne'
set output "orbites2D.png"
replot "rk10.txt" u 23:24 w l title 'Uranus'
set output "orbites2D.png"
replot "rk10.txt" u 26:27 w l title 'Neptune'
set output "orbites2D.png"
replot "rk10.txt" u 29:30 w l title 'Pluton'

set output "delta_phy_Mercure.png"
plot "pe10rk.txt" u 1:3 w l title 'perihelie_Mercure'

set output "delta_phy.png"
plot "pe10rk.txt" u 1:3 w l title 'Mercure'
set output "delta_phy.png"
replot "pe10rk.txt" u 1:4 w l title 'Venus'
set output "delta_phy.png"
replot "pe10rk.txt" u 1:5 w l title 'Terre'
set output "delta_phy.png"
replot "pe10rk.txt" u 1:6 w l title 'Mars'
set output "delta_phy.png"
replot "pe10rk.txt" u 1:7 w l title 'Jupiter'
set output "delta_phy.png"
replot "pe10rk.txt" u 1:8 w l title 'Saturne'

exit

