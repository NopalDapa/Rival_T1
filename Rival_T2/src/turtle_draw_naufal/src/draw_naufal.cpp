#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/TeleportAbsolute.h"
#include "turtlesim/SetPen.h"
#include <unistd.h> // untuk sleep
#include <cmath> // untuk M_PI

// Fungsi untuk memindahkan turtle dengan parameter yang ditentukan
void moveTurtle(ros::Publisher &pub, ros::ServiceClient &pen_client, double speed, double distance, double rotation_degree, bool draw) {
    // Mengatur pena
    turtlesim::SetPen pen_srv;
    pen_srv.request.off = !draw; // Jika draw true, maka off = 0 (hidupkan pena)
    pen_client.call(pen_srv);

    // Jika ada rotasi, hitung arah
    double direction = rotation_degree * M_PI / 180.0; // Konversi derajat ke radian
    geometry_msgs::Twist vel_msg;

    // Berputar terlebih dahulu jika ada rotasi yang ditentukan
    if (rotation_degree != 0.0) {
        vel_msg.angular.z = direction; // Atur rotasi
        ros::Rate loop_rate(10); // Rate loop 10 Hz

        double t0 = ros::Time::now().toSec();
        double current_angle = 0.0;

        // Berputar hingga mencapai sudut yang ditentukan
        while (current_angle < fabs(direction)) {
            pub.publish(vel_msg);
            double t1 = ros::Time::now().toSec();
            current_angle = fabs(direction) * (t1 - t0);
            ros::spinOnce();
            loop_rate.sleep();
        }

        // Menghentikan rotasi setelah mencapai sudut
        vel_msg.angular.z = 0;
        pub.publish(vel_msg);
    }

    // Atur kecepatan pergerakan
    vel_msg.linear.x = speed; // Atur kecepatan linear
    vel_msg.angular.z = 0; // Pastikan tidak ada rotasi saat bergerak
    ros::Rate loop_rate(10); // Rate loop 10 Hz

    double t0 = ros::Time::now().toSec();
    double current_distance = 0.0;

    // Menggerakkan turtle
    while (current_distance < distance) {
        pub.publish(vel_msg);
        double t1 = ros::Time::now().toSec();
        current_distance = speed * (t1 - t0);
        ros::spinOnce();
        loop_rate.sleep();
    }

    // Menghentikan turtle setelah mencapai jarak yang ditentukan
    vel_msg.linear.x = 0;
    pub.publish(vel_msg);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "draw_naufal");
    ros::NodeHandle nh;

    // Klien untuk teleportasi
    ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    // Klien untuk mengatur pena
    ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    // Publisher untuk pergerakan
    ros::Publisher velocity_publisher = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    // Tunggu hingga service tersedia
    ros::service::waitForService("/turtle1/teleport_absolute");
    ros::service::waitForService("/turtle1/set_pen");

    moveTurtle(velocity_publisher, pen_client, 2.0, 4.5, 225.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, -85.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.80, 210.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.50, 130.0, true);

    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -90.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, -85.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, 168.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -90.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -90.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, 166.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, 90.0, true);

    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, 160.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, -85.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, 85.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, 85.0, true);

    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -90.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, -80.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, 168.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -90.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, 166.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -80.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -80.0, true);

    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, 00.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, -85.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, 168.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -90.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, -90.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, 166.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.75, 90.0, true);

    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, 168.0, false);
    moveTurtle(velocity_publisher, pen_client, 2.0, 1.5, -90.0, true);
    moveTurtle(velocity_publisher, pen_client, 2.0, 0.05, 90.0, true);
    return 0;
}