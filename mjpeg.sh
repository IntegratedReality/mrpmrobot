#!/bin/bash

/home/mayfes/mjpg-streamer/mjpg-streamer/mjpg-streamer-experimental/mjpg_streamer -o "/home/mayfes/mjpg-streamer/mjpg-streamer/mjpg-streamer-experimental/output_http.so -w /home/mayfes/mjpg-streamer/mjpg-streamer/mjpg-streamer-experimental/www -p 8080" -i "/home/mayfes/mjpg-streamer/mjpg-streamer/mjpg-streamer-experimental/input_raspicam.so -fps 20 -x 320 -y 240"
