#!/bin/bash
sqlite3 ExerBase.db < createExerBase.sql

#echo '.import Quest.txt Quest' | sqlite3 ExerBase.db
echo '.import Answer.txt Answer' | sqlite3 ExerBase.db

echo '.import Kateg.txt Kateg' | sqlite3 ExerBase.db
echo 'INSERT INTO Kateg VALUES (11,"ΕΡΩΤΗΜΑΤΟΛΟΓΙΟ 1Α",35,0);' | sqlite3 ExerBase.db
echo 'INSERT INTO Kateg VALUES (12,"ΕΡΩΤΗΜΑΤΟΛΟΓΙΟ 2Α",15,0);' | sqlite3 ExerBase.db
#echo '.import Numbs.txt Numbs' | sqlite3 ExerBase.db

# import Special Category Questions
echo '.import updateTestDrive-A-1209/Quest.txt Quest' | sqlite3 ExerBase.db
# update Special Category ids to 1x
echo 'update Quest SET QKateg=11 WHERE QKateg=1;' | sqlite3 ExerBase.db
echo 'update Quest SET QKateg=12 WHERE QKateg=2;' | sqlite3 ExerBase.db
echo 'update Quest SET qlang=1;' | sqlite3 ExerBase.db
echo '.import Quest.txt Quest' | sqlite3 ExerBase.db

# ALTER TABLE to ADD COLUMN APicture
echo 'ALTER TABLE Answer ADD COLUMN APicture TEXT;' | sqlite3 ExerBase.db
echo 'UPDATE Answer SET APicture=0;' | sqlite3 ExerBase.db
echo '.import updateTestDrive-A-1209/Answer.txt Answer' | sqlite3 ExerBase.db

echo '.import updateTestDrive-A-1209/Numbs.txt Numbs' | sqlite3 ExerBase.db
# update Special Category ids to 1x and delete other categ > 2
echo 'DELETE FROM Numbs WHERE KCod>2;' | sqlite3 ExerBase.db
echo 'update Numbs SET KCod=11 WHERE KCod=1;' | sqlite3 ExerBase.db
echo 'update Numbs SET KCod=12 WHERE KCod=2;' | sqlite3 ExerBase.db
echo '.import Numbs.txt Numbs' | sqlite3 ExerBase.db

echo 'VACUUM;' | sqlite3 ExerBase.db

echo '.dump' | sqlite3 ExerBase.db | gzip -c > ExerBase.dump.gz
