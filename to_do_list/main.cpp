#include <iostream>
#include "TaskList.h"
#include "Task.h"
#include "SubTask.h"

int main() {
    TaskList elenco;
    bool uscita = false;
    int scelta;

    std::cout << "\n===== Benvenuto nel tuo Gestore Attivita =====" << std::endl;

    do {
        std::cout << "\nOpzioni disponibili:\n";
        std::cout << "1) Crea una nuova lista\n";
        std::cout << "2) Aggiungi un'attivita\n";
        std::cout << "3) Rimuovi un'attivita\n";
        std::cout << "4) Modifica un'attivita\n";
        std::cout << "5) Segna un'attivita come completata\n";
        std::cout << "6) Visualizza attivita non completate\n";
        std::cout << "7) Visualizza tutte le attivita\n";
        std::cout << "8) Segna un sotto-task come completato\n";
        std::cout << "9) Mostra percentuale di task completati\n";
        std::cout << "10) Salva su file\n";
        std::cout << "11) Carica da file\n";
        std::cout << "0) Esci\n";

        std::cout << "\nScegli un'opzione (0 per uscire): ";
        std::cin >> scelta;

        Date data;
        std::string nomeLista, descrizione, nuovaDescrizione, nomeFile, stringaData;
        char opzione;

        std::cin.ignore();

        switch (scelta) {
            case 0:
                uscita = true;
                std::cout << "\nGrazie per aver utilizzato il tuo Gestore Attivita. A presto!\n";
                break;

            case 1:
                std::cout << "Nome della lista: ";
                std::getline(std::cin, nomeLista);
                elenco.setTitolo(nomeLista);
                elenco.svuota();
                std::cout << "Lista '" << nomeLista << "' creata con successo.\n";
                break;

            case 2: {
                std::cout << "Descrizione dell'attivita: ";
                std::getline(std::cin, descrizione);
                std::cout << "Data di scadenza (gg/mm/aaaa): ";
                std::getline(std::cin, stringaData);
                data = Task::daStringaData(stringaData);

                Task nuovoTask(data, descrizione);

                char aggiungi;
                std::cout << "Vuoi aggiungere dei sotto-task? (s/n): ";
                std::cin >> aggiungi;
                std::cin.ignore();

                while (aggiungi == 's' || aggiungi == 'S') {
                    std::string sottoDesc;
                    std::cout << "Descrizione sotto-task: ";
                    std::getline(std::cin, sottoDesc);
                    nuovoTask.addSubTask(SubTask(sottoDesc));

                    std::cout << "Aggiungere un altro sotto-task? (s/n): ";
                    std::cin >> aggiungi;
                    std::cin.ignore();
                }

                elenco.aggiungiAttivita(nuovoTask);
                break;
            }

            case 3:
                std::cout << "Descrizione o data dell'attivita da rimuovere: ";
                std::getline(std::cin, descrizione);
                elenco.rimuoviAttivita(descrizione);
                break;

            case 4:
                std::cout << "Attivita da modificare (descrizione o data): ";
                std::getline(std::cin, descrizione);
                std::cout << "Cosa vuoi modificare? (d=descrizione, g=data, c=completamento): ";
                std::cin >> opzione;
                std::cin.ignore();

                if (opzione == 'd') {
                    std::cout << "Nuova descrizione: ";
                    std::getline(std::cin, nuovaDescrizione);
                    elenco.modificaAttivita(descrizione, nuovaDescrizione, data);
                } else if (opzione == 'g') {
                    std::cout << "Nuova data (gg/mm/aaaa): ";
                    std::getline(std::cin, stringaData);
                    data = Task::daStringaData(stringaData);
                    elenco.modificaAttivita(descrizione, nuovaDescrizione, data);
                } else if (opzione == 'c') {
                    elenco.modificaAttivita(descrizione, nuovaDescrizione, data);
                } else {
                    std::cout << "Opzione non valida.\n";
                }
                break;

            case 5:
                std::cout << "Descrizione o data dell'attivita da completare: ";
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
                std::cout << "Inserisci descrizione attivita per segnare sottotask completato: ";
                std::getline(std::cin, descrizione);
                {
                    std::string attivitaDesc = descrizione;
                    std::string sottoTaskDesc;
                    std::cout << "Descrizione sotto-task da segnare completato: ";
                    std::getline(std::cin, sottoTaskDesc);
                    elenco.completaSottoTask(attivitaDesc, sottoTaskDesc);
                }
                break;

            case 9:
                std::cout << "Percentuale di task completati: "
                          << elenco.calcolaPercentualeTaskCompletati() << "%\n";
                break;

            case 10:
                elenco.salvaSuFile(elenco.getTitolo() + ".txt");
                std::cout << "Attivita salvate su file.\n";
                break;

            case 11:
                std::cout << "Nome del file da caricare: ";
                std::getline(std::cin, nomeFile);
                TaskList::caricaDaFile(nomeFile, elenco);
                std::cout << "File caricato correttamente.\n";
                break;

            default:
                std::cout << "Scelta non valida. Riprova.\n";
        }

    } while (!uscita);

    return 0;
}
