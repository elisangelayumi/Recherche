
#include "page.hpp"

#include <algorithm>
#include <assert.h>
#include <stdlib.h>
#include <random>


int partitionRand(std::vector<Resultat>& mesResultats, int l, int r) {

    std::default_random_engine generateur;

    std::uniform_int_distribution<int> uniforme(l, r);

    int s = uniforme(generateur);

    std::swap(mesResultats.at(l), mesResultats.at(s));

    Resultat pivot = mesResultats.at(l);
    int j = l;

    for (int i = l+1; i <= r; i++)
    {
        if (mesResultats.at(i) < pivot) {
           j = j + 1;
           std::swap(mesResultats.at(i), mesResultats.at(j));
        }
    }
    std::swap(mesResultats.at(j), mesResultats.at(l));

    return j;
}

// retourne le kieme plus petit (c.a.d le kieme plus pertinent) resultat.
Resultat selectionRecRand(std::vector<Resultat>& mesResultats, int l, int r, int k) {

    int indexPivot = partitionRand(mesResultats, l, r);

    if (indexPivot-l+1 == k) {
        return mesResultats.at(indexPivot);
    }
    if (indexPivot-l + 1 > k){
        return selectionRecRand(mesResultats, l, indexPivot-1, k);
    }
    if (indexPivot-l + 1 < k) {
        return selectionRecRand(mesResultats, indexPivot+1, r, k-indexPivot+l-1);
    }
}

void triRapideRand(std::vector<Resultat>& mesResultats, int l, int r) {

    if (l < r){
        int pivot = partitionRand(mesResultats, l, r);
        triRapideRand(mesResultats, l, pivot-1);
        triRapideRand(mesResultats, pivot+1, r);
    }
}

// Retourne les resultats d'une page
// Entrees:
//   resultats_non_tries: tous les resultats de recherche non tries
//   nombre_resultats_par_page: le nombre de resultats par page (sauf possiblement sur la derniere page)
//   numero_page: le numero de la page. La premiere page est la page numero 0.
// Sortie:
//   page: les resultats de recherche se trouvant sur la page demandee
void retournePage(const std::vector<Resultat>& resultats_non_tries, unsigned int nombre_resultats_par_page, unsigned int numero_page, std::vector<Resultat>& page) {
  assert(!resultats_non_tries.empty());
  assert(page.empty());
  assert(nombre_resultats_par_page > 0);
  assert(numero_page < (resultats_non_tries.size() + nombre_resultats_par_page - 1) / nombre_resultats_par_page); // (a + b - 1) / b = plafond(a/b)

    std::vector<Resultat> mesResultats(resultats_non_tries); //copie du vector pour faire des modifications

    std::vector<Resultat> resultatsPertinentPage; // vector intermediaire

    int nombreTotalPages = resultats_non_tries.size()/ nombre_resultats_par_page;

    int resultatPageRequis = numero_page * nombre_resultats_par_page; // on cherche quel doit etre le premier resultat de la page requis

    Resultat rK; // le Kieme resultat plus pertinent de la page requis
    Resultat r1 = selectionRecRand(mesResultats, 0, mesResultats.size()-1, resultatPageRequis+1); // le premier resultat plus pertinent de la page requis


    std::vector<Resultat>::iterator iter = std::find(mesResultats.begin(), mesResultats.end(), r1);
    int indexR1 = std::distance(mesResultats.begin(), iter); // on cherche la position de R1 dans le vecteur

    // le kieme resultat plus pertinent va dependre de la page qu'on cherche, alors on voit en quel cas nous sommes
    if (numero_page != nombreTotalPages){
        rK = selectionRecRand(mesResultats, indexR1, mesResultats.size()-1, resultatPageRequis + nombre_resultats_par_page - indexR1 );
    }
    else {
        rK = selectionRecRand(mesResultats, indexR1, mesResultats.size()-1, mesResultats.size() - indexR1 );
    }


    iter = std::find(mesResultats.begin(), mesResultats.end(), rK);
    int indexRK = std::distance(mesResultats.begin(), iter); // on cherche la position de rK dans le vecteur

    // on copie dans le vector intermediaire  le k elements de la page requis, c.a.d, les resultats entre indexR1 et indexRK.
    for(int i = indexR1; i <= indexRK; i++ ){
        resultatsPertinentPage.push_back(mesResultats.at(i));
    }

    // on trie les k resultats - theta(k log k)
    triRapideRand(resultatsPertinentPage,0,resultatsPertinentPage.size()-1);

    page.swap(resultatsPertinentPage);
}
