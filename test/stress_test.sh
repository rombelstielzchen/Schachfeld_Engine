# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

# Secure bashing
set -o errexit
set -o nounset

time ./uci_test.pl --stress

