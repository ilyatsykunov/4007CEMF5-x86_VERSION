--
-- File generated with SQLiteStudio v3.1.0 on Tue Feb 26 14:34:26 2019
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: CreepsMain
CREATE TABLE CreepsMain (
    Creep_ID   INTEGER      PRIMARY KEY
                            NOT NULL,
    Creep_Name VARCHAR (32) NOT NULL,
    Creep_Class VARCHAR (32) NOT NULL,
    Creep_Attack_Physical INTEGER (32) NULL,
    Creep_Attack_Magical INTEGER (32) NULL,
    Creep_Defence_Physical INTEGER (32) NULL,
    Creep_Defence_Magical INTEGER (32) NULL, 
    Creep_Speed INTEGER (32) NULL
);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (1, 'vrvcrg fmltghhvy', 'Knight', 10, 21, 12, 32, 3);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (2, 'hljnbve', 'Priest', 30, 23, 2, 14, 4);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (3, 'jox dycgjkgtze', 'Mage', 35, 38, 11, 19, 10);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (4, 'qxbbj', 'Priest', 35, 48, 42, 6, 0);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (5, 'rwwbo', 'Assassin', 11, 6, 30, 28, 8);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (6, 'mnxu', 'Healer', 13, 4, 3, 12, 6);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (7, 'xeepkvyixtlxqvgxg', 'Assassin', 18, 28, 20, 18, 5);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (8, 'a gwxkd', 'Mage', 8, 28, 12, 11, 8);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (9, 't	mduvlsrttkdvsi	', 'Healer', 9, 22, 14, 10, 8);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (10, 'edlydnzopbuhy', 'Priest', 9, 16, 19, 50, 3);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (11, 'rf
 ', 'Mage', 0, 21, 31, 33, 9);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (12, ' dgqtjiyg cv	c in', 'Knight', 47, 7, 5, 45, 2);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (13, 'bctybnzvhigk
 	', 'Assassin', 2, 40, 20, 20, 9);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (14, 'tfzbr ', 'Knight', 28, 8, 10, 32, 5);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (15, 'apyxkim zn', 'Mage', 8, 34, 19, 37, 10);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (16, 'ukdchttank', 'Healer', 46, 7, 3, 25, 5);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (17, 'goaczpusnzqbowr', 'Priest', 23, 2, 25, 22, 5);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (18, '	bq  zo	', 'Knight', 29, 23, 26, 33, 9);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (19, 'dbs
jikyzauv', 'Mage', 0, 2, 0, 32, 6);
INSERT INTO CreepsMain (Creep_ID, Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed) VALUES (20, 'rrptodm neyooiamnwkc', 'Assassin', 12, 48, 24, 18, 3);

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
