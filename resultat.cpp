#include "resultat.hpp"

#include <algorithm>
#include <iostream>
#include <stdlib.h>

// Initialisation des membres statiques
unsigned int Resultat::compteur_copie = 0;
unsigned int Resultat::compteur_comparaison = 0;
unsigned int Resultat::compteur_mise_a_zero = 0;
  
// Constructeur par defaut (genere un url au hasard)
Resultat::Resultat() {
  const unsigned int longueur = 5 + rand() % 40; // Genere un entier dans [5, 45)
  const std::string prefix = "http://";
  const std::string suffix = ".com";
  
  m_url.resize(longueur + prefix.size() + suffix.size());
  for (unsigned int i = 0; i < longueur; i++)
    m_url[prefix.size() + i] = 'a' + rand() % 26;
  std::copy(prefix.begin(), prefix.end(), m_url.begin()); // Copie le prefix
  std::copy(suffix.begin(), suffix.end(), m_url.begin() + prefix.size() + longueur); // Copie le suffix
}

// Constructeur ou le url est specifie
Resultat::Resultat(const std::string& url)
  : m_url(url)
{
}

// Constructeur de copie
Resultat::Resultat(const Resultat& un_resultat)
  : m_url(un_resultat.m_url)
{
  compteur_copie++;
}

void Resultat::print() const {
  std::cout << m_url << std::endl;
}

unsigned int Resultat::miseAZeroDesCompteurs() {
  compteur_copie = 0;
  compteur_comparaison = 0;
  return ++compteur_mise_a_zero;
}

unsigned int Resultat::compteurComparaison() {
  return compteur_comparaison;
}

unsigned int Resultat::compteurCopie() {
  return compteur_copie;
}

bool Resultat::operator<(const Resultat& un_resultat) const {
  // Normalement, c'est la pertinence du URL plutot que son ordre alphabetique qui serait testee.
  compteur_comparaison++;
  return m_url < un_resultat.m_url; 
}

bool Resultat::operator<=(const Resultat& un_resultat) const {
  // Normallement, c'est la pertinence du URL plutot que son ordre alphabetique qui serait testee.
  compteur_comparaison++;
  return m_url <= un_resultat.m_url; 
}

bool Resultat::operator==(const Resultat& un_resultat) const {
  // Normallement, c'est la pertinence du URL plutot que son ordre alphabetique qui serait testee.
  compteur_comparaison++;
  return m_url == un_resultat.m_url;
}
