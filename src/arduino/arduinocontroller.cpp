#include "arduino/arduinocontroller.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

ArduinoController::ArduinoController() {
    // Constructor
}

ArduinoController::~ArduinoController() {
    // Destructor
    if (my_serial.isOpen()) {
        my_serial.close();
    }
}

void ArduinoController::_init() {
    port = "/dev/ttyUSB0";
    baudrate = 9600;
}

void ArduinoController::_process(float delta) {
    if (!my_serial.isOpen()) {
        my_serial.setPort(port.utf8().get_data());
        my_serial.setBaudrate(baudrate);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        my_serial.setTimeout(to);
        my_serial.open();
    }

    if (my_serial.available()) {
        std::string result = my_serial.readline();
    }
}

void ArduinoController::set_port(String p) {
    port = p;
}

void ArduinoController::set_baudrate(int b) {
    baudrate = b;
}

void register_classes() {
    ClassDB::register_class<ArduinoController>();
}

