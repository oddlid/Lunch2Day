// Trying out the results of menu.proto
// Odd, 2013-07-26 11:31:26

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "json/json.h"
#include "menu.pb.h"

using namespace std;

//#define K_NAME          "name"
//#define K_DISHES        "dishes"
//#define K_RESTAURANTS   "restaurants"
//#define K_SITES         "sites"
//#define K_CITIES        "cities"
//#define K_COUNTRIES     "countries"
#define K_DISH          "dish"
#define K_DESC          "desc"
#define K_PRICE         "price"
#define K_ENC           "_encoding"
#define V_ENC           "UTF-8"
#define K_VERSION       "_version"
#define V_VERSION       "2013-07-30 10:19:57"


void build_menu(Menu::Menu* menu) {
    array<string, 4> countries = { "Sweden", "Norway", "Denmark", "Finland" };
    array<string, 2> cities = { "City1", "City2" };
    array<string, 2> sites = { "Site 1", "Site 2" };
    array<string, 2> restaurants = { "Restaurant 1", "Restaurant 2" };
    array<string, 2> dishes = { "Dish 1", "Dish 2" };
    array<string, 2> descs = { "with french fries 1", "with klyftpotatis 2" };
    array<int, 2> prices = { 75, 85 };

    for (int cn = 0; cn < countries.size(); cn++) {
	Menu::Country* country = menu->add_countries();
	country->set_name(countries[cn]);
	for (int ci = 0; ci < cities.size(); ci++) {
	    Menu::City* city = country->add_cities();
	    city->set_name(cities[ci]);
	    for (int si = 0; si < sites.size(); si++) {
		Menu::Site* site = city->add_sites();
		site->set_name(sites[si]);
		for (int re = 0; re < restaurants.size(); re++) {
		    Menu::Restaurant* restaurant = site->add_restaurants();
		    restaurant->set_name(restaurants[re]);
		    for (int di = 0; di < dishes.size(); di++) {
			Menu::Dish* dish = restaurant->add_dishes();
			dish->set_name(dishes[di]);
			dish->set_desc(descs[di]);
			dish->set_price(prices[di]);
		    }
		}
	    }
	}
    }
}

void add_dish(
    Menu::Menu*   menu,
    const string& country,
    const string& city,
    const string& site,
    const string& restaurant,
    const string& dish,
    const string& desc,
    int price) {
    //...
}

//Json::Value to_json(Menu::Menu* menu) {
//    Json::Value jroot;
//    jroot[K_ENC] = V_ENC;
//    jroot[K_VERSION] = V_VERSION;
//    Json::Value countries(Json::arrayValue);
//    Json::Value cities(Json::arrayValue);
//    Json::Value sites(Json::arrayValue);
//    Json::Value restaurants(Json::arrayValue);
//    Json::Value dishes(Json::arrayValue);
//
//    for (int cn = 0; cn < menu->countries_size(); cn++) {
//	const Menu::Country& country = menu->countries(cn);
//	Json::Value jcountry;
//	jcountry[K_NAME] = country.name();
//	for (int ci = 0; ci < country.cities_size(); ci++) {
//	    const Menu::City& city = country.cities(ci);
//	    Json::Value jcity;
//	    jcity[K_NAME] = city.name();
//	    for (int si = 0; si < city.sites_size(); si++) {
//		const Menu::Site& site = city.sites(si);
//		Json::Value jsite;
//		jsite[K_NAME] = site.name();
//		for (int re = 0; re < site.restaurants_size(); re++) {
//		    const Menu::Restaurant& restaurant = site.restaurants(re);
//		    Json::Value jrestaurant;
//		    jrestaurant[K_NAME] = restaurant.name();
//		    for (int di = 0; di < restaurant.dishes_size(); di++) {
//			const Menu::Dish& dish = restaurant.dishes(di);
//			Json::Value jdish;
//			jdish[K_DISH] = dish.name();
//			jdish[K_DESC] = dish.desc();
//			jdish[K_PRICE] = dish.price();
//			dishes.append(jdish);
//		    }
//		    jrestaurant[K_DISHES] = dishes;
//		    restaurants.append(jrestaurant);
//		    dishes.clear();
//		}
//		jsite[K_RESTAURANTS] = restaurants;
//		sites.append(jsite);
//		restaurants.clear();
//	    }
//	    jcity[K_SITES] = sites;
//	    cities.append(jcity);
//	    sites.clear();
//	}
//	jcountry[K_CITIES] = cities;
//	countries.append(jcountry);
//	cities.clear();
//    }
//
//    jroot[K_COUNTRIES] = countries;
//
//    return jroot;
//}

// Another attempt
Json::Value as_json(Menu::Menu* menu) {
    Json::Value jroot;
    jroot[K_ENC] = V_ENC;
    jroot[K_VERSION] = V_VERSION;
    for (int cn = 0; cn < menu->countries_size(); cn++) {
	const Menu::Country& country = menu->countries(cn);
	jroot[country.name()] = Json::arrayValue;
	for (int ci = 0; ci < country.cities_size(); ci++) {
	    const Menu::City& city = country.cities(ci);
	    Json::Value jcity;
	    jcity[city.name()] = Json::arrayValue;
	    for (int si = 0; si < city.sites_size(); si++) {
		const Menu::Site& site = city.sites(si);
		Json::Value jsite;
		jsite[site.name()] = Json::arrayValue;
		for (int re = 0; re < site.restaurants_size(); re++) {
		    const Menu::Restaurant& restaurant = site.restaurants(re);
		    Json::Value jres;
		    jres[restaurant.name()] = Json::arrayValue;
		    for (int di = 0; di < restaurant.dishes_size(); di++) {
			const Menu::Dish& dish = restaurant.dishes(di);
			Json::Value jdish;
			jdish[K_DISH] = dish.name();
			jdish[K_DESC] = dish.desc();
			jdish[K_PRICE] = dish.price();
			jres[restaurant.name()].append(jdish);
		    }
		    jsite[site.name()].append(jres);
		}
		jcity[city.name()].append(jsite);
	    }
	    jroot[country.name()].append(jcity);
	}
    }
    return jroot;
}

int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    Menu::Menu menu;
    build_menu(&menu);
    string menufile("/tmp/menu.dat");
    fstream fh(menufile.c_str(), ios::out | ios::trunc | ios::binary);
    if (!fh) {
	cerr << "Unable to write to " << menufile << endl;
	return -1;
    }
    else if (!menu.SerializeToOstream(&fh)) {
	cerr << "Failed to write menu" << endl;
    }

    Json::Value jmenu = as_json(&menu);
    cout << jmenu.toStyledString() << endl;

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
