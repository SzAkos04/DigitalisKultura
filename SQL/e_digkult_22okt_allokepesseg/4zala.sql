SELECT SUM(IF(aerob.nem = 1, aerob.letszam, 0))
FROM aerob
INNER JOIN
	megye ON aerob.mkod = megye.kod
INNER JOIN
	allapot ON aerob.allkod = allapot.kod
WHERE
	megye.nev = "Zala"
    AND allapot.nev = "egészséges";
