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
           std::cout << "Deleting dish \"" << name << " " << desc << "\"" << std::endl;
        }
};

class Restaurant 
{
    public:
        std::string name;
        std::vector<std::shared_ptr<Dish>> dishes;

        Restaurant(const std::string& n) 
           : name(n) {
        }

        ~Restaurant() {
           std::cout << "Deleting restaurant \"" << name << "\"" << std::endl;
        }

        void dump() {
           std::cout << this->name << std::endl;
           for (auto ptr : dishes) {
              std::cout << "\t" << ptr->name << " " << ptr->desc << " - " << ptr->price << ";-" << std::endl;
           }
           std::cout << std::endl;
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
   //std::shared_ptr<Dish> d(new Dish("Meatballs", "with mashed potatoes", 85));
   //std::cout << "Dish: " << d->name << " " << d->desc << " - " << d->price << ";-" << std::endl;
   
   std::shared_ptr<Restaurant> r(new Restaurant("Semcon"));
   std::shared_ptr<Dish> d1(new Dish("Burger", "with fries", 85));
   std::shared_ptr<Dish> d2(new Dish("Meatballs", "with mashed potatoes", 75));
   std::shared_ptr<Dish> d3(new Dish("Lingon", "med hestflesk", 75));

   r->dishes.push_back(d1);
   r->dishes.push_back(d2);
   r->dishes.push_back(d3);

   r->dump();

   return 0;
}
