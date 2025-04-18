#ifndef BUTTONS_CONTROLS_H
#define BUTTONS_CONTROLS_H

typedef struct {
    int up;
    int down;
} ButtonState;

void Buttons_Init(void);
ButtonState Buttons_Read(void);

int Mode_IsAuto(void);



#endif
