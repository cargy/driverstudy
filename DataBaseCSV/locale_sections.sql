CREATE TABLE Section(	
	id INTERGER PRIMARY KEY,
	categoryID INTEGER);

CREATE UNIQUE INDEX section_unique ON Section ( id, categoryID );

CREATE TABLE SectionLocale(
	sectionID INTEGER,
	localeID INTEGER,
	name TEXT,
	description TEXT);

CREATE UNIQUE INDEX section_locale_unique ON SectionLocale ( sectionID, localeID ); 

CREATE TABLE Category(
	id INTEGER PRIMARY KEY,
	questionnaireNo INTEGER,
	testQuestionsAmount INTEGER,
	time INTEGER,
	image TEXT);

CREATE TABLE CategoryLocale(
	categoryID INTEGER,
	localeID INTEGER,
	name TEXT,
	questionnaireName TEXT);

CREATE UNIQUE INDEX category_locale_unique ON CategoryLocale ( categoryID, localeID ); 

CREATE TABLE Locale(
	id INTEGER PRIMARY KEY,
	code TEXT,
	shortCode TEST);

CREATE TABLE LocaleLocale(
	localeNameID INTEGER,
	localeID INTEGER,
	name TEXT);

CREATE UNIQUE INDEX locale_locale_unique ON LocaleLocale ( localeNameID, localeID );

INSERT INTO Category Values ( 1, 1, 30, 35, '');
INSERT INTO Category Values ( 2, 2, 10, 15, '');
INSERT INTO Category Values ( 3, 3, 10, 15, '');
INSERT INTO Category Values ( 4, 4, 10, 15, '');

INSERT INTO CategoryLocale VALUES ( 1, 1, 'Αυτοκίνητο', '');
INSERT INTO CategoryLocale VALUES ( 2, 1, 'Μοτοσυκλέτα', '');
INSERT INTO CategoryLocale VALUES ( 3, 1, 'Φορτηγό', '');
INSERT INTO CategoryLocale VALUES ( 4, 1, 'Λεωφορείο', '');
INSERT INTO CategoryLocale VALUES ( 1, 2, 'Car', '');
INSERT INTO CategoryLocale VALUES ( 2, 2, 'Motorcycle', '');
INSERT INTO CategoryLocale VALUES ( 3, 2, 'Truck', '');
INSERT INTO CategoryLocale VALUES ( 4, 2, 'Bus', '');
INSERT INTO CategoryLocale VALUES ( 1, 3, 'машина', '');
INSERT INTO CategoryLocale VALUES ( 2, 3, 'мотоцикл', '');
INSERT INTO CategoryLocale VALUES ( 3, 3, 'грузовик', '');
INSERT INTO CategoryLocale VALUES ( 4, 3, 'автобус', '');
INSERT INTO CategoryLocale VALUES ( 1, 4, 'kerr', '');
INSERT INTO CategoryLocale VALUES ( 2, 4, 'motoçikletë', '');
INSERT INTO CategoryLocale VALUES ( 3, 4, 'kamion', '');
INSERT INTO CategoryLocale VALUES ( 4, 4, 'autobus', '');

INSERT INTO Locale Values ( 1, 'el-GR', 'el'); 
INSERT INTO Locale Values ( 2, 'en-US', 'en' ); 
INSERT INTO Locale Values ( 3, 'ru-RU', 'ru' ); 
INSERT INTO Locale Values ( 4, 'al-AL', 'al' ); 

INSERT INTO LocaleLocale Values ( 1, 1, 'Ελληνικά' ); 
INSERT INTO LocaleLocale Values ( 2, 1, 'Greek' );
INSERT INTO LocaleLocale Values ( 3, 1, 'Greek' );
INSERT INTO LocaleLocale Values ( 4, 1, 'Greek' );
INSERT INTO LocaleLocale Values ( 1, 2, 'Αγγλικά' ); 
INSERT INTO LocaleLocale Values ( 2, 2, 'English' ); 
INSERT INTO LocaleLocale Values ( 3, 2, 'English' ); 
INSERT INTO LocaleLocale Values ( 4, 2, 'English' ); 
INSERT INTO LocaleLocale Values ( 1, 3, 'Ρώσικα' ); 
INSERT INTO LocaleLocale Values ( 2, 3, 'Russian' ); 
INSERT INTO LocaleLocale Values ( 3, 3, 'Russian' ); 
INSERT INTO LocaleLocale Values ( 4, 3, 'Russian' ); 
INSERT INTO LocaleLocale Values ( 1, 4, 'Αλβανικά' ); 
INSERT INTO LocaleLocale Values ( 2, 4, 'Albanian' ); 
INSERT INTO LocaleLocale Values ( 3, 4, 'Albanian' );
INSERT INTO LocaleLocale Values ( 4, 4, 'Albanian' ); 

