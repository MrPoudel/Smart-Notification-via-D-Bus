#include <dbus/dbus.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./client \"Your message here\"" << std::endl;
        return 1;
    }

    DBusError err;
    DBusConnection* conn;

    dbus_error_init(&err);
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

    DBusMessage* msg;
    msg = dbus_message_new_method_call(
        "org.example.NotificationService",
        "/org/example/Notification",
        "org.example.Notification",
        "Notify"
    );

    const char* message = argv[1];
    dbus_message_append_args(msg, DBUS_TYPE_STRING, &message, DBUS_TYPE_INVALID);
    dbus_connection_send(conn, msg, NULL);
    dbus_message_unref(msg);

    std::cout << "Message sent." << std::endl;
    return 0;
}
