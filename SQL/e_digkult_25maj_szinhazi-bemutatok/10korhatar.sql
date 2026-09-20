SELECT
	eloadas.cim,
    t1.ertek AS also,
    t2.ertek AS felso
FROM
	eloadas,
    tulajdonsag AS t1,
    tulajdonsag AS t2,
    szinhaz
WHERE
	eloadas.id = t1.eloadasid
    AND t1.nev = "tol"
    AND eloadas.id = t2.eloadasid
    AND t2.nev = "ig"
    AND eloadas.szinhazid = szinhaz.id
    AND szinhaz.szekhely = "Miskolc";
