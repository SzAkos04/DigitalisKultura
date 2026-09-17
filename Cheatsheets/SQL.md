# SQL Cheatsheet — emelt szintű digitális kultúra érettségi

Ez az összefoglaló önmagában is elegendő ahhoz, hogy a tipikus adatbázis-kezelős érettségi feladatokat (kb. 5–9 részfeladat egy adott adatbázisra) magabiztosan meg tudd oldani. A minta lekérdezések a `taxi` adatbázisra épülnek (táblák: `gepkocsi`, `fuvar`, `tarifa`), illetve egy klasszikus "webshop" példára (`vasarlo`, `rendeles`) a "nincs vásárlás" típusú feladatokhoz:

```
vasarlo(id, nev)
rendeles(id, vasarlo_id, datum, osszeg)
```

## Tartalomjegyzék

- [[#1. Lekérdezés felépítése és végrehajtási sorrend]]
- [[#2. Táblák kapcsolása — JOIN típusok]]
- [[#3. Aggregáló függvények, GROUP BY, HAVING]]
- [[#4. Részlekérdezések (subquery)]]
- [[#5. Szöveg- és dátumfüggvények]]
- [[#6. IF / CASE — feltételes logika]]
- [[#7. UNION]]
- [[#8. Önmagával összekapcsolt tábla (self join)]]
- [[#9. Több táblás, összetett minta feladat]]
- [[#10. Kulcsok és táblakapcsolatok röviden]]
- [[#11. DDL — táblák létrehozása, módosítása]]
- [[#12. DML — adatmódosító utasítások]]
- [[#13. Gyakori hibák — gyorslista ellenőrzéshez]]

---

## 1. Lekérdezés felépítése és végrehajtási sorrend

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

**Írási sorrend** ≠ **végrehajtási sorrend**! A motor ezt a logikai sorrendet követi:

```
FROM → JOIN → WHERE → GROUP BY → HAVING → SELECT → ORDER BY → LIMIT
```

Ebből két fontos gyakorlati következmény adódik:
- A `WHERE`-ben **nem** hivatkozhatsz a `SELECT`-ben `AS`-szel elnevezett (aliasolt) mezőre, mert a `WHERE` korábban fut le, mint a `SELECT`.
- Az `ORDER BY`-ban **igen** hivatkozhatsz az aliasra, mert az már a `SELECT` után fut le.

---

## 2. Táblák kapcsolása — JOIN típusok

| Típus | Mit ad vissza |
|---|---|
| `INNER JOIN` | csak azok a sorok, ahol **mindkét** táblában van egyező kulcs |
| `LEFT JOIN`  | a bal oldali tábla **összes** sora megmarad, a jobb oldali mezők `NULL`-ok lesznek, ha nincs pár |
| `RIGHT JOIN` | fordítva: a jobb oldali tábla összes sora megmarad |

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

**Fontos részlet:** a dátumfeltételt a `JOIN ... ON`-ba tettük, nem a `WHERE`-be! Ha `WHERE fuvar.mikor = "2025-10-13"` lenne, az kiszűrné a `NULL` sorokat is (mert a `NULL = "2025-10-13"` kiértékelése soha nem igaz), és a lekérdezés visszaesne `INNER JOIN` viselkedésre — elveszítenénk pont azokat a sofőröket, akiket meg akartunk keresni.

---

## 3. Aggregáló függvények, GROUP BY, HAVING

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

**Gyakori hiba:** a `SELECT`-ben olyan mezőt kiírni, ami nincs sem a `GROUP BY`-ban, sem összesítő függvényben (pl. `fuvar.tav` önmagában, csoportosítás nélkül). Ez az OH javítási útmutató szerint hibapont, mert nem egyértelmű, melyik sorból származna az érték.

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

**`WHERE` vs `HAVING`:** a `WHERE` a csoportosítás **előtti** egyedi sorokra szűr, a `HAVING` a csoportosítás **utáni** összesített értékre. Ökölszabály: ha a feltétel egy aggregált értéket (SUM, COUNT, AVG stb.) érint, az mindig `HAVING`-be kerül; ha egyedi soron eldönthető adatra vonatkozik (pl. dátum, tarifa típusa), az `WHERE`-be.

### Minta feladat — csoportosítás több mezőre

"Naponta, soforönként az összes megtett táv, csak azok a napok, amikor legalább 80 km-t vezetett aznap":

```sql
SELECT DISTINCT
    gepkocsi.sofor
FROM
    gepkocsi
INNER JOIN
    fuvar ON gepkocsi.rendszam = fuvar.rendszam
GROUP BY
    gepkocsi.sofor,
    fuvar.mikor
HAVING
    SUM(fuvar.tav) >= 80;
```

Itt a `GROUP BY` két mezőre történik (sofőr **és** nap), így minden sofőr-nap kombinációra külön összegzünk — ez a helyes megközelítés, ha a feladat "adott napon" típusú feltételt tartalmaz.

---

## 4. Részlekérdezések (subquery)

### a) `WHERE`-ben, skalár érték

"Melyik sofőr vitte a leghosszabb fuvart?"

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

"Mely sofőrök vittek fuvart 2025-10-12-én?"

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

**Csapda:** ha a `rendeles.vasarlo_id` mezőben előfordulhat `NULL` érték, a `NOT IN` hibásan **üres** eredményt ad (SQL logika: bármi `NULL`-lal való összehasonlítása ismeretlen/`UNKNOWN`, ez pedig egyetlen sort sem enged át). Ilyenkor biztonságosabb a `LEFT JOIN ... IS NULL` vagy a `NOT EXISTS` forma.

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

Az `EXISTS` nem konkrét értéket, hanem azt vizsgálja, hogy a belső (ún. **korrelált**) lekérdezés ad-e vissza legalább egy sort — ezért gyakran gyorsabb és `NULL`-biztos, mint a `NOT IN`. Korrelált subquery-nél a belső lekérdezés a külső tábla aktuális sorára hivatkozik (itt: `vasarlo.id`), ezért soronként újra lefut.

---

## 5. Szöveg- és dátumfüggvények

```sql
Concat(a, b, ...)            -- összefűzés
Length(szoveg)               -- karakterek száma
Substring(szoveg, honnan, hany)
Upper(szoveg) / Lower(szoveg)
Trim(szoveg)                  -- szóközök levágása
Locate(resz, szoveg)          -- hanyadik pozíciótól kezdődik, 0 ha nincs benne
Left(szoveg, n) / Right(szoveg, n)

Year(datum) / Month(datum) / Day(datum)
Hour(ido) / Minute(ido) / Second(ido)
Date(datumido) / Time(datumido)
DateDiff(datum1, datum2)      -- napok különbsége
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

`LIKE` minta karakterek: `%` — tetszőleges hosszú (akár 0 karakteres) rész; `_` — pontosan egy karakter.

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

## 6. IF / CASE — feltételes logika

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

### Minta feladat — arányszámítás IF-fel

```sql
SELECT
    Concat(SUM(IF(tav < 6, 1, 0)) / COUNT(*) * 100, "%") AS "arany"
FROM
    fuvar
INNER JOIN
    gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
WHERE
    gepkocsi.sofor = "Szokai Ada";
```

Gondolatmenet: az `IF` soronként 1-et vagy 0-t ad vissza, ezeket összegzi a `SUM`, majd elosztjuk az összes sorral — így kapjuk meg a feltételnek megfelelő sorok arányát százalékban.

### Több eset — `CASE WHEN`

Ha kettőnél több kategóriát kell megkülönböztetni, az `IF` egymásba ágyazása helyett átláthatóbb a `CASE`:

```sql
SELECT
    id,
    tav,
    CASE
        WHEN tav < 5  THEN "rövid"
        WHEN tav < 10 THEN "közepes"
        ELSE "hosszú"
    END AS "kategoria"
FROM
    fuvar;
```

---

## 7. UNION

Két, azonos oszlopszámú és típusú lekérdezés eredményének "egymás alá" fűzésére szolgál.

```sql
SELECT sofor FROM gepkocsi WHERE vizsga = 1
UNION
SELECT sofor FROM gepkocsi WHERE utasszam >= 6;
```

- `UNION` automatikusan kiszűri a duplikátumokat.
- `UNION ALL` mindent meghagy, gyorsabb, ha tudjuk, hogy nincs átfedés, vagy a duplikátum lényegtelen/kívánt.

---

## 8. Önmagával összekapcsolt tábla (self join)

Akkor kell, ha egy táblán belül kell két sort összehasonlítani (pl. "mely sofőrök vezetik ugyanazt a...", vagy hierarchikus adatnál "ki kinek a főnöke"). Ilyenkor a táblát két különböző aliasszal szerepeltetjük:

```sql
SELECT
    a.sofor AS "sofor1",
    b.sofor AS "sofor2"
FROM
    gepkocsi a
INNER JOIN
    gepkocsi b ON a.utasszam = b.utasszam AND a.sofor < b.sofor;
```

Az `a.sofor < b.sofor` feltétel biztosítja, hogy egy párt csak egyszer kapjunk meg, és hogy egy sofőrt ne párosítsunk saját magával.

---

## 9. Több táblás, összetett minta feladat

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
2. Külső lekérdezés: ezekre a rendszámokra szűrve összeszámoljuk soforönként az **összes** fuvart (nem csak a törzsutasokat — mindig figyelj a feladat pontos megfogalmazására: "akinek volt legalább egy..." vs. "a törzsutas fuvarjainak száma" két különböző feladat!).

---

## 10. Kulcsok és táblakapcsolatok röviden

- **Elsődleges kulcs (primary key):** egyértelműen azonosítja a tábla egy sorát, nem lehet `NULL`, nem ismétlődhet.
- **Idegen kulcs (foreign key):** egy másik tábla elsődleges kulcsára mutat, ezzel fejezi ki a táblák közötti kapcsolatot (pl. `fuvar.rendszam` → `gepkocsi.rendszam`).
- **Kapcsolat típusai:**
  - 1:N (egy a többhöz) — pl. egy sofőrhöz/autóhoz sok fuvar tartozik. Ez a leggyakoribb az érettségi adatbázisokban.
  - N:M (több a többhöz) — ilyenkor egy külön **kapcsolótábla** szükséges, amely mindkét tábla kulcsát idegen kulcsként tartalmazza.

Ha a feladat táblatervezést kér, mindig gondold végig: melyik oldalon "sok" van, arra kell az idegen kulcs, és szükség van-e kapcsolótáblára.

---

## 11. DDL — táblák létrehozása, módosítása

```sql
CREATE TABLE tablanev (
  mezo1 INT NOT NULL,
  mezo2 VARCHAR(50),
  PRIMARY KEY (mezo1)
);

ALTER TABLE tablanev ADD mezo3 DATE;
ALTER TABLE tablanev DROP mezo3;
ALTER TABLE tablanev MODIFY mezo2 VARCHAR(100);

ALTER TABLE tablanev
  ADD CONSTRAINT fk_nev FOREIGN KEY (mezo2) REFERENCES masiktabla(id);
```

---

## 12. DML — adatmódosító utasítások

```sql
INSERT INTO tablanev (mezo1, mezo2)
VALUES (ertek1, ertek2), (ertek3, ertek4);

UPDATE tablanev
SET mezonev = ertek
WHERE id = 9;

DELETE FROM tablanev
WHERE id = 9;
```

**Figyelem:** `UPDATE` és `DELETE` `WHERE` nélkül a **teljes táblára** vonatkozik — érettségin ez szinte mindig hibapont, ha a feladat egy konkrét sorra/körre vonatkozott.

---

## 13. Gyakori hibák — gyorslista ellenőrzéshez

- `GROUP BY` nélkül aggregáló függvény + sima mező a `SELECT`-ben együtt → hibapont.
- Dátum/idő feltétel `JOIN ... ON`-ba vagy `WHERE`-be kerül — `LEFT JOIN` esetén ez nem mindegy (lásd 2. rész).
- `NOT IN` subquery, ahol a belső halmaz tartalmazhat `NULL`-t → üres eredmény, helyette `NOT EXISTS` vagy `LEFT JOIN ... IS NULL`.
- `HAVING` helyett `WHERE`-t használni aggregált feltételhez (vagy fordítva).
- `ORDER BY` elfelejtése, ahol a feladat sorrendet is kér ("a leghosszabb", "csökkenő sorrendben").
- `DISTINCT` elmaradása, amikor a JOIN miatt duplikált sorok keletkeznek.
- `UPDATE`/`DELETE` `WHERE` nélkül — véletlenül az egész táblát módosítja/törli.
- `UNION` és `UNION ALL` összekeverése, amikor a duplikátumok kezelése számít.
- Self join-nál elfelejteni az `a.kulcs <> b.kulcs` (vagy `<`) feltételt — így egy sor önmagával is párosodik, vagy minden pár duplán jelenik meg.