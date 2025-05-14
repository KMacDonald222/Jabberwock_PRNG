# File:     Compile_Results.py
# Author:   Keegan MacDonald
# Created:  2025.04.01
# Purpose:  Extract the pass/fail results of the NIST SP 800-22 Rev 1a tests
#           and calculate the success rate of each test

# Get the number of test result files
file_count = int(input("Test count: "))

# Initialize test results
test_names = [ "" ] * 15
results = [ 0 ] * 15

# Read all test results
for index in range(file_count):
    in_file = open("Results/" + str(index + 1) + ".txt", "r")
    lines = in_file.readlines()
    in_file.close();
    # Iterate through test result lines
    for li in range(len(lines) - 15, len(lines)):
        p = 15 - (len(lines) - li)
        line = lines[li].strip()
        # Get the name of the current test
        if len(test_names[p]) == 0:
            for c in line:
                if c == ' ':
                    break
                test_names[p] += c
        # Add result
        if line.endswith("PASS"):
            results[p] += 1

# Print compiled results
for i in range(15):
    tn = test_names[i]
    r = results[i]
    fc = file_count
    pc = (100.0 * float(r)) / float(fc)
    print(tn, ": ", r, " / ", fc, " = ", pc, "%", sep = "")