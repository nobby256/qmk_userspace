qmk compile -kb crkbd/rev4_1/mini -km default

qmk flash -kb crkbd/rev4_1/mini -km default -bl uf2-split-right
qmk flash -kb crkbd/rev4_1/mini -km default -bl uf2-split-left
