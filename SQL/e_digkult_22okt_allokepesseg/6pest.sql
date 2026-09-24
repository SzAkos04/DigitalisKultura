SELECT
    (SELECT SUM(aerob.letszam) FROM aerob INNER JOIN megye ON aerob.mkod = megye.kod WHERE megye.nev = "Pest")
    /
    (SELECT megye.letszam FROM megye WHERE megye.nev = "Pest")
FROM megye
WHERE megye.nev = "Pest";
