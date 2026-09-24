SELECT megye.nev, SUM(aerob.letszam) AS szam
FROM aerob
INNER JOIN
	megye ON aerob.mkod = megye.kod
INNER JOIN
	allapot ON aerob.allkod = allapot.kod
WHERE
	aerob.nem = 0
    AND allapot.nev = "egészséges"
GROUP BY
	megye.kod
ORDER BY szam DESC;
