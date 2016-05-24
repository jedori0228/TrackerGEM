#!/bin/bash
for c in 0 10 50 100 140
do
	root -l -b -q "draw_MuonGunPU.C($c)"
done
root -l -b -q merge_PU.C