INSERT INTO Section VALUES ( 1, 1);
INSERT INTO Section VALUES ( 2, 1);
INSERT INTO Section VALUES ( 3, 1);
INSERT INTO Section VALUES ( 4, 1);
INSERT INTO Section VALUES ( 5, 1);
INSERT INTO Section VALUES ( 6, 1);
INSERT INTO Section VALUES ( 7, 1);
INSERT INTO Section VALUES ( 8, 1);
INSERT INTO Section VALUES ( 9, 1);
INSERT INTO Section VALUES ( 10, 1);
INSERT INTO Section VALUES ( 11, 1);
INSERT INTO Section VALUES ( 12, 1);
INSERT INTO Section VALUES ( 13, 1);
INSERT INTO Section VALUES ( 14, 1);
INSERT INTO Section VALUES ( 15, 1);
INSERT INTO Section VALUES ( 16, 1);
INSERT INTO Section VALUES ( 17, 1);
INSERT INTO Section VALUES ( 18, 1);
INSERT INTO Section VALUES ( 19, 1);
INSERT INTO Section VALUES ( 20, 1);
INSERT INTO Section VALUES ( 21, 1);
INSERT INTO Section VALUES ( 22, 1);
INSERT INTO Section VALUES ( 23, 1);
INSERT INTO Section VALUES ( 24, 1);
INSERT INTO Section VALUES ( 25, 1);

