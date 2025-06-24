//
// Created by chaki on 23/06/2025.
//

#ifndef DATA_H
#define DATA_H




class Date {
public:
    Date(int giorno, int mese, int anno);
    Date() : giorno(0), mese(0), anno(0) {}

    int getGiorno() const;
    int getMese() const;
    int getAnno() const;

    void setGiorno(int giorno);
    void setMese(int mese);
    void setAnno(int anno);

    bool operator==(const Date &d) const;

private:
    int giorno, mese, anno;

    bool isValida(int giorno, int mese, int anno);
    bool giornoValido(int giorno, int mese, int anno) const;
    bool meseValido(int mese);
    bool annoValido(int anno);

    int giorniNelMese(int mese, int anno) const;
    bool isBisestile(int anno) const;
};




#endif //DATA_H
