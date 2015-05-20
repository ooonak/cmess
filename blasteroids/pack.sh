#!/bin/sh
tar -cvf blasteroids_$1.tar blasteroids arial.ttf
tar -rvf blasteroids_$1.tar /usr/lib/liballegro.so.5.0* /usr/lib/liballegro_primitives.so.5.0* /usr/lib/liballegro_font.so.5.0* /usr/lib/liballegro_ttf.so.5.0*
gzip blasteroids_$1.tar
