SELECT DISTINCT
	etel.nev,
    atvaltas.tomeg,
    (atvaltas.tomeg * etel.kaloria / 100) AS kaloria
FROM
	fogyasztas
INNER JOIN
	etel ON fogyasztas.etelid = etel.id
INNER JOIN
	atvaltas ON fogyasztas.etelid = atvaltas.etelid
    AND fogyasztas.mertekegyseg = atvaltas.mertekegyseg
WHERE
	atvaltas.mertekegyseg = "adag";