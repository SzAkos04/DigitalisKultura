SELECT
	etel.nev,
    fogyasztas.mennyiseg,
    fogyasztas.mertekegyseg
FROM
	fogyasztas
INNER JOIN
	etel ON fogyasztas.etelid = etel.id
INNER JOIN
	etkezes ON fogyasztas.etkezesid = etkezes.id
WHERE
	etkezes.datum = "2023-12-24"
    AND etkezes.tipus = "vacsora";