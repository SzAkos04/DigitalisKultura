# Excel Cheatsheet — emelt szintű digitális kultúra érettségi

## Tartalomjegyzék

- [[#1. Hivatkozások — relatív, abszolút, vegyes]]
- [[#2. Logikai függvények]]
- [[#3. Keresőfüggvények]]
- [[#4. Összesítő (aggregáló) függvények]]
- [[#5. Szövegfüggvények]]
- [[#6. Dátum- és időfüggvények]]
- [[#7. Matematikai / kerekítő függvények]]
- [[#8. Statisztikai rangsor-függvények]]
- [[#9. Feltételes formázás (Conditional Formatting)]]
- [[#10. Adatérvényesítés (Data Validation)]]
- [[#11. Rendezés és szűrés]]
- [[#12. Kimutatás (Pivot tábla) — lépésről lépésre]]
- [[#13. Diagram létrehozása — lépésről lépésre]]
- [[#14. Elnevezett tartományok (Named Ranges)]]
- [[#15. Lapvédelem és munkafüzet-védelem]]
- [[#16. Nézet és nyomtatás]]
- [[#17. Hasznos billentyűparancsok]]
- [[#18. Gyakori hibák — gyorslista ellenőrzéshez]]

---

## 1. Hivatkozások — relatív, abszolút, vegyes

```
A1      -> relatív: másoláskor mindkét koordináta követi a mozgást
$A$1    -> abszolút: másoláskor semmi nem változik
$A1     -> csak az oszlop rögzített (A mindig A marad, a sor követi)
A$1     -> csak a sor rögzített
```

Rögzítés gyors váltása: cella kijelölése a képletsorban, majd **F4** billentyű (körbe váltja: A1 → $A$1 → A$1 → $A1 → A1).

Másik munkalapra hivatkozás: `Munka2!A1`
Másik fájlra hivatkozás: `[Fájlnév.xlsx]Munka2!A1`

---

## 2. Logikai függvények

```excel
HA(feltétel; ha_igaz; ha_hamis)                 -- IF
ÉS(feltétel1; feltétel2; ...)                   -- AND
VAGY(feltétel1; feltétel2; ...)                 -- OR
NEM(feltétel)                                    -- NOT
HAHIBA(képlet; hiba_esetén_érték)                -- IFERROR
HA.TÖBB(feltétel1; érték1; feltétel2; érték2; ...; alapértelmezett) -- IFS
```

Egymásba ágyazott HA:
```excel
=HA(C2<500; "olcsó"; HA(C2<2000; "közepes"; "drága"))
```

Modern helyettesítő (365/2019+), ha nem kell egymásba ágyazni:
```excel
=HA.TÖBB(C2<500; "olcsó"; C2<2000; "közepes"; IGAZ; "drága")
```

Kombinálva:
```excel
=HA(ÉS(C2<1000; D2>10); "kedvezmény"; "nincs kedvezmény")
=HA(VAGY(B2="Akció"; C2<500); "igen"; "nem")
```

Hibakezelés (pl. FKERES #HIÁNYZIK hibájára):
```excel
=HAHIBA(FKERES(G2; A:B; 2; 0); "nincs találat")
```

---

## 3. Keresőfüggvények

### FKERES (VLOOKUP) — jobbra, első oszlop szerint keres

```excel
=FKERES(keresési_érték; tábla; oszlopszám; 0)
```
A `0` / `HAMIS` a pontos egyezés — majdnem mindig ez kell.
`1` / `IGAZ` esetén közelítő (legközelebbi kisebb-egyenlő) egyezést ad, rendezett listán.

### VKERES (HLOOKUP) — ugyanez vízszintesen

```excel
=VKERES(keresési_érték; tábla; sorszám; 0)
```

### XKERES (XLOOKUP) — modern, rugalmasabb (365/2021+)

```excel
=XKERES(keresési_érték; keresési_tartomány; visszaadási_tartomány; [ha_nincs]; [egyezés_mód]; [keresési_mód])
```
Előnyök a FKERES-hez képest: nem kell oszlopszámot számolni, tud balra is keresni, van beépített "ha nincs találat" paraméter, alapértelmezetten pontos egyezést keres.

### INDEX + HOL.VAN — ha balra is kell keresni, vagy a tábla oszlopai bővülhetnek

```excel
=INDEX(visszaadási_tartomány; HOL.VAN(keresési_érték; keresési_tartomány; 0))
```
`HOL.VAN` (MATCH) megadja a pozíciót a tartományon belül, az `INDEX` (INDEX) ez alapján hozza vissza az értéket. Ez a páros a FKERES általánosítása: bármelyik oszlopból bármelyik oszlopba kereshet.

### KERES (LOOKUP) — egyszerűsített, ritkán szükséges

```excel
=KERES(keresési_érték; keresési_vektor; eredmény_vektor)
```

### Egyéb kereső jellegű függvények
```excel
CÍM(sor; oszlop)                 -- ADDRESS: cellahivatkozást ad szövegként
SOR(cella) / OSZLOP(cella)       -- ROW / COLUMN
SOROK(tartomány) / OSZLOPOK(tartomány) -- ROWS / COLUMNS
ELTOLÁS(alap; sorok; oszlopok; [magasság]; [szélesség]) -- OFFSET
```

---

## 4. Összesítő (aggregáló) függvények

```excel
ÖSSZEG(tartomány)                -- SUM
ÁTLAG(tartomány)                 -- AVERAGE
DARAB(tartomány)                 -- COUNT: csak számokat számol
DARAB2(tartomány)                -- COUNTA: nem üres cellákat számol
DARABÜRES(tartomány)             -- COUNTBLANK: üres cellák száma
MAX(tartomány) / MIN(tartomány)
MEDIÁN(tartomány)                -- MEDIAN
MÓDUSZ.EGY(tartomány)            -- MODE.SNGL
SZÓRÁS(tartomány) / SZÓRÁSP(tartomány) -- STDEV / STDEV.P
```

### Egy feltételes verzió

```excel
ÖSSZEGHA(feltétel_tartomány; feltétel; [összegzési_tartomány])   -- SUMIF
DARABTELI(feltétel_tartomány; feltétel)                          -- COUNTIF
ÁTLAGHA(feltétel_tartomány; feltétel; [átlagolási_tartomány])    -- AVERAGEIF
```

### Több feltételes verzió

```excel
ÖSSZEGZIK(összegzési_tartomány; feltétel1_tartomány; feltétel1; feltétel2_tartomány; feltétel2; ...)  -- SUMIFS
DARABTELI2(feltétel1_tartomány; feltétel1; feltétel2_tartomány; feltétel2; ...)                        -- COUNTIFS
ÁTLAGHATÖBB(átlagolási_tartomány; feltétel1_tartomány; feltétel1; ...)                                  -- AVERAGEIFS
MAXHATÖBB(max_tartomány; feltétel1_tartomány; feltétel1; ...)                                            -- MAXIFS
MINHATÖBB(min_tartomány; feltétel1_tartomány; feltétel1; ...)                                            -- MINIFS
```

Feltétel megadási formák: `"Akció"`, `">1000"`, `"<>"&B2`, `"*alma*"` (joker karakterrel).

### SZORZATÖSSZEG — SUMPRODUCT, "rejtett" összesítő

```excel
=SZORZATÖSSZEG((A2:A100="Akció")*(C2:C100))
```
Elemenként összeszorozza a tartományokat, majd összegzi — sokoldalú, ha a beépített feltételes függvények nem elegek (pl. két oszlop együttes, bonyolultabb logikájú feltétele).

### RÉSZÖSSZEGEK — SUBTOTAL (szűrt listánál hasznos, kihagyja a rejtett sorokat)

```excel
=RÉSZÖSSZEGEK(9; tartomány)   -- 9 = SUM funkciószám, 109 = SUM csak látható sorokra
```

---

## 5. Szövegfüggvények

```excel
BAL(szöveg; hossz)                -- LEFT
JOBB(szöveg; hossz)                -- RIGHT
KÖZÉP(szöveg; honnan; hossz)      -- MID
HOSSZ(szöveg)                      -- LEN
ÖSSZEFŰZ(a; b; ...)  vagy  a&b     -- CONCAT / &
SZÖVEGÖSSZEFŰZ(elválasztó; üres_figyelmen_kívül_hagyása; tartomány) -- TEXTJOIN
SZÖVEG.KERES(mit; hol; [honnan])   -- SEARCH: kis/nagybetű nem számít
SZÖVEG.TALÁL(mit; hol; [honnan])   -- FIND: kis/nagybetű számít
CSERE(régi_szöveg; honnan; hossz; új_szöveg)        -- REPLACE (pozíció alapján)
HELYETTE(szöveg; régi_rész; új_rész; [hányadik])     -- SUBSTITUTE (tartalom alapján)
NAGYBETŰS(szöveg) / KISBETŰS(szöveg)                  -- UPPER / LOWER
TNÉV(szöveg)                                          -- PROPER: minden szó első betűje nagy
TRIM(szöveg)                                          -- felesleges szóközök levágása
SZÖVEG(szám; formátum)                                -- TEXT: számot formázott szöveggé alakít
ÉRTÉK(szöveg)                                         -- VALUE: szöveget számmá alakít
ISMÉTEL(szöveg; hányszor)                             -- REPT
```

### Minta: "vágd le az utolsó szót egy szövegből"

```excel
=BAL(A2; SZÖVEG.KERES(" "; A2; HOSSZ(A2)-5)-1)
```
Gondolatmenet: `SZÖVEG.KERES` megkeresi a pozíciót (itt egy szóköz helyét hátulról indulva), utána `BAL`/`JOBB`/`KÖZÉP` vágja ki a kívánt darabot.

### Minta: "kötőjellel elválasztott lista egy cellába"

```excel
=SZÖVEGÖSSZEFŰZ("-"; IGAZ; A2:A10)
```

---

## 6. Dátum- és időfüggvények

```excel
ÉV(dátum) / HÓNAP(dátum) / NAP(dátum)     -- YEAR / MONTH / DAY
ÓRA(idő) / PERC(idő) / MPERC(idő)         -- HOUR / MINUTE / SECOND
MA()                                       -- TODAY(): csak dátum
MOST()                                     -- NOW(): dátum + idő
DÁTUM(év; hónap; nap)                      -- DATE
IDŐ(óra; perc; mp)                         -- TIME
NAPOK(vég; kezdet)                         -- DAYS(end, start)
DÁTUM.KÖZÖTT(kezdet; vég; egység)          -- DATEDIF ("d" nap, "m" hónap, "y" év)
HÉT.NAPJA(dátum; [típus])                  -- WEEKDAY
HÉT.SZÁMA(dátum)                           -- WEEKNUM
MUNKANAP(kezdő_dátum; napok; [ünnepek])    -- WORKDAY
KIHAGY(kezdő_dátum; záró_dátum; [ünnepek]) -- NETWORKDAYS
```

### Minta: "hány munkanap telt el két dátum között"

```excel
=KIHAGY(B2; C2)
```

---

## 7. Matematikai / kerekítő függvények

```excel
KEREKÍTÉS(szám; hány_tizedes)      -- ROUND
KEREKÍTÉS.FEL(szám; hány_tizedes)  -- ROUNDUP
KEREKÍTÉS.LE(szám; hány_tizedes)   -- ROUNDDOWN
CSONK(szám; [hány_tizedes])         -- TRUNC: levágja a tizedeseket kerekítés nélkül
PLAFON(szám; szorzó)                -- CEILING: felfelé kerekít a szorzó többszörösére
PADLÓ(szám; szorzó)                 -- FLOOR: lefelé kerekít a szorzó többszörösére
ABS(szám)                           -- ABS: abszolút érték
ELŐJEL(szám)                        -- SIGN
HATVÁNY(alap; kitevő) vagy alap^kitevő -- POWER
GYÖK(szám)                          -- SQRT
MARADÉK(szám; osztó)                -- MOD
VÉLETLEN()                          -- RAND: 0 és 1 közötti véletlen szám
VÉLETLEN.KÖZÖTT(alsó; felső)        -- RANDBETWEEN
RÓMAI(szám) / ARAB(szöveg)          -- ROMAN / ARABIC
```

**Fontos:** `KEREKÍTÉS` 2. paramétere lehet negatív is (pl. `-2` a százasokra kerekítéshez).

---

## 8. Statisztikai rangsor-függvények

```excel
RANG.EGY(szám; tartomány; [sorrend])   -- RANK.EQ: 0/elhagyva = csökkenő, 1 = növekvő
NAGY(tartomány; k)                      -- LARGE: k-adik legnagyobb érték
KICSI(tartomány; k)                     -- SMALL: k-adik legkisebb érték
PERCENTILIS.INC(tartomány; k)           -- PERCENTILE.INC
```

---

## 9. Feltételes formázás (Conditional Formatting)

**Menete:** Kezdőlap fül → Feltételes formázás → válassz szabálytípust.

### Beépített szabályok
- Cellakiemelési szabályok: nagyobb mint / kisebb mint / egyenlő / szöveg tartalmazza / dátum / duplikált értékek.
- Felső/alsó szabályok: felső 10 elem, felső 10%, átlag felett/alatt.
- Adatsávok, színskálák, ikonkészletek: vizuális, arányos megjelenítés cellánként.

### Egyéni szabály képlettel — ez a leggyakoribb érettségi feladat

Menete: **Feltételes formázás → Új szabály → Képlettel határozza meg, mely cellák legyenek formázva**

```excel
=$C2<1000
```
Fontos szabályok:
- A tartományt előbb ki kell jelölni (pl. `A2:E100`), a képlet pedig a **kijelölés bal felső cellájára** vonatkozik, mintha ott állna a képlet, és onnan másolódna végig — ezért kell itt is figyelni a `$` jelekre (a fenti példában a `$C` rögzíti az oszlopot, hogy minden sorban a saját C oszlopbeli értékét nézze, de a formázás minden kijelölt oszlopra érvényes legyen).
- A képletnek **logikai értéket** (IGAZ/HAMIS) kell visszaadnia.
- Több szabály is lehet egymás után; a **Szabályok kezelése** ablakban állítható a sorrend és hogy megálljon-e az első teljesülő szabálynál.

### Minta feladat — "ha egy sorban a Mennyiség (D oszlop) 0, az egész sor legyen piros"

Kijelölés: `A2:E100`, majd a szabály képlete:
```excel
=$D2=0
```

### Minta feladat — "emeld ki azokat a cellákat, ahol a dátum a mai napnál korábbi"

```excel
=E2<MA()
```

---

## 10. Adatérvényesítés (Data Validation)

**Menete:** Adatok fül → Adatellenőrzés.

Tipikus beállítások:
- **Egész szám / Tizedes** — minimum/maximum megadásával.
- **Lista** — legördülő menü, forrás lehet közvetlen felsorolás (`Igen;Nem`) vagy tartomány (`=$H$2:$H$5`).
- **Dátum / Idő** — érvényes tartomány megadása.
- **Egyéni** — saját logikai képlet, pl. hogy egy cella értéke ne ismétlődjön:
```excel
=DARABTELI($A$2:$A$100; A2)=1
```

Hibaüzenet és bemeneti üzenet fül: mit írjon ki érvénytelen adat esetén, illetve mit mutasson kijelöléskor.

---

## 11. Rendezés és szűrés

- **Rendezés:** Adatok fül → Rendezés — több szempont szerint is (pl. előbb Kategória, majd Ár szerint, mindkettőhöz külön irány állítható).
- **Autoszűrő:** Adatok fül → Szűrő; oszloponként be lehet állítani szöveg-, szám- vagy dátumfeltételt (pl. "1000 fölötti", "az elmúlt hónapban").
- **Irányított szűrő:** külön kritériumtartomány alapján, eredmény másolható másik helyre is.

### Dinamikus tömbfüggvények (365/2021+)

```excel
SZŰRŐ(tartomány; feltétel; [ha_üres])   -- FILTER
EGYEDI(tartomány; [oszloponként]; [csak_egyszeriek]) -- UNIQUE
RENDEZÉS(tartomány; [oszlop]; [sorrend])              -- SORT
RENDEZÉS.TÖMB(tartomány; kulcs_tartomány; [sorrend])   -- SORTBY
SOROZAT(sorok; [oszlopok]; [kezdő]; [lépés])           -- SEQUENCE
```

### Minta: "listázd ki egyedi módon az előforduló Kategóriákat, ABC sorrendbe rendezve"

```excel
=RENDEZÉS(EGYEDI(B2:B100))
```

### Minta: "szűrd ki azokat a sorokat, ahol Ár > 1000"

```excel
=SZŰRŐ(A2:E100; C2:C100>1000; "nincs találat")
```

---

## 12. Kimutatás (Pivot tábla) — lépésről lépésre

1. Jelöld ki a forrás adattartományt (minden oszlopnak legyen fejléce, ne legyen üres sor/oszlop középen).
2. **Beszúrás → Kimutatás(tábla)** → új munkalapra.
3. A jobb oldali mezőlistából húzd a mezőket:
   - **Sorok** — csoportosítási szempont (pl. Kategória).
   - **Oszlopok** — második bontási szempont (pl. Év).
   - **Értékek** — az összesítendő mező (alapból Összeg számoknál, Darab szövegnél — átállítható).
   - **Szűrő** — ha csak egy részhalmazra kell rákeresni.
4. Összesítő függvény módosítása: jobb klikk az érték cellán → **Értékmező beállításai** → Összeg / Átlag / Darab / Max / Min stb.
5. **Csoportosítás dátum szerint:** jobb klikk egy dátumcellán a kimutatásban → **Csoportosítás** → Hónapok / Negyedévek / Évek.
6. **Számított mező:** Kimutatás eszközök → Mezők, elemek, halmazok → Számított mező — új mező képlettel a meglévő mezőkből.
7. **Frissítés:** ha változik a forrásadat, jobb klikk a kimutatáson → Frissítés (vagy Adatok → Összes frissítése).

---

## 13. Diagram létrehozása — lépésről lépésre

1. Jelöld ki az ábrázolandó adatokat (fejléccel együtt).
2. **Beszúrás fül → Diagramok** csoport → válaszd ki a típust:
   - Oszlop/sáv diagram — kategóriák összehasonlítására.
   - Vonaldiagram — időbeli trendhez.
   - Kördiagram — egy egész részekre bontásához (100%).
   - Pontdiagram (XY) — két számsor közti összefüggéshez.
3. **Diagramelemek (+)** gomb: tengelycímek, adatfeliratok, jelmagyarázat, rácsvonalak be/kikapcsolása.
4. **Adatok kijelölése** (jobb klikk a diagramon): itt lehet pontosítani, melyik oszlop legyen kategória-, melyik érték-tengely, sorokat hozzáadni/törölni, sorok/oszlopok felcserélése.
5. Kimutatásból készített diagram automatikusan **Kimutatásdiagram**, ami követi a kimutatás szűréseit.

---

## 14. Elnevezett tartományok (Named Ranges)

**Menete:** jelöld ki a tartományt → Névdoboz (bal felső sarok) → írd be a nevet, Enter.
Vagy: Képletek fül → Névkezelő → Új.

Előny: a képletekben a cellahivatkozás helyett a név használható, és automatikusan abszolút hivatkozásként viselkedik.

```excel
=ÖSSZEG(Bevétel)
```
ahol `Bevétel` egy elnevezett tartomány neve.

---

## 15. Lapvédelem és munkafüzet-védelem

- **Lap védelme:** Véleményezés fül → Lap védelme — jelszóval korlátozható a szerkesztés; előtte cellánként beállítható, mely cellák maradjanak "zárolatlanok" (Cella formázása → Védelem fül).
- **Munkafüzet szerkezetének védelme:** Véleményezés → Munkafüzet védelme — megakadályozza munkalapok törlését/hozzáadását.
- **Rejtett képletek:** Cella formázása → Védelem → "Rejtett" bepipálása + lapvédelem bekapcsolása → a képlet tartalma nem látszik a képletsorban.

---

## 16. Nézet és nyomtatás

- **Ablaktáblák rögzítése:** Nézet fül → Ablaktáblák rögzítése — fejléc sor/oszlop mindig látható marad görgetéskor.
- **Nyomtatási terület:** Lapelrendezés fül → Nyomtatási terület megadása.
- **Ismétlődő sorok/oszlopok nyomtatáskor:** Lapelrendezés → Nyomtatási címek → Ismétlődő sorok fent.
- **Léptékezés egy oldalra:** Lapelrendezés → Igazítás → Szélesség/Magasság: 1 oldal.

---

## 17. Hasznos billentyűparancsok

```
Ctrl + ;         -- mai dátum beszúrása
Ctrl + Shift + ; -- aktuális idő beszúrása
F2               -- cella szerkesztése
F4               -- hivatkozás rögzítésének váltása ($ körbe)
Ctrl + Shift + L -- autoszűrő be/ki
Ctrl + T         -- kijelölés táblázattá alakítása
Alt + =          -- automatikus ÖSSZEG beszúrása
Ctrl + 1         -- Cella formázása ablak
Ctrl + Page Up/Down -- váltás munkalapok között
```

---

## 18. Gyakori hibák — gyorslista ellenőrzéshez

- Elfelejtett `$` jel másoláskor rögzítendő hivatkozásnál — a leggyakoribb hibapont-forrás.
- `FKERES`-nél a pontos egyezés (`0`/`HAMIS`) paraméter elhagyása — ilyenkor Excel "legközelebbi" találatot ad, ami legtöbbször hibás eredményhez vezet.
- `ÖSSZEGHA`/`DARABTELI` feltétel szövegként megadva idézőjel nélkül (helyesen: `"Akció"`, nem `Akció`).
- Feltételes formázásnál a kijelölés bal felső sarkára vonatkozó képlet hivatkozásainak elrontása (rossz `$` használat → nem az elvárt cellák formázódnak).
- Kimutatásnál elfelejteni frissíteni (jobb klikk → Frissítés), ha változott a forrásadat.
- Dátumfüggvényeknél a cella tényleges dátumformátumának ellenőrzése — ha szövegként van tárolva a dátum, a függvények hibát adnak (`#ÉRTÉK!`).
- `KEREKÍTÉS` és a megjelenítési tizedesjegyek beállítása összekeverve — a formázás csak a megjelenítést, a `KEREKÍTÉS` a tényleges tárolt értéket változtatja meg.
- Abszolút/relatív keverése olyan képletnél, ami sorban és oszlopban is másolásra kerül (pl. szorzótábla-szerű feladatok) — ilyenkor mindig `$A1` és `A$1` vegyes hivatkozás kell, nem `$A$1`.