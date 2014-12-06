#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QList>
#include <QDebug>
#include "SDL.h"
#undef main

#define XBOX_BUTTON_A_ID 10
#define XBOX_BUTTON_B_ID 11
#define XBOX_BUTTON_X_ID 12
#define XBOX_BUTTON_Y_ID 13
#define XBOX_BUTTON_LB_ID 8
#define XBOX_BUTTON_RB_ID 9
#define XBOX_BUTTON_BACK_ID 5
#define XBOX_BUTTON_SELECT_ID 4
#define XBOX_BUTTON_LJ_ID 6
#define XBOX_BUTTON_RJ_ID 7
#define XBOX_AXIS_LJ_X_ID 0
#define XBOX_AXIS_LJ_Y_ID 1
#define XBOX_AXIS_RJ_X_ID 2
#define XBOX_AXIS_RJ_Y_ID 3
#define XBOX_AXIS_TRIGGER_ID 5

struct JoystickInfo {
    int joystickId;
    QString name;
};

struct ButtonState {
    bool lastState;
    bool currentState;
};

class Joystick : public QObject
{
    Q_OBJECT
public:
    Joystick(int joystickId);
    ~Joystick();

    QString* init();

    qint16 getAxis(int axisId);
    float getAxisF(int axisId);
    bool getButtonState(int buttonId);
    bool getHasButtonJustBeenReleased(int buttonId);
    bool getHasButtonJustBeenPressed(int buttonId);
    int getNumAxes();
    int getNumButtons();
    bool isOpen();
    void poll();

    static QString* initSDL();
    static int numberOfJoysticks();
    static QString getJoystickName(int index);

private:
    QList<qint16> m_axes;
    QList<ButtonState> m_buttons;
    QList<bool> m_rawButtons;
    const int m_joystickId;
    SDL_Joystick* m_joystick;
    bool open;

signals:
    void buttonPressed(int buttonId);
    void buttonReleased(int buttonId);
    void axisChanged(int axisId, qint16 newVal, qint16 delta);
    void axisChangedF(int axisId, float newVal, float delta);

public slots:

};

#endif // JOYSTICK_H
