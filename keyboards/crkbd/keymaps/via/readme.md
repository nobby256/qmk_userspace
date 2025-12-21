qmk compile -kb crkbd/rev4_1/mini -km via

qmk flash -kb crkbd/rev4_1/mini -km via -bl uf2-split-right
qmk flash -kb crkbd/rev4_1/mini -km via -bl uf2-split-left
