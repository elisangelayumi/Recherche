#ifndef PAGE
#define PAGE

#include <vector>

#include "resultat.hpp"

// Retourne les resultats d'une page
// Entrees:
//   resultats_non_tries: tous les resultats de recherche non tries
//   nombre_resultats_par_page: le nombre de resultats par page (sauf possiblement sur la derniere page)
//   numero_page: le numero de la page. La premiere page est la page numero 0.
// Sortie:
//   page: les resultats de recherche se trouvant sur la page demandee
void retournePage(const std::vector<Resultat>& resultats_non_tries, unsigned int nombre_resultats_par_page, unsigned int numero_page, std::vector<Resultat>& page);

#endif