INSERT INTO SectionLocale VALUES ( 1, 1, 'ΟΡΓΑΝΑ', 'ΤΑ ΚΥΡΙΑ ΟΡΓΑΝΑ ΤΟΥ ΟΧΗΜΑΤΟΣ ΚΑΙ ΤΑ ΧΕΙΡΙΣΤΗΡΙΑ ΣΤΟ ΧΩΡΟ ΟΔΗΓΗΣΕΩΣ');
INSERT INTO SectionLocale VALUES ( 2, 1, 'ΟΔΗΓΟΣ', 'Η ΕΓΚΑΤΑΣΤΑΣΗ ΣΤΗ ΘΕΣΗ ΤΟΥ ΟΔΗΓΟΥ');
INSERT INTO SectionLocale VALUES ( 3, 1, 'ΣΗΜΑΝΣΗ', 'Η ΣΗΜΑΝΣΗ');
INSERT INTO SectionLocale VALUES ( 4, 1, 'ΔΙΑΣΤΑΥΡΩΣΕΙΣ', 'ΟΙ ΔΙΑΣΤΑΥΡΩΣΕΙΣ');
INSERT INTO SectionLocale VALUES ( 5, 1, 'ΤΑΧΥΤΗΤΑ', 'Η ΤΑΧΥΤΗΤΑ');
INSERT INTO SectionLocale VALUES ( 6, 1, 'ΟΔΟΣΤΡΩΜΑ', 'Η ΘΕΣΗ ΣΤΟ ΟΔΟΣΤΡΩΜΑ');
INSERT INTO SectionLocale VALUES ( 7, 1, 'ΑΠΟΣΤΑΣΕΙΣ', 'ΟΙ ΑΠΟΣΤΑΣΕΙΣ ΑΣΦΑΛΕΙΑΣ - Η ΑΠΟΣΤΑΣΗ ΣΤΑΣΕΩΣ ΚΑΙ Η ΤΑΧΥΤΗΤΑ');
INSERT INTO SectionLocale VALUES ( 8, 1, 'ΣΤΑΣΗ', 'ΣΤΑΣΗ ΚΑΙ ΣΤΑΘΜΕΥΣΗ');
INSERT INTO SectionLocale VALUES ( 9, 1, 'ΠΡΟΣΠΕΡΑΣΗ', 'ΔΙΑΣΤΑΥΡΩΝΕΣΤΕ, ΠΡΟΣΠΕΡΝΑΤΕ, ΣΑΣ ΠΡΟΣΠΕΡΝΟΥΝ');
INSERT INTO SectionLocale VALUES ( 10, 1,  'ΣΤΡΟΦΕΣ', 'ΟΙ ΣΤΡΟΦΕΣ');
INSERT INTO SectionLocale VALUES ( 11, 1,  'ΣΥΝΥΠΑΡΞΗ', 'Η ΣΥΝΥΠΑΡΞΗ ΜΕ ΤΟΥΣ ΑΛΛΟΥΣ ΧΡΗΣΤΕΣ ΤΗΣ ΟΔΟΥ');
INSERT INTO SectionLocale VALUES ( 12, 1, 'ΔΙΑΔΡΟΜΗ', 'ΑΚΟΛΟΥΘΏΝΤΑΣ ΜΙΑ ΔΙΑΔΡΟΜΗ');
INSERT INTO SectionLocale VALUES ( 13, 1, 'ΑΛΚΟΟΛ', 'ΤΟ ΑΛΚΟΟΛ ΚΑΙ ΑΛΛΕΣ ΧΗΜΙΚΕΣ ΟΥΣΙΕΣ, ΦΑΡΜΑΚΑ');
INSERT INTO SectionLocale VALUES ( 14, 1, 'ΕΙΣΟΔΟΣ', 'Η ΕΙΣΟΔΟΣ ΣΤΗΝ ΚΥΚΛΟΦΟΡΙΑ');
INSERT INTO SectionLocale VALUES ( 15, 1, 'ΑΥΤΟΚΙΝΗΤΟΔΡΟΜΟΣ', 'Ο ΑΥΤΟΚΙΝΗΤΟΔΡΟΜΟΣ');
INSERT INTO SectionLocale VALUES ( 16, 1, 'ΟΡΑΤΟΤΗΤΑ', 'Η ΟΔΗΓΗΣΗ ΜΕ ΠΕΡΙΟΡΙΜΕΝΗ ΟΡΑΤΟΤΗΤΑ');
INSERT INTO SectionLocale VALUES ( 17, 1, 'ΠΡΟΣΦΥΣΗ', 'ΟΔΗΓΩΝΤΑΣ ΜΕ ΜΕΙΩΜΕΝΗ ΠΡΟΣΦΥΣΗ');
INSERT INTO SectionLocale VALUES ( 18, 1, 'ΒΟΥΝΟ', 'ΟΔΗΓΗΣΗ ΣΕ ΒΟΥΝΟ');
INSERT INTO SectionLocale VALUES ( 19, 1, 'ΚΟΥΡΑΣΗ', 'Η ΚΟΥΡΑΣΗ ΚΑΙ Η ΕΤΟΙΜΟΤΗΤΑ');
INSERT INTO SectionLocale VALUES ( 20, 1, 'ΑΤΥΧΗΜΑ', 'Η ΣΥΜΠΕΡΙΦΟΡΑ ΣΕ ΑΤΥΧΗΜΑ');
INSERT INTO SectionLocale VALUES ( 21, 1, 'ΣΥΝΤΗΡΗΣΗ', 'ΣΥΝΤΗΡΗΣΗ ΚΑΙ ΕΠΙΣΚΕΥΗ');
INSERT INTO SectionLocale VALUES ( 22, 1, 'ΕΚΤΑΚΤΑ', 'ΟΙ ΕΚΤΑΚΤΕΣ ΚΑΤΑΣΤΑΣΕΙΣ');
INSERT INTO SectionLocale VALUES ( 23, 1, 'ΚΑΝΟΝΕΣ', 'ΟΙ ΔΙΟΙΚΗΤΙΚΟΙ ΚΑΝΟΝΕΣ');
INSERT INTO SectionLocale VALUES ( 24, 1, 'ΠΕΡΙΒΑΛΛΟΝ', 'ΠΡΟΣΤΑΣΙΑ ΠΕΡΙΒΑΛΛΟΝΤΟΣ - ΕΞΟΙΚΟΝΟΜΗΣΗ ΕΝΕΡΓΕΙΑΣ');
INSERT INTO SectionLocale VALUES ( 25, 1, 'ΟΙΚΟΛΟΓΙΑ', 'ΟΙΚΟΛΟΓΙΚΗ ΟΔΗΓΗΣΗ');

ALTER TABLE Quest ADD COLUMN sectionID INTEGER;

