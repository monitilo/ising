#!bin/bash


start=$(date +%s)

./ising.e

end=$(date +%s)

echo $(($end-$start))
