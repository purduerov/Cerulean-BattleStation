#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QMutexLocker>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QIODevice>
#include "godheader.h"

#define SERIAL_CTL_HEADER 0x12
#define SERIAL_CTL_FOOTER 0x13

/**
 * Establishes and maintains the serial connection to the robot.
 */
class Serial : public QObject
{
    Q_OBJECT

    /** Mutex lock to ensure singular access to control_packet_ */
    QMutex m_packet_mutex;

    /** Mutex lock to ensure singular access to the tool queue */
    QMutex m_tool_mutex;

    /** A queue containing transformations to SerialControlPacket::toolBits */
    QQueue<quint32> m_tool_events;

    /** The singleton control packet we use. Make a copy to send values */
    struct SerialControlPacket {
        quint8 header;
        quint8 motorHTL;
        quint8 motorHTR;
        quint8 motorHBR;
        quint8 motorHBL;
        quint8 motorVTL;
        quint8 motorVTR;
        quint8 motorVBR;
        quint8 motorVBL;
        quint8 footTurner;
        quint8 toolBits;
        quint8 laserStepper;
        quint8 led1;
        quint8 led2;
        quint8 led3;
        quint8 led4;
        quint8 led5;
        quint8 ledColor;
        quint8 crc8;
        quint8 footer;
    } m_control_packet;

    /** The serial port over which we communicate */
    QSerialPort* m_serial_port;

    /** An array to remap internal motor IDs to wire IDs */
    quint8 m_motor_mapping[8];


public:
    explicit Serial(QObject *parent = 0);
    ~Serial();

    /**
     * Opens the serial port with the given name.
     * Returns true if successful, false otherwise. Call GetError() for details.
     */
    bool Open(QString deviceName);

    /**
     * Gets the last error, or QSerialPort::NoError if no error.
     */
    QSerialPort::SerialPortError GetError();

    /**
     * Performs a network update pulse. This should NOT be on the UI thread.
     * If serial is not connected, then search for a connection and update the candidate list.
     * If the candidate list is zero, do nothing; if it has one element, set it as the active
     * serial; if there are more than one then let the user select it from the dropdown.
     * ##TENATIVE##
     * If connected, each pulse sends out a control packet with the latest motor values and whatever tool updates that
     * can be sent, so long as two update events cannot interfere (e.g. claw close and claw open cannot
     * be sent simultaneously, but claw open and light on can be).
     */
    void NetworkTick();

signals:

    /** Signalled when the serial device is changed, indicating success (true) or failure (false) */
    void SerialDeviceChanged(bool success);

public slots:
    /**
     * Set the current motor values. Value changes are not guaranteed to be sent immediately
     * and can be overwritten by later calls to this function if the Serial Network Thread has
     * not yet sent out another SerialControlPacket. Can be called from any thread.
     * @param values[] An array of 8 8-bit values encoded as per the packet spec. Len = 8 = num motors
     */
    void SetMotorValues(quint8 values[]);
    /**
     * Set the current foot turner value. Value changes are not guaranteed to be sent immediately
     * and can be overwritten by later calls to this function if the Serial Network Thread has
     * not yet sent out another SerialControlPacket. Can be called from any thread.
     */
    void SetFootTurner(quint8 value);
    /**
     * Enqueues a change to the tool bits. Assuming the connection does not fail, each change will be
     * sent independently, but not necessarily immediately. Can be called from any thread.
     */
    void EnqueueToolEvent(quint8 value, quint8 mask);

    /**
     * Set the current LED values and color. Value changes are not guaranteed to be sent immediately
     * and can be overwritten by later calls to this function if the Serial Network Thread has
     * not yet sent out another SerialControlPacket. Can be called from any thread.
     * @param values[] An array of 5 8-bit values encoded as per the packet spec. Len = 5 = num LEDs
     * @param color The color for the LEDs, encoded in 3-3-2 bit RGB.
     */
    void SetLedValues(quint8 values[], quint8 color);

    /**
     * Sets serial to use the given serial device.
     */
    void SetActiveSerialDevice(QString name);

};

#endif // SERIAL_H
