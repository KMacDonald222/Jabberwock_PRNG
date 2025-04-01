# File:     run_tests.sh
# Author:   Keegan MacDonald
# Created:  2025.04.01
# Purpose:  Run the Python implementation of the SP 800-22 Rev 1a Test Suite on
#           each file in the data/ directory

# Get the number of files to test
read -p "Data file count: " count

# Iterate over file names
for index in $(seq 1 $count)
do
    # Test the current file
    echo "Testing data/"$index".bin"
    python3 sp800_22_tests/sp800_22_tests.py "data/"$index".bin" \
        > "results/"$index".txt"
done