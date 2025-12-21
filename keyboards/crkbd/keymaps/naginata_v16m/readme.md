qmk compile -kb crkbd/rev1 -km naginata_v16m
qmk compile -kb crkbd/rev4_1/mini -km naginata_v16m

qmk flash -kb crkbd/rev4_1/mini -km naginata_v16m -bl uf2-split-right
qmk flash -kb crkbd/rev4_1/mini -km naginata_v16m -bl uf2-split-left
