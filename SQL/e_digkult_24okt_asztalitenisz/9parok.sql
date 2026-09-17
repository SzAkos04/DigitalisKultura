SELECT DISTINCT
	jatekos.nev
FROM bajnok
INNER JOIN
	jatekos ON bajnok.jatekos_id = jatekos.id
INNER JOIN
	versenyszam ON bajnok.vsz_id = versenyszam.id
WHERE
	(bajnok.ev, versenyszam.id) IN
    	(SELECT DISTINCT
            bajnok.ev,
            versenyszam.id
        FROM
            bajnok
        INNER JOIN
            jatekos on bajnok.jatekos_id = jatekos.id
        INNER JOIN
            versenyszam ON bajnok.vsz_id = versenyszam.id
        WHERE
            versenyszam.nev = "vegyes páros"
            AND jatekos.nev = "Pergel Szandra");