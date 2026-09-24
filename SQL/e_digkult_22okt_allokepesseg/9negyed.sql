SELECT
	megye.nev AS Megyenév,
    (SUM(IF(allapot.nev <> "egészséges", aerob.letszam, 0)) / megye.letszam) AS Arány
FROM aerob
INNER JOIN
	megye ON aerob.mkod = megye.kod
INNER JOIN
	allapot ON aerob.allkod = allapot.kod
GROUP BY megye.kod
HAVING Arány > 0.25
ORDER BY megye.kod;
