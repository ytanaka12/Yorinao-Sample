#!/bin/sh
sudo servod --p1pins=11,13,15,19,21,23,29,31,33,35,16,18,22,32 \
--min=10us --max=3000us \
--step-size=2us --cycle-time=3000us