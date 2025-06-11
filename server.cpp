#include <dbus/dbus.h>
#include <iostream>
#include <cstring>
#include <ctime>

void handle_message(DBusMessage* msg, DBusConnection* conn) {
    if (dbus_message_is_method_call(msg, "org.example.Notification", "Notify")) {
        DBusMessageIter args;
        dbus_message_iter_init(msg, &args);

        const char* message;
        dbus_message_iter_get_basic(&args, &message);


        std::time_t now = std::time(nullptr);
        std::tm* timeinfo = std::localtime(&now);
        char bufferTime[64];
        std::strftime(bufferTime, sizeof(bufferTime), "%c", timeinfo);
        std::cout << "[LOG " << bufferTime << "] " << message << std::endl;

        DBusMessage* reply = dbus_message_new_method_return(msg);
        dbus_connection_send(conn, reply, NULL);
        dbus_message_unref(reply);
    }
}

int main() {
    DBusConnection* conn;
    DBusError err;

    dbus_error_init(&err);
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

    dbus_bus_request_name(conn, "org.example.NotificationService", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);

    std::cout << "NotificationService running..." << std::endl;

    while (true) {
        dbus_connection_read_write(conn, 0);
        DBusMessage* msg = dbus_connection_pop_message(conn);
        if (msg) {
            handle_message(msg, conn);
            dbus_message_unref(msg);
        }
    }
}
