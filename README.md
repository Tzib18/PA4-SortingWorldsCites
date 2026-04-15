# PA4-SortingWorldsCites

to compile the main program: 

make run

This command will compile the program and run it. After it has been compiled once, you can run it again anytime using:

./program

Run the tests functions: 

To run the tests, simply type exit while in the program. This will take you to the testing file, where it will indicate whether the tests have passed or not.

Container Choice:
I used a vector<CITY> to store all of the city records. I chose a vector because it works well with sorting algorithms, supports indexed access, and made it easier to pass the full dataset into my sorting functions.

Missing Data:
Some rows in the CSV file had missing population values. For those rows, I decided to store the population as 0. I chose this because it allowed me to keep the record in the dataset instead of skipping it completely, while still handling the missing value in a simple and consistent way.

CSV Parsing:
To load the dataset, I manually parsed each line of the CSV file. I kept track of whether I was inside quotation marks so that commas inside quoted fields would not split the row incorrectly. This was important because some city or country-related fields can contain commas.

City Class:
I created a CITY class to store the data for each record. Each object stores: city name, latitude, longitude, country, population.

Testing:
I used cassert to test the correctness of my sorting functions. I grouped my tests into four main categories.

1. testInsertionSortCity()
This test checks that Insertion Sort works correctly with CITY objects.
It verifies:
- sorting by population in descending order
- sorting by city name alphabetically

2. testMergeSortCity()
This test checks that Merge Sort works correctly with CITY objects.
It verifies:
- sorting by country alphabetically
- sorting by latitude in descending order

3. testEdgeCases()
This test checks edge cases to make sure my sorting algorithms do not break on unusual inputs.
It verifies:
- empty vector
- single-element vector
- already-sorted vector
- reverse-sorted vector

4. testTemplateGenerality()
This test checks that my template sorting functions work beyond CITY.
It verifies:
- sorting a vector<int>
- sorting a vector<string>

Performance Analysis

I recorded the elapsed time for each algorithm and field below.

Field	Insertion Sort (ms) |	Merge Sort (ms)
population	[fill in]	| [69.989 ms]
city	    [fill in]	| [109.274 ms]
country	    [fill in]	| [107.129 ms]
latitude	[fill in]	| [82.442 ms]