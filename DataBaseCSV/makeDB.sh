#!/bin/bash
sqlite3 ExerBase.db < createExerBase.sql
echo '.import Quest.txt Quest' | sqlite3 ExerBase.db
echo '.import Answer.txt Answer' | sqlite3 ExerBase.db
echo '.import Kateg.txt Kateg' | sqlite3 ExerBase.db
echo '.import Numbs.txt Numbs' | sqlite3 ExerBase.db

echo '.dump' | sqlite3 ExerBase.db | gzip -c > ExerBase.dump.gz
