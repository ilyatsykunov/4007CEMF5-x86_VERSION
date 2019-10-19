--
-- File generated with SQLiteStudio v3.2.1 on Sat Feb 16 12:19:03 2019
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: SHOP
CREATE TABLE SHOP(
itemID INT PRIMARY KEY NOT NULL,
itemName VARCHAR NOT NULL,
itemEffect VARCHAR NOT NULL,
itemPrice INT
);
INSERT INTO SHOP (itemID, itemName, itemEffect, itemPrice) VALUES (1, 'Small Health Potion', '+25% HP', 50);
INSERT INTO SHOP (itemID, itemName, itemEffect, itemPrice) VALUES (2, 'Medium Health Potion', '+50% HP', 80);
INSERT INTO SHOP (itemID, itemName, itemEffect, itemPrice) VALUES (3, 'Large Health Potion', '+75% HP', 100);
INSERT INTO SHOP (itemID, itemName, itemEffect, itemPrice) VALUES (4, 'Attack Bonus', '+50% Attack', 150);
INSERT INTO SHOP (itemID, itemName, itemEffect, itemPrice) VALUES (5, 'Defense Bonus', '+50% Defense', 150);
INSERT INTO SHOP (itemID, itemName, itemEffect, itemPrice) VALUES (6, 'Special Attack Bonus', '+50% SP. Attack', 150);
INSERT INTO SHOP (itemID, itemName, itemEffect, itemPrice) VALUES (7, 'Special Defense Bonus', '+50% SP. Defense', 150);
INSERT INTO SHOP (itemID, itemName, itemEffect, itemPrice) VALUES (8, 'Speed Bonus', '+50% Speed', 150);

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
