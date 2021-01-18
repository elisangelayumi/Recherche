#ifndef RESULTAT
#define RESULTAT

#include <string>

class Resultat {
private:
  static unsigned int compteur_copie;
  static unsigned int compteur_comparaison;
  static unsigned int compteur_mise_a_zero;
  
  std::string m_url;

public:
  Resultat();	 // Constructeur par defaut (genere un url au hasard)
  Resultat(const std::string& url); // Constructeur ou le url est specifie
  Resultat(const Resultat& un_resultat); // Constructeur de copie

  void print() const;		// Pour deboguer

  static unsigned int miseAZeroDesCompteurs();
  static unsigned int compteurComparaison();
  static unsigned int compteurCopie();
  
  bool operator<(const Resultat& un_resultat) const;
  bool operator<=(const Resultat& un_resultat) const;
  bool operator==(const Resultat& un_resultat) const;
};

#endif
