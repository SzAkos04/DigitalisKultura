# SQL Cheatsheet — emelt szintű digitális kultúra érettségi

Minden mintafeladat a `taxi` adatbázisra épül (táblák: `gepkocsi`, `fuvar`, `tarifa`), ahol releváns, illetve egy általános "webshop" példára (`vasarlo`, `rendeles`) a klasszikus "nincs vásárlás" típusú feladatokhoz.

```
vasarlo(id, nev)
rendeles(id, vasarlo_id, datum, osszeg)
```

---

## 1. Lekérdezés felépítése — sorrend

```sql
SELECT   mezők
FROM     táblák
JOIN     ...  ON  ...
WHERE    sor szintű feltétel
GROUP BY csoportosító mező(k)
HAVING   csoport szintű feltétel
ORDER BY rendezés
LIMIT    n OFFSET m;
```

Végrehajtási sorrend (nem írási sorrend!): `FROM → WHERE → GROUP BY → HAVING → SELECT → ORDER BY → LIMIT`.
Ezért nem lehet a `WHERE`-ben `AS`-szel elnevezett mezőre hivatkozni, de `ORDER BY`-ban igen.

---

## 2. JOIN típusok

| Típus | Mit ad vissza |
|---|---|
| `INNER JOIN` | csak azok a sorok, ahol mindkét táblában van egyező kulcs |
| `LEFT JOIN`  | a bal tábla **összes** sora megmarad, jobb oldali mezők `NULL`-ok, ha nincs párja |
| `RIGHT JOIN` | fordítva: a jobb tábla összes sora megmarad |

### Minta feladat — "írj ki minden olyan vásárlót, aki még nem vásárolt"

Gondolatmenet: `LEFT JOIN`-nal a `vasarlo` tábla minden sora megmarad, a nem létező rendeléshez `NULL` kerül a `rendeles.id` helyére. Ezután `WHERE rendeles.id IS NULL` kiszűri azokat, akiknek egyáltalán nincs párja.

```sql
SELECT
    vasarlo.nev
FROM
    vasarlo
LEFT JOIN
    rendeles ON vasarlo.id = rendeles.vasarlo_id
WHERE
    rendeles.id IS NULL;
```

**Miért nem működik `INNER JOIN`-nal?** Mert az `INNER JOIN` eleve kidobja azokat a vásárlókat, akiknek nincs rendelésük — így sosem jutnánk el a `WHERE` szűrésig, mert azok a sorok már nem is léteznek az eredményhalmazban.

### Ugyanez a `taxi` adatbázison — "mely sofőr nem hajtott végre fuvart 2025-10-13-án"

```sql
SELECT
    gepkocsi.sofor
FROM
    gepkocsi
LEFT JOIN
    fuvar ON gepkocsi.rendszam = fuvar.rendszam
       AND fuvar.mikor = "2025-10-13"
WHERE
    fuvar.id IS NULL;
```

Fontos részlet: a dátumfeltételt a `JOIN ... ON`-ba tettük, nem a `WHERE`-be! Ha `WHERE fuvar.mikor = "2025-10-13"` lenne, az kiszűrné a `NULL` sorokat is, és a lekérdezés visszaesne `INNER JOIN` viselkedésre.

---

## 3. Aggregáló (összesítő) függvények

```sql
COUNT(*)      -- sorok száma
COUNT(mezo)   -- nem NULL értékek száma
SUM(mezo)
AVG(mezo)
MIN(mezo)
MAX(mezo)
```

### Minta feladat — "soforönként az összes megtett táv"

```sql
SELECT
    gepkocsi.sofor,
    SUM(fuvar.tav) AS "osszes_tav"
FROM
    gepkocsi
INNER JOIN
    fuvar ON gepkocsi.rendszam = fuvar.rendszam
GROUP BY
    gepkocsi.sofor
ORDER BY
    osszes_tav DESC;
```

**Gyakori hiba:** a `SELECT`-ben olyan mezőt kiírni, ami nincs sem a `GROUP BY`-ban, sem összesítő függvényben (pl. `fuvar.tav` önmagában). Ez az OH javítási útmutató szerint hibapont.

