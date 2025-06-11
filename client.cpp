#include <dbus/dbus.h>
#include <iostream>
#include <csignal>

bool keepRunning = true;

void signalHandler(int signum) {
    std::cout << "\n[Client] Exiting on signal " << signum << std::endl;
    keepRunning = false;
}

int main(int argc, char** argv) {

    signal(SIGINT, signalHandler); // Handle Ctrl+C

    DBusError err;
    dbus_error_init(&err);
    DBusConnection* conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

    if (dbus_error_is_set(&err)) {
        std::cerr << "Connection Error: " << err.message << std::endl;
        dbus_error_free(&err);
        return 1;
    }

    std::string input;
    std::cout << "[Client] Enter messages (Ctrl+C to exit):\n";
    while (keepRunning) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) break;

        DBusMessage* msg = dbus_message_new_method_call(
            "org.example.NotificationService",
            "/org/example/Notification",
            "org.example.Notification",
            "Notify"
        );

        const char* c_str = input.c_str();
        dbus_message_append_args(msg, DBUS_TYPE_STRING, &c_str, DBUS_TYPE_INVALID);
        dbus_connection_send(conn, msg, nullptr);
        dbus_message_unref(msg);
    }

    return 0;
}
