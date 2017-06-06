#!bin/bash


start=$(date +%s)

./ising.e

end=$(date +%s)

echo $(($end-$start))

#python graficos.py MvsT.txt
