/*
** datastore.cpp
** Defines the classes need for storing all lunch related data.
** Odd Eivind Ebbesen, 2013-06-23
*/

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <unordered_map>

//const std::string kv_as_json

typedef struct JSONEntry je {
   std::string key;
   std::string val;
};


class Dish 
{
    public:
        std::string name;
        std::string desc;
        int price;

        Dish(const std::string& n, const std::string& d = nullptr, const int p = 0)
          : name(n), desc(d), price(p) {
        }

        ~Dish() {
           std::cout << "Deleting dish: \"" << name << " " << desc << "\"" << std::endl;
        }

        const std::string as_json() {
           return std::string (
                 "{ \"dish\": \"" + 
                 this->name + 
                 "\", \"desc\": \"" + 
                 this->desc + 
                 "\", \"price\": \"" + 
                 std::to_string(this->price) + 
                 "\" }"
               );
        }
};

class Restaurant 
{
    public:
        std::string name;
        //std::vector<std::shared_ptr<Dish>> dishes;
        std::unordered_map<std::string, std::shared_ptr<Dish>> dishes;

        Restaurant(const std::string& n) 
           : name(n) {
        }

        ~Restaurant() {
           std::cout << "Deleting restaurant \"" << name << "\"" << std::endl;
        }

        /*
        void dump() {
           std::cout << this->name << std::endl;
           for (auto ptr : dishes) {
              std::cout << "\t" << ptr->name << " " << ptr->desc << " - " << ptr->price << ";-" << std::endl;
           }
           std::cout << std::endl;
        }
        */

        void dump() {
           using namespace std;
           cout << this->name << endl;
           for (auto& x : dishes) {
              cout << x.first << " : " << x.second->as_json() << endl;
           }
        }
};

class Site
{
    public:
        std::string name;
        std::vector<std::shared_ptr<Restaurant>> restaurants;
        //std::weak_ptr<City> parent;
        
        Site(const std::string& n) 
           : name(n) {
        }
};

class City
{
    public:
        std::string name;
        std::vector<std::shared_ptr<Site>> sites;
        //std::weak_ptr<Country> parent;
        
        City(const std::string& n) 
           : name(n) {
        }
};

class Country
{
    public:
        std::string name;
        std::vector<std::shared_ptr<City>> cities;

        Country(const std::string& n) 
           : name(n) {
        }
};

class GlobalMenu
{
    public:
       std::string name;
        std::vector<std::shared_ptr<Country>> countries;

        GlobalMenu(const std::string& n = "DEF::GlobalMenu") 
           : name(n) {
        }
};

int main() {
   
   std::shared_ptr<Restaurant> r(new Restaurant("Semcon"));
   std::shared_ptr<Dish> d1(new Dish("Burger", "with fries", 85));
   std::shared_ptr<Dish> d2(new Dish("Meatballs", "with mashed potatoes", 75));
   std::shared_ptr<Dish> d3(new Dish("Lingon", "med hestflesk", 75));

   r->dishes.emplace(d1->name, d1);
   r->dishes.emplace(d2->name, d2);
   r->dishes.emplace(d3->name, d3);

   r->dump();

   return 0;
}
