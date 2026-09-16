SELECT
    etkezes.datum
FROM
    etkezes
INNER JOIN
    fogyasztas ON etkezes.id = fogyasztas.etkezesid
INNER JOIN
    etel ON fogyasztas.etelid = etel.id
INNER JOIN
    atvaltas ON fogyasztas.etelid = atvaltas.etelid 
    AND fogyasztas.mertekegyseg = atvaltas.mertekegyseg
GROUP BY
    etkezes.datum
HAVING
    SUM(fogyasztas.mennyiseg * atvaltas.tomeg * etel.kaloria / 100) < 1200;