echo Starting compilation.

cd 2c_euler
echo ...2c_euler.c compilation started
gcc 2c_euler.c -lm -o 2c_euler.out
echo ...2c_euler.c compilation over
cd ..

cd 2c_rk
echo ...2c_rk.c compilation started
gcc 2c_rk.c -lm -o 2c_rk.out
echo ...2c_rk.c compilation over
cd ..

cd 10c_euler
echo ...10c_euler.c compilation started
gcc 10c_euler.c -lm -o 10c_euler.out
echo ...10c_euler.c compilation over
cd ..

cd 10c_rk
echo ...10c_rk.c compilation started
gcc 10c_rk.c -lm -o 10c_rk.out
echo ...10c_rk.c compilation over
cd ..

echo compilation over
echo  
echo starting program execution

cd 2c_euler
echo ...2c_euler.out running
./2c_euler.out
echo ...2c_euler.out finished
cd ..

cd 2c_rk
echo ...2c_rk.out running
./2c_rk.out
echo ...2c_rk.out finished
cd ..

cd 10c_euler
echo ...10c_euler.out running
./10c_euler.out
echo ...10c_euler.out finished
cd ..

cd 10c_rk
echo ...10c_rk.out running
./10c_rk.out
echo ...10c_rk.out finished
cd ..

echo run sequence over
echo  
echo starting creation of graphs

echo ...creating plots:2c_euler
cd 2c_euler
chmod u+x 2c_euler.sh
gnuplot 2c_euler.sh
mkdir -p graphs
mv orbites3D.png -t graphs
mv orbites2D.png -t graphs
mv r_i.png -t graphs
mv vitesse_soleil.png -t graphs
mv vitesse_terre.png -t graphs
mv moment_cinétique.png -t graphs
mv energie.png -t graphs
mv impulsion.png -t graphs
mv perihelie.png -t graphs
echo ...2c_euler plots made
mkdir -p data
mv euler2.txt -t data
mv extra2eu.txt -t data
mv pe2eu.txt -t data
cd ..

echo ...creating plots:2c_rk
cd 2c_rk
chmod u+x 2c_rk.sh
gnuplot 2c_rk.sh
mkdir -p graphs
mv orbites3D.png -t graphs
mv orbites2D.png -t graphs
mv r_i.png -t graphs
mv vitesse_soleil.png -t graphs
mv vitesse_terre.png -t graphs
mv moment_cinétique.png -t graphs
mv energie.png -t graphs
mv impulsion.png -t graphs
mv perihelie.png -t graphs
echo ...2c_rk plots made
mkdir -p data
mv rk2.txt -t data
mv extra2rk.txt -t data
mv pe2rk.txt -t data
cd ..

echo ...creating plots:10c_euler
cd 10c_euler
chmod u+x 10c_euler.sh
gnuplot 10c_euler.sh
mkdir -p graphs
mv orbites3D.png -t graphs
mv orbites2D.png -t graphs
mv perihelie_Mercure.png -t graphs
mv perihelie.png -t graphs
echo ...10c_euler plots made
mkdir -p data
mv euler10.txt -t data
mv pe10eu.txt -t data
cd ..

echo ...creating plots:10c_rk
cd 10c_rk
chmod u+x 10c_rk.sh
gnuplot 10c_rk.sh
mkdir -p graphs
mv orbites3D.png -t graphs
mv orbites2D.png -t graphs
mv delta_phy_Mercure.png -t graphs
mv delta_phy.png -t graphs
echo ...10c_rk plots made
mkdir -p data
mv rk10.txt -t data
mv pe10rk.txt -t data
cd ..

