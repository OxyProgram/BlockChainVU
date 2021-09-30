VU MIF ISI 2k. 1 pgr. Karolis Kučinskas Block Chain Hash projektas

Pseudokodas kaip veikia algoritmas:


<img width="702" alt="Screenshot 2021-09-30 at 13 26 57" src="https://user-images.githubusercontent.com/75229680/135438747-3ef05979-f688-4fa7-b512-dbf09846c457.png">

Funkcijos analizė:

1.Funkcijos įvestis gali būti bet kokio dydžio:

Testas: funkcija sugeneruoja Hash string kai simbolių eilutėje yra nuo 0 iki 1 000 000;

2. Funkcijos įšvestis visada bus 64 simbolių hex'as

Testas: funkcija sugeneruoja Hash string, kuris yra 64 simbolių hex'as, kai simbolių eilutėje yra nuo 0 iki 1 000 000;

3. Funkcija yra deterministinė:

Testas: funkcija sugeneruoja tą patį Hash string elementui "a"/"b" 1000;

4. Funkcija veikia greitai

Testas: funkcija sugeneravo Hash string's failui konstitucija.txt per 54 ms.

5. Funkcija atspari kolizijai

Testas: sugeneruota 100 000 porų, kuriuose yra skirtingos simbolių eilutės. Aptikta 0 kolizijų.

6. Pakeitus įvesti minimaliai gaunamas visiškai kitas rezultatas

Testas: <img width="659" alt="Screenshot 2021-10-01 at 01 30 30" src="https://user-images.githubusercontent.com/75229680/135538572-cefc2cd7-e86f-496a-ae4e-892fa9a56640.png">
