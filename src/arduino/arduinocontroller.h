// src/ArduinoController.h
#ifndef ARDUINO_CONTROLLER_H
#define ARDUINO_CONTROLLER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <serial/serial.h>

using namespace godot;

class ArduinoController : public Node {
    GDCLASS(ArduinoController, Node);

private:
    serial::Serial my_serial;
    String port;
    int baudrate;

public:
    ArduinoController();
    ~ArduinoController();

    void _init();
    void _process(float delta);

    void set_port(String p);
    void set_baudrate(int b);
};

#endif
