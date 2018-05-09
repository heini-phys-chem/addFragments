#!/bin/bash

#e2ts_C_E_E_D_A_B_2.xyz

FG=("A.xyz" "B.xyz" "C.xyz" "D.xyz" "E.xyz") 
position=(1 2 3 4)

for i in "${FG[@]}"
do
	for j in "${position[@]}"
	do
		if [ $j == 1 ] 
		then
			./main xyz/e2ts_C_E_E_D_A_B_2.xyz	test/${i::-4}_$j.xyz $j C xyz/$i
		fi
		if [ $j == 2 ]
		then
			./main xyz/e2ts_C_E_E_D_A_B_2.xyz	test/${i::-4}_$j.xyz $j E xyz/$i
		fi
		if [ $j == 3 ]
		then
			./main xyz/e2ts_C_E_E_D_A_B_2.xyz	test/${i::-4}_$j.xyz $j E xyz/$i
		fi
		if [ $j == 4 ]
		then
			./main xyz/e2ts_C_E_E_D_A_B_2.xyz	test/${i::-4}_$j.xyz $j D xyz/$i
		fi
	done
done

rm test/C_1.xyz test/E_2.xyz test/E_3.xyz test/D_4.xyz
