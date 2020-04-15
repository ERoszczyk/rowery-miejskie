**Rowery miejskie**

Projekt ma na celu udostępnienie możliwości wypożyczenia rowerów. Trzema głównymi aspektami projektu są 
użytkownicy, rowery i wypożyczalnia. Użytkownik będzie mógł wypożyczyć rower na określoną ilość czasu, po 
czym musi zwrócić do jednego z punktów wypożyczalni. 

**Członkowie**

    Krupa Olga gr.108
    Kwoka Kinga gr.108
    Roszczyk Ewa gr.108

**Początkowy podział pracy**

Klasy 
- rower - obsługa danego roweru, o przypisanym indeksie; informacja o stanie(wolny/zajęty) ; 
	czas do końca wypożyczenia; numer lokalizacji (stojak). 
- wypożyczalnia - baza rowerow ; dostepne stojaki; przypisanie rowerów do stojaków;
	wiadomośc o wolnym miejscu przy stojaku; wiadomość o zajętych rowerach.
- użytkownicy - Dane: imię nazwisko, indeks w bazie użytkowników; logowanie : login i hasło;
	numer wypożyczonego roweru (jeśli taki jest); możliwość dodania nowego użytkownika do bazy.



Opis klas
- Klasa Bike - jej 2 głównymi funkcjami są StartOfRent oraz Stop.
Po sprawdzeniu przez wypożyczalnie stanu roweru, wypożyczalnia wywołuje ‘StartOfRent’ która zwalnia stojak do którego był przypięty rower oraz rozpoczyna czas wypożyczenia. Druga funkcja - ‘Stop’ jest odpowiedzialna za zwrot roweru. Prosi ona użytkownika o podanie id stojaka do którego użytkownik chce przypiąć rower. Zapisuje dane do bazy oraz zwalnia użytkownika od danego roweru. Pobiera również z konta odpowiednią sumę (różnica czasu od wypożyczenia roweru do przypięcia do wolnego stojaka). Funkcja ma również opcję zapisania do historii wypożyczeń oraz wyświetlenie całej historii.
