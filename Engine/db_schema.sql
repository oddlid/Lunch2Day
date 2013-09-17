/*
 * db_schema.sql
 * Database layout in SQlite3 for Lunch2Day
 * 
 * Odd Eivind Ebbesen <odd@oddware.net>, 2013-09-17 18:31:47
 */

PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS "parsers";
DROP TABLE IF EXISTS "dishes";
DROP TABLE IF EXISTS "restaurants";
DROP TABLE IF EXISTS "sites";
DROP TABLE IF EXISTS "cities";
DROP TABLE IF EXISTS "countries";

CREATE TABLE countries(
   id               INTEGER PRIMARY KEY,
   name             VARCHAR NOT NULL
);

CREATE TABLE cities(
   id               INTEGER PRIMARY KEY,
   country_id       INTEGER NOT NULL,
   name             VARCHAR NOT NULL,
   FOREIGN KEY(country_id) REFERENCES countries(id)
);

CREATE TABLE sites(
   id               INTEGER PRIMARY KEY,
   city_id          INTEGER NOT NULL,
   name             VARCHAR NOT NULL,
   FOREIGN KEY(city_id) REFERENCES cities(id)
);

/* url should be updated every time a result comes in, 
   if it has changed since last result. It's the parser
   that has the correct url, but it's saved here to be able 
   to use it in HTML output or whatever */
CREATE TABLE restaurants(
   id               INTEGER PRIMARY KEY,
   site_id          INTEGER NOT NULL,
   name             VARCHAR NOT NULL,
   url              VARCHAR,
   FOREIGN KEY(site_id) REFERENCES sites(id)
);

/* If date is null, then today is assumed. 
   If set, one can fill in for days ahead, and select for only 
   the day in question */
CREATE TABLE dishes(
   id               INTEGER PRIMARY KEY,
   restaurant_id    INTEGER NOT NULL,
   name             VARCHAR NOT NULL,
   desc             VARCHAR,
   price            INTEGER,
   date             INTEGER,
   FOREIGN KEY(restaurant_id) REFERENCES restaurants(id)
);

/* 
Not related to the menu structure, but for keeping track of parsers, 
see chatlog between me and Jonas from 2013-09-17.

The idea is that when adding a new parser, the parser must register with 
the engine, with a checksum of itself (the executable) and the restaurant
it will parse for. 
If the parser changes, it will get a new id, as the checksum will change, 
and so one will never have conflict with naming and such.

*/

CREATE TABLE parsers(
   id               INTEGER PRIMARY KEY,
   md5sum           VARCHAR NOT NULL,
   restaurant_id    INTEGER NOT NULL,
   reg_date         INTEGER NOT NULL,
   last_seen        INTEGER NOT NULL,
   comment          TEXT,
   FOREIGN KEY(restaurant_id) REFERENCES restaurants(id)
);


/*** Triggers and views ***/
/* ... to be done, later... */
