# UNICODE_ENABLE = yes
# CONSOLE_ENABLE = yes
# COMMAND_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  naginata_v16m.c
SRC +=  naginata_parts.c
SRC +=	unicode_P.c
#SRC +=  twpair_on_jis.c

# 以下、独自に追加
SRC +=  x_userprocess.c
SRC +=  x_nagi_adopt.c
SRC +=  x_alttab.c
SRC +=  x_layer.c
SRC +=  x_combo.c
SRC +=  x_kakutei.c
SRC +=  x_zenkaku.c
SRC +=  x_ngedit.c
