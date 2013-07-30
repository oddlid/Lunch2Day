// Testing the same principles as in pbtest.cc, but with
// JSON only, no backing via ProtocolBuffers.
// Odd, 2013-07-30 11:33:50

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "json/json.h"
#include "json/value.h"
#include "json/reader.h"
#include "json/writer.h"

#define K_VERSION       "_version"
#define V_VERSION       "2013-07-30 11:35:31"
#define K_ENC           "_encoding"
#define V_ENC           "UTF-8"
#define K_DISH          "dish"
#define K_DESC          "desc"
#define K_PRICE         "price"

using namespace std;

Json::Value build_menu() {
    array<string, 4> countries   = { "Sweden", "Norway", "Denmark", "Finland" };
    array<string, 2> cities      = { "City1", "City2" };
    array<string, 2> sites       = { "Site 1", "Site 2" };
    array<string, 2> restaurants = { "Restaurant 1", "Restaurant 2" };
    array<string, 2> dishes      = { "Dish 1", "Dish 2" };
    array<string, 2> descs       = { "with french fries 1", "with klyftpotatis 2" };
    array<int,    2> prices      = { 75, 85 };

    Json::Value jroot;
    jroot[K_ENC]     = V_ENC;
    jroot[K_VERSION] = V_VERSION;

    for (int cn = 0; cn < countries.size(); cn++) {
	jroot[countries[cn]] = Json::arrayValue;
	for (int ci = 0; ci < cities.size(); ci++) {
	    Json::Value jcity;
	    jcity[cities[ci]] = Json::arrayValue;
	    for (int si = 0; si < sites.size(); si++) {
		Json::Value jsite;
		jsite[sites[si]] = Json::arrayValue;
		for (int re = 0; re < restaurants.size(); re++) {
		    Json::Value jres;
		    jres[restaurants[re]] = Json::arrayValue;
		    for (int di = 0; di < dishes.size(); di++) {
			Json::Value jdish;
			jdish[K_DISH] = dishes[di];
			jdish[K_DESC] = descs[di];
			jdish[K_PRICE] = prices[di];
			jres[restaurants[re]].append(jdish);
		    }
		    jsite[sites[si]].append(jres);
		}
		jcity[cities[ci]].append(jsite);
	    }
	    jroot[countries[cn]].append(jcity);
	}
    }
    return jroot;
}

int main(int argc, char* argv[]) {

    Json::Value menu = build_menu();
    cout << menu.toStyledString() << endl;

    return 0;
}
