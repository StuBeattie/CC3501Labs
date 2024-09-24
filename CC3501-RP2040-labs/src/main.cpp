<<<<<<< HEAD
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include <iostream>

#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "drivers/leds.h" 

#define LED_PIN 14

int main() {
    stdio_init_all(); // Initialize standard I/O
    init_leds(LED_PIN, 800000); // Initialize the LEDs

    while (true) {
        // User interaction to set LED colors
        uint32_t led_index;
        uint8_t red, green, blue;

        printf("Enter LED index (0 to %d): ", NUM_LEDS - 1);
        scanf("%u", &led_index); // Read the LED index from user input

        if (led_index >= NUM_LEDS) {
            printf("Invalid LED index. Please try again.\n");
            continue; // Skip to the next iteration if the index is invalid
        }

        printf("Enter color values (0-255) for Red, Green, Blue:\n");

        printf("Red: ");
        scanf("%hhu", &red);
        printf("You entered Red: %hhu\n", red); // Display the entered value

        printf("Green: ");
        scanf("%hhu", &green);
        printf("You entered Green: %hhu\n", green); // Display the entered value

        printf("Blue: ");
        scanf("%hhu", &blue);
        printf("You entered Blue: %hhu\n", blue); // Display the entered value

        // Set the specified LED color
        set_led(led_index, red, green, blue);
        update_leds(); // Commit changes to the LEDs

        // Optionally, to turn off all LEDs, you can include a check
        char command;
        printf("Do you want to turn off all LEDs? (y/n): ");
        scanf(" %c", &command);
        if (command == 'y' || command == 'Y') {
            turn_off_leds(); // Turn off all LEDs
            update_leds(); // Commit the changes
        }

        printf("\n"); // Add a new line for better readability
    }

    return 0;
}
=======
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

Mat bgr_img, hsv_img;

int main()
{
    // Open the video camera.
    std::string pipeline = "libcamerasrc"
        " ! video/x-raw, width=800, height=600" // camera needs to capture at a higher resolution
        " ! videoconvert"
        " ! videoscale"
        " ! video/x-raw, width=400, height=300" // can downsample the image after capturing
        " ! videoflip method=rotate-180" // remove this line if the image is upside-down
        " ! appsink drop=true max_buffers=2";
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        printf("Could not open camera.\n");
        return 1;
    }

    // Create the OpenCV window
 //   cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);
    cv::Mat frame;

    // Measure the frame rate - initialize variables
    int frame_id = 0;
    timeval start, end;
    gettimeofday(&start, NULL);

    // Create a control window
    namedWindow("Control", WINDOW_AUTOSIZE);
    cv::resizeWindow("Control", 400, 100); // Set the size of the control window
    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 0;
    int iHighV = 255;

    // Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); // Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255); // Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255); // Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);

    // Create the display windows
//    namedWindow("Display", WINDOW_AUTOSIZE);
//    namedWindow("Thresholded", WINDOW_AUTOSIZE);

    while (true) {
        if (!cap.read(frame)) {
            printf("Could not read a frame.\n");
            break;
        }

        // Process your frame here...

        // Measure the frame rate
        frame_id++;
        if (frame_id >= 30) {
            gettimeofday(&end, NULL);
            double diff = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
 //           printf("30 frames in %f seconds = %f FPS\n", diff, 30 / diff);
            frame_id = 0;
            gettimeofday(&start, NULL);
        }

        // Convert to HSV colour space
        cvtColor(frame, hsv_img, COLOR_BGR2HSV);

        // Display the result of the current calibration settings
        Mat thresh_img;
        Mat display_img = frame.clone(); // deep copy because we will modify it below

        // Threshold the image
        inRange(hsv_img, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), thresh_img);

        // Apply morphological opening operation
        Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
        morphologyEx(thresh_img, thresh_img, MORPH_OPEN, kernel);

        // Apply morphological closing operation
        morphologyEx(thresh_img, thresh_img, MORPH_CLOSE, kernel);

        // Calculate moments of the thresholded image
        Moments moments = cv::moments(thresh_img);

        // Calculate center of mass
        double cx = moments.m10 / moments.m00;
        double cy = moments.m01 / moments.m00;

        // Print the coordinates to the terminal
        printf("Objects Centre of mass: X = %.2f, Y = %.2f\n", cx, cy);

        // Show the thresholded image
        imshow("Thresholded", thresh_img);

        // Draw the final image
        imshow("Display", display_img);

        // Allow OpenCV to process GUI events
        waitKey(100);
    }

    // Release the camera
    cap.release();
    return 0;
}

>>>>>>> 93d3d86f6d72182dad392f012228c06558fc8288
