SELECT
	megye.nev,
	SUM(aerob.letszam) / megye.letszam AS arany
FROM aerob
INNER JOIN
	megye ON aerob.mkod = megye.kod
GROUP BY megye.kod
ORDER BY arany DESC;