UPDATE Quest SET sectionID = 1 WHERE QKateg = 1 AND QBook LIKE 'ΟΡΓΑΝΑ%';
UPDATE Quest SET sectionID = 2 WHERE QKateg = 1 AND QBook LIKE 'ΟΔΗΓΟΣ%';
UPDATE Quest SET sectionID = 3 WHERE QKateg = 1 AND QBook LIKE 'ΣΗΜΑΝΣΗ%'; 
UPDATE Quest SET sectionID = 4 WHERE QKateg = 1 AND QBook LIKE 'ΔΙΑΣΤΑΥΡΩΣΕΙΣ%';
UPDATE Quest SET sectionID = 5 WHERE QKateg = 1 AND QBook LIKE 'ΤΑΧΥΤΗΤΑ%';
UPDATE Quest SET sectionID = 6 WHERE QKateg = 1 AND QBook LIKE 'ΟΔΟΣΤΡΩΜΑ%'; 
UPDATE Quest SET sectionID = 7 WHERE QKateg = 1 AND QBook LIKE 'ΑΠΟΣΤΑΣΕΙΣ%'; 
UPDATE Quest SET sectionID = 8 WHERE QKateg = 1 AND QBook LIKE 'ΣΤΑΣΗ%';
UPDATE Quest SET sectionID = 9 WHERE QKateg = 1 AND QBook LIKE 'ΠΡΟΣΠΕΡΑΣΗ%';
UPDATE Quest SET sectionID = 10 WHERE QKateg = 1 AND  QBook LIKE 'ΣΤΡΟΦΕΣ%';
UPDATE Quest SET sectionID = 11 WHERE QKateg = 1 AND  QBook LIKE 'ΣΥΝΥΠΑΡΞΗ%'; 
UPDATE Quest SET sectionID = 12 WHERE QKateg = 1 AND QBook LIKE 'ΔΙΑΔΡΟΜΗ%';
UPDATE Quest SET sectionID = 13 WHERE QKateg = 1 AND QBook LIKE 'ΑΛΚΟΟΛ%';
UPDATE Quest SET sectionID = 14 WHERE QKateg = 1 AND QBook LIKE 'ΕΙΣΟΔΟΣ%'; 
UPDATE Quest SET sectionID = 15 WHERE QKateg = 1 AND QBook LIKE 'ΑΥΤΟΚΙΝΗΤΟΔΡΟΜΟΣ%';
UPDATE Quest SET sectionID = 16 WHERE QKateg = 1 AND QBook LIKE 'ΟΡΑΤΟΤΗΤΑ%';
UPDATE Quest SET sectionID = 17 WHERE QKateg = 1 AND QBook LIKE 'ΠΡΟΣΦΥΣΗ%';
UPDATE Quest SET sectionID = 18 WHERE QKateg = 1 AND QBook LIKE 'ΒΟΥΝΟ%';
UPDATE Quest SET sectionID = 19 WHERE QKateg = 1 AND QBook LIKE 'ΚΟΥΡΑΣΗ%'; 
UPDATE Quest SET sectionID = 20 WHERE QKateg = 1 AND QBook LIKE 'ΑΤΥΧΗΜΑ%';
UPDATE Quest SET sectionID = 21 WHERE QKateg = 1 AND QBook LIKE 'ΣΥΝΤΗΡΗΣΗ%'; 
UPDATE Quest SET sectionID = 22 WHERE QKateg = 1 AND QBook LIKE 'ΕΚΤΑΚΤΑ%';
UPDATE Quest SET sectionID = 23 WHERE QKateg = 1 AND QBook LIKE 'ΚΑΝΟΝΕΣ%';
UPDATE Quest SET sectionID = 24 WHERE QKateg = 1 AND QBook LIKE 'ΠΕΡΙΒΑΛΛΟΝ%';
UPDATE Quest SET sectionID = 25 WHERE QKateg = 1 AND QBook LIKE 'ΟΙΚΟΛΟΓΙΑ%';

-- categk 2
INSERT INTO Section VALUES ( 50 , 2);


INSERT INTO SectionLocale VALUES ( 50, 1, 'Μ', 'ΕΡΩΤΗΣΕΙΣ ΓΙΑ ΤΗΝ ΕΜΠΕΔΩΣΗ ΤΗΣ ΥΛΗΣ');

