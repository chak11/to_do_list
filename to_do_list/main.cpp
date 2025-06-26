#include <iostream>
#include "taskList.h"
#include "task.h"

int main() {
    TaskList elenco;
    bool uscita = false;
    int scelta;


    std::cout << "\n===== Benvenuto nel tuo Gestore Attivita =====" << std::endl;

    do {
        std::cout << "\nOpzioni disponibili:" << std::endl;
        std::cout << "1) Crea una nuova lista" << std::endl;
        std::cout << "2) Aggiungi un'attivita" << std::endl;
        std::cout << "3) Rimuovi un'attivita" << std::endl;
        std::cout << "4) Modifica un'attivita" << std::endl;
        std::cout << "5) Segna come completata" << std::endl;
        std::cout << "6) Visualizza attivita non completate" << std::endl;
        std::cout << "7) Visualizza tutte le attivita" << std::endl;
        std::cout << "8) Salva su file" << std::endl;
        std::cout << "9) Carica da file" << std::endl;
        std::cout << "0) Esci" << std::endl;

        std::cout << "\nScegli un'opzione (0 per uscire): ";
        std::cin >> scelta;

        Date data;
        std::string nomeLista, descrizione, nuovaDescrizione, nomeFile, stringaData;
        char opzione;

        switch (scelta) {
            case 0:
                uscita = true;
                std::cout << "\nGrazie per aver utilizzato il tuo Gestore Attivita. A presto!" << std::endl;
                break;
            case 1:
                std::cout << "Nome della lista: ";
                std::cin.ignore();
                std::getline(std::cin, nomeLista);
                elenco.setTitolo(nomeLista);
                elenco.svuota();
                std::cout << "Lista '" << nomeLista << "' creata con successo." << std::endl;
                break;
            case 2:
                std::cout << "Descrizione dell'attivita: ";
                std::cin.ignore();
                std::getline(std::cin, descrizione);
                std::cout << "Data di scadenza (gg/mm/aaaa): ";
                std::getline(std::cin, stringaData);
                data = Task::daStringaData(stringaData);
                elenco.aggiungiAttivita(Task(data, descrizione));
                break;
            case 3:
                std::cout << "Inserisci la descrizione o la data dell'attivita da rimuovere: ";
                std::cin.ignore();
                std::getline(std::cin, descrizione);
                elenco.rimuoviAttivita(descrizione);
                break;
            case 4:
                std::cout << "Attivita da modificare (descrizione o data): ";
                std::cin.ignore();
                std::getline(std::cin, descrizione);
                std::cout << "Cosa vuoi modificare? (d=descrizione, g=data, c=completamento): ";
                std::cin >> opzione;
                if (opzione == 'd') {
                    std::cout << "Nuova descrizione: ";
                    std::cin.ignore();
                    std::getline(std::cin, nuovaDescrizione);
                    elenco.modificaAttivita(descrizione, nuovaDescrizione, data);
                } else if (opzione == 'g') {
                    std::cout << "Nuova data (gg/mm/aaaa): ";
                    std::cin.ignore();
                    std::getline(std::cin, stringaData);
                    data = Task::daStringaData(stringaData);
                    elenco.modificaAttivita(descrizione, nuovaDescrizione, data);
                } else if (opzione == 'c') {
                    elenco.modificaAttivita(descrizione, nuovaDescrizione, data);
                } else {
                    std::cout << "Opzione non valida." << std::endl;
                }
                break;
            case 5:
                std::cout << "Descrizione o data dell'attivita da completare: ";
                std::cin.ignore();
                std::getline(std::cin, descrizione);
                elenco.completaAttivita(descrizione);
                break;
            case 6:
                elenco.mostraIncompleti();
                break;
            case 7:
                elenco.mostraTutte();
                break;
            case 8:
                elenco.salvaSuFile(elenco.getTitolo() + ".txt");
                std::cout << "Attivita salvate su file." << std::endl;
                break;
            case 9:
                std::cout << "Nome del file da caricare: ";
                std::cin.ignore();
                std::getline(std::cin, nomeFile);
                TaskList::caricaDaFile(nomeFile, elenco);
                std::cout << "File caricato correttamente." << std::endl;
                break;
            default:
                std::cout << "Scelta non valida. Riprova." << std::endl;
        }
    } while (!uscita);

    return 0;
}