### Minta feladat — HAVING: "mely sofőrök vittek összesen legalább 10 fuvart"

```sql
SELECT
    gepkocsi.sofor,
    COUNT(*) AS "fuvarok_szama"
FROM
    gepkocsi
INNER JOIN
    fuvar ON gepkocsi.rendszam = fuvar.rendszam
GROUP BY
    gepkocsi.sofor
HAVING
    COUNT(*) >= 10;
```

`WHERE` vs `HAVING`: a `WHERE` a csoportosítás **előtti** egyedi sorokra szűr, a `HAVING` a csoportosítás **utáni** összesített értékre. Ha egy feltétel az aggregált értéket (SUM, COUNT, stb.) érinti, az mindig `HAVING`-be kerül.

---

## 4. Részlekérdezések (subquery)

### a) `WHERE`-ben, skalár érték

Minta feladat — "melyik sofőr vitte a leghosszabb fuvart"

```sql
SELECT
    gepkocsi.sofor
FROM
    gepkocsi
INNER JOIN
    fuvar ON gepkocsi.rendszam = fuvar.rendszam
WHERE
    fuvar.tav = (SELECT MAX(tav) FROM fuvar);
```

### b) `IN` — halmazzal való összevetés

Minta feladat — "mely sofőrök vittek fuvart 2025-10-12-én"

```sql
SELECT DISTINCT
    gepkocsi.sofor
FROM
    gepkocsi
WHERE
    gepkocsi.rendszam IN (
        SELECT rendszam FROM fuvar WHERE mikor = "2025-10-12"
    );
```

### c) `NOT IN` — "aki még nem vásárolt" subquery-vel (LEFT JOIN alternatívája)

```sql
SELECT
    vasarlo.nev
FROM
    vasarlo
WHERE
    vasarlo.id NOT IN (SELECT vasarlo_id FROM rendeles);
```

**Csapda:** ha a `rendeles.vasarlo_id` mezőben előfordulhat `NULL` érték, a `NOT IN` hibásan üres eredményt ad (SQL logika: `NULL`-lal való összehasonlítás ismeretlen). Ilyenkor biztonságosabb a `LEFT JOIN ... IS NULL` vagy a `NOT EXISTS` forma.

### d) `EXISTS` / `NOT EXISTS`

```sql
SELECT
    vasarlo.nev
FROM
    vasarlo
WHERE NOT EXISTS (
    SELECT 1 FROM rendeles WHERE rendeles.vasarlo_id = vasarlo.id
);
```

Az `EXISTS` nem konkrét értéket, hanem azt vizsgálja, hogy a belső lekérdezés ad-e vissza legalább egy sort — ezért gyakran gyorsabb és `NULL`-biztos, mint a `NOT IN`.

---

## 5. Szöveg- és dátumfüggvények

```sql
Concat(a, b, ...)          -- összefűzés
Length(szoveg)             -- karakterek száma
Substring(szoveg, honnan, hany)
Upper(szoveg) / Lower(szoveg)
Trim(szoveg)                -- szóközök levágása
Locate(resz, szoveg)        -- hanyadik pozíciótól kezdődik, 0 ha nincs benne

Year(datum) / Month(datum) / Day(datum)
Hour(ido) / Minute(ido) / Second(ido)
Date(datumido) / Time(datumido)
```

### Minta feladat — "azok a sofőrök, akiknek a rendszámában szerepel a 3-as vagy az 5-ös szám, és a nevük 'Sz'-re kezdődik"

```sql
SELECT
    sofor,
    rendszam
FROM
    gepkocsi
WHERE
    (rendszam LIKE "%3%" OR rendszam LIKE "%5%")
    AND sofor LIKE "Sz%";
```

### Minta feladat — "hónapok szerinti bontásban a fuvarok darabszáma"

```sql
SELECT
    Month(mikor) AS "honap",
    COUNT(*) AS "darab"
FROM
    fuvar
GROUP BY
    Month(mikor)
ORDER BY
    honap;
```

