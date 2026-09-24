SELECT SUM(IF(megye.letszam < (SELECT megye.letszam FROM megye WHERE megye.nev = "Heves"), 1, 0))
FROM megye;
