SELECT
	bajnok.ev,
    versenyszam.nev
FROM bajnok
INNER JOIN
	jatekos ON bajnok.jatekos_id = jatekos.id
INNER JOIN
	versenyszam ON bajnok.vsz_id = versenyszam.id
WHERE jatekos.nev = "Harczi Zsolt";