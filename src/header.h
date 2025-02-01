#ifndef HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdint.h>


#define HEADER_H
#define NB_LIGNES 7
#define NB_EMPLACEMENTS 15
#define NB_TYPES_ENNEMIS 6
#define NB_TYPES_TOURELLES 6


// couleurs de texte de sortie terminal

#define ANSI_RESET "\033[0m"
#define CLEAR_LINE "\033[2K"

#define ANSI_TEXTE_BLANC "\033[38;5;15m"
#define ANSI_TEXTE_BLEU_FONCE "\033[38;5;12m"
#define ANSI_TEXTE_BLEU_MOYEN "\033[38;5;25m"
#define ANSI_TEXTE_GRIS "\033[38;5;252m"

#define ANSI_BG_BLEU_SHINY "\033[104m" // bleu éléctrique
#define ANSI_BG_BLANC "\033[48;5;15m"
#define ANSI_BG_BLEU_MEGA_LIGHT "\033[48;5;195m" // bleu ECTS
#define ANSI_BG_BLEU_CLAIR "\033[48;5;81m" // Steel blue vrmt clair
#define ANSI_BG_GRIS_CLAIR "\033[48;5;254m"
#define ANSI_BG_VERT_FONCE "\033[48;5;37m"
#define ANSI_BG_BLEU_FONCE "\033[48;5;17m" // Navy blue
#define ANSI_BG_ROUGE "\033[48;5;124m"




/// definition des structures du jeu
typedef struct {
    char msg_erreur[150];
    int statut_erreur;
} Erreur;


typedef struct etudiant {
    // type correspond a la valeur ASCII du symbole associé
    int type;
    int pointsDeVie;
    int ligne;
    int position;
    int vitesse;
    int tour;
    int immobilisation;
    int deplace;// 1 si l'ennemi a été déplacé, uniquement pour le type F
    struct etudiant* next;
    struct etudiant* next_line;
    struct etudiant* prev_line;
} Etudiant;

typedef struct tourelle {
    int type;
    int pointsDeVie;
    int ligne;
    int position;
    int prix;
    struct tourelle* next;
} Tourelle;

typedef struct {
    const char symbole; // Caractère représentant le type dans le fichier
    int pointsDeVie;
    int vitesse;
    const char* nom;     
    const char* description; 
} TypeEnnemi;

typedef struct {
    const char symbole;        
    int pointsDeVie;   
    int prix;
    const char* nom;
    const char* description;
} TypeTourelle;

typedef struct {
    // pointeur vers la première tourelle
    Tourelle* tourelles;
    // pointeur vers le premier ennemi
    Etudiant* etudiants;
    int cagnotte;
    int tour;
} Jeu;

//prototypes de fonctions d'introduction 
void IntroduireJeu(Erreur* erreur);
void VisualiserEnnemis(Etudiant* etudiants, Erreur* erreur);

// prototypes de fonctions de gestion des ennemis
const TypeEnnemi* trouverTypeEnnemi(char symbole);
const TypeEnnemi* VerifType(int *tour, int *ligne, char *symbole, Erreur *erreur);
Etudiant* InitialisationEnnemis(FILE* fichier_ennemis, Jeu* jeu, Erreur* erreur);
void SupprimerEnnemi(Jeu* jeu, Erreur* erreur, Etudiant* ennemi);
void LibererEnnemis(Etudiant* premier);
int ActionFaineant2(Jeu* jeu, Etudiant* e);

// protopypes de fonctions de gestion des tourelles
Tourelle * InitialisationTourelles(int * cagnotte, Erreur* erreur);
int VerifEntreeLigne(char * ligne_tourelles, Erreur* erreur);
void LibererTourelles(Tourelle* premier);
Tourelle* AjouterTourelles(Tourelle* * premier, Tourelle* dernier, char* ligne_tourelles, int ligne, Erreur* erreur);

// fonctions d'aide
void ResoudreFichier(FILE* fichier_ennemis, Erreur* erreur);
void Attendre(int ms);
void ChangerLigne(Jeu * jeu, Etudiant* e, int saut);

// prototypes de fonctions de jeu
void JouerPartie(Jeu* jeu, Erreur* erreur);
void AfficherPlateau(Jeu* jeu);

// prototypes de visualisation
void animer_attente(int attente_ms, char *message);
void print_avec_delai(const char *text, int delai_ms);
void barre_de_chargement(int ms);

#endif