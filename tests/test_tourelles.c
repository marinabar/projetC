#include <assert.h>
#include "header.h"
char pseudo[50];
void test_VerifEntreeLigne() {
    Erreur erreur;
    erreur.statut_erreur = 0;

    /* Tests avec T (prix=80) */
    assert(VerifEntreeLigne("T 3\n", &erreur) == 80);
    assert(VerifEntreeLigne("T 7, T 1\n", &erreur) == 160);
    assert(VerifEntreeLigne("T 12,T 1\n", &erreur) == 160);

    /* Cas B 3: vérification de format ou autre erreur */
    assert(VerifEntreeLigne("B 3", &erreur) == -1);

    /* Positions hors limites */
    assert(VerifEntreeLigne("T 20", &erreur) == -1);
    assert(VerifEntreeLigne("T 0", &erreur) == -1);

    /* Positions en double */
    assert(VerifEntreeLigne("T 4, T 4", &erreur) == -1);

    /* Formats invalides */
    assert(VerifEntreeLigne("T", &erreur) == -1);
    assert(VerifEntreeLigne("T,3", &erreur) == -1);
    assert(VerifEntreeLigne("T T9", &erreur) == -1);
    assert(VerifEntreeLigne("T10", &erreur) == -1);
    assert(VerifEntreeLigne(",T", &erreur) == -1);
    assert(VerifEntreeLigne(",,", &erreur) == -1);

    /* Virgule finale */
    assert(VerifEntreeLigne("T 10,", &erreur) == -1);

    /* Virgule en trop */
    assert(VerifEntreeLigne("T 9,,T 1", &erreur) == -1);

    /* Caractère invalide pour la position */
    assert(VerifEntreeLigne("T m", &erreur) == -1);

    printf("VerifEntreeLigne a été testée avec succès.\n");
}

int main() {
    test_VerifEntreeLigne();
    return 0;
}