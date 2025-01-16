#include "Tests/personnetest.h"

void PersonneTest::runTests() {
    std::cout << "Démarrage des tests pour la classe Personne...\n";
    testConstructeur();
    testGetNom();
    testSetNom();
    testGetPrenom();
    testSetPrenom();
    testGetId();
    std::cout << "Tous les tests de la classe Personne ont réussi avec succès !\n";
}

void PersonneTest::testConstructeur() {
    Personne personne("Royer", "Tom");
    assert(personne.getNom() == "Royer");
    assert(personne.getPrenom() == "Tom");
    assert(personne.getId() == 1);
    std::cout << "Test constructeur : OK\n";
}

void PersonneTest::testGetNom() {
    Personne personne1("Jozwiak", "Corentin");
    assert(personne1.getNom() == "Jozwiak");
    std::cout << "Test getNom : OK\n";
}

void PersonneTest::testSetNom() {
    Personne personne2("Theuil", "Martin");
    personne2.setNom("Bob");
    assert(personne2.getNom() == "Bob");
    std::cout << "Test setNom : OK\n";
}

void PersonneTest::testGetPrenom() {
    Personne personne3("Theuil", "Martin");
    assert(personne3.getPrenom() == "Martin");
    std::cout << "Test getPrenom : OK\n";
}

void PersonneTest::testSetPrenom() {
    Personne personne4("Alice", "Smith");
    personne4.setPrenom("Brown");
    assert(personne4.getPrenom() == "Brown");
    std::cout << "Test setPrenom : OK\n";
}

void PersonneTest::testGetId() {
    Personne personne5("John", "Doe");
    Personne personne6("Jane", "Doe");
    assert(personne5.getId() == 6);
    assert(personne6.getId() == 7);
    std::cout << "Test getId : OK\n";
}