---

## 6. IF / CASE — feltételes logika a SELECT-ben

```sql
IF(feltetel, igaz_ertek, hamis_ertek)
```

### Minta feladat — "minden fuvarhoz jelezze ki, hogy 'rövid' (5 km alatt) vagy 'hosszú'"

```sql
SELECT
    id,
    tav,
    IF(tav < 5, "rövid", "hosszú") AS "kategoria"
FROM
    fuvar;
```

### Minta feladat — arányszámítás IF-fel (lásd `8szokai.sql` mintaanyagodban is)

```sql
SELECT
    Concat(SUM(IF(tav < 6, 1, 0)) / COUNT(*) * 100, "%") AS "arany"
FROM
    fuvar;
```

Gondolatmenet: az `IF` soronként 1-et vagy 0-t ad vissza, ezeket összegzi a `SUM`, majd elosztjuk az összes sorral — így kapjuk meg a feltételnek megfelelő sorok arányát százalékban.

---

## 7. Több táblás, összetettebb minta feladat

"Írd ki azon sofőrök nevét és az általuk vezetett fuvarok darabszámát, akiknek volt legalább egy 'törzsutas' tarifájú fuvarja, csökkenő sorrendben a fuvarok száma szerint."

```sql
SELECT
    gepkocsi.sofor,
    COUNT(*) AS "fuvarok_szama"
FROM
    gepkocsi
INNER JOIN
    fuvar ON gepkocsi.rendszam = fuvar.rendszam
WHERE
    gepkocsi.rendszam IN (
        SELECT fuvar.rendszam
        FROM fuvar
        INNER JOIN tarifa ON fuvar.tarifaid = tarifa.id
        WHERE tarifa.tipus = "törzsutas"
    )
GROUP BY
    gepkocsi.sofor
ORDER BY
    fuvarok_szama DESC;
```

Gondolatmenet lépésről lépésre:
1. Belső lekérdezés: mely rendszámok szerepelnek legalább egy törzsutas fuvarban.
2. Külső lekérdezés: ezekre a rendszámokra szűrve összeszámoljuk soforönként az **összes** fuvart (nem csak a törzsutasokat — figyelj a feladat pontos megfogalmazására!).

---

## 8. DDL — táblák létrehozása/módosítása

```sql
CREATE TABLE tablanev (
  mezo1 INT NOT NULL,
  mezo2 VARCHAR(50),
  PRIMARY KEY (mezo1)
);

ALTER TABLE tablanev ADD mezo3 DATE;
ALTER TABLE tablanev DROP mezo3;

ALTER TABLE tablanev
  ADD CONSTRAINT fk_nev FOREIGN KEY (mezo2) REFERENCES masiktabla(id);
```

## 9. DML — módosító utasítások

```sql
INSERT INTO tablanev (mezo1, mezo2)
VALUES (ertek1, ertek2), (ertek3, ertek4);

UPDATE tablanev
SET mezonev = ertek
WHERE id = 9;

DELETE FROM tablanev
WHERE id = 9;
```

---

## 10. Gyakori hibák — gyorslista ellenőrzéshez

- `GROUP BY` nélkül aggregáló függvény + sima mező a `SELECT`-ben együtt → hibapont.
- Dátum/idő feltétel `JOIN ... ON`-ba vagy `WHERE`-be kerül — LEFT JOIN esetén ez nem mindegy (lásd 2. rész).
- `NOT IN` subquery, ahol a belső halmaz tartalmazhat `NULL`-t → üres eredmény, helyette `NOT EXISTS` vagy `LEFT JOIN IS NULL`.
- `HAVING` helyett `WHERE`-t használni aggregált feltételhez (vagy fordítva).
- `ORDER BY` elfelejtése, ahol a feladat sorrendet is kér ("a leghosszabb", "csökkenő sorrendben").
- `DISTINCT` elmaradása, amikor a JOIN miatt duplikált sorok keletkeznek.