UPDATE Quest SET sectionID = 50 WHERE QKateg = 2 AND QBook LIKE 'Μ %';
UPDATE Quest SET sectionID = 50 WHERE QKateg = 2 AND QBook LIKE 'M %';



-- categk 3
INSERT INTO Section VALUES ( 30, 3);
INSERT INTO Section VALUES ( 31, 3);
INSERT INTO Section VALUES ( 32, 3);
INSERT INTO Section VALUES ( 33, 3);
INSERT INTO Section VALUES ( 34, 3);
INSERT INTO Section VALUES ( 35, 3);
INSERT INTO Section VALUES ( 36, 3);
INSERT INTO Section VALUES ( 37, 3);
INSERT INTO Section VALUES ( 38, 3);

INSERT INTO SectionLocale VALUES ( 30, 1, 'ΑΛΚΟΟΛ', 'ΤΟ ΑΛΚΟΟΛ - Η ΚΟΥΡΑΣΗ - ΤΟ ΑΤΥΧΗΜΑ - ΔΙΟΙΚΗΤΙΚΟΙ ΚΑΝΟΝΕΣ');
INSERT INTO SectionLocale VALUES ( 31, 1, 'ΑΣΦΑΛΕΙΑ1', 'ΓΕΝΙΚΟΙ ΚΑΝΟΝΕΣ ΑΣΦΑΛΟΥΣ ΟΔΗΓΗΣΕΩΣ');
INSERT INTO SectionLocale VALUES ( 32, 1, 'ΑΣΦΑΛΕΙΑ2', 'ΚΑΝΟΝΕΣ ΑΣΦΑΛΟΥΣ ΟΔΗΓΗΣΕΩΣ ΦΟΡΤΗΓΩΝ' );
INSERT INTO SectionLocale VALUES ( 33, 1, 'ΔΙΑΣΤΑΣΕΙΣ', 'ΔΙΑΣΤΑΣΕΙΣ ΚΑΙ ΒΑΡΗ');
INSERT INTO SectionLocale VALUES ( 34, 1, 'ΕΞΟΠΛΙΣΜΟΣ', 'ΕΞΟΠΛΙΣΜΟΣ - ΦΟΡΤΩΣΗ');
INSERT INTO SectionLocale VALUES ( 35, 1, 'ΜΗΧΑΝΟΛΟΓΙΑ', 'ΜΗΧΑΝΟΛΟΓΙΑ ΦΟΡΤΗΓΩΝ');
INSERT INTO SectionLocale VALUES ( 36, 1, 'ΣΗΜΑΝΣΗ', 'ΣΗΜΑΝΣΗ');
INSERT INTO SectionLocale VALUES ( 37, 1, 'ΣΥΝΤΗΡΗΣΗ', 'ΕΠΙΣΚΕΥΗ ΚΑΙ ΣΥΝΤΗΡΗΣΗ');
INSERT INTO SectionLocale VALUES ( 38, 1, 'ΤΕΧΝΙΚΑ', 'ΤΕΧΝΙΚΟΙ ΚΑΝΟΝΕΣ');

UPDATE Quest SET sectionID = 30 WHERE QKateg = 3 AND QBook LIKE 'ΑΛΚΟΟΛ%' ;
UPDATE Quest SET sectionID = 31 WHERE QKateg = 3 AND QBook LIKE 'ΑΣΦΑΛΕΙΑ1%' ;
UPDATE Quest SET sectionID = 32 WHERE QKateg = 3 AND QBook LIKE 'ΑΣΦΑΛΕΙΑ2%' ;
UPDATE Quest SET sectionID = 33 WHERE QKateg = 3 AND QBook LIKE 'ΔΙΑΣΤΑΣΕΙΣ%' ;
UPDATE Quest SET sectionID = 34 WHERE QKateg = 3 AND QBook LIKE 'ΕΞΟΠΛΙΣΜΟΣ%' ;
UPDATE Quest SET sectionID = 35 WHERE QKateg = 3 AND QBook LIKE 'ΜΗΧΑΝΟΛΟΓΙΑ%' ;
UPDATE Quest SET sectionID = 36 WHERE QKateg = 3 AND QBook LIKE 'ΣΗΜΑΝΣΗ%' ;
UPDATE Quest SET sectionID = 37 WHERE QKateg = 3 AND QBook LIKE 'ΣΥΝΤΗΡΗΣΗ%' ;
UPDATE Quest SET sectionID = 38 WHERE QKateg = 3 AND QBook LIKE 'ΤΕΧΝΙΚΑ%' ;

