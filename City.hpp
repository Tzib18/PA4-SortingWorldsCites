#include "Sorting.hpp"

class CITY{
    private:
    string city;
    double lat;
    double lng;
    string country;
    int population;

    public:
    // Default constructor
    CITY() : city(""), lat(0.0), lng(0.0), country(""), population(0) {}
    
    // Constructor
    CITY(string city, double lat, double lng, string country, int population){
        this->city = city;
        this->lat = lat;
        this->lng = lng;
        this->country = country;
        this->population = population;
    }
    // deconstructor 
    ~CITY(){}

    // Getters
    string getCity() const { return city; }
    double getLat() const { return lat; }
    double getLng() const { return lng; }
    string getCountry() const { return country; }
    int getPopulation() const { return population; }

    // setters
    void setCity(string city) { this->city = city; }
    void setLat(double lat) { this->lat = lat; }
    void setLng(double lng) { this->lng = lng; }
    void setCountry(string country) { this->country = country; }
    void setPopulation(int population) { this->population = population; }

};

vector<CITY> parseFile(const string &filename); 

void handleSortCommand(const string& algorithmName,
                       const string& fieldName,
                       const vector<CITY>& masterData); 

void run_app(); 