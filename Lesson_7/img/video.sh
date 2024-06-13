#!/bin/bash
ffmpeg -f x11grab -framerate 30 -video_size 1250x680 -i :0  -b:v 10M output.mp4

