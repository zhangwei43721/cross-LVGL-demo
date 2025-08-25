SET(SOURCES components/ui_comp_rfidcontainer.c
    components/ui_comp.c
    screens/ui_Login_Screen.c
    screens/ui_Main_Screen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    fonts/ui_font_MiSans15.c
    fonts/ui_font_MiSans18.c
    fonts/ui_font_MiSans20.c)

add_library(ui ${SOURCES})
