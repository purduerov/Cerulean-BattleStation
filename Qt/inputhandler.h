#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include "joystick.h"
#include "tickclock.h"
#include "interpolator.h"

/**
 * The InputHandler class manages joystick input and converts it into
 * values for controlling motors, tools, etc.
 */
class InputHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<JoystickInfo> joysticks READ listJoysticks NOTIFY joysticksChanged)
    Q_PROPERTY(bool joystickActive READ joystickActive NOTIFY joystickActiveChanged)

    Joystick* m_joystick;
    bool m_joystickActive;
    QList<JoystickInfo> m_joysticks;
    Interpolator** interpolators;
    quint8 claw = 0;

public:
    InputHandler();
    //~InputHandler();

    /**
      * Sets the current/active joystick to the stick at the given index.
      * This function does not return a success/fail, but rather emits the
      * signal joystickActiveChanged(boolean success) indicating whether or
      * not the change went through.
      */
    Q_INVOKABLE void setJoystick(int index);

    /**
     * Returns a list of available joysticks.
     */
    QList<JoystickInfo> listJoysticks();


    /**
     * Performs on-tick actions. CALL IT EVERY TICK. OR ELSE.
     */
    void tick(TickClock* clock);

    /**
     * JoystickActive property
     */
    bool joystickActive() const {
        return m_joystickActive;
    }

    void setSliders(QObject* root);

    void scale(qint32 thrusters[]);

    QObject* horizontalSlider;
    QObject* verticalSlider;
    QObject* pitchRollSlider;
    QObject* strafeSlider;

    QObject* t1MaxSpeed;
    QObject* t2MaxSpeed;
    QObject* t3MaxSpeed;
    QObject* t4MaxSpeed;

    QObject* t5MaxSpeed;
    QObject* t6MaxSpeed;
    QObject* t7MaxSpeed;
    QObject* t8MaxSpeed;

public slots:

signals:
    /**
     * Signalled when the available joysticks changes.
     */
    void joysticksChanged(QList<JoystickInfo> list);
    /**
     * Signalled after the active joystick has been changed (or failed to change).
     */
    void joystickActiveChanged(bool newVal);
};

#endif // INPUTHANDLER_H
