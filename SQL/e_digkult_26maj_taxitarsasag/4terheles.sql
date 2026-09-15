SELECT DISTINCT
    gepkocsi.sofor
FROM
    fuvar
INNER JOIN 
    gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
GROUP BY
    gepkocsi.sofor,
    fuvar.mikor
HAVING
    SUM(fuvar.tav) > 80;
