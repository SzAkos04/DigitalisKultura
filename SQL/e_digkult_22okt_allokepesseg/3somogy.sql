SELECT SUM(aerob.letszam)
FROM aerob
INNER JOIN
	megye ON aerob.mkod = megye.kod
WHERE
	megye.nev = "Somogy";
