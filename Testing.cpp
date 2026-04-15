#include "Testing.hpp"

void testInsertionSortCity()
{
    // Hand-made city data for testing
    vector<CITY> cities;
    cities.push_back(CITY("Tokyo", 35.68, 139.69, "Japan", 37732000));
    cities.push_back(CITY("Seattle", 47.61, -122.33, "United States", 750000));
    cities.push_back(CITY("Pullman", 46.73, -117.17, "United States", 32000));

    // Test sorting by population (descending)
    insertionSort(cities, [](const CITY& a, const CITY& b)
    {
        return a.getPopulation() > b.getPopulation();
    });

    assert(cities[0].getCity() == "Tokyo");
    assert(cities[1].getCity() == "Seattle");
    assert(cities[2].getCity() == "Pullman");

    // Reset vector for another field test
    cities.clear();
    cities.push_back(CITY("Tokyo", 35.68, 139.69, "Japan", 37732000));
    cities.push_back(CITY("Seattle", 47.61, -122.33, "United States", 750000));
    cities.push_back(CITY("Pullman", 46.73, -117.17, "United States", 32000));

    // Test sorting by city name (A-Z)
    insertionSort(cities, [](const CITY& a, const CITY& b)
    {
        return a.getCity() < b.getCity();
    });

    assert(cities[0].getCity() == "Pullman");
    assert(cities[1].getCity() == "Seattle");
    assert(cities[2].getCity() == "Tokyo");

    cout << "testInsertionSortCity passed!" << endl;
}

void testMergeSortCity()
{
    vector<CITY> cities;
    cities.push_back(CITY("Tokyo", 35.68, 139.69, "Japan", 37732000));
    cities.push_back(CITY("Seattle", 47.61, -122.33, "United States", 750000));
    cities.push_back(CITY("Sydney", -33.86, 151.20, "Australia", 5300000));
    cities.push_back(CITY("Paris", 48.85, 2.35, "France", 2100000));

    // Test sorting by country (A-Z)
    mergeSort(cities, [](const CITY& a, const CITY& b)
    {
        return a.getCountry() < b.getCountry();
    });

    assert(cities[0].getCountry() == "Australia");
    assert(cities[1].getCountry() == "France");
    assert(cities[2].getCountry() == "Japan");
    assert(cities[3].getCountry() == "United States");

    // Reset vector for latitude test
    cities.clear();
    cities.push_back(CITY("Tokyo", 35.68, 139.69, "Japan", 37732000));
    cities.push_back(CITY("Seattle", 47.61, -122.33, "United States", 750000));
    cities.push_back(CITY("Sydney", -33.86, 151.20, "Australia", 5300000));
    cities.push_back(CITY("Paris", 48.85, 2.35, "France", 2100000));

    // Test sorting by latitude (descending, north to south)
    mergeSort(cities, [](const CITY& a, const CITY& b)
    {
        return a.getLat() > b.getLat();
    });

    assert(cities[0].getCity() == "Paris");
    assert(cities[1].getCity() == "Seattle");
    assert(cities[2].getCity() == "Tokyo");
    assert(cities[3].getCity() == "Sydney");

    cout << "testMergeSortCity passed!" << endl;
}

void testEdgeCases()
{
    // Empty vector
    vector<int> emptyVec;
    insertionSort(emptyVec, [](int a, int b)
    {
        return a < b;
    });
    assert(emptyVec.empty());

    mergeSort(emptyVec, [](int a, int b)
    {
        return a < b;
    });
    assert(emptyVec.empty());

    // Single-element vector
    vector<int> oneElement = {42};
    insertionSort(oneElement, [](int a, int b)
    {
        return a < b;
    });
    assert(oneElement[0] == 42);

    mergeSort(oneElement, [](int a, int b)
    {
        return a < b;
    });
    assert(oneElement[0] == 42);

    // Already sorted vector
    vector<int> sortedVec = {1, 2, 3, 4, 5};
    insertionSort(sortedVec, [](int a, int b)
    {
        return a < b;
    });
    assert(sortedVec[0] == 1);
    assert(sortedVec[4] == 5);

    // Reverse sorted vector
    vector<int> reverseVec = {5, 4, 3, 2, 1};
    mergeSort(reverseVec, [](int a, int b)
    {
        return a < b;
    });
    assert(reverseVec[0] == 1);
    assert(reverseVec[1] == 2);
    assert(reverseVec[2] == 3);
    assert(reverseVec[3] == 4);
    assert(reverseVec[4] == 5);

    cout << "testEdgeCases passed!" << endl;
}

void testTemplateGenerality()
{
    // Test with integers
    vector<int> nums = {4, 1, 3, 2};
    insertionSort(nums, [](int a, int b)
    {
        return a < b;
    });

    assert(nums[0] == 1);
    assert(nums[1] == 2);
    assert(nums[2] == 3);
    assert(nums[3] == 4);

    // Test with strings
    vector<string> words = {"zebra", "apple", "cat", "banana"};
    mergeSort(words, [](const string& a, const string& b)
    {
        return a < b;
    });

    assert(words[0] == "apple");
    assert(words[1] == "banana");
    assert(words[2] == "cat");
    assert(words[3] == "zebra");

    cout << "testTemplateGenerality passed!" << endl;
}

void runAllTests()
{
    testInsertionSortCity();
    testMergeSortCity();
    testEdgeCases();
    testTemplateGenerality();
}