-- categk 4
INSERT INTO Section VALUES ( 40, 4);
INSERT INTO Section VALUES ( 41, 4);
INSERT INTO Section VALUES ( 42, 4);
INSERT INTO Section VALUES ( 43, 4);
INSERT INTO Section VALUES ( 44, 4);
INSERT INTO Section VALUES ( 45, 4);
INSERT INTO Section VALUES ( 46, 4);
INSERT INTO Section VALUES ( 47, 4);
INSERT INTO Section VALUES ( 48, 4);

INSERT INTO SectionLocale VALUES ( 40, 1, 'ΔΙΑΣΤΑΣΕΙΣ', 'ΒΑΡΗ ΚΑΙ ΔΙΑΣΤΑΣΕΙΣ');
INSERT INTO SectionLocale VALUES ( 41, 1, 'ΚΑΝΟΝΕΣ', 'ΔΙΟΙΚΗΤΙΚΟΙ ΚΑΝΟΝΕΣ');
INSERT INTO SectionLocale VALUES ( 42, 1, 'ΚΥΡΩΣΕΙΣ','ΠΑΡΑΒΑΣΕΙΣ Κ.Ο.Κ. - ΚΥΡΩΣΕΙΣ');
INSERT INTO SectionLocale VALUES ( 43, 1, 'ΜΗΧΑΝΟΛΟΓΙΑ', 'ΜΗΧΑΝΟΛΟΓΙΑ ΛΕΩΦΟΡΕΙΩΝ');
INSERT INTO SectionLocale VALUES ( 44, 1, 'ΟΔΗΓΗΣΗ', 'ΟΔΗΓΗΣΗ ΚΑΙ ΚΥΚΛΟΦΟΡΙΑ');
INSERT INTO SectionLocale VALUES ( 45, 1, 'ΣΗΜΑΝΣΗ', 'ΣΗΜΑΝΣΗ ΚΑΙ ΣΗΜΑΤΟΔΟΤΗΣΗ');
INSERT INTO SectionLocale VALUES ( 46, 1, 'ΣΥΝΤΗΡΗΣΗ', 'ΣΥΝΤΗΡΗΣΗ ΚΑΙ ΕΠΙΣΚΕΥΗ');
INSERT INTO SectionLocale VALUES ( 47, 1, 'ΤΑΧΟΓΡΑΦΟΙ', 'ΤΑΧΟΓΡΑΦΟΙ ΚΑΙ ΠΕΡΙΟΡΙΣΤΕΣ ΤΑΧΥΤΗΤΑΣ');
INSERT INTO SectionLocale VALUES ( 48, 1, 'ΤΑΧΥΤΗΤΑ', 'ΟΡΙΑ ΤΑΧΥΤΗΤΑΣ');

UPDATE Quest SET sectionID = 40 WHERE QKateg = 4 AND QBook LIKE 'ΔΙΑΣΤΑΣΕΙΣ%';
UPDATE Quest SET sectionID = 41 WHERE QKateg = 4 AND QBook LIKE 'ΚΑΝΟΝΕΣ%' ;
UPDATE Quest SET sectionID = 42 WHERE QKateg = 4 AND QBook LIKE 'ΚΥΡΩΣΕΙΣ%' ;
UPDATE Quest SET sectionID = 43 WHERE QKateg = 4 AND QBook LIKE 'ΜΗΧΑΝΟΛΟΓΙΑ%' ;
UPDATE Quest SET sectionID = 44 WHERE QKateg = 4 AND QBook LIKE 'ΟΔΗΓΗΣΗ%' ;
UPDATE Quest SET sectionID = 45 WHERE QKateg = 4 AND QBook LIKE 'ΣΗΜΑΝΣΗ%' ;
UPDATE Quest SET sectionID = 46 WHERE QKateg = 4 AND QBook LIKE 'ΣΥΝΤΗΡΗΣΗ%' ;
UPDATE Quest SET sectionID = 47 WHERE QKateg = 4 AND QBook LIKE 'ΤΑΧΟΓΡΑΦΟΙ%' ;
UPDATE Quest SET sectionID = 48 WHERE QKateg = 4 AND QBook LIKE 'ΤΑΧΥΤΗΤΑ%' ;
