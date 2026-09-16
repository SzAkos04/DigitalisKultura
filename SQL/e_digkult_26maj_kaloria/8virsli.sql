SELECT
	(SELECT DISTINCT atvaltas.tomeg
    FROM fogyasztas
    INNER JOIN
     	atvaltas ON fogyasztas.etelid = atvaltas.etelid
     	AND fogyasztas.mertekegyseg = atvaltas.mertekegyseg
    INNER JOIN
     	etel ON fogyasztas.etelid = etel.id
    WHERE fogyasztas.mertekegyseg = "adag"
    	AND etel.nev = "baromfivirsli")
    /
    (SELECT DISTINCT atvaltas.tomeg
    FROM fogyasztas
    INNER JOIN
     	atvaltas ON fogyasztas.etelid = atvaltas.etelid
     	AND fogyasztas.mertekegyseg = atvaltas.mertekegyseg
    INNER JOIN
     	etel ON fogyasztas.etelid = etel.id
    WHERE fogyasztas.mertekegyseg = "darab"
    	AND etel.nev = "baromfivirsli");