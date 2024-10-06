### CSC 357 Assignment 2 - Pointers and Arrays

Purpose:
- This assignment involves working with pointers and arrays in C to manipulate and visualize data. Specifically, you will build a program to generate a histogram from a dataset provided in CSV (comma-separated values) format.
  
Tasks and Specifics:

Ground Rules:
- Your code must compile on the Cal Poly UNIX servers using gcc with flags like -Wall, -Wextra, -Werror, -ansi, and -pedantic.
- Programs must compile and run on these servers without errors.

Histograms:
- The main task is to create a C program called hist that visualizes a dataset as a histogram.
- The histogram represents intervals of data points with bars, where each bar's height corresponds to the number of data points within a specific interval.
- The first interval corresponds to the minimum data point, rounded down to the nearest multiple of 10, and the last interval corresponds to the maximum data point, rounded up to the nearest multiple of 10.
- Intervals follow the form [2i−1, 2i], and intervals where 2i is a multiple of 10 are labeled on the horizontal axis.
- The height of the histogram corresponds to the tallest interval, rounded up to the nearest multiple of 5, with labeled heights.
  
Handling CSV Input:
- The dataset is provided in CSV format, with each row of the CSV representing a data point in the histogram.
- You need to sum each row of the CSV to get a data point. Rows may contain non-integer values, which should be treated as zero.
- Spaces, tabs, and non-integer values are ignored in the dataset.
- If a row has a mismatched number of cells or contains unsupported characters (like quotation marks), the program must print an error message and exit with a specific status code (1 for mismatched cells, 2 for unsupported characters).
- If no errors are encountered, the program should terminate with exit status 0.
  
Key Library Functions:
- The assignment suggests using standard C library functions like fgets, strtol, strchr, and strlen to handle input and process the CSV data.
  
Testing:
- The histogram output should be tested by comparing the generated output with the expected output using the diff command.
  
Sample test cases include:
- Correctly formatted CSV data resulting in a properly displayed histogram.
- Mismatched CSV data that triggers an error message.
- CSV data containing unsupported characters like quotes.
