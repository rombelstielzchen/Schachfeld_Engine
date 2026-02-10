# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

# Secure bashing
set -o errexit
set -o nounset

echo "### 1) Quick selftest first ... ########"
./uci_test.pl --selftest

echo "### 2) Basic UCI-test ... ##############"
./uci_test.pl

echo "### 3) Repeated start and shutdown ... ##"
for j in { 1..123 }
do
    ./uci_test.pl --quit
done

echo "### 4) Main stress-test ... ############"
time ./uci_test.pl --stress

echo "Stress-test finished"

