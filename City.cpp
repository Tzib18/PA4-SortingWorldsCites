#include "City.hpp"

vector<CITY> parseFile(const string &filename)
{
    // Open the CSV file
    ifstream infile(filename);

    // Safety check to make sure the file opened correctly
    if (!infile.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return {};
    }

    string line;

    // This vector will store all City objects from the file
    vector<CITY> storedCities;

    // Skip the header line at the top of the CSV file
    getline(infile, line);

    // Read the file one line at a time
    while (getline(infile, line))
    {
        // This vector will store each field from one CSV row
        vector<string> fields;

        // This string temporarily builds one field at a time
        string currentField = "";

        // Tracks whether we are currently inside quotation marks
        // This matters because commas inside quotes should NOT split fields
        bool inQuotes = false;

        // Go through each character in the line manually
        for (size_t i = 0; i < line.length(); i++)
        {
            char ch = line[i];

            // If we hit a quote, flip the inQuotes flag
            if (ch == '"')
            {
                inQuotes = !inQuotes;
            }
            // If we hit a comma and we are NOT inside quotes,
            // then that comma ends the current field
            else if (ch == ',' && !inQuotes)
            {
                fields.push_back(currentField);
                currentField = "";
            }
            // Otherwise, keep adding characters to the current field
            else
            {
                currentField += ch;
            }
        }

        // Push the very last field after the loop ends
        fields.push_back(currentField);

        // Make sure the row has enough columns before accessing indexes
        // The common worldcities.csv format has at least 10 columns
        if (fields.size() < 10)
        {
            continue; // skip malformed rows
        }

        // Extract only the fields needed for this assignment
        // These indexes match the common worldcities.csv dataset format:
        // 0 = city
        // 2 = latitude
        // 3 = longitude
        // 4 = country
        // 9 = population
        string city = fields[0];
        string latStr = fields[2];
        string lngStr = fields[3];
        string country = fields[4];
        string populationStr = fields[9];

        // Variables to hold converted numeric values
        double lat = 0.0;
        double lng = 0.0;
        int population = 0;

        try
        {
            // Convert latitude and longitude from string to double
            lat = stod(latStr);
            lng = stod(lngStr);

            // Handle missing population values
            // If population is blank, store 0 as the default
            if (!populationStr.empty())
            {
                population = stoi(populationStr);
            }
            else
            {
                population = 0;
            }
        }
        catch (const exception &e)
        {
            // If any conversion fails, skip this row
            cout << "Error parsing line: " << line << endl;
            continue;
        }

        // Create a CITY object from the parsed values
        CITY newCity(city, lat, lng, country, population);

        // Add the city to the vector
        storedCities.push_back(newCity);
    }

    // Close the file when finished
    infile.close();

    // Return the full vector of City objects
    return storedCities;
}

void handleSortCommand(const string& algorithmName,
                       const string& fieldName,
                       const vector<CITY>& masterData)
{
    // Make sure the master dataset is not empty
    if (masterData.empty())
    {
        cout << "No city data loaded." << endl;
        return;
    }

    // Comparator that will be assigned depending on the chosen field
    function<bool(const CITY&, const CITY&)> comp;

    // Build the correct comparator
    if (fieldName == "population")
    {
        // Sort by population descending (largest first)
        comp = [](const CITY& a, const CITY& b)
        {
            return a.getPopulation() > b.getPopulation();
        };
    }
    else if (fieldName == "city")
    {
        // Sort city names alphabetically (A-Z)
        comp = [](const CITY& a, const CITY& b)
        {
            return a.getCity() < b.getCity();
        };
    }
    else if (fieldName == "country")
    {
        // Sort country names alphabetically (A-Z)
        comp = [](const CITY& a, const CITY& b)
        {
            return a.getCountry() < b.getCountry();
        };
    }
    else if (fieldName == "latitude")
    {
        // Sort latitude descending (north to south)
        comp = [](const CITY& a, const CITY& b)
        {
            return a.getLat() > b.getLat();
        };
    }
    else
    {
        cout << "Invalid field name: " << fieldName << endl;
        return;
    }

    // Make a fresh copy so every command sorts unsorted original data
    vector<CITY> workingData = masterData;

    Timer timer;

    // Choose the sorting algorithm
    if (algorithmName == "insertionSort")
    {
        timer.start();
        insertionSort(workingData, comp);
        timer.stop();
    }
    else if (algorithmName == "mergeSort")
    {
        timer.start();
        mergeSort(workingData, comp);   // use wrapper version
        timer.stop();
    }
    else
    {
        cout << "Invalid algorithm name: " << algorithmName << endl;
        return;
    }

    // Print top 10 results
    int limit = 10;
    if (workingData.size() < 10)
    {
        limit = workingData.size();
    }

    for (int i = 0; i < limit; i++)
    {
        cout << i + 1 << ". "
             << workingData[i].getCity() << ", "
             << workingData[i].getCountry() << ", "
             << workingData[i].getPopulation() << ", "
             << workingData[i].getLat() << endl;
    }

    // Print timing
    cout << "\nElapsed time: " << timer.elapsedMilliseconds() << " ms" << endl;
}

void run_app()
{
    // Load the CSV dataset
    vector<CITY> cities = parseFile("worldcities.csv");

    cout << "Loaded " << cities.size() << " cities." << endl << endl;

    // ---------------- REPL ----------------
    string line;
    while (true){
        cout << "> ";

        if (!getline(cin, line)){
            break; // EOF
        }

        // Trim leading whitespace
        size_t start = line.find_first_not_of(" \t");
        if (start == string::npos)
        {
            continue;
        }
        line = line.substr(start);

        // Quit command
        if (line == "quit" || line == "exit")
        {
            cout << "Goodbye!" << endl;
            break;
        }

        // Parse command: <algorithm> <field>
        istringstream iss(line);
        string algorithm;
        string field;
        iss >> algorithm >> field;

        // Check if the user entered both parts
        if (algorithm.empty() || field.empty())
        {
            cout << "Usage: <algorithm> <field>" << endl;
            cout << "  Algorithms: insertionSort, mergeSort" << endl;
            cout << "  Fields: population, city, country, latitude" << endl;
            cout << "  Or type 'quit' to exit." << endl << endl;
            continue;
        }

        // Validate algorithm
        if (algorithm != "insertionSort" && algorithm != "mergeSort")
        {
            cout << "Unknown algorithm: " << algorithm << endl;
            cout << "Valid algorithms: insertionSort, mergeSort" << endl << endl;
            continue;
        }

        // Validate field
        if (field != "population" && field != "city" &&
            field != "country" && field != "latitude")
        {
            cout << "Unknown field: " << field << endl;
            cout << "Valid fields: population, city, country, latitude" << endl << endl;
            continue;
        }

        // Run the requested sort command
        handleSortCommand(algorithm, field, cities);

        cout << endl;
    }
}