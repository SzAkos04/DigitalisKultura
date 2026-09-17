SELECT MIN(bajnok.ev)
FROM bajnok
INNER JOIN
	versenyszam ON bajnok.vsz_id = versenyszam.id
WHERE versenyszam.nev = "vegyes páros";