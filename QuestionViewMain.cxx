//      main.cxx
//      
//      Copyright 2010 Argyriadis Christos <krizz@Freak>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <iostream>


#include <fltk/run.h>
#include <fltk/visual.h>
#include "QuestionViewUI.h"
using namespace std;

int main(int argc, char** argv)
{
	// Initial global objects.
	fltk::args(argc, argv);

	
	Answer a[3] = { Answer("Κανονική θερμοκρασία.", 0,"snd.wav", -1),
					Answer("Θα προχωρήσετε μέχρι το ύψος της πινακίδας STOP, θα σταματήσετε εκεί και θα παραχωρήσετε προτεραιότητα στα οχήματα που βλέπετε ότι κινούνται σε κάθετη με σας πορεία. Όταν δεν βλέπετε να έρχονται άλλα οχήματα, θα διασχίσετε τη διασταύρωση.", 1,"snd.wav", -1),
					Answer("O οδηγός του φορτηγού να φορτώσει το όχημα μέχρι το ανώτερο προβλεπόμενο ύψος και βάρος, αλλά επί πλέον να ελέγχει (από τις σχετικές πινακίδες) το ύψος κάθε γέφυρας (αν διέρχεται από κάτω) και το ανώτερο επιτρεπόμενο βάρος (αν τη διασχίζει).", 0,"snd.wav", -1)
				};
				
	Answer b[3] = { Answer("- Answer 1", 0,"snd.wav", -1),
					Answer("- Answer 2", 1,"snd.wav", -1),
					Answer("- Answer 3", 0,"snd.wav", -1)
				};
								
	//Question *q = new Question("What's up?", a, 3);
	Question q[5] = { Question("Όταν σε ένα αυτοκίνητο υπάρχει έλλειψη ψυκτικού υγρού στο ψυγείο ή είναι κομμένος ή χαλαρωμένος ο ιμάντας του ανεμιστήρα ή υπάρχει έλλειψη λαδιού στον κινητήρα, ποια είναι η πιθανή ένδειξη που θα παρατηρήσετε στα όργανα του αυτοκινήτου:","img.jpg","snd.wav","ΣΥΝΤΗΡΗΣΗ 67",a, 3),
					  Question("What's down","img.jpg","snd.wav","Section 01",b, 3),
					  Question("What's left","img.jpg","snd.wav","Section 01",a, 3),
					  Question("What's right","img.jpg","snd.wav","Section 01",a, 3),
					  Question("What's that","img.jpg","snd.wav","Section 01",a, 3)
				  };
	Test* t = new Test(q,3);			  
	QuestionViewUI qvui;
	qvui.setTest(t);
	qvui.show();
    
    return fltk::run();
}
