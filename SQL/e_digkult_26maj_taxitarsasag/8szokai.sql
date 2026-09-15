SELECT
	(SELECT SUM(fuvar.tav)
     FROM fuvar
     INNER JOIN
     	gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
     WHERE
     	gepkocsi.sofor = "Szokai Ada"
     	AND fuvar.tav < 6)
     /
     (SELECT SUM(fuvar.tav)
      FROM fuvar
      INNER JOIN
      	gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
      WHERE gepkocsi.sofor = "Szokai Ada") * 100 AS "% rovidebb, mint 6 km";
