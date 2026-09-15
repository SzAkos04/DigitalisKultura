SELECT DISTINCT
	diakok.nev
FROM
	diakok
WHERE
	diakok.telepules = (
        SELECT DISTINCT
        	diakok.telepules
        FROM
        	diakok
        WHERE
        	diakok.nev = "Majer Melinda");
