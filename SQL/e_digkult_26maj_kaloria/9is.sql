SELECT datum, tipus
FROM etel AS e1, fogyasztas AS f1, 
     etel AS e2, fogyasztas AS f2, etkezes
WHERE
	e1.nev = "paradicsom"
    AND e2.nev = "paprika"
    AND e1.id = f1.etelid
    AND e2.id = f2.etelid
    AND etkezes.id = f1.etkezesid
    AND etkezes.id = f2.etkezesid;