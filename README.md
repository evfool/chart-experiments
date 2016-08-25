# chart-experiments
Experiments with graphs and charts in a GTK world, and with the Meson build system.

The goal would be to have a performant library able to display realtime charts for CPU/disk/network monitoring.
The current implementation (as well as the one in System-Monitor) eats too much CPU (and is occasionally choppy).
CPU time is mostly consumed in cairo (88.85 based on a callgrind run of tests/graph test),
more specifically due to the cairo_curve_to calls responsible for drawing the smooth graph.

The starting point is a shameless copy from the gnome-builder repository (https://git.gnome.org/browse/gnome-builder/):
* the contrib/rg folder
* egg-signal-group.{c,h} from contrib/egg
* tests/test-cpu-graph.c is from tests
