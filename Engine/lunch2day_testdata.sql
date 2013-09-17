/*
 * some test data for the Lunch2Day DB
 * Odd Eivind Ebbesen <odd@oddware.net>, 2013-09-17 22:30:11
 */

INSERT INTO COUNTRIES VALUES(1, 'Sweden');
INSERT INTO CITIES VALUES(1, 1, 'Gothenburg');
INSERT INTO SITES VALUES(1, 1, 'Lindholmen');
INSERT INTO RESTAURANTS VALUES(1, 1, 'Bistrot', 'http://www.lindholmen.se/sv/restaurang/bistrot');
INSERT INTO RESTAURANTS VALUES(2, 1, 'Semcon', 'http://www.lindholmen.se/sv/restaurang/lindholmens-matsal-semcon');

INSERT INTO DISHES VALUES(1, 1, 'Bistrots decembersallad', 'med kalkon, granatäpple, apelsin, och matvete och apelsindressing', 85, null);
INSERT INTO DISHES VALUES(2, 1, 'Spagetti', 'med fläskfilé och lufttorkad skinka i en gräddig tomatsås', 85, null);

INSERT INTO DISHES VALUES(3, 2, 'Gris', 'med mumsig sås', 75, null);
INSERT INTO DISHES VALUES(4, 2, 'Äckel', 'med lök', 75, null);
